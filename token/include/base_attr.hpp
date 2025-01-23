#ifndef BASE_ATTR_HPP
#define BASE_ATTR_HPP

#include<string>

class TOKEN;
class AST_TOKEN;

typedef std::string TOKEN_CONTAIN_STR;

class BASE_ATTR{

public:
    //TODO: 创建具体方法，获取private 数据
    void addchar(char c);
    void addstring(TOKEN_CONTAIN_STR str);
    void add_string_to_front(TOKEN_CONTAIN_STR str);
    void show_contain_str() const;
    BASE_ATTR& operator=(const BASE_ATTR& other);
    TOKEN_CONTAIN_STR get_contain_str() const;
private:
    //TODO: 创建具体变量，用于表示TOKEN基础属性(共有部分)
    TOKEN_CONTAIN_STR inside_str;
};

class AST_TOKEN_ATTR:public BASE_ATTR{

public:
    AST_TOKEN_ATTR& operator=(const AST_TOKEN_ATTR& other);
    void add_string(TOKEN tk);
    void add_string(AST_TOKEN tk);
    void add_string_to_front(TOKEN_CONTAIN_STR str);
private:

};

#endif