#include "../includes/ConfigParser.hpp"

ConfigParser::ConfigParser(std::string &path) {
  std::stack<BlockPair> stack;

  _rootBlock = new RootBlock();
  _start = 0;
  _pos = 0;
  readConfig(path);
  if (_line.empty()) return;

  stack.push(std::make_pair(ROOT, _rootBlock));
  parseBlock(stack);
}

ConfigParser::~ConfigParser() {}

void ConfigParser::readConfig(std::string &path) {
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

bool ConfigParser::skipBracket() {
  _pos = _line.find_first_of("{", _pos);
  if (_pos == std::string::npos) return false;
  _start = _line.find_first_of("}", _pos);
  if (_start == std::string::npos) return false;
  ++_pos;
  return true;
}

void ConfigParser::setKey(std::string &key) {
  key.clear();
  _start = _line.find_first_not_of(ISSPACE, _pos);
  if (_start == std::string::npos) return;
  _pos = _line.find_first_of(ISSPACE, _start);
  if (_pos == std::string::npos) return;
  key = _line.substr(_start, _pos - _start);
}

void ConfigParser::setValue(std::string &value) {
  value.clear();
  _start = _line.find_first_not_of(ISSPACE, _pos);
  if (_start == std::string::npos) return;
  _pos = _line.find_first_of(SEMICOLON, _start);
  if (_pos == std::string::npos) return;
  value = _line.substr(_start, _pos - _start);
  ++_pos;
}

RootBlock *ConfigParser::getRootBlock() { return _rootBlock; }

std::stack<BlockPair> ConfigParser::addBlock(BlockPair &top) {
  RootBlock *newBlock;
  BlockPair pair;

  if (top.first == ROOT) {
    newBlock = new ServerBlock(top.second);
    _serverBlocks.push_back(newBlock);
  } else if (top.first == SERVER) {
    newblock = static_cast<ServerBlock>(top.second).newLocationBlock();

    newBlock = new LocationBlock(static_cast<ServerBlock &>(top.second));
    setKey();
    newBlock->setKeyVal("path", _key);
  }
  pair = std::make_pair(stack.top().first + 1, newBlock);
}

void ConfigParser::setKeyVal(enum BLOCK type) {
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

void ConfigParser::parseBlock(std::stack<BlockPair> stack) {
  enum BLOCK type = stack.top().first;
  std::string key;
  std::string value;

  while (true) {
    setKey(key);
    if (type != ROOT && key == "}") return stack.pop();
    if ((type == ROOT && key == "server") ||
        (type == SERVER && key == "location")) {
      if (type == ROOT && !skipBracket()) continue;
      std::stack<BlockPair> temp = addBlock(stack.top());
      if (type == SERVER && !skipBracket()) continue;
      stack.push(static_cast<enum BLOCK>(type + 1));
      parseBlock(stack);
      continue;
    }
    setValue(value);
    if (key.empty() || value.empty()) return stack.pop();
    _rootBlock->setKeyVal(key, value);
  }
}

RootBlock *config(std::string path) {
  ConfigParser parser(path);
  RootBlock *root = parser.getRootBlock();
  return root;
}
