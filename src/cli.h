#ifndef  __CLI_H_
#define  __CLI_H_

#include <exception>
#include <stdexcept>
#include <iostream>
#include "basic.h"
#include "my_sql.h"
#include <vector>


class cli
{
    public:
        cli();
        ~cli();
    public:
        int register_person_information(const PERSON &);
        int register_car_information(const CAR &);
    public:
        void get_gps_information(LOCATION &loc,const std::string &GPS_number);
        void get_person_information(PERSON &per,const std::string &);
        void get_car_information(CAR &car,const std::string&);
        bool test_sign_in_information(const COUNT &count);//sign in test
        void display_worning_information(CAR &,const WORN &);
        void confirm_worning_information();
    private:
       // void get_database_connector();construction function write
        void set_gps_information(const LOCATION &);
        void set_car_information(const CAR &);
    private:
        sql_connector sql_handle;
        int cli_id;
        std::vector<LIST_IN> list;
};


#endif  //__CLI_H_

