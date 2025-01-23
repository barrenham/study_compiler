#include "include/text_parser.hpp"
#include "syntax_parser.hpp"
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
    std::shared_ptr<TOKEN_LIST> container=tp.program(fileContent.c_str());
    // for(const auto& item: *(container.get())){
    //     item.show();
    // }
    SYNTAX_PARSER sp;
    sp.program(container);
    return 0;
}