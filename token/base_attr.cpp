#include "include/base_attr.hpp"

void BASE_ATTR::addchar(char c){
    inside_str.push_back(c);
}

void BASE_ATTR::show_contain_str() const{
    printf("%s",inside_str.c_str());
}