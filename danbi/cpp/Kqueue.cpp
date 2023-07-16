#include "Kqueue.hpp"

Kqueue::Kqueue() : _kqFd(kqueue()), _isClosed(false) {
  if (_kqFd == -1) {
    std::cerr << "Failed to create kqueue" << std::endl;
    _isClosed = true;
    return;
  }
  std::memset(&_changeList[0], 0, _changeList.size());
}

int Kqueue::eventRun() {
  if (kevent(_kqFd, &_changeList[0], _changeList.size(), _eventList, 8, NULL) ==
      -1) {
    std::cerr << "Failed to register server socket to kqueue" << std::endl;
    _isClosed = true;
    return FAIL;
  }
  return SUCCESS;
}

const int& Kqueue::getKqFd() const { return _kqFd; }

const struct kevent& Kqueue::getEvent() const { return _changeList[0]; }

const bool& Kqueue::getIsClosed() const { return _isClosed; }

void Kqueue::setEvent(int socket, uintptr_t ident, int16_t filter,
                      uint16_t flags, uint32_t fflags, intptr_t data,
                      void* udata) {
  struct kevent tmp;

  EV_SET(&tmp, ident, filter, flags, fflags, data, udata);
  _changeList.push_back(tmp);
}

Kqueue::~Kqueue() {
  close(_kqFd);
  _isClosed = true;
}
