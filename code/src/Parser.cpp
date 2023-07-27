#include "../includes/Parser.hpp"

#include <sstream>

Parser::Parser(std::string &path) : _key(), _value(), _error(true) {
  std::stack<enum BLOCK> stack;

  _root = new RootBlock();
  _start = 0;
  _pos = 0;
  readConfig(path);
  if (_line.empty()) return;
  stack.push(ROOT);
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

void Parser::setKey() {
  _key.clear();
  _start = _line.find_first_not_of(ISSPACE, _pos);
  if (_start == std::string::npos) return;
  _pos = _line.find_first_of(ISSPACE, _start);
  if (_pos == std::string::npos) return;
  _key = _line.substr(_start, _pos - _start);
}

void Parser::setValue() {
  _value.clear();
  _start = _line.find_first_not_of(ISSPACE, _pos);
  if (_start == std::string::npos) return;
  _pos = _line.find_first_of(SEMICOLON, _start);
  if (_pos == std::string::npos) return;
  _value = _line.substr(_start, _pos - _start);
  ++_pos;
}

RootBlock *Parser::getRootBlock() { return _root; }

void Parser::addBlock(enum BLOCK type) {
  ServerBlock *serverBlock;

  if (type == ROOT) {
    serverBlock = new ServerBlock();
    _root->addServerBlock(serverBlock);
  } else if (type == SERVER) {
    serverBlock = (_root->getBlockList()).back();
    LocationBlock *locationBlock = new LocationBlock();
    serverBlock->addLocationBlock(locationBlock);
    setKey();
    locationBlock->setKeyVal("path", _key);
  }
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

void Parser::parseBlock(std::stack<enum BLOCK> &stack) {
  enum BLOCK type = stack.top();
  while (true) {
    setKey();
    if (type != ROOT && _key == "}") return stack.pop();
    if ((type == ROOT && _key == "server") ||
        (type == SERVER && _key == "location")) {
      if (type == ROOT && !skipBracket()) continue;
      addBlock(type);
      if (type == SERVER && !skipBracket()) continue;
      stack.push(static_cast<enum BLOCK>(type + 1));
      parseBlock(stack);
      continue;
    }
    setValue();
    if (_key.empty() || _value.empty()) return stack.pop();
    setKeyVal(type);
  }
}

RootBlock *config(std::string path) {
  Parser parser(path);
  RootBlock *root = parser.getRootBlock();
  return root;
}
