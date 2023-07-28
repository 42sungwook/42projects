#include "../includes/Parser.hpp"
#include "../includes/RootBlock.hpp"
#include <sstream>


Parser::Parser(std::string &path) :  _error(true) {
  std::stack<BlockPair> stack;

  _root = new RootBlock();
  _start = 0;
  _pos = 0;
  readConfig(path);
  if (_line.empty()) return;

  stack.push(std::make_pair(ROOT, _root));
  parseBlock(stack);
}

Parser::~Parser() {}

void Parser::readConfig(std::string &path) {
  //	std::string buf;
  //	std::ifstream filestream(path.c_str());
  //
  //	if (!filestream.is_open()) {
  //		std::cerr << "Error: " << strerror(errno) << std::endl;;
  //	}
  //	while (getline(filestream, buf)) {
  //		if (!filestream.eof())
  //			_line += '\n';
  //		else
  //			break;
  //	}
  //	std::cout <<"<" << _line<<">" << std::endl;
  std::ifstream filestream(path.c_str());
  if (!filestream.is_open()) {
    std::cerr << "error" << std::endl;
    return;
  }
  std::stringstream buffer;
  buffer << filestream.rdbuf();
  _line = buffer.str();
}

bool Parser::skipBracket() {
  _pos = _line.find_first_of("{", _pos);
  if (_pos == std::string::npos) return false;
  _start = _line.find_first_of("}", _pos);
  if (_start == std::string::npos) return false;
  ++_pos;
  return true;
}

void Parser::setKey(std::string &key) {
  key.clear();
  _start = _line.find_first_not_of(ISSPACE, _pos);
  if (_start == std::string::npos) return;
  _pos = _line.find_first_of(ISSPACE, _start);
  if (_pos == std::string::npos) return;
  key = _line.substr(_start, _pos - _start);
}

void Parser::setValue(std::string &value) {
  value.clear();
  _start = _line.find_first_not_of(ISSPACE, _pos);
  if (_start == std::string::npos) return;
  _pos = _line.find_first_of(SEMICOLON, _start);
  if (_pos == std::string::npos) return;
  value = _line.substr(_start, _pos - _start);
  ++_pos;
}

RootBlock *Parser::getRootBlock() { return _root; }

std::stack<BlockPair> Parser::addBlock(std::stack<BlockPair> &stack) {
  RootBlock *newBlock;
  BlockPair pair;
  
  if (stack.top().first == ROOT) {
    newBlock = new ServerBlock(*_root);
    _serverBlocks.push_back(newBlock);
  } else if (stack.top().first == SERVER) {
    ServerBlock *serverBlock = stack.top().second;
    newBlock = new LocationBlock(*_root, serverBlock);
    serverBlock->addLocationBlock(newBlock);
    setKey();
    newBlock->setKeyVal("path", _key);
  }
  pair = std::make_pair(stack.top().first + 1, newBlock);
}

void Parser::setKeyVal(enum BLOCK type) {
  ServerBlock *serverBlock;
  LocationBlock *locationBlock;

  if (type == ROOT)
    _root->setKeyVal(_key, _value);
  else if (type == SERVER) {
    serverBlock = (_root->getBlockList()).back();
    serverBlock->setKeyVal(_key, _value);
  } else {
    serverBlock = (_root->getBlockList()).back();
    locationBlock = (serverBlock->getBlockList()).back();
    locationBlock->setKeyVal(_key, _value);
  }
}

bool Parser::getState() const { return _error; }

void Parser::parseBlock(std::stack<BlockPair> stack) {
  enum BLOCK type = stack.top().first;
  std::string key;
  std::string value;

  while (true) { 
    setKey(key);
    if (type != ROOT && key == "}") return stack.pop();
    if ((type == ROOT && key == "server") ||
        (type == SERVER && key == "location")) 
    {
      
      if (type == ROOT && !skipBracket()) 
        continue;
      std::stack<BlockPair> temp = addBlock(stack);
      if (type == SERVER && !skipBracket()) 
        continue;
      stack.push(static_cast<enum BLOCK>(type + 1));
      parseBlock(stack);
      continue;
    }
    setValue(value);
    if (key.empty() || value.empty()) return stack.pop();
    block.setKeyVal(key, value);
  }
}

RootBlock *config(std::string path) {
  Parser parser(path);
  RootBlock *root = parser.getRootBlock();
  return root;
}
