#ifndef BASE_ATTR_HPP
#define BASE_ATTR_HPP

#include<string>

typedef std::string TOKEN_CONTAIN_STR;

class BASE_ATTR{

public:
    //TODO: 创建具体方法，获取private 数据
    void addchar(char c);
    void show_contain_str() const;
private:
    //TODO: 创建具体变量，用于表示TOKEN基础属性(共有部分)
    TOKEN_CONTAIN_STR inside_str;
};

#endif