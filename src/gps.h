#include <iostream>
#include "basic.h"
#include "my_sql.h"

typedef LOCATION Loc_m;
class gps
{
	public:
	gps(int _number);
	~gps();
	public:
	bool get_gps_information(Loc_m& loc);//主动获取gps信息，查数据库
	int get_gps_orbit_information(Loc_m* loc, std::string begin_time,std::string end_time);//获取一段时间的GPS信息 查数据库
	int get_worning_information(WORN &worn);//主动获取历史报警信息，查数据库
	private:
	bool set_gps_information(Loc_m &);//将gps信息写入数据库
	bool set_worning_information(Loc_m &);//将报警信息写入数据库
	bool call_client_worning_message();//告知客户端，报警信息。回调函数。
	private:
	sql_connector handle;
};
