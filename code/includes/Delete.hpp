#ifndef DELETE_HPP
#define DELETE_HPP

#include "IMethod.hpp"

class Delete : public IMethod {
 private:
  std::string _result;
  std::string _path;

 public:
  Delete();
  ~Delete();

  void process(Request &request, Response &response);

  std::string makeStatusLine(Request &request, Response &response);
};

#endif
