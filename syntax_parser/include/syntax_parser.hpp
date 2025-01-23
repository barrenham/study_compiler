#ifndef SYNTAX_PARSER_HPP
#define SYNTAX_PARSER_HPP

#include <memory>
#include <string>
#include <list>
#include <tuple>
#include <functional>

#include "general_type.hpp"
#include "text_parser.hpp"
#include "token.hpp"




class SYNTAX_PARSER{
public:
    void program(std::shared_ptr<TOKEN_LIST> ptl);
    AST_TOKEN match_main(std::shared_ptr<TOKEN_LIST>&ptl, TOKEN_LIST_PTR&tlp,TOKEN_LIST_INDEX&TLI);
    template<ast_token_type ATT>
    AST_TOKEN match(std::shared_ptr<TOKEN_LIST>&ptl, TOKEN_LIST_PTR&tlp, TOKEN_LIST_INDEX&TLI,INDEX index=0);
private:
    #define INC(value) ((value)++)
    #define NEXT(value) (INC(value))
    #define DEC(value)  ((value)--)
    #define PREV(value) (DEC(value))
    static constexpr  STEP_CNT func_step_cnt=6;
};

template<ast_token_type ATT>
class SYNTAX_TABLE{
public:
    static std::tuple<token_type,TRUE_CHOICE,FALSE_CHOICE> step[SYNTAX_MAX_STEP][SYNTAX_MAX_FIRSTSIGN];
};

template<>
inline std::tuple<token_type,TRUE_CHOICE,FALSE_CHOICE> SYNTAX_TABLE<ast_token_type::FUNC>::step[SYNTAX_MAX_STEP][SYNTAX_MAX_FIRSTSIGN]=
{
    {std::make_tuple(token_type::RESERVER,1,SYNTAX_FALSE)},
    {std::make_tuple(token_type::IDENTIFIER,2,SYNTAX_FALSE)},
    {std::make_tuple(token_type::SEPERATOR,3,SYNTAX_FALSE)},
    {std::make_tuple(token_type::SEPERATOR,4,SYNTAX_FALSE)},
    {std::make_tuple(token_type::SEPERATOR,5,SYNTAX_FALSE)},
    {std::make_tuple(token_type::SEPERATOR,SYNTAX_TRUE,SYNTAX_NEXT_ONE),std::make_tuple(token_type::RESERVER,SPECIAL,SYNTAX_FALSE)}
};

template<>
inline std::tuple<token_type,TRUE_CHOICE,FALSE_CHOICE> SYNTAX_TABLE<ast_token_type::EXPRESSION>::step[SYNTAX_MAX_STEP][SYNTAX_MAX_FIRSTSIGN]=
{
    {std::make_tuple(token_type::RESERVER,1,SYNTAX_FALSE)},
    {std::make_tuple(token_type::IDENTIFIER,2,SYNTAX_FALSE)},
    {std::make_tuple(token_type::SEPERATOR,3,SYNTAX_FALSE)},
    {std::make_tuple(token_type::SEPERATOR,4,SYNTAX_FALSE)},
    {std::make_tuple(token_type::SEPERATOR,5,SYNTAX_FALSE)},
    {std::make_tuple(token_type::SEPERATOR,SYNTAX_TRUE,SYNTAX_FALSE),std::make_tuple(token_type::RESERVER,SPECIAL,SYNTAX_FALSE)}
};


template <ast_token_type ATT>
inline AST_TOKEN SYNTAX_PARSER::match(std::shared_ptr<TOKEN_LIST> &ptl, TOKEN_LIST_PTR &tlp, TOKEN_LIST_INDEX &TLI, INDEX index)
{   
    AST_TOKEN_LIST saved_token_list;
    AST_TOKEN astt;
    STEP_CNT i=index;

    std::function<bool(AST_TOKEN)> check=
    [](AST_TOKEN astt)->bool
    {return astt.get_ast_token_type()!=ast_token_type::NOTYPE;};
loop_back:
    INDEX j=0;
    while(i!=SYNTAX_TRUE&&std::get<0>(SYNTAX_TABLE<ATT>::step[i][j])!=token_type::NOTYPE){
        astt=AST_TOKEN();
        if((*tlp).get_token_type()==std::get<0>(SYNTAX_TABLE<ATT>::step[i][j])){
            auto tlp_bat=tlp;
            STEP_CNT i_bat=i;
            i=get<TRUE_NEXT>(SYNTAX_TABLE<ATT>::step[i][j]);
            if(i==SYNTAX_TRUE){
                astt.token_gen(ATT,(*(tlp)));
                if(!saved_token_list.empty()){
                    for(auto& item:saved_token_list)
                    {
                        astt.AST_LIST_append_to_front(item);
                    }
                }
                NEXT(tlp);
                INC(TLI);
                return astt;
            }
            if(i==SPECIAL){
                saved_token_list.push_front(match_main(ptl,tlp,TLI));
                i=i_bat;
                j=0;
                goto loop_back;
            }
            NEXT(tlp);
            INC(TLI);
            auto check_tmp=match<ATT>(ptl,tlp,TLI,i);
            if(check(check_tmp)){
                astt=check_tmp;
                if(!saved_token_list.empty()){
                    for(auto& item:saved_token_list)
                    {
                        astt.AST_LIST_append_to_front(item);
                    }
                }
                astt.AST_LIST_append_to_front(*tlp_bat);
                return astt;
            }else{
                PREV(tlp);
                DEC(TLI);
                i=i_bat;
            }
        }else{
            auto tmp_value=get<FALSE_NEXT>(SYNTAX_TABLE<ATT>::step[i][j]);
            if(tmp_value!=SYNTAX_FALSE){
                PASS;
            }else{
                return astt;
            }
        }
        j++;
    }
    return astt;
}

#endif