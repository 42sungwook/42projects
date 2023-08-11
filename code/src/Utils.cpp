#include "Utils.hpp"

int ftStoi(std::string str) {
  int ret = 0;
  bool neg = false;

  if (str[0] == '-') {
    neg = true;
    str = str.substr(1, str.size() - 1);
  }
  for (size_t i = 0; i < str.size() && str[i] >= '0' && str[i] <= '9'; i++) {
    ret *= 10;
    ret += str[i] - '0';
  }
  if (neg) ret = -ret;
  return ret;
}

std::string ftItos(int num) {
  std::string ret;
  bool neg = false;

  if (num == 0) return "0";
  if (num < 0) {
    neg = true;
    num = -num;
  }
  while (num) {
    ret += num % 10 + '0';
    num /= 10;
  }
  std::reverse(ret.begin(), ret.end());
  if (neg) ret = "-" + ret;
  return ret;
}
