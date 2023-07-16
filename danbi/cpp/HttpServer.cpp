#include "HttpServer.hpp"

HttpServer::HttpServer(int port) : port(port)
{}

void HttpServer::addRoute(const std::string &path, HttpHandler *handler)
{
	routes[path] = handler;
}

void HttpServer::start()
{
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
	{
		std::cerr << "Failed to create server socket" << std::endl;
		return;
	}

	sockaddr_in serverAddress;
	std::memset(&serverAddress, 0, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, reinterpret_cast<struct sockaddr *>(&serverAddress),
					 sizeof(serverAddress)) == -1)
	{
		std::cerr << "Failed to bind server socket" << std::endl;
		close(serverSocket);
		return;
	}

	if (listen(serverSocket, 10) == -1)
	{
		std::cerr << "Failed to listen on server socket" << std::endl;
		close(serverSocket);
		return;
	}

	std::cout << "Server running on port " << port << std::endl;

	int kqueueFd = kqueue();
	if (kqueueFd == -1)
	{
		std::cerr << "Failed to create kqueue" << std::endl;
		close(serverSocket);
		return;
	}

	struct kevent serverEvent;
	std::memset(&serverEvent, 0, sizeof(serverEvent));
	EV_SET(&serverEvent, serverSocket, EVFILT_READ, EV_ADD, 0, 0, NULL);
	if (kevent(kqueueFd, &serverEvent, 1, NULL, 0, NULL) == -1)
	{
		std::cerr << "Failed to register server socket to kqueue" << std::endl;
		close(kqueueFd);
		close(serverSocket);
		return;
	}

	struct kevent events[64];

	while (true)
	{
		int eventCount = kevent(kqueueFd, NULL, 0, events, 64, NULL);
		if (eventCount == -1)
		{
			std::cerr << "Failed to retrieve events from kqueue" << std::endl;
			break;
		}

		for (int i = 0; i < eventCount; ++i)
		{
			if (events[i].ident == serverSocket)
			{
				if (events[i].filter == EVFILT_READ)
				{
					handleNewConnection(serverSocket, kqueueFd);
				}
			}
			else
			{
				if (events[i].filter == EVFILT_READ)
				{
					handleClient(events[i].ident);
				}
			}
		}
	}

	close(kqueueFd);
	close(serverSocket);
}

void HttpServer::handleNewConnection(int serverSocket, int kqueueFd)
{
	sockaddr_in clientAddress;
	std::memset(&clientAddress, 0, sizeof(clientAddress));
	socklen_t clientAddressLength = sizeof(clientAddress);
	int clientSocket =
			accept(serverSocket, reinterpret_cast<struct sockaddr *>(&clientAddress),
						 &clientAddressLength);
	if (clientSocket == -1)
	{
		std::cerr << "Failed to accept client connection" << std::endl;
		return;
	}

	struct kevent clientEvent;
	std::memset(&clientEvent, 0, sizeof(clientEvent));
	EV_SET(&clientEvent, clientSocket, EVFILT_READ, EV_ADD, 0, 0, NULL);
	if (kevent(kqueueFd, &clientEvent, 1, NULL, 0, NULL) == -1)
	{
		std::cerr << "Failed to register client socket to kqueue" << std::endl;
		close(clientSocket);
		return;
	}
}

void HttpServer::handleClient(int clientSocket)
{
	HttpRequest request = parseRequest(clientSocket);

	HttpResponse response;
	response.headers["Server"] = "CustomHTTPServer";

	std::string path = request.path;
	if (routes.count(path) > 0)
	{
		HttpHandler *handler = routes[path];
		handler->handleRequest(request, response);
	}
	else
	{
		NotFoundHandler notFoundHandler;
		notFoundHandler.handleRequest(request, response);
	}

	sendResponse(clientSocket, response);

	close(clientSocket);
}

HttpRequest HttpServer::parseRequest(int clientSocket)
{
	HttpRequest request;

	char buffer[4096];
	std::memset(buffer, 0, sizeof(buffer));
	ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
	if (bytesRead <= 0)
	{
		return request;
	}

	std::string requestString(buffer, bytesRead);

	std::stringstream ss(requestString);
	std::string line;

	// Read the first line containing the method and path
	if (std::getline(ss, line))
	{
		std::stringstream lineStream(line);
		lineStream >> request.method >> request.path;
	}

	// Read headers
	while (std::getline(ss, line) && line != "\r")
	{
		std::size_t colonPos = line.find(':');
		if (colonPos != std::string::npos)
		{
			std::string key = line.substr(0, colonPos);
			std::string value = line.substr(colonPos + 1);
			request.headers[key] = value;
		}
	}

	// Read body if Content-Length is provided
	if (request.headers.count("Content-Length") > 0)
	{
		int contentLength = std::atoi(request.headers["Content-Length"].c_str());
		if (contentLength > 0)
		{
			char *bodyBuffer = new char[contentLength + 1];
			std::memset(bodyBuffer, 0, contentLength + 1);
			ssize_t bodyBytesRead =
					recv(clientSocket, bodyBuffer, contentLength, 0);
			request.body = std::string(bodyBuffer, bodyBytesRead);
			delete[] bodyBuffer;
		}
	}

	return request;
}

void HttpServer::sendResponse(int clientSocket, const HttpResponse &response)
{
	std::stringstream ss;

	ss << "HTTP/1.1 " << response.status << " OK\r\n";

	std::map<std::string, std::string>::const_iterator it;
	for (it = response.headers.begin(); it != response.headers.end(); ++it)
	{
		const std::pair<std::string, std::string> &pair = *it;
		ss << pair.first << ": " << pair.second << "\r\n";
	}

	ss << "\r\n";

	if (!response.body.empty())
	{
		ss << response.body;
	}

	std::string responseString = ss.str();
	send(clientSocket, responseString.c_str(), responseString.length(), 0);
}
