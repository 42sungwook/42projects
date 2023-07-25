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
#include "ServerBlock.hpp"

/* class Server {
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
}; */

class Server {
 private:
  const int _port;
  int _socket;
  std::map<int, std::string> _clients;  // map for client socket:data
  std::vector<ServerBlock *> _serverBlock;

 public:
  Server(const int port);
  ~Server();

  void setServerBlockList(ServerBlock *serverBlockList);
  const int getSocket() const;
  void setClientContents(int clientSock, std::string buffer);
  void setClientContentsClear(int clientSock);
  void disconnectClient(int clientSock);
  const std::string getClientContents(int clientSock);
  std::vector<ServerBlock *> getServerBlockList();
  bool isExistClient(int clientSock);
  int init(std::list<ServerBlock *> serverBlockList);
};

#endif