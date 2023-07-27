#ifndef SERVERBLOCK_HPP
#define SERVERBLOCK_HPP

#include <iostream>
#include <list>
#include <map>

#include "LocationBlock.hpp"

class ServerBlock {
  private:
    int _listen;
    std::string _root;
    std::string _index;
    std::string _serverName;
    unsigned long _clientMaxBodySize;
    std::string _cgi;
    std::list<LocationBlock *> _locationList;

  public:
    ServerBlock();
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

    std::list<LocationBlock *> getBlockList();

    void test(); // TODO test
};

#endif
