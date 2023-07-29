#ifndef GET_HPP
#define GET_HPP

#include "IMethod.hpp"

class Get : public IMethod
{
private:
public:
	void process(Request &request, Response &response);
	Get();
	~Get();
	Get(const Get &obj);
	Get &operator=(const Get &obj);
	void makeBody(Request &request, Response &response);
	void makeHeader(Request &request, Response &response);
	void makeStatusLine(Request &request, Response &response);
	void openFile(Request &request, Response &response);
};

#endif
