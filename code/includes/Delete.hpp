#ifndef DELETE_HPP
#define DELETE_HPP

#include "IMethod.hpp"

class Delete : public IMethod
{
public:
	void process(Request &request, Response &response);
	Delete();
	~Delete();
	Delete(const Delete &obj);
	Delete &operator=(const Delete &obj);
	void makeHeaders(Request &request, Response &response);
	void makeStatusLine(Request &request, Response &response);
	void openFile(Request &request, Response &response);
};

#endif
