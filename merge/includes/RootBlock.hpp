#ifndef ROOTBLOCK_HPP
#define ROOTBLOCK_HPP

#include <iostream>
#include <list>
#include <map>

#include "ServerBlock.hpp"

typedef struct s_serverInfo {
    int listen;
    std::list<ServerBlock *> serverList;
} t_serverInfo;

class RootBlock {
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
    int getMaxConnection() const;
    int getWorkerCnt() const;
    t_serverInfo *getServerInfo(std::list<t_serverInfo *> infoList, int listen);
    std::list<t_serverInfo *> getServerInfoList();

    std::list<ServerBlock *> getBlockList();

    void test(); // TODO test
};

#endif
