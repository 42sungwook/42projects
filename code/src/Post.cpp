#include "../includes/Post.hpp"

void Post::process(Request &request, Response &response)
{
	std::cout << "Post" << std::endl;
}

Post::Post()
{
}

Post::~Post()
{
}

Post::Post(const Post &obj)
{
	*this = obj;
}

Post &Post::operator=(const Post &obj)
{
	*this = obj;
	return (*this);
}
