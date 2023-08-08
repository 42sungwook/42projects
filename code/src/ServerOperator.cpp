#include "../includes/ServerOperator.hpp"

ServerOperator::ServerOperator(ServerMap &serverMap, LocationMap &locationMap)
    : _serverMap(serverMap), _locationMap(locationMap) {}

ServerOperator::~ServerOperator() {}

void ServerOperator::run() {
  /* init kqueue & add event for server socket*/
  Kqueue kq;
  if (kq.init(_serverMap) == EXIT_FAILURE) exit(EXIT_FAILURE);

  struct kevent *currEvent;
  int eventNb;
  while (1) {
    eventNb = kq.countEvents();

    kq.clearCheckList();  // clear change_list for new changes
    for (int i = 0; i < eventNb; ++i) {
      currEvent = &(kq.getEventList())[i];
      if (currEvent->flags & EV_ERROR) {
        handleEventError(currEvent);
      } else if (currEvent->filter == EVFILT_READ) {
        handleReadEvent(currEvent, kq);
      } else if (currEvent->filter == EVFILT_WRITE) {
        handleWriteEvent(currEvent, kq);
      }
    }
  }
}

void ServerOperator::handleEventError(struct kevent *event) {
  if (_serverMap.find(event->ident) != _serverMap.end()) {
    std::cerr << "server socket error" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cerr << "client socket error" << std::endl;
  disconnectClient(event->ident);
}

void ServerOperator::handleReadEvent(struct kevent *event, Kqueue kq) {
  if (_serverMap.find(event->ident) != _serverMap.end()) {
    std::cout << "ident: " << event->ident << std::endl;
    int clientSocket;

    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    if ((clientSocket = accept(event->ident, (struct sockaddr *)&clientAddr,
                               &clientAddrLen)) == -1) {
      std::cerr << "accept() error\n";
      exit(EXIT_FAILURE);
    }
    std::cout << "accept new client: " << clientSocket << std::endl;
    char *clientIp = inet_ntoa(clientAddr.sin_addr);
    _clientToServer[clientSocket] = event->ident;
    fcntl(clientSocket, F_SETFL, O_NONBLOCK);

    /* add event for client socket - add read && write event */
    kq.changeEvents(clientSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    _clients[clientSocket].addRawContents("");
    _clients[clientSocket].addHeader("ClientIP", clientIp);
  } else if (isExistClient(event->ident)) {
    /* read data from client */
    char buf[1024];
    int n;
    n = read(event->ident, buf, sizeof(buf));
    if (n == 0) {
      disconnectClient(event->ident);
    } else if (n > 0) {
      buf[n] = '\0';
      _clients[event->ident].addRawContents(buf);
      _clients[event->ident].parsing();
      if (_clients[event->ident].isFullReq()) {
        kq.changeEvents(event->ident, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0,
                        NULL);
      }
    }
  }
}

ServerBlock *ServerOperator::findLocationBlock(struct kevent *event) {
  ServerBlock *locBlock =
      NULL;  // Location Block or Server Block (not match directory)
  if (_serverMap.find(_clientToServer[event->ident]) == _serverMap.end()) {
    std::cout << "client socket error" << std::endl;
    return NULL;
  }
  SPSBList *temp = _serverMap[_clientToServer[event->ident]]->getSPSBList();
  for (SPSBList::iterator it = temp->begin(); it != temp->end(); it++) {
    if (_clients[event->ident].getHost() == (*it)->getServerName()) {
      locBlock = getLocationBlock(_clients[event->ident], (*it));
      break;
    }
  }
  if (locBlock == NULL) {
    locBlock = getLocationBlock(_clients[event->ident], temp->front());
  }
  _clients[event->ident].addHeader("RootDir", locBlock->getRoot());
  _clients[event->ident].addHeader("AutoIndex", locBlock->getAutoindex());
  _clients[event->ident].addHeader("Index", locBlock->getIndex());
  _clients[event->ident].addHeader("Name", locBlock->getServerName());
  _clients[event->ident].addHeader("Port", ftItos(locBlock->getListenPort()));
  return locBlock;
}

void ServerOperator::handleWriteEvent(struct kevent *event, Kqueue kq) {
  /* send data to client */
  Response res;
  ServerBlock *locBlock = findLocationBlock(event);
// TODO method 확인, 그리고 타임아웃 cgi일때 제한된경로일깨

  if (locBlock == NULL) return;
  if (_clients[event->ident].getStatus() != 200) {
    res.setErrorRes(_clients[event->ident].getStatus());
  } else {
    Method *method;

    if (_clients[event->ident].getMethod() == "GET")
      method = new Get();
    else if (_clients[event->ident].getMethod() == "POST")
      method = new Post();
    else
      method = new Delete();

    method->process(_clients[event->ident], res);
    delete method;
  }

  if (res.sendResponse(event->ident) == 1) {
    std::cerr << "client write error!" << std::endl;
    disconnectClient(event->ident);
  } else {
    _clients[event->ident].clear();
    kq.changeEvents(event->ident, EVFILT_WRITE, EV_ADD | EV_DISABLE, 0, 0,
                    NULL);
  }
}

ServerBlock *ServerOperator::getLocationBlock(Request &req, ServerBlock *sb) {
  LocationList *locList = _locationMap[sb];
  std::string requestURI;

  for (LocationList::iterator it = locList->begin(); it != locList->end();
       it++) {
    requestURI = req.getHeaderByKey("BasicURI");
    if (requestURI.find((*it)->getPath()) != requestURI.npos) {
      return (*it);
    }
  }
  return sb;  // 끝까지 없으면 Server Block 제공
}

bool ServerOperator::isExistClient(int clientSock) {
  if (_clients.find(clientSock) == _clients.end()) return false;
  return true;
}

void ServerOperator::disconnectClient(int clientSock) {
  std::cout << "client disconnected: " << clientSock << std::endl;
  close(clientSock);
  _clients.erase(clientSock);
}
