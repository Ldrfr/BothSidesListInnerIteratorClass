#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <cstddef>
#include <cstring>
#include <iosfwd>

enum ErrorCode {
  EC_FUNCTION = -4,
  EC_RANGE = -3,
  EC_MEMORY = -2,
  EC_UNKNOWN = -1,
  EC_OK = 0
};

class Exception {
private:
  char message_[256];
  ErrorCode code_;

public:
  const char *GetMessage() const;
  ErrorCode GetCode() const;
  Exception operator=(const Exception &) = delete;
  Exception(ErrorCode c, const char *msg) {
    code_ = c;
    strncpy(message_, msg, 256); // destination, source, size to copy
  }
  friend std::ostream& operator<<(std::ostream &os, const Exception &e);
};

#endif