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
    /*  apply changes and return new events(pending events) */
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

    if ((clientSocket = accept(event->ident, NULL, NULL)) == -1) {
      std::cerr << "accept() error\n";
      exit(EXIT_FAILURE);
    }
    std::cout << "accept new client: " << clientSocket << std::endl;
    _clientToServer[clientSocket] = event->ident;
    fcntl(clientSocket, F_SETFL, O_NONBLOCK);

    /* add event for client socket - add read && write event */
    kq.changeEvents(clientSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    _clients[clientSocket].addRawContents("");
  } else if (isExistClient(event->ident)) {
    /* read data from client */
    char buf[2048];
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

void ServerOperator::handleWriteEvent(struct kevent *event, Kqueue kq) {
  /* send data to client */
  Response res("test");

  ServerBlock *locBlock =
      NULL;  // Location Block or Server Block (not match directory)
  if (_serverMap.find(_clientToServer[event->ident]) == _serverMap.end()) {
    std::cout << "client socket error" << std::endl;
    return;
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
  // autoIndex on off 여부 req에 저장

  if (_clients[event->ident].getStatus() > 0) {
    res.setErrorRes(_clients[event->ident].getStatus());
  } else if (_clients[event->ident].getMethod() == "GET")
    std::cout << "GET" << std::endl;
  else if (_clients[event->ident].getMethod() == "POST")
    std::cout << "POST" << std::endl;
  else if (_clients[event->ident].getMethod() == "DELETE")
    std::cout << "DELETE" << std::endl;
  // std::cout << getClientContents(event->ident) << std::endl;
  //  write method 작성 전까지 살려두기
  std::cout << _clients[event->ident].getRawContents() << std::endl;
  if (write(event->ident, _clients[event->ident].getRawContents().c_str(),
            _clients[event->ident].getRawContents().size()) == -1) {
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
  std::string dir;

  for (LocationList::iterator it = locList->begin(); it != locList->end();
       it++) {
    dir = req.getUri();  // uri를 쪼개서 처리를 거친 디렉토리 경로를 찾아서 넣기
    if (dir == (*it)->getPath()) {
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
