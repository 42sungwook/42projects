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
#include <list>
#include <map>
#include <sstream>
#include <vector>

#include "Kqueue.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "RootBlock.hpp"
#include "ServerBlock.hpp"

class Server
{
private:
  int _socket;
  t_serverInfo *_serverBlockInfo;

public:
  Server(t_serverInfo *_serverBlockInfo);
  ~Server();

  int getSocket() const;
  std::list<ServerBlock *> getServerBlockList();
  int getListen();
  int init();
};

#endif