#include "../includes/Response.hpp"

Response::Response() {}

Response::~Response() {}

void Response::setHeader(std::string key, std::string value) {
	if (_headers.find(key) == _headers.end())
		_headers[key] = value;
}

void Response::setBody(std::string body) {
	_body = body;
}

const std::string Response::getResponse() const {
	std::string response = "HTTP/1.1 " + "200 OK" + "\n";
	std::map<std::string, std::string>::const_iterator it;
	for (it = _headers.begin(); it != _headers.end(); it++)
		response += it->first + ": " + it->second + "\n";
	if (!_body.empty())
		response += "\n" + _body;
	return response;
}
