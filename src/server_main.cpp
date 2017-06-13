#include "server_main.h"

tcp_server::tcp_server(std::string _host_ip,unsigned int _host_port):_host_ip(_host_ip),_host_port(_host_port)
{
    this->listen_sock = -1;
}

tcp_server::~tcp_server()
{
    if (0 > this->listen_sock)
    {
        close(listen_sock);
    }
}

int tcp_server::init()
{
    this->listen_sock = socket(AF_INET,SOCK_STREAM,0);
    if (this->listen_sock == -1)
    {
        print_log("create socket failed");
        return -1;
    }
    print_log("create socket success! \n");

    struct sockaddr_in local_address;
    bzero(&local_address,sizeof(local_address));
    local_address.sin_family = AF_INET;
    local_address.sin_port = htons(this->_host_port);
    local_address.sin_addr.s_addr = inet_addr(this->_host_ip.c_str());

    socklen_t len = sizeof(struct sockaddr_in);
    int bind_ret = bind(listen_sock,(sockaddr *)&local_address,len);
    if (bind_ret == -1)
    {
        print_log("bind socker failed!");
        return -2;
    }
}

int tcp_server::get_line(char buf[],int buf_size)
{
	char c = '\0';
	int n = 0;
	int i=0;
	int flag = 0;
	while(buf_size - 1>0 && c != '\n')
	{
		flag = recv(listen_sock,&c,1,MSG_WAITALL);
		if (flag == -1)
			return 0;
		if (c == '\r')
		{
			n = recv(listen_sock,&c,1,MSG_PEEK);
			if (n > 0 && c == '\n')
			{
				recv(listen_sock,&c,1,MSG_WAITALL);
			}
			else
				c = '\n';
		}
		buf[i] = c;
		buf_size--;
		i++;
	}
	buf[i] = '\0';
	return i;
}

void tcp_server::unimplement()
{
	char buf[] = "not define action";
	if (send(listen_sock,buf,sizeof(buf),0) == sizeof(buf))
	{
		print_log("unimplement success");
	}
}

void tcp_server::bad_request()
{
    return; 
}

void tcp_server::execute_post(char *url,std::string para = "NONE")
{
    int content_length = -1;
    int numbers = 0;
    char buf[BUFFER_SIZE];
    //char *length
    char c;
    int status = 0;
    do{
        numbers = get_line(buf,sizeof(buf));
        buf[15] = '\0';
        //length = &(buf[16]);
        //
        if (strncasecmp(buf,"Content-Length:",15) == 0)
        {
            content_length = atoi(&(buf[16]));
        }
    }while(strcmp("\n",buf) && numbers > 0);
    if (content_length == -1)
    {
        bad_request();
        return ;
    }
    bzero(buf,sizeof(buf));
	sprintf(buf,"HTTP/1.0 200 OK\r\n\r\n");//this is the key \r\n
	send(listen_sock,buf,strlen(buf),0);
    std::string json;
    int i = 0;
    for (;i<content_length;i++) 
    {
        recv(listen_sock,&(json[i]),1,MSG_WAITALL);
    }
    Json::Reader reader;
    Json::Value value;
    reader.parse(json,value);
    std::string device = value["device"].asString();
    std::string function = value["function"].asString();
    if (device.compare("gps") == 0)
    {
        Gps gps;
        if (function.compare("set_gps_information") == 0)
        {
            LOCATION loc;
            loc.GPS_number = value["GPS_number"].asString();
            loc.Lng = value["Lng"].asString();
            loc.Lat = value["Lat"].asString();
            loc.Time = value["Time"].asString();
            gps.set_gps_information(loc);
            //get the information from cli and store it,  needn't give a response,   
        }
        if (function.compare("set_worning_information") == 0)
        {
            WORN worn;
            worn.loc.GPS_number = value["GPS_number"].asString();
            worn.loc.Lng = value["Lng"].asString();
            worn.loc.Lat = value["Lat"].asString();
            worn.loc.Time = value["Time"].asString();
            worn.Worning = value["Worning"].asString();
            gps.set_worning_information(worn);
        }
    }
    if (device.compare("cli") == 0)
    {
        Cli cli;
        if (function.compare("set_person_information") == 0)
        {
            PERSON per;
            per.Name = value["Name"].asString();
            per.ID = value["ID"].asString();
            per.Sex = value["Sex"].asString();
            per.Address = value["Address"].asString();
            per.Tel = value["Tel"].asString();
            per.E_mail = value["E_mail"].asString();
            per.Client_id = value["Client_id"].asString();
            cli.register_person_information(per);
        }
        if (function.compare("set_car_information") == 0)
        {
            CAR car;
            car.ID = value["ID"].asString();
            car.GPS_number = value["GPS_number"].asString();
            car.Car_brand = value["Car_brand"].asString();
            car.Car_number = value["Car_number"].asString();
            car.Car_VIN_number = value["Car_VIN_number"].asString();
            car.Car_type = value["Car_type"].asString();
            car.Car_buy_time = value["Car_buy_time"].asString();
            car.Car_color = value["Car_color"].asString();
            cli.register_car_information(car);
        }
        if (function.compare("test_in_information") == 0)
        {
            COUNT cou;
            cou.ID = value["ID"].asString();
            cou.passwd = value["passwd"].asString();
            Json::Value root;
            if (cli.test_sign_in_information(cou))
            {
                root["status"] = "YES";
                std::string out = root.toStyledString();
	            send(listen_sock,out.c_str(),strlen(out.c_str()),0);
            }
            else
            {
                root["status"] = "NO";
                std::string out = root.toStyledString();
	            send(listen_sock,out.c_str(),strlen(out.c_str()),0);
            }

        }
        if (function.compare("comfirm_worning_information") == 0)
        {
            LIST_IN list;
            list.car.Car_number = value["Car_number"].asString();
            list.car.GPS_number = value["GPS_number"].asString();
            list.person.ID = value["ID"].asString();
            cli.confirm_worning_information();/////////need modify
        }
        if (function.compare("remove_worning_information") == 0)
        {
            CAR car;
            car.ID = value["ID"].asString();
            car.Car_number = value["Car_number"].asString();
            car.Status = value["Status"].asString();
            cli.remove_worning_information();
        }
    }
    if (device.compare("pli") == 0)
    {
        Pli pli;
        if (function.compare("register_pli_information") == 0)
        {
            POLICEMAN pli_man;
            pli_man.Name = value["Name"].asString();
            pli_man.Number = value["Number"].asString();
            pli_man.Sex = value["Sex"].asString();
            pli_man.Age = value["Age"].asString();
            pli_man.Location = value["Location"].asString();
            pli_man.Tel = value["Tel"].asString();
            pli.register_pli_information(pli_man);
        }
        if (function.compare("begin_dealWith_worning_information") == 0)
        {
            POLICEMAN pli_man;
            CAR car;
            PERSON per;
            pli_man.Name = value["Name"].asString();
            pli_man.Number = value["Number"].asString();
            pli_man.Sex = value["Sex"].asString();
            pli_man.Age = value["Age"].asString();
            pli_man.Location = value["Location"].asString();
            pli_man.Tel = value["Tel"].asString();
            car.Status = value["status"].asString();
            car.Car_number = value["Car_number"].asString();
            per.ID = value["ID"].asString();
            pli.begin_dealWith_worning_information(pli_man,car,per);
        }
        if (function.compare("end_dealWith_worning_information") == 0)
        {
            CAR car;
            PERSON per;
            car.Car_number = value["Car_number"].asString();
            per.ID = value["ID"].asString();
            pli.end_dealWith_worning_information(per,car);
            Json::Value root;
            //root["message"] = "Car is found,please call the plice man tel number";
            //std::string out = root.toStyledString();
           // send_file(out);//push message
        }
        if (function.compare("test_sign_in_information"))
        {
            COUNT cou;
            cou.ID = value["ID"].asString();
            cou.passwd = value["passwd"].asString();
            pli.test_sign_in_information(cou);
        }
    }


}


void tcp_server::execute_get(char *url,std::string para = "NONE")
{
    Json::Reader reader;
    Json::Value value;
    Cli cli;
    int numbers = 0;
    int status  = 0;
    reader.parse(para,value);
    std::string device = value["device"].asString();
    std::string function = value["function"].asString();
    if (device.compare("cli") == 0)
    {
        if (function.compare("get_gps_information") == 0)
        {
            LOCATION loc;
            loc.GPS_number = value["GPS_number"].asString();
            cli.get_gps_information(loc,loc.GPS_number);
            Json::Value root;
            root["GPS_number"] = loc.GPS_number;
            root["Lng"] = loc.Lng;
            root["Lat"] = loc.Lat;
            root["Time"] = loc.Time;
            std::string out = root.toStyledString();
            send_file(out);
        }
        if (function.compare("get_car_information") == 0)
        {
           CAR car;
           car.ID = value["ID"].asString();
           cli.get_car_information(car,car.ID);
           Json::Value root;
           root["ID"] = car.ID;
           root["GSP_number"] = car.GPS_number;
           root["Car_brand"] = car.Car_brand;
           root["Car_number"] = car.Car_number;
           root["Car_VIN_number"] = car.Car_VIN_number;
           root["Car_type"] = car.Car_type;
           root["Car_buy_time"] = car.Car_buy_time;
           root["Car_color"] = car.Car_color;
           std::string out = root.toStyledString();
           send_file(out);
        }
        if (function.compare("get_person_information") == 0)
        {
            PERSON per;
            per.ID = value["ID"].asString();
            cli.get_person_information(per,per.ID);
            Json::Value root;
            root["ID"] = per.ID;
            root["Name"] = per.Name;
            root["Sex"] = per.Sex;
            root["Address"] = per.Address;
            root["Tel"] = per.Tel;
            root["E_mail"] = per.E_mail;
            root["Client_id"] = per.Client_id;
            std::string out = root.toStyledString();
            send_file(out);
        }
/*        if (function.compare("test_in_information") == 0)
        {
            COUNT cou;
            Json::Value root;
            cou.ID = value["ID"].asString();
            cou.passwd = value["passwd"].asString();
            if (cli.test_sign_in_information(cou))
            {
                root["status"] = "Yes";
            }
            else
            {
                root["status"] = "NO";
            }
            std::string out = root.toStyledString();
            send_file(out);
        }*/
    }
    if (device.compare("pli") == 0)
    {
        if (function.compare("get_gps_information") == 0)
        {}
        if (function.compare("get_car_information") == 0)
        {}
        if (function.compare("get_person_information") == 0)
        {}
    }
	char head[BUFFER_SIZE];
	bzero(head,sizeof(head));
}

int tcp_server::send_file(const std::string &buf)
{
    char head[BUFFER_SIZE];
    bzero(head,sizeof(head));
	strcat(head,"HTTP/1.0 200 OK \r\n\r\n");
	int ret = send(listen_sock,head,strlen(head),0);
	ret = send(listen_sock,buf.c_str(),strlen(buf.c_str()),0);
}


void* accept_request(void *tmp)
{   
    //typedef (int *)tmp tcp;
    tcp_server* tcp=(tcp_server*)tmp;
    int sock_client = tcp->listen_sock;
	int cgi = 0;
	char buf[BUFFER_SIZE];
	char *query_string;
	char url[BUFFER_SIZE];
	char path[BUFFER_SIZE];
	char method[BUFFER_SIZE];
	bzero(buf,sizeof(buf));
	bzero(url,sizeof(url));
	bzero(path,sizeof(path));
	bzero(method,sizeof(method));
	int i = 0,j = 0;
	int numbers;
//	struct stat st;
	
    numbers = tcp->get_line(buf,sizeof(buf));
	while ( !isspace(buf[i]) && (j < sizeof(method) - 1))
	{

		method[j] = buf[i];
		i++,j++;
	}	
	method[j] = '\0';
	if(strcasecmp(method ,"GET") && strcasecmp(method ,"POST"))
	{
		tcp->unimplement();
		return (void *)0;
	}
	while(isspace(buf[i]))
	{
		i++;
	}
	j = 0;
	while( !isspace(buf[i]) && j < BUFFER_SIZE && i < BUFFER_SIZE-1)//why i < BUFFER_SIZE -1
	{
		url[j] = buf[i];
		i++,j++;
	}
	url[j] = '\0';
	if( !strcasecmp(method,"GET"))
	{	
		query_string = url;
		while(*query_string != '\0'&& *query_string != '?')
		{
			query_string++;
		}
        char *parameter = query_string+1;
		if (*query_string == '?')
        {
			*query_string = '\0';
        }
        if (*query_string == '\0')
        {
            //tcp->execute_get(url);
        }
        int pos = 0;
        std::string para;
        while(*parameter != ' ' && *parameter != '\0')
        {
            para[pos++] = *(parameter++);
        }

		tcp->execute_get(url,para);
	}
    if ( !strcasecmp(method,"POST"))
    {
        query_string = url;
        while(*query_string != '\0' && *query_string != '?')
        {
            query_string++;
        }
        char *parameter = query_string+1;
        if (*query_string == '?')
        {
            *query_string = '\0';
        }
        if (*query_string == '\0')
        {
           // tcp->execute_post(url);
        }
        int pos = 0;
        std::string para;
        while(*parameter != ' ' && *parameter != '\0')
        {
            para[pos++] = *(parameter++);
        }
        tcp->execute_post(url,para);

    }
    close(sock_client);
}

int main()
{
    tcp_server tcp;
    tcp.init();
    int  listen_ret = listen(tcp.listen_sock,5);
    if ( listen_ret == -1 )
    {
        print_log("listen sock failed!");
    }
    print_log("listen sock success");

    struct sockaddr_in local_address;
    bzero(&local_address,sizeof(local_address));
    socklen_t client_addr_len = sizeof(local_address);

    while(true)
    {
        int sockfd = accept(tcp.listen_sock,(struct sockaddr *)&local_address,&client_addr_len);
        if (sockfd == -1)
        {
            print_log("accept socket failed");
            continue;
        }
        print_log("accpet socked success!");

        pthread_t new_client;
        int ret = pthread_create(&new_client,NULL,&accept_request,(void*)&tcp); 

    }
        
    
}


