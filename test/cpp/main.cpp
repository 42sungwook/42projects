#include "HttpServer.hpp"

int main()
{

	HttpServer server(8080);

	HelloWorldHandler helloHandler;

	server.addRoute("/", &helloHandler);

	server.start();

	return 0;
}
