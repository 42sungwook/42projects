#include "../includes/Delete.hpp"

void Delete::process(Request &request, Response &response)
{
	std::cout << "Delete" << std::endl;
}

Delete::Delete()
{
}

Delete::~Delete()
{
}

Delete::Delete(const Delete &obj)
{
	*this = obj;
}

Delete &Delete::operator=(const Delete &obj)
{
	*this = obj;
	return (*this);
}
