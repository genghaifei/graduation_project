#include "basic.h"
#include "my_sql.h"

class pli
{
    public:
        pli();
        ~pli();
    public:
        int register_pli_information(const POLICEMAN &);
        bool test_sign_in_information(const COUNT &);
        int get_gps_information();
        int get_person_information();
        int get_car_information();
        int get_worning_information();
        int begin_dealWith_worning_information(POLICEMAN &,CAR &,PERSON &);
        int end_dealWith_worning_information(PERSON &,CAR &); 
    private:
        sql_connector sql_handle;
        int pli_id;
};
