#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <map>
#include <iostream>

class Response {
  private:
    std::string _body;
	std::map<std::string, std::string> _headers;

  public:
    Response();
    ~Response();

	void setHeader(std::string key, std::string value);
	void setBody(std::string body);

	const std::string getResponse() const;
};

#endif