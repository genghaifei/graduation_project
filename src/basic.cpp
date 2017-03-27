#include "basic.h"


hash_t hash_(char const* str)
{
    hash_t ret{basis}; //   C++11 features  use {} to  initialize the variable  it can't happen  type conversion
    while (*str)
    {
        ret ^= *str;
        ret *= prime;
        str++;
    }
    return ret;
}

constexpr hash_t hash_compile_time(char const* str,hash_t last_value = basis)
{
    return *str ? hash_compile_time(str+1,(*str ^ last_value) * prime) : last_value ;
}

constexpr unsigned long long operator "" _hash(char const* p,size_t)
{
    return hash_compile_time(p);
}
