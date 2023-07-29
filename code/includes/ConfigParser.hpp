#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <string.h>

#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

#include "./LocationBlock.hpp"
#include "./RootBlock.hpp"
#include "./ServerBlock.hpp"

#define ISSPACE " \t\n\r\f\v"
#define SEMICOLON ";"

typedef std::pair<enum BLOCK, RootBlock &> BlockPair;

enum BLOCK { ROOT, SERVER, LOCATION };

class Parser {
 private:
  std::size_t _pos;
  std::size_t _start;
  std::string _line;
  RootBlock *_root;
  std::vector<RootBlock *> _serverBlocks; 

  bool _error;

 private:
  void setKey(std::string &key);
  void setValue(std::string &value);
  void readConfig(std::string &path);
  void parseRootBlock();
  void parseServerBlock();
  void parseLocationBlock(ServerBlock *server);
  bool skipBracket();

  void parseBlock(std::stack<BlockPair> stack);
  std::stack<BlockPair> addBlock(std::stack<BlockPair> &stack);
  void setKeyVal(enum BLOCK type);

 public:
  Parser(std::string &path);
  ~Parser();
  RootBlock *getRootBlock();

  bool getState() const;
};

RootBlock *config(std::string path);

#endif
