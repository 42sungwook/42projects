#ifndef KQUEUE_HPP
#define KQUEUE_HPP

#include <sys/event.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

#define SUCCESS 0
#define FAIL 1

class Kqueue {
 private:
  int _kqFd;
  std::vector<struct kevent> _changeList;
  struct kevent _eventList[8];
  bool _isClosed;
  int _eventCount;

  int eventRun();
  const int& getKqFd() const;
  const struct kevent& getEvent() const;
  const bool& getIsClosed() const;
  void setEvent(int socket, uintptr_t ident, int16_t filter, uint16_t flags,
                uint32_t fflags, intptr_t data, void* udata);

 public:
  Kqueue();
  ~Kqueue();
};

#endif