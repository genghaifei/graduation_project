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

constexpr hash_t hash_compile_time(char const* str, hash_t last_value = basis)
{
    return *str ? hash_compile_time(str+1,(*str ^ last_value) * prime) : last_value ;
}

void print_log(const std::string &message)
{
    int fd = open("/home/graduation_project/src/log_file",O_RDWR|O_CREAT| O_APPEND,S_IRWXU);
    if (fd  == -1)
    {
        perror("open error");
        return;
    }
    int numbers = write(fd,message.c_str(),strlen(message.c_str()));
    if (numbers == -1)
    {
        perror("write error");
        return ;
    }
    close(fd);
}

constexpr unsigned long long operator "" _hash(char const* p,size_t)
{
    return hash_compile_time(p);
}
