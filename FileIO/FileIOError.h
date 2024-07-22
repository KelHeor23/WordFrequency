#ifndef FILEIOERROR_H
#define FILEIOERROR_H

#include <string>
#include <exception>

namespace FileIO {

class FileIOError : public std::exception {
public:
    FileIOError(const std::string &message) : msg(message) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

}


#endif // FILEIOERROR_H
