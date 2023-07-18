#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <map>

enum METHOD {
  GET,
  POST,
  DELETE
};

enum PROCESS {
  ERROR,
  CGI,
  NORMAL
};

class Request
{
private:
  std::string msg;

public:
	Request();
	~Request();
	void  parsing(std::string msg);
  const std::string getMessage() const;
  enum PROCESS getProcess();
  enum METHOD getMethod();
};




#endif