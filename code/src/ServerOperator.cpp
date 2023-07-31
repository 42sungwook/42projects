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
        handleWriteEvent(currEvent);
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
    fcntl(clientSocket, F_SETFL, O_NONBLOCK);

    /* add event for client socket - add read && write event */
    kq.changeEvents(clientSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    kq.changeEvents(clientSocket, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
    _clients[clientSocket] = "";
  } else if (isExistClient(event->ident)) {
    /* read data from client */
    char buf[1024];
    int n = read(event->ident, buf, sizeof(buf));
    if (n <= 0) {
      if (n < 0) std::cerr << "client read error!" << std::endl;
      disconnectClient(event->ident);
    } else {
      buf[n] = '\0';
      addClientContents(event->ident, buf);
      std::cout << "received data from " << event->ident << ": "
                << getClientContents(event->ident) << std::endl;
    }
  }
}

void ServerOperator::handleWriteEvent(struct kevent *event) {
  /* send data to client */
  if (getClientContents(event->ident) != "") {
    Request req;
    Response res("test");

    req.parsing(getClientContents(event->ident));

    RootBlock *locBlock =
        NULL;  // Location Block or Server Block (not match directory)
    SPSBList temp = _serverMap[event->ident]->getSPSBList();
    for (SPSBList::iterator it = temp.begin(); it != temp.end(); it++) {
      if (req.getHost() == (*it)->getServerName()) {
        locBlock = getLocationBlock(req, (*it));
        break;
      }
    }
    if (locBlock == NULL) {
      locBlock = getLocationBlock(req, temp.front());
    }
    // autoIndex on off 여부 req에 저장

    if (req.getStatus() > 0) std::cout << "fill error" << std::endl;
    // res.fillError(req.getStatus());
    if (req.getMethod() == GET)
      std::cout << "GET" << std::endl;
    else if (req.getMethod() == POST)
      std::cout << "POST" << std::endl;
    else if (req.getMethod() == DELETE)
      std::cout << "DELETE" << std::endl;
    std::cout << getClientContents(event->ident) << std::endl;
    // write method 작성 전까지 살려두기
    if (write(event->ident, getClientContents(event->ident).c_str(),
              getClientContents(event->ident).size()) == -1) {
      std::cerr << "client write error!" << std::endl;
      disconnectClient(event->ident);
    } else
      setClientContentsClear(event->ident);
  }
}

const std::string ServerOperator::getClientContents(int clientSock) {
  return _clients[clientSock];
}

RootBlock *ServerOperator::getLocationBlock(Request &req, ServerBlock *sb) {
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

void ServerOperator::setClientContentsClear(int clientSock) {
  _clients[clientSock].clear();
}

void ServerOperator::addClientContents(int clientSock, std::string buffer) {
  _clients[clientSock] += buffer;
}

void ServerOperator::disconnectClient(int clientSock) {
  std::cout << "client disconnected: " << clientSock << std::endl;
  close(clientSock);
  _clients.erase(clientSock);
}
