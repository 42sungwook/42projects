#ifndef SERVERBLOCK_HPP
#define SERVERBLOCK_HPP

#include <iostream>
#include <list>
#include <map>
#include <vector>

#include "RootBlock.hpp"

class ServerBlock : public RootBlock {
 protected:
  int _listenPort;
  std::string _listenHost;
  std::string _root;
  std::string _index;
  std::string _serverName;
  std::string _clientMaxBodySize;
  std::string _autoindex;

 public:
  ServerBlock(RootBlock &rootBlock);
  ServerBlock(ServerBlock &copy);
  ~ServerBlock();

  void setListen(std::string value);
  void setRoot(std::string value);
  void setIndex(std::string value);
  void setServerName(std::string value);
  void setClientMaxBodySize(std::string value);
  void setAutoindex(std::string value);
  virtual void setKeyVal(std::string key, std::string value);

  int getListenPort() const;
  const std::string getListenHost() const;
  const std::string getRoot() const;
  const std::string getIndex() const;
  const std::string getServerName() const;
  const std::string getClientMaxBodySize() const;
  const std::string getAutoindex() const;
};

#endif
