#ifndef SERVEROPERATOR_HPP
#define SERVEROPERATOR_HPP
#include <list>

#include "Kqueue.hpp"
#include "Server.hpp"

class ServerOperator {
 private:
  ServerMap &_serverMap;
  LocationMap &_locationMap;
  std::map<int, std::string> _clients;
  std::map<int, int> _clientToServer; // key: client socket, value: serversocket

  void addClientContents(int clientSock, std::string buffer);
  void setClientContentsClear(int clientSock);
  void disconnectClient(int clientSock);
  const std::string getClientContents(int clientSock);
  bool isExistClient(int clientSock);
  RootBlock *getLocationBlock(Request &req, ServerBlock *sb);

  void handleEventError(struct kevent *event);
  void handleReadEvent(struct kevent *event, Kqueue kq);
  void handleWriteEvent(struct kevent *event);

 public:
  ServerOperator(ServerMap &serverMap, LocationMap &locationMap);
  ~ServerOperator();

  void run();
};

#endif
