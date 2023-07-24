#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>

class Response {
  private:
    std::string _result;

  public:
    Response();
    ~Response();
    const std::string &getResult() const;
};

#endif