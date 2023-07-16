#include "Kqueue.hpp"

Kqueue::Kqueue() : _kqFd(kqueue()), _isClosed(false) {
  if (_kqFd == -1) {
    std::cerr << "Failed to create kqueue" << std::endl;
    _isClosed = true;
    return;
  }
  std::memset(&_event, 0, sizeof(_event));
}

int Kqueue::eventRun() {
  if (kevent(_kqFd, &_event, 1, NULL, 0, NULL) == -1) {
    std::cerr << "Failed to register server socket to kqueue" << std::endl;
    _isClosed = true;
    return FAIL;
  }
  return SUCCESS;
}

const int& Kqueue::getKqFd() const { return _kqFd; }

const struct kevent& Kqueue::getEvent() const { return _event; }

const bool& Kqueue::getIsClosed() const { return _isClosed; }

const std::vector<struct kevent>& Kqueue::getChangeList() const {
  return _changeList;
}

const struct kevent* Kqueue::getEventList() const { return _eventList; }

Kqueue::~Kqueue() {
  close(_kqFd);
  _isClosed = true;
}
