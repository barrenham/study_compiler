#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <exception>
#include "general_type.hpp"
#include "base_attr.hpp"

enum class token_type
{
    IDENTIFIER,
    OPERATOR,
    VALUE,
    SEPERATOR,
    RESERVER,
    NOTE,
    STRING,
    FINAL
};


class TOKEN{
public:
    token_type get_token_type() const;
    void token_gen(token_type tkt,Serial& s,Serial_begin begin,Serial_end end);
    void show() const;
private:
    void set_token_type(token_type tkt);
    void set_attr(Serial& s,Serial_begin begin,Serial_end end);
    token_type type;
    BASE_ATTR  attribute; //该部分可能会修改，用于指代不同的TOKEN
};

enum class reserver_type{
    INT,
    CHAR,
    VOID,
    STRING,
    NOT_RESERVER_TYPE
};

class RTOKEN_CHECKER{
public:
    reserver_type check(Serial& s,Serial_begin begin,Serial_end end);
    bool CMP_string(const Serial& s1,Serial_begin begin_s1,Serial_end end_s1,
                    const Serial& s2,Serial_begin begin_s2,Serial_end end_s2);
private:
    static const char rtoken_table[MAX_RTOKEN_TYPE][RTOKEN_MAX_LEN];
};

class RESERVE_TOKEN:public TOKEN{
public:
    void set_reserver_type(reserver_type rtype);
private:
    reserver_type rtype;
};


#endif