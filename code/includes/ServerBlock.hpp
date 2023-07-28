#ifndef SERVERBLOCK_HPP
#define SERVERBLOCK_HPP

#include <iostream>
#include <list>
#include <map>
#include <vector>

#include "RootBlock.hpp"
class LocationBlock;

class ServerBlock : public RootBlock{
  protected:
    int _listen;
    std::string _root;
    std::string _index;
    std::string _serverName;
    unsigned long _clientMaxBodySize;
    std::string _cgi;
    std::vector<LocationBlock *> _locationList;

  public:
    ServerBlock(RootBlock& rootBlock);
    ServerBlock(ServerBlock& copy);
    ~ServerBlock();

    void setListen(std::string value);
    void setRoot(std::string value);
    void setIndex(std::string value);
    void setServerName(std::string value);
    void setClientMaxBodySize(std::string value);
    void setCgi(std::string value);
    void setKeyVal(std::string key, std::string value);

    int getListen() const;
    const std::string getRoot() const;
    const std::string getIndex() const;
    const std::string getServerName() const;
    unsigned long getClientMaxBodySize() const;
    const std::string getCgi() const;

    void addLocationBlock(LocationBlock *location);

    std::vector<LocationBlock *> getBlockList();

    void test(); // TODO test
};

#endif
