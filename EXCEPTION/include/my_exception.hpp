#ifndef MY_EXCEPTION_HPP
#define MY_EXCEPTION_HPP

#include <exception>
#include <stdexcept>
#include <source_location>
#include "general_type.hpp"

class noType{};

template<class T>
class LOOP_VALUE_CHECKER{
public:
    typedef long long TIMER;
    LOOP_VALUE_CHECKER(T loop_value=noType(),Loopback_limit cnt=100) :limit(cnt),timer(0),prev_loop_value(loop_value) {
        if(typeid(T)==typeid(noType)){
            throw std::runtime_error("LOOP_VALUE_CHECKER FIRST ARGS SHOULD NOT BE noType!");
        }
        
        PASS;
    }
    inline void checkpoint(T loop_value,std::source_location location = std::source_location::current());
    void setcheckpoint(T loop_value,Loopback_limit cnt);
private:
    #define INC(value) ((value)++)
    #define ZERO(value) ((value)=0)
    Loopback_limit limit;
    TIMER timer;
    T   prev_loop_value;
    bool have_set_loop;
};

template <class T>
void LOOP_VALUE_CHECKER<T>::checkpoint(T loop_value,std::source_location location)
{
    if(loop_value==prev_loop_value){
        INC(timer);
    }else{
        prev_loop_value=loop_value;
        ZERO(timer);
    }

    if(timer>limit){
        char buf[500];
        snprintf(buf,
                450,
                "EXCEED Time Limit! \n[\ncalling func: %20s \nline: %20d \nfile: %50s\n]",
                location.function_name(),
                location.line(),
                location.file_name()
                );
        throw std::runtime_error(buf);
    }
}
template<class T>
void LOOP_VALUE_CHECKER<T>::setcheckpoint(T loop_value, Loopback_limit cnt)
{
    this.loop_value=loop_value;
    limit=cnt;
}


#endif
