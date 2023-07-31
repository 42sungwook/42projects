#ifndef ROOTBLOCK_HPP
#define ROOTBLOCK_HPP

#include <iostream>
#include <list>
#include <map>
#include <vector>

class RootBlock
{
protected:
  std::string _user;
  std::string _group;
  int _workerProcesses;
  std::string _errorLog;
  std::string _pid;
  int _workerRlimitNofile;
  int _workerConnections;
  std::string _include;

  std::map<std::string, std::string> _statusCodes;

public:
  RootBlock();
  RootBlock(RootBlock &copy);
  ~RootBlock();

  void setUser(std::string value);
  void setWorkerProcesses(std::string value);
  void setErrorLog(std::string value);
  void setPid(std::string value);
  void setWorkerRlimitNofile(std::string value);
  void setWorkerConnections(std::string value);
  void setInclude(std::string value);
  virtual void setKeyVal(std::string key, std::string value);

  const std::string getUser() const;
  const std::string getGroup() const;
  const std::string getInclude() const;
  const std::string getErrorLog() const;
  int getWorkerRlimitNofile() const;
  const std::string getPid() const;
  int getWorkerConnection() const;
  int getWorkerProcesses() const;

  std::string getStatusCode(std::string key);

  void test(); // TODO test
};

#endif
