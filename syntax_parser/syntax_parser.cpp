#include "include/syntax_parser.hpp"

#include <my_exception.hpp>
#include <stdexcept>
#include <assert.h>



void SYNTAX_PARSER::program(std::shared_ptr<TOKEN_LIST> ptl)
{
    TOKEN_LIST_PTR tlp=ptl.get()->begin();
    TOKEN_LIST_INDEX TLI=0;
    static LOOP_VALUE_CHECKER LVC(TLI,2);
    while(tlp!=ptl.get()->end()){
        match_main(ptl,tlp,TLI).show();
        LVC.checkpoint(TLI);
    }
}

AST_TOKEN SYNTAX_PARSER::match_main(std::shared_ptr<TOKEN_LIST> &ptl, TOKEN_LIST_PTR &tlp, TOKEN_LIST_INDEX &TLI)
{
    TOKEN_LIST_ACTUAL_PTR ptr=ptl.get();
    AST_TOKEN astt;
    astt.token_gen(ast_token_type::DIR);
    switch((*tlp).get_token_type()){
        case token_type::RESERVER:
        {
            astt.AST_LIST_append_to_end(match<ast_token_type::FUNC>(ptl,tlp,TLI));
            break;
        }
        case token_type::FINAL:
        {
            NEXT(tlp);
            INC(TLI);
            break;
        }
    }
    return astt;
}

