//
// Created by omrizaiman on 12/05/2021.
//

#ifndef SERVER_SOCKETEXCEPTION_H
#define SERVER_SOCKETEXCEPTION_H

#include <string>
#include <exception>
#include <utility>

class SocketException : public std::exception
{
public:
    explicit SocketException (std::string msg) : _message (std::move(msg)) {};

    [[nodiscard]] const char* what() const noexcept override {
        return this->_message.c_str();
    }

private:

    std::string _message;
};

#endif //SERVER_SOCKETEXCEPTION_H
