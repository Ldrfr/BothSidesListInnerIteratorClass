#include "exception.h"

#include <iostream>

std::ostream& operator << (std::ostream& os, const Exception &e) { // why it works only with iosfwd??????
  os << e.code_ << ": " << e.message_;
  return os;
}

const char* Exception::GetMessage() const {
  return message_;
}

ErrorCode Exception::GetCode() const {
  return code_;
}
