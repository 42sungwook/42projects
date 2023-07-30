#include "../includes/LocationBlock.hpp"

LocationBlock::LocationBlock(ServerBlock &serverBlock)
    : ServerBlock(serverBlock), _path(), _autoindex("off"), _limitExcept() {}

LocationBlock::~LocationBlock() {}

void LocationBlock::setPath(std::string value) { _path = value; }

void LocationBlock::setAutoindex(std::string value) { _autoindex = value; }

void LocationBlock::setLimitExcept(std::string value) { _limitExcept = value; }

const std::string LocationBlock::getPath() const { return _path; }

const std::string LocationBlock::getAutoindex() const { return _autoindex; }

const std::string LocationBlock::getLimitExcept() const { return _limitExcept; }

void LocationBlock::setKeyVal(std::string key, std::string value)
{
    typedef void (LocationBlock::*funcptr)(std::string);
    typedef std::map<std::string, funcptr> funcMap;
    typedef funcMap::iterator funcIter;
    funcMap map;
    funcIter iter;

    map["path"] = &LocationBlock::setPath;
    map["index"] = &LocationBlock::setIndex;
    map["root"] = &LocationBlock::setRoot;
    map["autoindex"] = &LocationBlock::setAutoindex;
    map["limit_except"] = &LocationBlock::setLimitExcept;
    map["client_max_body_size"] = &LocationBlock::setClientMaxBodySize;
    //  std::cout << "key: <" << key << "> value: <" << value << ">" <<
    //  std::endl;
    iter = map.find(key);
    if (iter != map.end())
        (this->*(iter->second))(value);
}

// TODO test
void LocationBlock::test()
{
    std::cout << "===========LOCATION===========" << std::endl;
    std::cout << "_path: " << _path << std::endl;
    // std::cout << "_index: " << _index << std::endl;
    // std::cout << "_root: " << _root << std::endl;
    std::cout << "_autoindex: " << _autoindex << std::endl;
    std::cout << "_limitExcept: " << _limitExcept << std::endl;
    // std::cout << "_clientMaxBodySize: " << _clientMaxBodySize << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << std::endl;
}