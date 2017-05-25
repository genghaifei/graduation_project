#include "basic.h"

class pli
{
    public:
        pli();
        ~pli();
    public:
        int register_pli_information();
        int test_sign_in_information();
        int get_gps_information();
        int get_person_information();
        int get_car_information();
        int get_worning_information();
        int set_worn_response_information();
    private:
        sql::mysql::MySQL_Driver *driver;
        int pli_id;
};
