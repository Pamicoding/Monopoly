#ifndef _ERROR_H_
#define _ERROR_H_

#include <exception>
#include <string>

class NotImplement : public std::exception {
private:
    std::string message;

public:
    inline NotImplement(std::string&& msg): message(msg) {}

    inline const char* what() const noexcept override {
      return message.c_str();
    }
};

#endif // _ERROR_H_