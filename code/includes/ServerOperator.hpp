#ifndef SERVEROPERATOR_HPP
#define SERVEROPERATOR_HPP
#include <list>

#include "Kqueue.hpp"
#include "Server.hpp"

class ServerOperator
{
private:
  int _shutDown;
  std::vector<Server *> _serverList;
  std::map<int, std::string> _clients;

  void setClientContents(int clientSock, std::string buffer);
  void setClientContentsClear(int clientSock);
  void disconnectClient(int clientSock);
  const std::string getClientContents(int clientSock);
  bool isExistClient(int clientSock);
  bool findSocketBy(int ident);

  void handleEventError(struct kevent *event, Kqueue kq);
  void handleReadEvent(struct kevent *event, Kqueue kq);
  void handleWriteEvent(struct kevent *event, Kqueue kq);
  std::vector<ServerBlock *> getServerBlockListBy(int port);
  ServerBlock *getServerBlockBy(std::string host, int port);
  LocationBlock *getLocationBlockBy(std::string host, int port,
                                    std::string uri);

public:
  ServerOperator(std::vector<Server *> serverList);

  int run();
};

#endif