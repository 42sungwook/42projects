#ifndef METHOD_HPP
#define METHOD_HPP

#include "IMethod.hpp"

class Method : public IMethod {
 private:
 protected:
  std::string _statusLine;
  std::string _header;
  std::string _body;
  std::string _path;

 public:
  virtual ~Method();

  void process(Request &request, Response &response);
};

#endif