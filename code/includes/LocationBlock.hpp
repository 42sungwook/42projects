#ifndef LOCATIONBLOCK_HPP
#define LOCATIONBLOCK_HPP

#include <iostream>
#include <map>

#include "ServerBlock.hpp"

class LocationBlock : public ServerBlock {
 private:
  std::string _path;
  std::string _limitExcept;

 public:
  LocationBlock(ServerBlock &serverBlock);
  ~LocationBlock();

  void setPath(std::string value);
  void setLimitExcept(std::string value);
  void setKeyVal(std::string key, std::string value);

  const std::string getPath() const;
  const std::string getLimitExcept() const;

  void test();  // TODO test
};

#endif
