#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
  std::ifstream csvFile("data.csv");
  std::string line;
  std::string date;
  float value;

  if (!csvFile) {
    throw std::runtime_error("Error: Unable to open csv file");
  }

  std::getline(csvFile, line);
  if (line != "date,exchange_rate") {
    throw std::runtime_error("Error: Invalid csv file format");
  }

  while (std::getline(csvFile, line)) {
    date = line.substr(0, line.find(','));
    value = std::atof(line.substr(line.find(',') + 1).c_str());
    if (!checkDate(date)) {
      throw std::runtime_error("Error: Invalid csv file format2");
    }
    _csvData[date] = value;
  }
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
  _csvData = other._csvData;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
  if (this != &other) {
    _csvData = other._csvData;
  }
  return *this;
}

void BitcoinExchange::exchange(const char* filename) {
  std::ifstream inputFile;
  std::string line;

  inputFile.open(filename);

  if (!inputFile) {
    throw std::runtime_error("Error: Unable to open input file");
  }
  std::getline(inputFile, line);
  if (line != "date | value") {
    throw std::runtime_error("Error: Invalid input file format");
  }

  while (std::getline(inputFile, line)) {
    std::string removeSpaceLine(line);
    removeSpaceLine.erase(std::remove_if(removeSpaceLine.begin(),
                                         removeSpaceLine.end(), ::isspace),
                          removeSpaceLine.end());
    if (removeSpaceLine.find('|') != 10) {
      std::cout << "Error: bad input => " << line << std::endl;
      continue;
    }
    std::string date = removeSpaceLine.substr(0, 10);
    if (!checkDate(date)) {
      std::cout << "Error: bad input => " << date << std::endl;
      continue;
    }
    float value = std::atof(removeSpaceLine.substr(11).c_str());
    if (value < 0) {
      std::cout << "Error: not a positive number" << std::endl;
      continue;
    }
    if (value > 1000) {
      std::cout << "Error: too large a number" << std::endl;
      continue;
    }

    std::cout << date << " => " << value << " = ";
    std::map<std::string, float>::iterator it = _csvData.lower_bound(date);
    if (it == _csvData.end()) {
      if (it->first != date) {
        it--;
      }
    }
    std::cout << value * it->second << std::endl;
  }
  inputFile.close();
}

bool BitcoinExchange::checkDate(const std::string& date) {
  // Year-Month-Day 포맷 확인
  for (size_t i = 0; i < 10; i++) {
    if (i == 4 || i == 7) {
      if (date[i] != '-') {
        return false;
      }
    } else {
      if (date[i] < '0' || date[i] > '9') {
        return false;
      }
    }
  }
  unsigned int year = std::atoi(date.substr(0, 4).c_str());
  unsigned int month = std::atoi(date.substr(5, 2).c_str());
  unsigned int day = std::atoi(date.substr(8, 2).c_str());

  if (year > 9999 || month > 12 || day > 31 || month == 0 || day == 0) {
    return false;
  }

  if (month % 2 == 1 && month > 7 && day > 30) {
    return false;
  } else if (month % 2 == 0 && month < 7) {
    if (month == 2) {
      if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        if (day > 29) return false;
      } else {
        if (day > 28) return false;
      }
    } else {
      if (day > 30) return false;
    }
  }

  return true;
}