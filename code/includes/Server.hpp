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

#include "RootBlock.hpp"
#include "ServerBlock.hpp"
#include "ConfigParser.hpp"
#include "Kqueue.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "ConfigParser.hpp"
class Server
{
private:
  int         _socket;
  int         _listenPort;
  SPSBList    &_sbList;

public:
  Server(const int port, SPSBList &sbList);
  ~Server();

  int init();
  int getSocket() const;
  int getListenPort() const;
  SPSBList &getSPSBList() const;
};

#endif