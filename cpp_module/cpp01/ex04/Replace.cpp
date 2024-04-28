#include "Replace.hpp"

Replace::Replace(const std::string &filename, const std::string &str1,
                 const std::string &str2)
    : _filename(filename), _str1(str1), _str2(str2) {}

Replace::~Replace() {
  if (_inputFile) {
    _inputFile->close();
    delete _inputFile;
  }
}

void Replace::openInFile() {
  std::ifstream *inputFile = new std::ifstream(_filename.c_str());

  if (!inputFile->is_open()) {
    std::cout << _filename << ": file doesn't exist" << std::endl;
    return;
  }

  _inputFile = inputFile;
}

void Replace::makeLine() {
  std::string line;

  if (!_inputFile) {
    std::cout << "File not open" << std::endl;
    return;
  }

  while (std::getline(*_inputFile, line)) {
    _line += line;
    if (!_inputFile->eof()) {
      _line += '\n';
    }
  }
}

void Replace::replaceStr() {
  size_t pos = 0;
  size_t len = _str1.length();

  if (_line.empty()) {
    std::cout << "line is empty" << std::endl;
    return;
  }
  if (_str1.empty()) {
    std::cout << "str1 is empty" << std::endl;
    return;
  }
  while ((pos = _line.find(_str1, pos)) != std::string::npos) {
    _line.erase(pos, len);
    _line.insert(pos, _str2);
    pos += _str2.length();
  }
}

void Replace::makeOutFile() {
  std::string outFile = _filename;
  outFile += ".replace";

  if (_line.empty()) {
    std::cout << "line is empty" << std::endl;
    return;
  }

  std::ofstream outputFile(outFile.c_str());

  if (!outputFile.is_open()) {
    std::cout << outFile << ": outfile error" << std::endl;
    return;
  }
  outputFile << _line;
  outputFile.close();
  _inputFile = 0;
}