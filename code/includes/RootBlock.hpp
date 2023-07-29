#ifndef ROOTBLOCK_HPP
#define ROOTBLOCK_HPP

#include <iostream>
#include <list>
#include <map>
#include <vector>

class ServerBlock;

typedef struct s_serverInfo {
  int listen;
  std::vector<ServerBlock *> samePortServerList;
} t_serverInfo;

class RootBlock {
 protected:
  std::string _user;
  std::string _include;
  int _maxConnection;
  int _workerCnt;
  std::map<std::string, std::string> _statusCodes;

 public:
  RootBlock();
  RootBlock(RootBlock &copy);
  ~RootBlock();

  void setUser(std::string value);
  void setInclude(std::string value);
  void setMaxConnection(std::string value);
  void setWorkerCnt(std::string value);
  void setKeyVal(std::string key, std::string value);

  const std::string getUser() const;
  const std::string getInclude() const;
  int getMaxConnection() const;
  int getWorkerCnt() const;
  t_serverInfo *getServerInfo(std::vector<t_serverInfo *> infoList, int listen);
  std::vector<t_serverInfo *> getServerInfoList();

  std::string getStatusCode(std::string key);

  void test();  // TODO test
};

#endif
