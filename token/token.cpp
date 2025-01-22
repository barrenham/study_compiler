#include "include/token.hpp"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "token.hpp"


void TOKEN::token_gen(token_type tkt,Serial& s,Serial_begin begin,Serial_end end)
{
    set_token_type(tkt);
    set_attr(s,begin,end);
}

void TOKEN::set_token_type(token_type tkt)
{
    type=tkt;
}

void TOKEN::set_attr(Serial& s,Serial_begin begin,Serial_end end) //attr.content= s[begin:end]
{
    for(STR_POS i=begin;i<=end;i++)
    {
        attribute.addchar(s[i]);
    }
}

void TOKEN::show() const{
    printf("<");
    printf("token_type:");
    switch(type)
    {
        case token_type::VALUE:
        {
            printf("%10s","VALUE");
            break;
        }
        case token_type::IDENTIFIER:
        {
            printf("%10s","IDENTIFIER");
            break;
        }
        case token_type::OPERATOR:
        {
            printf("%10s","OPERATOR");
            break;
        }
        case token_type::SEPERATOR:
        {
            printf("%10s","SEPERATOR");
            break;
        }
        case token_type::RESERVER:
        {
            printf("%10s","RESERVER");
            break;
        }
        case token_type::NOTE:
        {
            printf("%10s","NOTE");
            break;
        }
        case token_type::STRING:
        {
            printf("%10s","STRING");
            break;
        }
        case token_type::FINAL:
        {
            printf("%10s","FINAL");
            break;
        }
    }
    printf("\n");
    printf("content:");
    attribute.show_contain_str();
    printf(">");
    printf("\n");
}
void RESERVE_TOKEN::set_reserver_type(reserver_type rtype)
{
    this->rtype=rtype;
}

const char RTOKEN_CHECKER::rtoken_table[MAX_RTOKEN_TYPE][RTOKEN_MAX_LEN]=
{
    "int",
    "char",
    "void",
    "string",
    0
};

reserver_type RTOKEN_CHECKER::check(Serial &s, Serial_begin begin, Serial_end end)
{
    RTOKEN_PTR  idx=0;
    STR_LEN     len=(end-begin+1);
    while(idx<MAX_RTOKEN_TYPE&&(strlen(rtoken_table[idx])<len)){
        idx++;
    }
    while(idx<MAX_RTOKEN_TYPE&&(strlen(rtoken_table[idx])==len)){
        if(CMP_string(s,begin,end,rtoken_table[idx],0,len-1)){
            return static_cast<reserver_type>(idx);
        }
        idx++;
    }
    return reserver_type::NOT_RESERVER_TYPE;
}

bool RTOKEN_CHECKER::CMP_string(const Serial &s1, Serial_begin begin_s1, Serial_end end_s1, const Serial &s2, Serial_begin begin_s2, Serial_end end_s2)
{
    STR_LEN len_s1=(end_s1-begin_s1+1);
    STR_LEN len_s2=(end_s2-begin_s2+1);
    if(len_s1!=len_s2){
        return false;
    }else{
        Serial_ptr idx_s1=begin_s1;
        Serial_ptr idx_s2=begin_s2;
        for(loop_number i=0;i<len_s1;i++){
            if(s1[idx_s1]!=s2[idx_s2]){
                return false;
            }
            idx_s1++;
            idx_s2++;
        }
    }
    return true;
}
