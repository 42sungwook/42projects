#include "../includes/Get.hpp"

Get::Get() {}

Get::~Get() {}

Get::Get(const Get &obj)
{
	*this = obj;
}

Get &Get::operator=(const Get &obj)
{
	*this = obj;
	return (*this);
}

void Get::openFile(Request &request, Response &response)
{
	std::string uri = request.getUri();
	size_t pos = uri.find("/");
	if (pos != std::string::npos)
	{
		std::string path = uri.substr(uri.find("/"));
		std::fstream file(path.c_str());
		if (file.is_open())
		{
			
		}
	}
	else
	{
		std::cout << "URI does not contain '/'" << std::endl;
	}
}

void Get::makeStatusLine(Request &request, Response &response)
{
}

void Get::makeHeader(Request &request, Response &response)
{
}

void Get::makeBody(Request &request, Response &response)
{
}

void Get::process(Request &request, Response &response)
{
	openFile(request, response);
	makeStatusLine(request, response);
	makeHeader(request, response);
	makeBody(request, response);
}
