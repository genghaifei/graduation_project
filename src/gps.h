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
	int get_gps_information(Loc_m& loc);//������ȡgps��Ϣ�������ݿ�
	int get_gps_orbit_information(Loc_m* loc, std::string begin_time,std::string end_time);//��ȡһ��ʱ���GPS��Ϣ �����ݿ�
	int get_worning_information(std::string& worning_message);//������ȡ��ʷ������Ϣ�������ݿ�
	private:
	bool set_gps_information(Loc_m location_message ,std::string time);//��gps��Ϣд�����ݿ�
	bool set_worning_information(std::string worning_message,std::string time);//��������Ϣд�����ݿ�
	bool call_client_worning_message();//��֪�ͻ��ˣ�������Ϣ���ص�������
	private:
	sql_connector handle;
};