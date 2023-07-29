#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

#include "./LocationBlock.hpp"
#include "./RootBlock.hpp"
#include "./ServerBlock.hpp"

#define ISSPACE " \t\n\r\f\v"
#define SEMICOLON ";"

enum BLOCK { ROOT, SERVER, LOCATION };

typedef std::pair<enum BLOCK, RootBlock &> BlockPair;
typedef std::vector<LocationBlock *> LocationList;
std::map<ServerBlock *, LocationList &> ServerMap;

class ConfigParser {
 private:
  std::size_t _pos;
  std::size_t _start;
  std::string _line;
  RootBlock *_rootBlock;
  ServerList _serverList;  //

 private:
  void setKey(std::string &key);
  void setValue(std::string &value);
  void readConfig(std::string &path);
  bool skipBracket();

  void parseBlock(std::stack<BlockPair> stack);
  std::stack<BlockPair> addBlock(BlockPair &top);
  void setKeyVal(enum BLOCK type);

 public:
  ConfigParser(std::string &path);
  ~ConfigParser();
  RootBlock *getRootBlock();
};

RootBlock *config(std::string path);

#endif
