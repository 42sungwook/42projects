#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <string>

class BitcoinExchange {
 public:
  BitcoinExchange();
  ~BitcoinExchange();
  BitcoinExchange(const BitcoinExchange& other);
  BitcoinExchange& operator=(const BitcoinExchange& other);

  void fileRead(const char* filename);
  void fileWrite(const char* filename);

 private:
  std::map<std::string, float> _data;
  std::map<std::string, float> _csvData;
};

bool checkDate(const std::string& date);

#endif
