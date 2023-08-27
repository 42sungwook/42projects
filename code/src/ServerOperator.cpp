#include "../includes/ServerOperator.hpp"

ServerOperator::ServerOperator(ServerMap &serverMap, LocationMap &locationMap)
    : _serverMap(serverMap), _locationMap(locationMap) {}

ServerOperator::~ServerOperator() {}

void ServerOperator::run()
{
  /* init kqueue & add event for server socket*/
  Kqueue kq;
  if (kq.init(_serverMap) == EXIT_FAILURE)
    exit(EXIT_FAILURE);

  struct kevent *currEvent;
  int eventNb;
  while (1)
  {
    eventNb = kq.countEvents();

    kq.clearCheckList(); // clear change_list for new changes

    for (int i = 0; i < eventNb; ++i)
    {
      currEvent = &(kq.getEventList())[i];
      if (currEvent->flags & EV_ERROR)
      {
        handleEventError(currEvent);
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

void ServerOperator::handleEventError(struct kevent *event)
{
  if (_serverMap.find(event->ident) != _serverMap.end())
  {
    std::cerr << "server socket error" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cerr << "client socket error" << std::endl;
  disconnectClient(event->ident);
}

void ServerOperator::handleRequestTimeOut(int clientSock, Kqueue &kq)
{
  kq.changeEvents(clientSock, EVFILT_TIMER, EV_DELETE, 0, 0, NULL);
  Response res;
  res.setErrorRes(408);
  res.sendResponse(clientSock);
  disconnectClient(clientSock);
}

// TODO TCP 연결 관리
// void ServerOperator::setKeepAlive(int &fd, Server *server) {
//   int optVal = 1;

//   if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &optVal, sizeof(optVal)) ==
//   -1) {
//     std::cerr << "Setsockopt SO_KEEPALIVE failed: " << strerror(errno)
//               << std::endl;
//     close(fd);
//   } else {
//     int keepAliveTime = server->getkeepAliveTime();
//     keepAliveTime = 20;
//     int interval = 11;
//     int max_probes = 3;

//     if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPALIVE, &keepAliveTime,
//                    sizeof(keepAliveTime)) == -1 ||
//         setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(int)) <
//             0 ||
//         setsockopt(fd, IPPROTO_TCP, TCP_KEEPCNT, &max_probes, sizeof(int)) <
//             0) {
//       std::cerr << "Setsockopt TCP_KEEPALIVE failed: " << strerror(errno)
//                 << std::endl;
//       close(fd);
//     }
//   }
// }

void ServerOperator::handleReadEvent(struct kevent *event, Kqueue &kq)
{
  if (_serverMap.find(event->ident) != _serverMap.end())
  {
    int clientSocket;

    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    if ((clientSocket = accept(event->ident, (struct sockaddr *)&clientAddr,
                               &clientAddrLen)) == -1)
    {
      std::cerr << "accept() error\n";
      exit(EXIT_FAILURE);
    }
    std::cout << "accept new client: " << clientSocket << std::endl;
    char *clientIp = inet_ntoa(clientAddr.sin_addr);
    _clientToServer[clientSocket] = event->ident;
    fcntl(clientSocket, F_SETFL, O_NONBLOCK);
    // setKeepAlive(clientSocket, _serverMap[event->ident]);

    /* add event for client socket - add read && write event */
    kq.changeEvents(
        clientSocket, EVFILT_TIMER, EV_ADD | EV_ENABLE, 0,
        _serverMap[event->ident]->getSPSBList()->front()->getKeepAliveTime() *
            1000,
        NULL);
    kq.changeEvents(clientSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    _clients[clientSocket].addRawContents("");
    _clients[clientSocket].addHeader("ClientIP", clientIp);
  }
  else if (isExistClient(event->ident))
  {
    Request &req = _clients[event->ident];
    /* read data from client */
    char buf[8092];
    int n;

    while (true)
    {
      n = read(event->ident, buf, sizeof(buf) - 1);
      if (n == 0)
      {
        disconnectClient(event->ident);
        return;
      }
      else if (n == -1)
      {
        continue;
      }
      else
      {
        buf[n] = '\0';
        req.addRawContents(buf);
        memset(buf, 0, sizeof(buf));
        if (n < (int)sizeof(buf) - 1 ||
            recv(event->ident, buf, sizeof(buf) - 1, MSG_PEEK) == -1)
        {
          req.parsing(_serverMap[_clientToServer[event->ident]]->getSPSBList(),
                      _locationMap);
        }
        if (req.isFullReq() && n != (int)sizeof(buf) - 1)
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
  }
}

void ServerOperator::handleWriteEvent(struct kevent *event, Kqueue &kq)
{
  /* send data to client */
  Response res;
  Request &req = _clients[event->ident];
  ServerBlock *locBlock = req.getLocBlock();
  // TODO method 확인, 그리고 타임아웃 cgi일때 제한된경로일깨

  if (req.getStatus() != 200)
  {
    res.setErrorRes(req.getStatus());
  }
  else
  {
    Method *method;

    if (req.getMethod() == "GET" && (locBlock->getLimitExcept() == "GET" ||
                                     locBlock->getLimitExcept() == ""))
      method = new Get();
    else if ((req.getMethod() == "POST" || req.getMethod() == "PUT") &&
             (locBlock->getLimitExcept() == "POST" ||
              locBlock->getLimitExcept() == ""))
    {
      method = new Post();
    }
    else if (req.getMethod() == "DELETE" &&
             (locBlock->getLimitExcept() == "DELETE" ||
              locBlock->getLimitExcept() == ""))
      method = new Delete();
    else
    {
      method = new Method();
    }
    method->process(req, res);
    delete method;
  }

  if (res.sendResponse(event->ident) == EXIT_FAILURE)
  {
    std::cerr << "client write error!" << std::endl;
    disconnectClient(event->ident); // 몇번에러 때리지?
  }
  else if (req.getStatus() == 413)
  {
    disconnectClient(event->ident);
  }
  else
  {
    kq.changeEvents(event->ident, EVFILT_TIMER, EV_ENABLE, 0,
                    req.getLocBlock()->getKeepAliveTime() * 1000, NULL);
    req.clear();
    kq.changeEvents(event->ident, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
    kq.changeEvents(event->ident, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
  }
}

bool ServerOperator::isExistClient(int clientSock)
{
  if (_clients.find(clientSock) == _clients.end())
    return false;
  return true;
}

void ServerOperator::disconnectClient(int clientSock)
{
  std::cout << "client disconnected: " << clientSock << std::endl;
  close(clientSock);
  _clients.erase(clientSock);
  _clientToServer.erase(clientSock);
}
