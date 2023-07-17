#include "Kqueue.hpp"

Kqueue::Kqueue() {}

Kqueue::~Kqueue() {}

int Kqueue::init(int serverSocket) {
  if ((_kq = kqueue()) == -1) {
    std::cout << "kqueue() error\n"
              << std::string(strerror(errno)) << std::endl;
    return EXIT_FAILURE;
  }
  changeEvents(serverSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
  return EXIT_SUCCESS;
}

void Kqueue::changeEvents(uintptr_t ident, int16_t filter, uint16_t flags,
                          uint32_t fflags, intptr_t data, void* udata) {
  struct kevent tmp;

  EV_SET(&tmp, ident, filter, flags, fflags, data, udata);
  _checkList.push_back(tmp);
}

int Kqueue::countEvents() {
  int cnt;
  cnt = kevent(_kq, &_checkList[0], _checkList.size(), _eventList, 8, NULL);
  if (cnt == -1) {
    std::cout << "kevent() error\n" + std::string(strerror(errno)) << std::endl;
    return -1;
  }
  return cnt;
}

void Kqueue::clearCheckList() { _checkList.clear(); }

struct kevent* Kqueue::getEventList() { return _eventList; }

std::map<int, std::string>& Kqueue::getClients() { return _clients; }

void Kqueue::disconnectClient(int clientFd,
                              std::map<int, std::string>& clients) {
  std::cout << "client disconnected: " << clientFd << std::endl;
  close(clientFd);
  clients.erase(clientFd);
}