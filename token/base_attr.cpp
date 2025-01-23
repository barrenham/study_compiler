#include "include/base_attr.hpp"
#include "base_attr.hpp"
#include "token.hpp"

void BASE_ATTR::addchar(char c){
    inside_str.push_back(c);
}

void BASE_ATTR::addstring(TOKEN_CONTAIN_STR str)
{
    inside_str+=str;
    inside_str+='#';
}

void BASE_ATTR::add_string_to_front(TOKEN_CONTAIN_STR str)
{
    inside_str='#'+inside_str;
    inside_str=str+inside_str;
}

BASE_ATTR& BASE_ATTR::operator=(const BASE_ATTR& other){
    if(this!=&other){
        inside_str=other.inside_str;
    }
    return *this;
}

void BASE_ATTR::show_contain_str() const{
    printf("%s",inside_str.c_str());
}

TOKEN_CONTAIN_STR BASE_ATTR::get_contain_str() const
{
    return inside_str;
}

void AST_TOKEN_ATTR::add_string(TOKEN tk)
{
    AST_TOKEN_ATTR::BASE_ATTR::addstring(tk.get_attribute());
}

void AST_TOKEN_ATTR::add_string(AST_TOKEN tk)
{
    AST_TOKEN_ATTR::BASE_ATTR::addstring(tk.get_attribute());
}

void AST_TOKEN_ATTR::add_string_to_front(TOKEN_CONTAIN_STR str)
{
    AST_TOKEN_ATTR::BASE_ATTR::add_string_to_front(str);
}

AST_TOKEN_ATTR& AST_TOKEN_ATTR::operator=(const AST_TOKEN_ATTR& other) 
{
    if(this!=&other){
        BASE_ATTR::operator=(other);
    }
    return *this;
}