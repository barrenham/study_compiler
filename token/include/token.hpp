#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <exception>
#include "general_type.hpp"
#include "base_attr.hpp"

typedef     std::list<TOKEN>       TOKEN_LIST;
typedef     TOKEN_LIST*            TOKEN_LIST_ACTUAL_PTR;
typedef     TOKEN_LIST::iterator   TOKEN_LIST_PTR;
typedef     TOKEN_LIST::iterator   TOKEN_LIST_BEGIN;
typedef     TOKEN_LIST::iterator   TOKEN_LIST_END;
typedef     long long              TOKEN_LIST_INDEX;

typedef     std::list<AST_TOKEN>   AST_TOKEN_LIST;

enum class token_type
{
    NOTYPE,
    IDENTIFIER,
    OPERATOR,
    VALUE,
    SEPERATOR,
    RESERVER,
    NOTE,
    STRING,
    FINAL,
    AST_TYPE
};

enum class reserver_type{
    INT,
    CHAR,
    VOID,
    STRING,
    NOT_RESERVER_TYPE
};

enum class ast_token_type{
    NOTYPE,
    FUNC,
    EXPRESSION,
    DIR,
};


class TOKEN{
public:
    TOKEN():type(token_type::NOTYPE),rtype(),attribute(){}
    token_type get_token_type() const;
    TOKEN_CONTAIN_STR get_attribute() const;
    TOKEN(const TOKEN& other);
    TOKEN& operator=(const TOKEN& other);
    void token_gen(token_type tkt,Serial& s,Serial_begin begin,Serial_end end);
    void set_reserver_type(reserver_type rtype);
    void show() const;
private:
    void set_token_type(token_type tkt);
    void set_attr(Serial& s,Serial_begin begin,Serial_end end);
    token_type type;
    reserver_type rtype;
    BASE_ATTR  attribute; //该部分可能会修改，用于指代不同的TOKEN
};

class AST_TOKEN:public TOKEN{
public:
    AST_TOKEN():TOKEN::TOKEN(),ast_token_attribute(),att(ast_token_type::NOTYPE),ast_token_list(){}
    AST_TOKEN(const TOKEN& token):TOKEN::TOKEN(token),ast_token_attribute(),att(ast_token_type::NOTYPE),ast_token_list() {}
    void token_gen(ast_token_type att,TOKEN tk);
    void token_gen(ast_token_type att);
    void token_gen(ast_token_type att,AST_TOKEN tk);
    void AST_LIST_append_to_front(AST_TOKEN tk);
    void AST_LIST_append_to_front(TOKEN tk);
    void AST_LIST_append_to_end  (TOKEN tk);
    void AST_LIST_append_to_end  (AST_TOKEN tk);
    void AST_LIST_pop_end        ();
    void AST_TOKEN_CONTAIN_STRING_append_to_front(TOKEN_CONTAIN_STR str);
    ast_token_type get_ast_token_type() const;
    TOKEN_CONTAIN_STR get_attribute() const;
    AST_TOKEN(const AST_TOKEN&other) ;
    AST_TOKEN& operator=(const AST_TOKEN& other) ;
    void show() const;
private:
    AST_TOKEN_ATTR ast_token_attribute;
    ast_token_type att;
    AST_TOKEN_LIST ast_token_list;
};



class RTOKEN_CHECKER{
public:
    reserver_type check(Serial& s,Serial_begin begin,Serial_end end);
    bool CMP_string(const Serial& s1,Serial_begin begin_s1,Serial_end end_s1,
                    const Serial& s2,Serial_begin begin_s2,Serial_end end_s2);
private:
    static const char rtoken_table[MAX_RTOKEN_TYPE][RTOKEN_MAX_LEN];
};


#endif