#include <iostream>

typedef std::uint64_t hash_t;  //uint64_t == unsigned long long

constexpr hash_t prime = 0x1000000001B3ull;   //ull == unsigned long long 
constexpr hash_t basis = 0xCBF29CE484222325ull;

hash_t hash_(char const* str);
constexpr hash_t hash_compile_time(char const* str,hash_t last_value = basis);

constexpr unsigned long long operator "" _hash(char const* p,size_t);

