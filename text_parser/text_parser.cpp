#include "include/text_parser.hpp"
#include "my_exception.hpp"
#include "text_parser.hpp"

bool TEXT_PARSER::isDigit(char c)
{
    return ((c>='0')&&(c<='9'));
}

bool TEXT_PARSER::isAlpha(char c)
{
    return (((c>='a')&&(c<='z'))||((c>='A')&&(c<='Z')));
}
bool TEXT_PARSER::isSpace(char c)
{
    return (c==' ');
}

bool TEXT_PARSER::isDot(char c)
{
    return (c=='.');
}

bool TEXT_PARSER::isSep(char c)
{
    return ((c==';')||(c=='}')||(c=='{')||(c==',')||(c=='[')||(c==']')
    ||(c=='(')||(c==')')||(c==':')||(c=='.'));
}

bool TEXT_PARSER::isOp(char c)
{
    return ((c=='+')||(c=='-')||(c=='*')||(c=='/')||(c=='=')||(c=='%')
    ||(c=='^')||(c=='&')||(c=='|')||(c=='!')||(c=='<')||(c=='>'));
}

bool TEXT_PARSER::isLF(char c)
{
    return (c=='\n');
}

bool TEXT_PARSER::isOcto(char c)
{
    return (c=='#');
}

bool TEXT_PARSER::isCR(char c)
{
    return (c=='\r');
}

bool TEXT_PARSER::isUdl(char c)
{
    return (c=='_');
}

bool TEXT_PARSER::isStrSp(char c)
{
    return (c=='\"');
}

void TEXT_PARSER::program(Serial str)
{
    STR_POS pos=0;
    LOOP_VALUE_CHECKER LVC(pos,1);
    while(str[pos]!=CTYPE_STR_END){
        try{
            TOKEN token=match(str,pos);
            token.show();
            LVC.checkpoint(pos);
        }
        catch(TEXT_PARSER_ERROR_GRAMMAR&e){
            printf("\nERROR:%s\n",e.what());
            return;
        }
    }
}

void TEXT_PARSER::next(STR_POS& pos){
    pos++;
}

TOKEN TEXT_PARSER::match(Serial& str,STR_POS& pos){
    TOKEN item;
    static RTOKEN_CHECKER rtoken_checker;
    while(isSpace(str[pos])||isLF(str[pos])) next(pos);
    //1.[.0-9]+
    if(isDigit(str[pos])){
        Serial_begin begin=pos;
        Serial_end   end  =pos;
        do{
            end=pos;
            next(pos);
        }while(isDigit(str[pos]));
        item.token_gen(token_type::VALUE,str,begin,end);
        // if(str[pos]!=FIN&&!isSpace(str[pos])){
        //     char buf[100];
        //     snprintf(buf,80,"INVALID GRAMMAR of '%c', now in str[%lld:%lld]",str[pos],begin,end);
        //     throw TEXT_PARSER_ERROR_GRAMMAR(buf);
        // }
    }
    //2. '$' FIN
    else if(str[pos]==FIN){
        Serial_begin begin=pos;
        Serial_end   end  =pos;
        next(pos);
        item.token_gen(token_type::FINAL,str,begin,end);
    }
    //3.[a-zA-Z][a-zA-Z0-9_]*
    else if(isAlpha(str[pos])){
        Serial_begin begin=pos;
        Serial_end   end  =pos;
        do{
            end=pos;
            next(pos);
        }while(isAlpha(str[pos])||isDigit(str[pos])||(isUdl(str[pos])));
        
        if(rtoken_checker.check(str,begin,end)!=reserver_type::NOT_RESERVER_TYPE){
            item.token_gen(token_type::RESERVER,str,begin,end);
        }else{
            item.token_gen(token_type::IDENTIFIER,str,begin,end);
        }
        
        // if(str[pos]!=FIN&&!isSpace(str[pos])){
        //     char buf[100];
        //     snprintf(buf,80,"INVALID GRAMMAR of '%c', now in str[%lld:%lld]",str[pos],begin,end);
        //     throw TEXT_PARSER_ERROR_GRAMMAR(buf);
        // }
    }
    //4. Seperator
    else if(isSep(str[pos])){
        Serial_begin begin=pos;
        Serial_end   end  =pos;
        next(pos);
        item.token_gen(token_type::SEPERATOR,str,begin,end);
    }
    //5. Operator
    else if(isOp(str[pos])){
        Serial_begin begin=pos;
        Serial_end   end  =pos;
        next(pos);
        item.token_gen(token_type::SEPERATOR,str,begin,end);
    }
    //6.[#][^\n]*[\n]
    else if(isOcto(str[pos])){
        Serial_begin begin=pos;
        Serial_end   end  =pos;
        do{
            end=pos;
            next(pos);
        }while(!isLF(str[pos]));
        next(pos);
        item.token_gen(token_type::NOTE,str,begin,end);
    }
    //7. STRING: ["][^"]["]
    else if(isStrSp(str[pos])){
        Serial_begin begin=pos;
        Serial_end   end  =pos;
        do{
            end=pos;
            next(pos);
        }while(!isStrSp(str[pos]));
        end=pos;
        next(pos);
        item.token_gen(token_type::STRING,str,begin,end);
    }
    return item;
}