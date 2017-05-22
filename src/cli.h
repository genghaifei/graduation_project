#ifndef  __CLI_H_
#define  __CLI_H_

#include <iosteam>
#include "basic.h"
#include "mysql/sql_connect.h"
#include <vector>


class cli
{
    public:
        cli();
        ~cli();
    public:
        int register_person_information();
        int register_car_information();
    public:
        void get_gps_information(LOCATION loc);
        void get_person_information(PERSON per);
        void get_car_information(CAR car);
        void test_sign_in_information();//sign in test
        void dispaly_worning_information();
        void confirm_worning_information();
    privte:
        void get_database_connector();
        void set_gps_information();
        void set_person_information();
        void set_car_information();
        void mix_worning_information();
    private:
        
        int cli_id;
        std::vector<LIST> list;
};


#endif  //__CLI_H_

