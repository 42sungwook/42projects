#include "../includes/RootBlock.hpp"

RootBlock::RootBlock()
    : _user(), _include(), _maxConnection(0), _workerCnt(0) {}

RootBlock::~RootBlock() {}

void RootBlock::setUser(std::string value) { _user = value; }

void RootBlock::setInclude(std::string value) { _include = value; }

void RootBlock::setMaxConnection(std::string value) {
  _maxConnection = stoi(value);  // TODO stoi() 동작 함수 만들어야 함
}

void RootBlock::setWorkerCnt(std::string value) {
  _workerCnt = stoi(value);  // TODO stoi() 동작 함수 만들어야 함
}

void RootBlock::setKeyVal(std::string key, std::string value) {
  typedef void (RootBlock::*funcptr)(std::string);
  typedef std::map<std::string, funcptr> funcMap;
  typedef funcMap::iterator funcIter;
  funcMap map;
  funcIter iter;

  map["user"] = &RootBlock::setUser;
  map["include"] = &RootBlock::setInclude;
  map["max_connection"] = &RootBlock::setMaxConnection;
  map["worker_cnt"] = &RootBlock::setWorkerCnt;

  iter = map.find(key);
  if (iter != map.end()) (this->*(iter->second))(value);
}

void RootBlock::addServerBlock(ServerBlock *server) {
  _serverList.push_back(server);
}

const std::string RootBlock::getUser() const { return _user; }

const std::string RootBlock::getInclude() const { return _include; }

const int RootBlock::getMaxConnection() const { return _maxConnection; }

const int RootBlock::getWorkerCnt() const { return _workerCnt; }

std::list<ServerBlock *> RootBlock::getBlockList() {
  if (_serverList.empty()) throw std::runtime_error("server block is empty");
  return _serverList;
}

// TODO test
void RootBlock::test() {
  std::cout << "===========ROOT===========" << std::endl;
  std::cout << "_user: " << _user << std::endl;
  std::cout << "_include: " << _include << std::endl;
  std::cout << "_maxConnection: " << _maxConnection << std::endl;
  std::cout << "_workerCnt: " << _workerCnt << std::endl;

  std::cout << "serverList size: " << _serverList.size() << std::endl;

  std::list<ServerBlock *>::iterator it;
  std::cout << std::endl;
  for (it = _serverList.begin(); it != _serverList.end(); it++) (*it)->test();
}

t_serverInfo *RootBlock::getServerInfo(std::list<t_serverInfo *> infoList,
                                       int listen) {
  std::list<t_serverInfo *>::iterator it;

  for (it = infoList.begin(); it != infoList.end(); it++) {
    if ((*it)->listen == listen) return (*it);
  }
  return NULL;
}

std::list<t_serverInfo *> RootBlock::getServerInfoList() {
  std::list<t_serverInfo *> infoList;

  std::list<ServerBlock *>::iterator it;
  std::cout << std::endl;
  for (it = _serverList.begin(); it != _serverList.end(); it++) {
    t_serverInfo *find = getServerInfo(infoList, (*it)->getListen());
    if (find != NULL)
      find->serverList.push_back((*it));
    else {
      t_serverInfo *info = new t_serverInfo;

      info->listen = (*it)->getListen();
      info->serverList.push_back(*it);
      infoList.push_back(info);
    }
  }
  return infoList;
}
