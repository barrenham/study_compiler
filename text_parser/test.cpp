#include "include/text_parser.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

int main(){
    TEXT_PARSER tp;
    std::ifstream ifs("program.txt", std::ios_base::in);
    std::string content;
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string fileContent = buffer.str(); 
    tp.program(fileContent.c_str());
    return 0;
}