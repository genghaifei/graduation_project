#include <iostream>
#include <stdint.h> //uint64_t 
#include "json.h"
typedef uint64_t hash_t;  //uint64_t == unsigned long long

constexpr hash_t prime = 0x1000000001B3ull;   //ull == unsigned long long 
constexpr hash_t basis = 0xCBF29CE484222325ull;

hash_t hash_(char const* str);
constexpr hash_t hash_compile_time(char const* str,hash_t last_value);

constexpr unsigned long long operator "" _hash(char const* p,size_t);

struct PERSON
{
    std::string Name;
    std::string ID;
    std::string Sex;
    std::string Address;
    std::string Tel;
    std::string E_mail;
    std::string Client_id;
};

struct CAR
{
    std::string ID;
    std::string GPS_number;
    std::string Car_brand;
    std::string Car_number;
    std::string Car_VIN_number;
    std::string Car_type;
    std::string Car_buy_time;
    std::string Car_color;
};

struct COUNT
{
    std::string ID;
    std::string passwd;
};

struct LOCATION
{
    std::string GPS_number;
    std::string Lng;
    std::string Lat;
    std::string Time;
};

struct WORN
{
    LOCATION loc;
    std::string Worning;
};

struct LIST_IN
{
    CAR car;
    PERSON person;
    WORN worn;
    LOCATION loc;
};

#define BUFFER_SIZE 1024

const std::string _host("");
const std::string _usr("");
const std::string _passwd("");
const std::string _db("");
