#ifndef GENERAL_TYPE_HPP
#define GENERAL_TYPE_HPP

#include <string>
#include <list>

#define     FIN     '$'
#define     CTYPE_STR_END   '\0'
#define     PASS            do{}while(0)

#define     MAX_RTOKEN_TYPE 32
#define     RTOKEN_MAX_LEN  20
#define     SYNTAX_MAX_FIRSTSIGN    60
#define     SYNTAX_MAX_STEP         40

#define     SYNTAX_FALSE    -1
#define     SYNTAX_TRUE     -2
#define     SPECIAL         -3
#define     SYNTAX_NEXT_ONE -4

#define     TRUE_NEXT       1
#define     FALSE_NEXT      2

typedef     long long       STR_POS;
typedef     const char*     Serial;
typedef     long long       Serial_begin;
typedef     long long       Serial_ptr;
typedef     long long       Serial_end;
typedef     long long       Loopback_limit;
typedef     std::string     CALLING_FUNC_NAME;
typedef     long long       RTOKEN_PTR;
typedef     long long       STR_LEN;
typedef     long long       loop_number;
typedef     long long       STEP_CNT;
typedef     long long       TRUE_CHOICE;
typedef     long long       FALSE_CHOICE;
typedef     long long       INDEX;

#endif