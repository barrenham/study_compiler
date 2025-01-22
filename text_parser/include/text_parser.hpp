#ifndef TEXT_PARSER_HPP
#define TEXT_PARSER_HPP

#include <string>
#include "general_type.hpp"
#include "token.hpp"

class TEXT_PARSER_ERROR_GRAMMAR:public std::exception
{
public:
    TEXT_PARSER_ERROR_GRAMMAR(const std::string& message) : msg_(message) {}
    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

class TEXT_PARSER{
public:
    void  program(Serial str);
    TOKEN match(Serial&str,STR_POS& pos);
    inline void next(STR_POS& pos);
private:
    bool isDigit(char c); //[0-9]
    bool isAlpha(char c); //[a-zA-Z]
    bool isSpace(char c); //[' ']
    bool isDot  (char c); //[.]
    bool isSep  (char c); //[{}[];,():.]
    bool isOp   (char c); //[+-*/^%=&|!<>]
    bool isLF   (char c); //[\n]
    bool isOcto (char c); //[#]
    bool isCR   (char c); //[\r]
    bool isUdl  (char c); //[_]
    bool isStrSp(char c); //["]
};



#endif