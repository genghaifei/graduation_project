#include "pli.h"

pli::pli()
{}

pli::~pli()
{}

int pli::register_pli_information(const POLICEMAN &pli_man)
{
    std::string sql = "insert into POLICE_message VALUES ('"+pli_man.Name+"','"+pli_man.Number+"','"+pli_man.Sex+"','"+pli_man.Age+"','"+pli_man.Location+"','"+pli_man.Tel+"')";
    int ret = sql_handle.sql_insert(sql);
    if (ret != 0)
    {
        return -1;
    }
    return 0;
}

bool pli::test_sign_in_information(const COUNT &cou)
{
    std::string sql = "select passwd form POLICE_message where ID='"+cou.ID+"'";
    sql_handle.sql_select(sql);
    std::string passwd;
    while(sql_handle.resultSet->next())
    {
        try{
            passwd = sql_handle.resultSet->getString(2);
        }
        catch (std::exception e)
        {
            std::cout<<e.what();
        }
    }
    Json::Value root;
    if (passwd.compare(cou.passwd) == 0)
    {
        root["status"] = "YES";
    }
    else
    {
        root["status"] = "NO";
    }
    std::string out = root.toStyledString();
    send(sock_client,out.c_str(),strlen(out.c_str()),0);
}

int pli::get_gps_information()
{}

int pli::get_person_information()
{}

int pli::get_car_information()
{}

int pli::get_worning_information()
{}

int pli::begin_dealWith_worning_information(POLICEMAN &police,CAR &car,PERSON &per)
{
    std::string sql = "select * from POLICEMAN_message where Number="+police.number+"";
    sql_handle.sql_select(sql);
    while(sql_handle.resultSet->next())
    {
        try
        {
            police.Name = sql_handle.resultSet->getString(1);
            police.Sex = sql_handle.resultSet->getString(3);
            police.Age = sql_handle.resultSet->getString(4);
            police.Location = sql_handle.resultSet->getString(5);
            police.Tel = sql_handle.resultSet->getString(6);

        }
        catch (std::exception e)
        {
            std::cout<<e.what();
        }
    }
    car.status = "FOUNDING";
    //push 
    //car number person ID  police man information
}

int pli::end_dealWith_worning_information(PERSON &per,CAR &car)
{
    //push
    //car number per ID 
}

