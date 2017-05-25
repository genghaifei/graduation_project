#include "cli.h"

cli::cli()
{
    sql::Connection *con = NULL;
    driver = sql::mysql::get_mysql_driver_instance();
    if (driver == NULL)
}

cli::~cli()
{}

int cli::register_person_information(PERSON per)
{
    std::string sql = "insert into ID_message VALUES ('"+per.Name+"','"+per.ID+"','"+per.Sex+"','"+per.Address+"','"+per.Tel+"','"+per.E_mail+"','"+per.Client_id+"')";
    if (!conn.sql_insert(sql))
    {
        return -1;
    }
    return 0;
}

int register_car_information(CAR car)
{
    std::string sql = "insert into Car_message VALUES ('"+car.ID+"','"+car.Car_GPS_number+"','"+car.Car_brand+"','"+car.Car_number+"','"+car.VIN_number+"','"+car.Car_type+"','"+car.Car_buy_time+"','"+car.Car_color+"')";
    if (! conn.sql_insert(sql))
    {
        return -1;
    }
    return 0;
}

void cli::get_gps_information(PERSON* per , sql_connector conn)
{
    std::string ID = per->ID;
    std::string sql = "select Car_GPS_number form Car_message where ID = '"+ID+"'"
    conn.sql_select(sql);
}


















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
