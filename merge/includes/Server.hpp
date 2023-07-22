#ifndef SERVER_HPP
#define SERVER_HPP

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "Kqueue.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "ServerBlock.hpp"

class Server {
 private:
  int _socket;
  int _shutDown;
  struct sockaddr_in _serverAddr;
  void handleEventError(struct kevent *event, Kqueue kq);
  void handleReadEvent(struct kevent *event, Kqueue kq);
  void handleWriteEvent(struct kevent *event, Kqueue kq);

 public:
  Server();
  ~Server();

  int init(ServerBlock *serverBlock);
  int run();
};

#endif