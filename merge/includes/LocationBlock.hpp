#ifndef LOCATIONBLOCK_HPP
#define LOCATIONBLOCK_HPP

#include <iostream>
#include <map>

class LocationBlock {
 private:
  std::string _path;
  std::string _index;
  std::string _root;
  std::string _autoindex;
  std::string _limitExcept;
  unsigned long _clientMaxBodySize;

 public:
  LocationBlock();
  ~LocationBlock();

  void setPath(std::string value);
  void setIndex(std::string value);
  void setRoot(std::string value);
  void setAutoindex(std::string value);
  void setLimitExcept(std::string value);
  void setClientMaxBodySize(std::string value);
  void setKeyVal(std::string key, std::string value);

  const std::string getPath() const;
  const std::string getIndex() const;
  const std::string getRoot() const;
  const std::string getAutoindex() const;
  const std::string getLimitExcept() const;
  const unsigned long getClientMaxBodySize() const;

  void test();  // TODO test
};

#endif
