#include "../includes/LocationBlock.hpp"

LocationBlock::LocationBlock(ServerBlock &serverBlock)
    : ServerBlock(serverBlock),
      _path(),
      _autoindex("off"),
      _limitExcept("all") {}

LocationBlock::~LocationBlock() {}

void LocationBlock::setPath(std::string value) { _path = value; }

void LocationBlock::setAutoindex(std::string value) { _autoindex = value; }

void LocationBlock::setLimitExcept(std::string value) { _limitExcept = value; }

const std::string LocationBlock::getPath() const { return _path; }

const std::string LocationBlock::getAutoindex() const { return _autoindex; }

const std::string LocationBlock::getLimitExcept() const { return _limitExcept; }

void LocationBlock::setKeyVal(std::string key, std::string value) {
  typedef void (LocationBlock::*funcptr)(std::string);
  std::map<std::string, funcptr> funcmap;

  funcmap["path"] = &LocationBlock::setPath;
  funcmap["autoindex"] = &LocationBlock::setAutoindex;
  funcmap["limit_except"] = &LocationBlock::setLimitExcept;

  if (funcmap.find(key) != funcmap.end())
    (this->*(funcmap[key]))(value);
  else
    (this->ServerBlock::setKeyVal(key, value));
}

// TODO test
void LocationBlock::test() {
  std::cout << "===========LOCATION===========" << std::endl;
  std::cout << "_path: " << _path << std::endl;
  std::cout << "_index: " << getIndex() << std::endl;  // 부모 클래스 index
  std::cout << "_root: " << getRoot()
            << std::endl;  // 부모 클래스의 root(or 갱신)
  std::cout << "_autoindex: " << _autoindex << std::endl;
  std::cout << "_limitExcept: " << _limitExcept << std::endl;
  std::cout << "_clientMaxBodySize: " << getClientMaxBodySize()
            << std::endl;  // 부모 클래스의 clientMax어쩌구
  std::cout << "==============================" << std::endl;
  std::cout << std::endl;
}
