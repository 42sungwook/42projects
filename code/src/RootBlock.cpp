#include "../includes/RootBlock.hpp"

RootBlock::RootBlock() : _user(), _include(), _workerConnections(0), _workerProcesses(0) {
  _statusCodes["200"] = "OK";
  _statusCodes["201"] = "Created";
  _statusCodes["202"] = "Accepted";
  _statusCodes["204"] = "No Content";
  _statusCodes["300"] = "Multiple Choice";
  _statusCodes["301"] = "Moved Permanently";
  _statusCodes["303"] = "See Other";
  _statusCodes["304"] = "Not Modified";
  _statusCodes["307"] = "Temporary Redirect";
  _statusCodes["400"] = "Bad Request";
  _statusCodes["401"] = "Unauthorized";
  _statusCodes["403"] = "Forbidden";
  _statusCodes["404"] = "Not Found";
  _statusCodes["405"] = "Method Not Allowed";
  _statusCodes["406"] = "Not Acceptable";
  _statusCodes["409"] = "Conflict";
  _statusCodes["410"] = "Gone";
  _statusCodes["412"] = "Precondition Failed";
  _statusCodes["414"] = "URI Too Long";
  _statusCodes["415"] = "Unsupported Media Type";
  _statusCodes["500"] = "Server Error";
}

RootBlock::RootBlock(RootBlock &copy)
    : _user(copy._user),
      _include(copy._include),
      _workerConnections(copy._workerConnections),
      _workerProcesses(copy._workerProcesses),
      _statusCodes(copy._statusCodes) {}

RootBlock::~RootBlock() {}

void RootBlock::setUser(std::string value) {
  size_t  tmp = value.find_first_of(" \t\n\r\f\v");
  if (tmp != std::string::npos) {
    _user = value.substr(0, tmp - 1);
    tmp = value.find_first_not_of(" \t\n\r\f\v", tmp);
    _group = value.substr(tmp, value.size() - tmp);
  }
  else {
    _user = value;
    _group = value;
  }
}

void RootBlock::setInclude(std::string value) { _include = value; }

void RootBlock::setWorkerConnection(std::string value) {
  _workerConnections = atoi(value.c_str());
}

void RootBlock::setWorkerProcesses(std::string value) {
  _workerProcesses = atoi(value.c_str());
}

void RootBlock::setKeyVal(std::string key, std::string value) {
  typedef void (RootBlock::*funcptr)(std::string);
  typedef std::map<std::string, funcptr> funcMap;
  funcMap map;

  map["user"] = &RootBlock::setUser;
  map["worker_processes"] = &RootBlock::setWorkerProcesses;
  map["error_log"] = &RootBlock::setErrorLog;
  map["pid"] = &RootBlock::setPid;
  map["worker_rlimit_nofile"] = &RootBlock::setWorkerRlimitNofile;
  map["worker_connections"] = &RootBlock::setWorkerConnection;
  map["include"] = &RootBlock::setInclude;

  if (map.find(key) != map.end())
    (this->*(map[key]))(value);
}

const std::string RootBlock::getUser() const { return _user; }

const std::string RootBlock::getGroup() const { return _group; }

int RootBlock::getWorkerProcesses() const { return _workerProcesses; }

const std::string RootBlock::getErrorLog() const { return _errorLog; }

const std::string RootBlock::getPid() const { return _pid; }

int RootBlock::getWorkerRlimitNofile() const { return _workerRlimitNofile; }

int RootBlock::getWorkerConnection() const { return _workerConnections; }

const std::string RootBlock::getInclude() const { return _include; }

std::string RootBlock::getStatusCode(std::string key) {
  std::map<std::string, std::string>::iterator it;
  for (it = _statusCodes.begin(); it != _statusCodes.end(); it++) {
    if (it->first == key) return _statusCodes[key];
  }
  throw std::runtime_error("Invalid status code");
}

// TODO test
void RootBlock::test() {
  std::cout << "===========ROOT===========" << std::endl;
  std::cout << "_user: " << _user << std::endl;
  std::cout << "_group: " << _group << std::endl;
  std::cout << "_workerProcesses: " << _workerProcesses << std::endl;
  std::cout << "_errorLog: " << _errorLog << std::endl;
  std::cout << "_pid: " << _pid << std::endl;
  std::cout << "_workerRlimitNofile: " << _workerRlimitNofile << std::endl;
  std::cout << "_workerConnections: " << _workerConnections << std::endl;
  std::cout << "_include: " << _include << std::endl;
  std::cout << "==========================" << std::endl;
}

