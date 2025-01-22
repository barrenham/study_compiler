#ifndef GENERAL_TYPE_HPP
#define GENERAL_TYPE_HPP

#include<string>

#define     FIN     '$'
#define     CTYPE_STR_END   '\0'
#define     PASS            do{}while(0)

#define     MAX_RTOKEN_TYPE 32
#define     RTOKEN_MAX_LEN  20

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

#endif