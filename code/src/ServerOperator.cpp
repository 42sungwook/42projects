#include "../includes/ServerOperator.hpp"

ServerOperator::ServerOperator(ServerMap &serverMap, LocationMap &locationMap)
    : _serverMap(serverMap), _locationMap(locationMap) {}

ServerOperator::~ServerOperator() {}

void ServerOperator::run()
{
  Kqueue kq;
  if (kq.init(_serverMap) == EXIT_FAILURE)
    exit(EXIT_FAILURE);

  struct kevent *currEvent;
  int eventNb;
  while (1)
  {
    eventNb = kq.countEvents();
    kq.clearCheckList();

    for (int i = 0; i < eventNb; ++i)
    {
      currEvent = &(kq.getEventList())[i];
      if (currEvent->flags & EV_ERROR)
      {
        handleEventError(currEvent, kq);
      }
      else if (currEvent->filter == EVFILT_READ)
      {
        handleReadEvent(currEvent, kq);
      }
      else if (currEvent->filter == EVFILT_WRITE)
      {
        handleWriteEvent(currEvent, kq);
      }
      else if (currEvent->filter == EVFILT_TIMER)
      {
        handleRequestTimeOut(currEvent->ident, kq);
      }
    }
  }
}

void ServerOperator::handleEventError(struct kevent *event, Kqueue &kq)
{
  if (_serverMap.find(event->ident) != _serverMap.end())
  {
    std::cerr << "server socket error : " << event->ident << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cerr << "client socket error : " << event->ident << std::endl;
  disconnectClient(event->ident, kq);
}

void ServerOperator::handleRequestTimeOut(int clientSock, Kqueue &kq)
{
  kq.changeEvents(clientSock, EVFILT_TIMER, EV_DELETE, 0, 0, NULL);
  Response res;
  res.setErrorRes(408);
  res.sendResponse(clientSock);
  disconnectClient(clientSock, kq);
}

void ServerOperator::handleReadEvent(struct kevent *event, Kqueue &kq)
{
  if (kq.getFdGroup(event->ident) == FD_SERVER)
  {
    int clientSocket;

    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    if ((clientSocket = accept(event->ident, (struct sockaddr *)&clientAddr,
                               &clientAddrLen)) == -1) {
      std::cerr << "accept() error\n";
      exit(EXIT_FAILURE);
    }
    std::cout << "accept new client: " << clientSocket << std::endl;
    kq.setFdGroup(clientSocket, FD_CLIENT);
    std::string clientIp = ftInetNtoa(clientAddr.sin_addr);
    _clientToServer[clientSocket] = event->ident;

    fcntl(clientSocket, F_SETFL, O_NONBLOCK, FD_CLOEXEC);

    kq.changeEvents(
        clientSocket, EVFILT_TIMER, EV_ADD | EV_ENABLE, 0,
        _serverMap[event->ident]->getSPSBList()->front()->getKeepAliveTime() *
            1000,
        NULL);
    kq.changeEvents(clientSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    _clients[clientSocket] = new Request();
    _clients[clientSocket]->addHeader("ClientIP", clientIp);
  }
  else if (kq.getFdGroup(event->ident) == FD_CLIENT)
  {
    Request *req = _clients[event->ident];
    static char buf[8092];
    int n;

    n = read(event->ident, buf, sizeof(buf) - 1);
    if (n == 0) {
      disconnectClient(event->ident, kq);
      return;
    }
    else if (n == -1) {
      return;
    }
    else {

      req->addRawContents(buf, n);

      if (n < (int)sizeof(buf) - 1 ||
          recv(event->ident, buf, sizeof(int), MSG_PEEK) == -1)
      {
        req->parsing(_serverMap[_clientToServer[event->ident]]->getSPSBList(),
                    _locationMap);
      }

      if (req->isFullReq())
      {
        kq.changeEvents(event->ident, EVFILT_TIMER, EV_ENABLE, 0,
                        _serverMap[_clientToServer[event->ident]]
                                ->getSPSBList()
                                ->front()
                                ->getKeepAliveTime() *
                            1000,
                        NULL);
        kq.changeEvents(event->ident, EVFILT_READ, EV_DELETE, 0, 0, NULL);
        kq.changeEvents(event->ident, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0,
                        NULL);
        return;
      }
    }
  }
  else if (kq.getFdGroup(event->ident) == FD_CGI)
  {
    std::vector<int> udata = *static_cast<std::vector<int> *>(event->udata);
    int clientFd = udata[0];
    pid_t pid = udata[1];
    Request *req = _clients[clientFd];
    static char buf[8092];
    int n;

    n = read(event->ident, buf, sizeof(buf) - 1);
    if (n == -1) {
	  return;
	}
    else {
      req->addRawContents(buf, n);
      if (waitpid(pid, NULL, WNOHANG) == pid && n == 0) {
        kq.eraseFdGroup(event->ident, FD_CGI);
        close(event->ident);
        Response res;
        res.convertCGI(req->getRawContents());
        if (res.sendResponse(clientFd) == EXIT_FAILURE)
        {
          std::cerr << "client write error!" << std::endl;
          disconnectClient(clientFd, kq);
        }
        else
        {
          kq.changeEvents(clientFd, EVFILT_TIMER, EV_ENABLE, 0,
                          req->getLocBlock()->getKeepAliveTime() * 1000, NULL);
          req->clear();
          kq.changeEvents(clientFd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
        }
      }
    }
  }
}

void ServerOperator::handleWriteEvent(struct kevent *event, Kqueue &kq)
{
  if (kq.getFdGroup(event->ident) == FD_CGI) {
    std::vector<int> &udata = *static_cast<std::vector<int> *>(event->udata);
    int clientFd = udata[0];
    Request *req = _clients[clientFd];

    size_t bodySize = req->getBody().size();
    ssize_t bytesWritten = 0;
    int &totalBytesWritten = udata[4];
    size_t chunk = 16384;

    if (totalBytesWritten + chunk > bodySize)
      chunk = bodySize - totalBytesWritten;
     bytesWritten = write(event->ident, req->getBody().substr(totalBytesWritten, chunk).c_str(), chunk);
    if (bytesWritten == -1)
    {
      // close(event->ident);
      std::cerr << "임시 에러" << std::endl;
      return ;
    }
    totalBytesWritten += bytesWritten;

    if (totalBytesWritten == static_cast<int>(req->getBody().size())) {
      kq.eraseFdGroup(event->ident, FD_CGI);
      close(event->ident);
    }
    return ;
  }
  else if (kq.getFdGroup(event->ident) == FD_CLIENT)
  {
  Response res;
  Request *req = _clients[event->ident];
  ServerBlock *locBlock = req->getLocBlock();
  
  if (req->getStatus() != 200)
  {
    res.setErrorRes(req->getStatus());
  }
  else
  {
    Method *method;
    const std::string &limit = locBlock->getLimitExcept();

    if ((req->getMethod() == "GET" || req->getMethod() == "HEAD") && (limit == "GET" || limit == ""))
      method = new Get();
    else if ((req->getMethod() == "POST" || req->getMethod() == "PUT") &&
            (limit == "POST" || limit == ""))
    {
      method = new Post(kq, event->ident);
    }
    else if (req->getMethod() == "DELETE" &&
            (limit == "DELETE" ||
              limit == ""))
      method = new Delete();
    else
    {
      method = new Method();
    }
    method->process(*req, res);
    delete method;
  }

  if (res.isInHeader("Content-Length") == false) {
	kq.changeEvents(event->ident, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
    return ;
  }

  if (res.sendResponse(event->ident) == EXIT_FAILURE)
  {
    std::cerr << "client write error!" << std::endl;
    disconnectClient(event->ident, kq);
  }
  else if (req->getStatus() == 413)
  {
    disconnectClient(event->ident, kq);
  }
  else
  {
    kq.changeEvents(event->ident, EVFILT_TIMER, EV_ENABLE, 0,
                    req->getLocBlock()->getKeepAliveTime() * 1000, NULL);
    req->clear();
    kq.changeEvents(event->ident, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
    kq.changeEvents(event->ident, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
  	}
  }
}

bool ServerOperator::isExistClient(int clientSock)
{
  if (_clients.find(clientSock) == _clients.end())
    return false;
  return true;
}

void ServerOperator::disconnectClient(int clientSock, Kqueue &kq)
{
  std::cout << "client disconnected: " << clientSock << std::endl;
  kq.eraseFdGroup(clientSock, FD_CLIENT);
  close(clientSock);
  delete _clients[clientSock];
  _clients.erase(clientSock);
  _clientToServer.erase(clientSock);
}
