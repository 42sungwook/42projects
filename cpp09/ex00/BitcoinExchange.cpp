#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
  std::ifstream csvFile("data.csv");
  std::string line;
  std::string date;
  float value;

  if (!csvFile) {
    std::cerr << "Error: Unable to open csv file\n";
    return;
  }

  std::getline(csvFile, line);
  if (line != "date,exchange_rate") {
    std::cerr << "Error: Invalid csv file format\n";
    return;
  }

  while (std::getline(csvFile, line)) {
    date = line.substr(0, line.find(','));
    value = std::stof(line.substr(line.find(',') + 1));
    // date 형식 오류 확인
    // value 0 and 1000 사이인지 + 오류인지 확인
    _csvData[date] = value;
  }
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
  _data = other._data;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
  _data = other._data;
  return *this;
}

void BitcoinExchange::fileRead(const char* filename) {
  std::ifstream inputFile;

  inputFile.open(filename);

  if (!inputFile) {
    std::cerr << "Error: Unable to open input file\n";
    return;
  }

  // 구분자 | 확인
}

void BitcoinExchange::fileWrite(const char* filename) {
  // Year-Month-Day 포맷 확인
  // 0 and 1000 사이 int 또는 float인지 확인
  /* If the date used in the input does not exist in your DB then you
     must use the closest date contained in your DB. Be
     careful to use the lower date and not the upper one */
  // print하기
}

bool checkDate(const std::string& date) {
  // Year-Month-Day 포맷 확인

  unsigned int year;
  unsigned int month;
  unsigned int day;

  if (year > 9999 || month > 12 || day > 31 || month == 0 || day == 0)
    return false;

  if (month % 2 == 1) {
    if (month > 7) {
      if (day > 30) return false;
    }
  } else {
    if (month < 7) {
      if (month == 2) {
        if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
          if (day > 29) return false;
        } else {
          if (day > 28) return false;
        }
      }
      if (day > 30) return false;
    }
  }

  return true;
}