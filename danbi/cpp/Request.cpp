#include "Request.hpp"

Request::Request() {}

Request::~Request() {}

void Request::parsing(std::string tmp) { std::cout << "parsing" << std::endl; }

const std::string Request::getMessage() const {};

enum PROCESS Request::getProcess(){

};

const int &Request::getError() const { return _error; }

enum METHOD Request::getMethod(){};