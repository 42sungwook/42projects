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
#include <map>
#include <vector>

class Kqueue {
 private:
  int _kq;                                // Kqueue FD
  std::map<int, std::string> _clients;    // map for client socket:data
  std::vector<struct kevent> _checkList;  // kevent vector for changelist
  struct kevent _eventList[8];  // kevent array for saving event infomation

 public:
  Kqueue();
  ~Kqueue();

  int init(int serverSocket);
  void changeEvents(uintptr_t ident, int16_t filter, uint16_t flags,
                    uint32_t fflags, intptr_t data, void* udata);
  int countEvents();
  void clearCheckList();

  struct kevent* getEventList();
  std::map<int, std::string>& getClients();
  void disconnectClient(int clientFd, std::map<int, std::string>& clients);
};

#endif