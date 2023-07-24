#ifndef ROOTBLOCK_HPP
#define ROOTBLOCK_HPP

#include <iostream>
#include <list>
#include <map>

#include "ServerBlock.hpp"

typedef struct s_serverInfo
{
  int _listen;
  std::list<ServerBlock *> _serverList;
} ServerInfo;

class RootBlock
{
private:
  std::string _user;
  std::string _include;
  int _maxConnection;
  int _workerCnt;
  std::list<ServerBlock *> _serverList;

public:
  RootBlock();
  ~RootBlock();

  void setUser(std::string value);
  void setInclude(std::string value);
  void setMaxConnection(std::string value);
  void setWorkerCnt(std::string value);
  void setKeyVal(std::string key, std::string value);
  void addServerBlock(ServerBlock *server);

  const std::string getUser() const;
  const std::string getInclude() const;
  const int getMaxConnection() const;
  const int getWorkerCnt() const;
  ServerInfo *getServerInfo(std::list<ServerInfo *> infoList, int listen);
  std::list<ServerInfo *> getServerInfoList();

  std::list<ServerBlock *> getBlockList();

  void test(); // TODO test
};

#endif
