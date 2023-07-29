#include "../includes/RootBlock.hpp"

RootBlock::RootBlock() : _user(), _include(), _maxConnection(0), _workerCnt(0) {
  _statusCodes["200"] = "OK";
  _statusCodes["201"] = "Created";
  _statusCodes["202"] = "Accepted";
  _statusCodes["204"] = "No Content";
  _statusCodes["300"] = "Multiple Choice";
  _statusCodes["301"] = "Moved Permanently";
  _statusCodes["303"] = "See Other";
  _statusCodes["304"] = "Not Modified";
  _statusCodes["307"] = "Temporary Redirect";
  _statusCodes["400"] = "Bad Request";
  _statusCodes["401"] = "Unauthorized";
  _statusCodes["403"] = "Forbidden";
  _statusCodes["404"] = "Not Found";
  _statusCodes["405"] = "Method Not Allowed";
  _statusCodes["406"] = "Not Acceptable";
  _statusCodes["409"] = "Conflict";
  _statusCodes["410"] = "Gone";
  _statusCodes["412"] = "Precondition Failed";
  _statusCodes["414"] = "URI Too Long";
  _statusCodes["415"] = "Unsupported Media Type";
  _statusCodes["500"] = "Server Error";
}

RootBlock::RootBlock(RootBlock &copy)
    : _user(copy._user),
      _include(copy._include),
      _maxConnection(copy._maxConnection),
      _workerCnt(copy._workerCnt),
      _statusCodes(copy._statusCodes) {}

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

const std::string RootBlock::getUser() const { return _user; }

const std::string RootBlock::getInclude() const { return _include; }

int RootBlock::getMaxConnection() const { return _maxConnection; }

int RootBlock::getWorkerCnt() const { return _workerCnt; }

// std::vector<ServerBlock *> RootBlock::getBlockList() {
//     if (_serverList.empty())
//         throw std::runtime_error("server block is empty");
//     return _serverList;
// }

std::string RootBlock::getStatusCode(std::string key) {
  std::map<std::string, std::string>::iterator it;
  for (it = _statusCodes.begin(); it != _statusCodes.end(); it++) {
    if (it->first == key) return _statusCodes[key];
  }
  throw std::runtime_error("Invalid status code");
}

// TODO test
void RootBlock::test() {
  std::cout << "===========ROOT===========" << std::endl;
  std::cout << "_user: " << _user << std::endl;
  std::cout << "_include: " << _include << std::endl;
  std::cout << "_maxConnection: " << _maxConnection << std::endl;
  std::cout << "_workerCnt: " << _workerCnt << std::endl;

  // std::cout << "serverList size: " << _serverList.size() << std::endl;

  // std::vector<ServerBlock *>::iterator it;
  // std::cout << std::endl;
  // for (it = _serverList.begin(); it != _serverList.end(); it++)
  //     (*it)->test();
}

t_serverInfo *RootBlock::getServerInfo(std::vector<t_serverInfo *> infoList,
                                       int listen) {
  std::vector<t_serverInfo *>::iterator it;

  for (it = infoList.begin(); it != infoList.end(); it++) {
    if ((*it)->listen == listen) return (*it);
  }
  return NULL;
}

std::vector<t_serverInfo *> RootBlock::getServerInfoList() {
  std::vector<t_serverInfo *> infoList;

  std::vector<ServerBlock *>::iterator it;
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
