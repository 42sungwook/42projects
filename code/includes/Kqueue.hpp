#ifndef KQUEUE_HPP
#define KQUEUE_HPP

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <list>
#include <map>
#include <vector>

#include "Server.hpp"

class Server;
typedef std::map<int, Server *> ServerMap; // key: socket, value: server class pointer

class Kqueue {
 private:
  int _kq;                                 // Kqueue FD
  std::vector<struct kevent> *_checkList;  // kevent vector for changelist
  struct kevent _eventList[8];  // kevent array for saving event infomation

 public:
  Kqueue();
  ~Kqueue();

  int init(ServerMap serverMap);
  void changeEvents(uintptr_t ident, int16_t filter, uint16_t flags,
                    uint32_t fflags, intptr_t data, void *udata);
  int countEvents();
  void clearCheckList();
  struct kevent *getEventList();
};

#endif
