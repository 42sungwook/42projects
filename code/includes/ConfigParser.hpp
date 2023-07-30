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

enum BLOCK { ROOT, SERVER, LOCATION, EVENT };

typedef std::pair<enum BLOCK, RootBlock *> BlockPair;

typedef std::vector<ServerBlock *> SPSBList;
typedef std::map<int, SPSBList *> ServerBlockMap;

typedef std::vector<LocationBlock *> LocationList;
typedef std::map<ServerBlock *, LocationList *> LocationMap;

class ConfigParser {
 private:
  std::size_t           _pos;
  std::size_t           _start;
  std::string           _line;
  std::stack<BlockPair> _stack;
  ServerBlockMap        _serverBlockMap;
  LocationMap           _locationMap;

 private:
  void setKey(std::string &key);
  void setValue(std::string &value);
  void readConfig(const char *path);
  bool skipBracket();
  RootBlock *addBlock(BlockPair &top);

 public:
  ConfigParser(const char *path, RootBlock *root);
  ~ConfigParser();
  void parseBlocks();
};


#endif
