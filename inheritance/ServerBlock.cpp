#include "./ServerBlock.hpp"

ServerBlock::ServerBlock(RootBlock &rootBlockRef)
    : RootBlock(rootBlockRef),
      _listen(8080),
      _root(),
      _index(),
      _serverName(),
      _clientMaxBodySize(8192) {}

ServerBlock::~ServerBlock() {}

void ServerBlock::setListen(std::string value) {
  _listen = stoi(value);  // TODO stoi() 동작 함수 만들어야 함
}

void ServerBlock::setRoot(std::string value) { _root = value; }

void ServerBlock::setIndex(std::string value) { _index = value; }
ㄴ void ServerBlock::setServerName(std::string value) { _serverName = value; }

void ServerBlock::setClientMaxBodySize(std::string value) {
  _clientMaxBodySize = stoul(value);  // TODO stoul() 동작 함수 만들어야 함
}

void ServerBlock::setCgi(std::string value) { _cgi = value; }

void ServerBlock::setKeyVal(std::string key, std::string value) {
  typedef void (ServerBlock::*funcptr)(std::string);
  typedef std::map<std::string, funcptr> funcMap;
  typedef funcMap::iterator funcIter;
  funcMap map;
  funcIter iter;

  map["listen"] = &ServerBlock::setListen;
  map["root"] = &ServerBlock::setRoot;
  map["index"] = &ServerBlock::setIndex;
  map["server_name"] = &ServerBlock::setServerName;
  map["client_max_body_size"] = &ServerBlock::setClientMaxBodySize;
  map["cgi"] = &ServerBlock::setCgi;

  iter = map.find(key);
  if (iter != map.end()) (this->*(iter->second))(value);
}

int ServerBlock::getListen() const { return _listen; }
const std::string ServerBlock::getRoot() const { return _root; }
const std::string ServerBlock::getIndex() const { return _index; }
const std::string ServerBlock::getServerName() const { return _serverName; }
unsigned long ServerBlock::getClientMaxBodySize() const {
  return _clientMaxBodySize;
}
const std::string ServerBlock::getCgi() const { return _cgi; }

void ServerBlock::addLocationBlock(LocationBlock *location) {
  _locationList.push_back(location);
}

std::list<LocationBlock *> ServerBlock::getBlockList() {
  // 비어있는 리스트를 요청할 경우 없음
  if (_locationList.empty())
    throw std::runtime_error("location block is empty");

  return _locationList;
}

// TODO test
void ServerBlock::test() {
  std::cout << "===========SERVER===========" << std::endl;
  std::cout << "_listen: " << _listen << std::endl;
  std::cout << "_root: " << _root << std::endl;
  std::cout << "_index: " << _index << std::endl;
  std::cout << "_serverName: " << _serverName << std::endl;
  std::cout << "_clientMaxBodySize: " << _clientMaxBodySize << std::endl;
  std::cout << "_cgi: " << _cgi << std::endl;

  std::cout << std::endl;
  std::list<LocationBlock *>::iterator it;
  for (it = _locationList.begin(); it != _locationList.end(); it++) {
    (*it)->test();
  }
}