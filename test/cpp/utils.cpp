#include "utils.hpp"

void HelloWorldHandler::handleRequest(const HttpRequest &request, HttpResponse &response)
{
	response.status = 200;
	response.body = "Hello, World!";
	response.headers["Content-Type"] = "text/plain";
}

void NotFoundHandler::handleRequest(const HttpRequest &request, HttpResponse &response)
{
	response.status = 404;
	response.body = "Not Found";
	response.headers["Content-Type"] = "text/plain";
}