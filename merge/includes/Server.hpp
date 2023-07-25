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

class Server {
 private:
  int _socket;
  t_serverInfo *_serverBlockInfo;
  std::map<int, std::string> _clients;

 public:
  Server(t_serverInfo *_serverBlockInfo);
  ~Server();

  const int getSocket() const;
  void setClientContents(int clientSock, std::string buffer);
  void setClientContentsClear(int clientSock);
  void disconnectClient(int clientSock);
  const std::string getClientContents(int clientSock);
  std::list<ServerBlock *> getServerBlockList();
  bool isExistClient(int clientSock);
  int init();
};

#endif