#include "../includes/Kqueue.hpp"

Kqueue::Kqueue() { _checkList = new std::vector<struct kevent>; }

Kqueue::~Kqueue() {}

int Kqueue::init(std::list<Server *> serverList) {
  if ((_kq = kqueue()) == -1) {
    std::cout << "kqueue() error\n"
              << std::string(strerror(errno)) << std::endl;
    return EXIT_FAILURE;
  }
  std::list<Server *>::iterator it;
  for (it = serverList.begin(); it != serverList.end(); it++) {
    changeEvents((*it)->getSocket(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0,
                 NULL);
  }
  return EXIT_SUCCESS;
}

void Kqueue::changeEvents(uintptr_t ident, int16_t filter, uint16_t flags,
                          uint32_t fflags, intptr_t data, void *udata) {
  struct kevent tmp;

  EV_SET(&tmp, ident, filter, flags, fflags, data, udata);
  _checkList->push_back(tmp);
}

int Kqueue::countEvents() {
  int cnt;
  cnt = kevent(_kq, &(*_checkList)[0], _checkList->size(), _eventList, 8, NULL);
  if (cnt == -1) {
    std::cout << "kevent() error\n" + std::string(strerror(errno)) << std::endl;
    return -1;
  }
  return cnt;
}

void Kqueue::clearCheckList() { _checkList->clear(); }

struct kevent *Kqueue::getEventList() { return _eventList; }
