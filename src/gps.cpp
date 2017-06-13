#include "gps.h"
Gps::Gps()
{
    handle.begin_connect();
    handle.sql_init();
}

Gps::~Gps()
{}

bool Gps::get_gps_information(Loc_m& loc)
{
	std::string sql = "select loc_time from gps where gps_number="+loc.GPS_number+"";
	handle.sql_select(sql);
    while(handle.resultSet->next())
    {
        try
        {
            loc.Lng = handle.resultSet->getString(2);
            loc.Lat = handle.resultSet->getString(3);
            loc.Time = handle.resultSet->getString(4);
        }
        catch (std::exception e)
        {
            std::cout<<e.what();
        }
    }
	
	return true;//return error message
}

int Gps::get_gps_orbit_information(Loc_m* loc, std::string begin_time,std::string end_time)
{
	std::string sql = "select loc_time form gps where ~~(time duration)";
}
int Gps::get_worning_information(WORN &worn)
{
	std::string sql = "select worning form woring_message where gps_number="+worn.loc.GPS_number+"";
    handle.sql_select(sql);
    while (handle.resultSet->next())
    {
        try
        {
            worn.Worning = handle.resultSet->getString(1);
        }
        catch (std::exception e)
        {
            std::cout<<e.what();
        }
    }
	return 0;
}

bool Gps::set_gps_information(Loc_m &loc)
{
    
}

bool Gps::set_worning_information(WORN &worn)
{
    // push the worning  message to the platform;
}

bool Gps::call_client_worning_message()
{}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
