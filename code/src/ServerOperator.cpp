#include "../includes/ServerOperator.hpp"

ServerOperator::ServerOperator(std::vector<Server *> serverList)
    : _shutDown(false), _serverList(serverList) {}

int ServerOperator::run()
{
  /* init kqueue & add event for server socket*/
  Kqueue kq;
  if (kq.init(_serverList) == EXIT_FAILURE)
    return EXIT_FAILURE;

  struct kevent *currEvent;
  int eventNb;
  while (1)
  {
    /*  apply changes and return new events(pending events) */
    eventNb = kq.countEvents();
    kq.clearCheckList(); // clear change_list for new changes
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
      if (_shutDown == true)
        return EXIT_FAILURE;
    }
  }
}

void ServerOperator::handleEventError(struct kevent *event, Kqueue kq)
{
  std::vector<Server *>::iterator it;
  (void)kq;
  for (it = _serverList.begin(); it != _serverList.end(); it++)
  {
    if (event->ident == (unsigned int)(*it)->getSocket())
    {
      std::cerr << "server socket error" << std::endl;
      _shutDown = true;
      return;
    }
  }
  std::cerr << "client socket error" << std::endl;
  disconnectClient(event->ident);
}

bool ServerOperator::findSocketBy(int ident)
{
  std::vector<Server *>::iterator it;

  for (it = _serverList.begin(); it != _serverList.end(); it++)
  {
    if ((*it)->getSocket() == ident)
      return true;
  }
  return false;
}

void ServerOperator::handleReadEvent(struct kevent *event, Kqueue kq)
{
  if (findSocketBy(event->ident))
  {
    std::cout << "ident: " << event->ident << std::endl;
    int clientSocket;

    if ((clientSocket = accept(event->ident, NULL, NULL)) == -1)
    {
      std::cerr << "accept() error\n";
      _shutDown = true;
      return;
    }
    std::cout << "accept new client: " << clientSocket << std::endl;
    fcntl(clientSocket, F_SETFL, O_NONBLOCK);

    /* add event for client socket - add read && write event */
    kq.changeEvents(clientSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    kq.changeEvents(clientSocket, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
    setClientContents(clientSocket, "");
  }
  else if (isExistClient(event->ident))
  {
    /* read data from client */
    char buf[1024];
    std::cout << "5" << std::endl;
    int n = read(event->ident, buf, sizeof(buf));
    std::cout << "6" << std::endl;
    if (n <= 0)
    {
      if (n < 0)
        std::cerr << "client read error!" << std::endl;
      disconnectClient(event->ident);
    }
    else
    {
      buf[n] = '\0';
      setClientContents(event->ident, buf);
      std::cout << "received data from " << event->ident << ": "
                << getClientContents(event->ident) << std::endl;
    }
  }
}

void ServerOperator::handleWriteEvent(struct kevent *event, Kqueue kq)
{
  /* send data to client */
  std::vector<Server *>::iterator it;
  (void)kq;
  for (it = _serverList.begin(); it != _serverList.end(); it++)
  {
    if (isExistClient(event->ident))
    {
      if (getClientContents(event->ident) != "")
      {
        Request req;
        Response res("test");
        LocationBlock *loc;

        req.parsing(getClientContents(event->ident));
        // loc = getLocationBlockBy(req.getHost(), req.getPort(), req.getUri());
        (void)loc;
        if (req.getStatus() > 0)
          std::cout << "fill error\n";
        // res.fillError(req.getStatus());
        else if (req.getProcess() == CGI)
        {
          if (req.getMethod() == GET)
            std::cout << "CGI GET" << std::endl;
          else if (req.getMethod() == POST)
            std::cout << "CGI POST" << std::endl;
        }
        else if (req.getProcess() == NORMAL)
        {
          if (req.getMethod() == GET)
            std::cout << getClientContents(event->ident) << std::endl;
          else if (req.getMethod() == POST)
            std::cout << "NORMAL POST" << std::endl;
          else if (req.getMethod() == DELETE)
            std::cout << "NORMAL DELETE" << std::endl;
        }
        std::cout << getClientContents(event->ident) << std::endl;
        // write method 작성 전까지 살려두기
        if (write(event->ident, getClientContents(event->ident).c_str(),
                  getClientContents(event->ident).size()) == -1)
        {
          std::cerr << "client write error!" << std::endl;
          disconnectClient(event->ident);
        }
        else
          setClientContentsClear(event->ident);
      }
    }
  }
}

// std::vector<ServerBlock *> ServerOperator::getServerBlockListBy(int port)
//{
//   std::vector<Server *>::iterator it;
//   for (it = _serverList.begin(); it != _serverList.end(); it++)
//   {
//     if ((*it)->getListen() == port)
//       return (*it)->getServerBlockList();
//   }
//   throw std::runtime_error("location block is empty");
// }

// ServerBlock *ServerOperator::getServerBlockBy(std::string host, int port)
// {
//   std::vector<ServerBlock *> serverBlockList;
//   std::vector<ServerBlock *>::iterator it;

//   serverBlockList = getServerBlockListBy(port);
//   for (it = serverBlockList.begin(); it != serverBlockList.end(); it++)
//   {
//     if ((*it)->getServerName() == host)
//       return (*it);
//   }
//   return (*serverBlockList.begin());
// }

// LocationBlock *ServerOperator::getLocationBlockBy(std::string host, int port,
//                                                   std::string uri) {
//   std::vector<LocationBlock *> locationBlockList;
//   std::vector<LocationBlock *>::iterator it;

//  // 임시로 설정
//  port = 8080;
//  uri = "/";

//  locationBlockList = getServerBlockBy(host, port)->getBlockList();
//  for (it = locationBlockList.begin(); it != locationBlockList.end(); it++) {
//    if ((*it)->getPath() == uri) return (*it);
//  }
//  return (*locationBlockList.begin());
//}

const std::string ServerOperator::getClientContents(int clientSock)
{
  return _clients[clientSock];
}

bool ServerOperator::isExistClient(int clientSock)
{
  if (_clients.find(clientSock) == _clients.end())
    return false;
  return true;
}

void ServerOperator::setClientContentsClear(int clientSock)
{
  _clients[clientSock].clear();
}

void ServerOperator::setClientContents(int clientSock, std::string buffer)
{
  _clients[clientSock] += buffer;
}

void ServerOperator::disconnectClient(int clientSock)
{
  std::cout << "client disconnected: " << clientSock << std::endl;
  close(clientSock);
  _clients.erase(clientSock);
}