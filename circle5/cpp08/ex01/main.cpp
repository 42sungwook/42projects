#include "Span.hpp"

int main() {
  std::cout << "===== Test 과제 main.cpp =====" << std::endl;
  try {
    Span sp = Span(5);
    sp.addNumber(5);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;
    sp.addNumber(12);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "===== Test 30000 numbers + 중복 숫자 =====" << std::endl;
  try {
    Span sp = Span(30000);
    sp.addNumber(1, 15000);
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;
    sp.addNumber(15001, 29999);
    sp.addNumber(4001202);
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "===== Test 숫자 1개일 때 shortestSpan =====" << std::endl;
  try {
    Span sp = Span(10000);
    sp.addNumber(1);
    std::cout << sp.shortestSpan() << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "===== Test 숫자 1개일 때 longestSpan =====" << std::endl;
  try {
    Span sp = Span(10000);
    sp.addNumber(1);
    std::cout << sp.longestSpan() << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
