#include "Request.hpp"

Request::Request() : _method(-1), _process(-1) {}

Request::~Request() {}

void Request::parsing(std::string tmp) {
  _start = int i = 0;

  while (tmp.c_str()[i] && tmp.c_str()[i] != '\r') {
  }
}

const std::string Request::getMessage() const {};

enum PROCESS Request::getProcess(){};

enum METHOD Request::getMethod(){};