#ifndef SERVERBLOCK_HPP
#define SERVERBLOCK_HPP

#include <iostream>
#include <list>
#include <map>
#include <vector>

#include "RootBlock.hpp"

class ServerBlock : public RootBlock
{
protected:
  std::string _listen;
  std::string _root;
  std::string _index;
  std::string _serverName;
  unsigned long _clientMaxBodySize;
  std::string _cgi;

public:
  ServerBlock(RootBlock &rootBlock);
  ServerBlock(ServerBlock &copy);
  ~ServerBlock();

  void setListen(std::string value);
  void setRoot(std::string value);
  void setIndex(std::string value);
  void setServerName(std::string value);
  void setClientMaxBodySize(std::string value);
  void setCgi(std::string value);
  virtual void setKeyVal(std::string key, std::string value);

  const std::string getListen() const;
  const std::string getRoot() const;
  const std::string getIndex() const;
  const std::string getServerName() const;
  unsigned long getClientMaxBodySize() const;
  const std::string getCgi() const;

  void test(); // TODO test
};

#endif
