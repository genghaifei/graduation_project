#include "gps.h"
gps::gps(int _number)
{
	gps_number = _number;
	worning_message = "";
	conn = get_connector();
}

gps::~gps()
{}

int gps::get_gps_information(Loc_m& location_message)
{
	std::string time = get_time();
	std::string sql = "select loc_time from gps where gps_number="+itoa(gps_number)+""
	conn.exec_sql(sql);
	location_message.lat = conn.
	location_message.lng = conn
	location_message.time = time;
	
	return 0;//return error message
}

int gps::get_gps_orbit_information(Loc_m* loc, std::string begin_time,std::string end_time)
{
	std::string sql = "select loc_time form gps where ~~(time duration)";
	
}

int gps::get_worning_information(std::string& worning_message)
{
	std::string sql = "select worning form woring_message where gps_number="+itoa(gps_number)+"";
	conn.exec_sql(sql);
	woring_message = conn.
	
	return 0;
}






















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
