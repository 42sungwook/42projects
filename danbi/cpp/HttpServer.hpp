#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "utils.hpp"

class HttpServer
{
public:
	HttpServer(int port);

	void addRoute(const std::string &path, HttpHandler *handler);
	void start();

private:
	int port;
	std::map<std::string, HttpHandler *> routes;

	void handleNewConnection(int serverSocket, int kqueueFd);
	void handleClient(int clientSocket);
	HttpRequest parseRequest(int clientSocket);
	void sendResponse(int clientSocket, const HttpResponse &response);
};

#endif