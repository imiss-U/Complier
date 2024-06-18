#pragma once

#include <exception>
#include <string>

class Exceptions : public std::exception {
public:
    Exceptions() : __message("Error:") {}
    Exceptions(const std::string& message) : __message("Errors: " + message) {}
    const char* what() const noexcept override {
        return __message.c_str();
    }
    int get_msg_len() { return __message.length(); }
    std::string __message;
};

class NoInputException : public Exceptions {
public:
    NoInputException(const std::string& msg) :Exceptions("Short of Input!" + msg) {}
};

class NosemicolonException : public Exceptions {
public:
    NosemicolonException(const std::string& msg) : Exceptions("Short of Semicolon" + msg) {}
};

class NoIdentifierException : public Exceptions {
public:
    NoIdentifierException(const std::string& msg) : Exceptions(msg + " is not a valid identifier") {}
};

class UnEnclosedQuotation : public Exceptions {
public:
    UnEnclosedQuotation(const std::string& msg) : Exceptions(msg + " 's quotation are unenclosed") {}
};

class NotContainMainException : public Exceptions {
public:
    NotContainMainException(const std::string& msg) : Exceptions(msg + " does not contain main function") {}
};

class InvalidIncludeException : public Exceptions {
public:
    InvalidIncludeException(const std::string& msg) : Exceptions(msg + " is not a valid include") {}
};

class WrongParseException : public Exceptions {
public:
    WrongParseException(const std::string& msg) : Exceptions(msg + "Wrong parse") {}
};