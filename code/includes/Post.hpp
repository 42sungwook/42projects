#ifndef POST_HPP
#define POST_HPP

#include "IMethod.hpp"

class Post : public IMethod
{
public:
	void process(Request &request, Response &response);
	Post();
	~Post();
	Post(const Post &obj);
	Post &operator=(const Post &obj);
	void makeHeaders(Request &request, Response &response);
	void makeStatusLine(Request &request, Response &response);
	void openFile(Request &request, Response &response);
};

#endif
