#ifndef KQUEUE_HPP
#define KQUEUE_HPP

#include <sys/event.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#define SUCCESS 0
#define FAIL 1

class Kqueue {
 private:
  int _kqFd;
  struct kevent _event;
  std::vector<struct kevent> _changeList;
  struct kevent _eventList[8];
  bool _isClosed;

  int eventRun();
  const int& getKqFd() const;
  const struct kevent& getEvent() const;
  const bool& getIsClosed() const;
  const std::vector<struct kevent>& getChangeList() const;
  const struct kevent* getEventList() const;

 public:
  Kqueue();
  ~Kqueue();
};

#endif