#include "../includes/ConfigParser.hpp"

ConfigParser::ConfigParser(const char *path, RootBlock *root) : _start(0), _pos(0) {

  readConfig(path);
  if (_line.empty()) return;
  _stack.push(std::make_pair(ROOT, root));
}

ConfigParser::~ConfigParser() {}

void ConfigParser::readConfig(const char *path) {
  std::ifstream filestream(path);
  if (!filestream.is_open()) {
    std::cerr << "Path Error" << std::endl;
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
  _start = _line.find_first_not_of(ISSPACE, _pos); // spaces skip
  if (_start == std::string::npos) return;
  _pos = _line.find_first_of(ISSPACE, _start); // find next index of directive
  if (_pos == std::string::npos) return;
  key = _line.substr(_start, _pos - _start); // get directive
}

void ConfigParser::setValue(std::string &value) {
  value.clear();
  _start = _line.find_first_not_of(ISSPACE, _pos); // spaces skip
  if (_start == std::string::npos) return;
  _pos = _line.find_first_of(SEMICOLON, _start); // find end of directives(end of line)
  if (_pos == std::string::npos) return;
  value = _line.substr(_start, _pos - _start); // get directive's parameters
  ++_pos;
}

RootBlock *ConfigParser::addBlock(BlockPair &top) {
  RootBlock *newBlock;

  if (top.first == ROOT) {
    newBlock = new ServerBlock(*(top.second));
  } else if (top.first == SERVER) {
    newBlock = new LocationBlock(static_cast<ServerBlock &>(*(top.second)));
    std::string key;
    setKey(key);
    newBlock->setKeyVal("path", key);
    if (_locationMap.find(static_cast<ServerBlock *>(top.second)) == _locationMap.end()) {
      _locationMap[static_cast<ServerBlock *>(top.second)] = new LocationList;
    }
    _locationMap[static_cast<ServerBlock *>(top.second)]->push_back(static_cast<LocationBlock *>(newBlock));
  }
  return newBlock;
}

void ConfigParser::parseBlocks() {

  std::string key;
  std::string value;
  enum BLOCK type = _stack.top().first;

  while (true) {
    setKey(key);
    if (type != ROOT && key == "}") return _stack.pop();
    else if ((type == ROOT && key == "server") || (type == ROOT && key == "event") || (type == SERVER && key == "location")) {
      if (type == ROOT && !skipBracket()) continue;
      if (key == "event")
        _stack.push(std::make_pair(EVENT, _stack.top().second));
      else {
        RootBlock *temp = addBlock(_stack.top());
        if (type == SERVER && !skipBracket()) continue;
        _stack.push(std::make_pair(type + 1, temp));
      }
      parseBlocks();
      continue;
    }
    setValue(value);
    if (key.empty() || value.empty()) return _stack.pop();
    _stack.top().second->setKeyVal(key, value); // set data on the Block
    if (key == "listen") { // When ServerBlock's port is determined
      int port = static_cast<ServerBlock *>(_stack.top().second)->getListen();
      if (_serverBlockMap.find(port) == _serverBlockMap.end()) {
        _serverBlockMap[port] = new SPSBList;
      }
      _serverBlockMap[port]->push_back(static_cast<ServerBlock *>(_stack.top().second));
    }
  }
}
