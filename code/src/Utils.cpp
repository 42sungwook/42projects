#include "../includes/Utils.hpp"

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

void ftToupper(std::string &str) {
  std::string res;

  for (int i = 0; i < str.length(); i++) {
    res += static_cast<char>(std::toupper(str.at(i)));
  }
  str = res;
}
/*convert to seconde unit, defualt is second*/
size_t convertTimeUnits(std::string value) {
  std::stringstream ss(value);
  size_t sum = 0;
  std::string timeUnits[4] = {"", "MS", "S", "M"};
  float times[4] = {1, 0.001, 1, 60000};

  while (true) {
    int num = 0;
    std::string unit;
    ss >> num >> unit;
    if (num == 0) break;
    ftToupper(unit);
    for (int index = 0; index < 4; index++) {
      if (unit == timeUnits[index]) {
        sum += num * times[index];
        break;
      }
    }
  }
  return sum;
}

size_t convertByteUnits(std::string value) {
  int num;
  std::string unit;
  std::stringstream ss(value);
  const std::string byteUnits[4] = {"", "K", "M", "G"};
  int index;

  ss >> num >> unit;
  ftToupper(unit);
  for (index = 0; index < 4; index++)
    if (unit == byteUnits[index]) break;

  return (num * std::pow(1024, index));
}
