#include "gps.h"
gps::gps(int _number)
{
	conn = get_connector();
}

gps::~gps()
{}

int gps::get_gps_information(Loc_m& loc)
{
	std::string time = get_time();
	std::string sql = "select loc_time from gps where gps_number="+loc.GPS_number+""
	handle.sql_select(sql);
    while(sql_handle.resultSet->next())
    {
        try
        {
            loc.Lng = sql_handle.resultSet->getString(2);
            loc.Lat = sql_handle.resultSet->getString(3);
            loc.Time = sql_handle.resultSet->getString(4);
        }
        catch (std::exception e)
        {
            std::cout<<e.what();
        }
    }
	
	return 0;//return error message
}

int gps::get_gps_orbit_information(Loc_m* loc, std::string begin_time,std::string end_time)
{
	std::string sql = "select loc_time form gps where ~~(time duration)";
}
int gps::get_worning_information(const Loc_m &loc ,std::string& worning_message)
{
	std::string sql = "select worning form woring_message where gps_number="+loc.GPS_number+"";
    sql_handle.sql_select(sql);
    while (sql_handle.resultSet->next())
    {
        try
        {
            loc.Worning = sql_hanle.resultSet->getString(1);
        }
        catch (std::exception e)
        {
            std::cout<<e.what();
        }
    }
	return 0;
}

bool gps::set_gps_information(Loc_m &loc)
{

}

bool gps::set_worning_information(Loc_m &loc)
{}

bool gps::call_client_worning_message()
{}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
