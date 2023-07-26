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

const std::string Response::getResponse(std::string status) const {
	std::string response = "HTTP/1.1 " + status + "\n";
	std::map<std::string, std::string>::const_iterator it;
	for (it = _headers.begin(); it != _headers.end(); it++)
		response += it->first + ": " + it->second + "\n";
	if (!_body.empty())
		response += "\n" + _body;
	return response;
}

int main() {
	Response rp = Response();

	rp.setHeader("Date", "2023.02.03");
	rp.setHeader("Server", "ngnix/1.25.1");
	rp.setHeader("Content-Type", "text/html");
	rp.setHeader("Content-Length", "153");
	rp.setHeader("Connection", "keep-alive");
//	rp.setBody("<html>\n"
//			   "  <head>\n"
//			   "    <title>Dockerfile</title>\n"
//			   "    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n"
//			   "  </head>\n"
//			   "\n"
//			   "  <body>\n"
//			   "    <h1>ㅎㅇ</h1>\n"
//			   "  </body>\n"
//			   "</html>");

	std::cout << rp.getResponse("200 OK") << std::endl;
}