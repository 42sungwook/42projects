#ifndef HTTP_H
#define HTTP_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class HttpRequest
{
public:
	std::string method;
	std::string path;
	std::string body;
	std::map<std::string, std::string> headers;
};

class HttpResponse
{
public:
	int status;
	std::string body;
	std::map<std::string, std::string> headers;
};

class HttpHandler
{
public:
	virtual void handleRequest(const HttpRequest &request, HttpResponse &response) = 0;
};

class HelloWorldHandler : public HttpHandler
{
public:
	void handleRequest(const HttpRequest &request, HttpResponse &response);
};

class NotFoundHandler : public HttpHandler
{
public:
	void handleRequest(const HttpRequest &request, HttpResponse &response);
};

#endif