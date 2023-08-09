#include "../includes/LocationBlock.hpp"

LocationBlock::LocationBlock(ServerBlock &serverBlock)
    : ServerBlock(serverBlock), _path(), _limitExcept("all") {}

LocationBlock::~LocationBlock() {}

void LocationBlock::setPath(std::string value) { _path = value; }

void LocationBlock::setLimitExcept(std::string value) { _limitExcept = value; }

const std::string LocationBlock::getPath() const { return _path; }

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
