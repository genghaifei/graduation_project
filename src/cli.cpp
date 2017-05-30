#include "cli.h"


cli::cli()
{
    sql_handle.begin_connect();
    sql_handle.sql_init();
}

cli::~cli()
{

}

int cli::register_person_information(const PERSON &per)
{
    std::string sql = "insert into ID_message VALUES ('"+per.Name+"','"+per.ID+"','"+per.Sex+"','"+per.Address+"','"+per.Tel+"','"+per.E_mail+"','"+per.Client_id+"')";
    int ret = sql_handle.sql_insert(sql);
    if (ret != 0)
    {
        return -1;
    }
    return 0;
}

int cli::register_car_information(const CAR &car)
{
    std::string sql = "insert into Car_message VALUES ('"+car.ID+"','"+car.GPS_number+"','"+car.Car_brand+"','"+car.Car_number+"','"+car.Car_VIN_number+"','"+car.Car_type+"','"+car.Car_buy_time+"','"+car.Car_color+"')";
    int ret = sql_handle.sql_insert(sql);
    if (ret != 0)
    {
        return -1;
    }
    return 0;
}

void cli::get_gps_information(LOCATION &loc,const std::string &GPS_number)
{
    std::string sql = "select * from Location_message where GPS_number='"+GPS_number+"'";
    sql_handle.sql_select(sql);
    loc.GPS_number = GPS_number;
    while(sql_handle.resultSet->next())
    {
        try{
             loc.Lng = sql_handle.resultSet->getString(2);
             loc.Lat = sql_handle.resultSet->getString(3);
             loc.Time = sql_handle.resultSet->getString(4);
            }
        catch (std::exception e)
        {
            std::cout<<e.what();
        }
    }
}

void cli::get_person_information(PERSON &per,const std::string &ID)
{
    std::string sql = "select * from ID_message where ID='"+ID+"'";
    sql_handle.sql_select(sql);
    per.ID = ID;
    while(sql_handle.resultSet->next())
    {
        try{
            per.Name = sql_handle.resultSet->getString(1);
            per.Sex = sql_handle.resultSet->getString(3);
            per.Address = sql_handle.resultSet->getString(4);
            per.Tel = sql_handle.resultSet->getString(5);
            per.E_mail = sql_handle.resultSet->getString(6);
            per.Client_id = sql_handle.resultSet->getString(7);
        }
        catch(std::exception e)
        {
            std::cout<<e.what();
        }

    }
}

void cli::get_car_information(CAR &car,const std::string &ID)
{
    std::string sql = "select * from Car_message where ID='"+ID+"'";
    sql_handle.sql_select(sql);
    car.ID = ID;
    while(sql_handle.resultSet->next())
    {
        try{   
            car.GPS_number = sql_handle.resultSet->getString(2);
            car.Car_brand = sql_handle.resultSet->getString(3);
            car.Car_number = sql_handle.resultSet->getString(4);
            car.Car_VIN_number = sql_handle.resultSet->getString(5);
            car.Car_type = sql_handle.resultSet->getString(6);
            car.Car_buy_time = sql_handle.resultSet->getString(7);
            car.Car_color = sql_handle.resultSet->getString(8);
        }
        catch(std::exception e)
        {
            std::cout<<e.what();
        }
    }
}

bool cli::test_sign_in_information(const COUNT &count)
{
    std::string sql = "select passwd from ID_message where ID='"+count.ID+"'";
    sql_handle.sql_select(sql);
    while(sql_handle.resultSet->next())
    {
        try{
            std::string passwd = sql_handle.resultSet->getString(2);
            if (passwd.compare(count.passwd) == 0)
            {
                return true;
            }
        }
        catch (std::exception e)
        {
            std::cout<<e.what();
        }
    }
    return false;
}

void cli::display_worning_information(CAR &car, const WORN &worn)//gps function call ,take all the gps information
{
    std::string sql = "select * form Car_message where GPS_number='"+worn.loc.GPS_number+"'";
    sql_handle.sql_select(sql);
    car.GPS_number = worn.loc.GPS_number;
    while(sql_handle.resultSet->next())
    {
        try{
            car.ID  = sql_handle.resultSet->getString(1);
            car.Car_brand  = sql_handle.resultSet->getString(3);
            car.Car_number  = sql_handle.resultSet->getString(4);
            car.Car_VIN_number  = sql_handle.resultSet->getString(5);
            car.Car_type  = sql_handle.resultSet->getString(6);
            car.Car_buy_time  = sql_handle.resultSet->getString(7);
            car.Car_color  = sql_handle.resultSet->getString(8);
        }
        catch(std::exception e)
        {
            std::cout<<e.what();
        }

    }
    //how to do it   how to solove it 
}

void cli::confirm_worning_information()
{
}

void cli::set_gps_information(const LOCATION &loc)
{
    std::string sql = "insert into Location_message values ('"+loc.GPS_number+"','"+loc.Lng+"','"+loc.Lat+"','"+loc.Time+"')";
    sql_handle.sql_insert(sql);
}

void cli::set_car_information(const CAR &car)
{
    std::string sql = "insert into Car_message values ('"+car.ID+"','"+car.GPS_number+"','"+car.Car_brand+"','"+car.Car_number+"','"+car.Car_VIN_number+"','"+car.Car_type+"','"+car.Car_buy_time+"','"+car.Car_color+"')";
    sql_handle.sql_insert(sql);
}












/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */












/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
