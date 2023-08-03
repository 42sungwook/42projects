#ifndef SERVEROPERATOR_HPP
#define SERVEROPERATOR_HPP
#include <list>

#include "Kqueue.hpp"
#include "Request.hpp"
#include "Server.hpp"

class ServerOperator {
 private:
  ServerMap &_serverMap;
  LocationMap &_locationMap;
  std::map<int, Request> _clients;
  std::map<int, int>
      _clientToServer;  // key: client socket, value: serversocket

  void disconnectClient(int clientSock);
  bool isExistClient(int clientSock);
  ServerBlock *getLocationBlock(Request &req, ServerBlock *sb);

  void handleEventError(struct kevent *event);
  void handleReadEvent(struct kevent *event, Kqueue kq);
  void handleWriteEvent(struct kevent *event, Kqueue kq);

 public:
  ServerOperator(ServerMap &serverMap, LocationMap &locationMap);
  ~ServerOperator();

  void run();
};

#endif
