#include "server_main.h"

tcp_server::tcp_server(std::string _host_ip,unsigned int _host_port):_host_ip(_host_ip),_host_port(_host_port)
{
    std::string _host_ip=get_host_ip();
    this->listen_sock = -1;
}

tcp_server::~tcp_server()
{

////////////////////////////////////////////test
    std::cout<<listen_sock<<std::endl;
//////////////////////////////////////////////
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
        print_log("errno is %d,error is %s",errno,strerror(errno));
        go_down(errno,strerror(errno));
    }
    print_log("create socket success! \n");

    struct sockaddr_in local_address;
    bzero(&local_address,sizeof(local_address));
    local_address.sin_family = AF_INET;
    local_address.sin_port = htons(this->_host_port);
    local_address.sin_addr.s_addr = inet_addr(this->_host_ip.c_str());

    socklen_t len = sizeof(struct sockaddr_in);
    int bind_ret = bind(listen_sock,&local_address,len);
    if (bind_ret == -1)
    {
        print_log("bind socker failed!");
        print_log("errno is %d error is %s",errno ,strerror(errno));
        go_down(errno,strerror(errno));
    }
}

int get_line(int sockfd,char buf[],int buf_size)
{
	char c = '\0';
	int n = 0;
	int i=0;
	int flag = 0;
	while(buf_size - 1>0 && c != '\n')
	{
		flag = recv(sockfd,&c,1,NULL);
		if (flag == -1)
			return 0;
		if (c == '\r')
		{
			n = recv(sockfd,&c,1,MSG_PEEK);
			if (n > 0 && c == '\n')
			{
				recv(sockfd,&c,1,NULL);
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

void unimplement(int sock_client)
{
	char* buf = "not define action";
	if (send(sock_client,buf,sizeof(buf),0) == sizeof(buf))
	{
		syslog(LOG_DEBUG,"unimplement success");
	}
}


void tcp_server::execute_get(char *url,std::string &para)
{
    ;
}


void tcp_server::accept_request()
{
    sock_listen = listen_sock
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
	
    numbers = get_line(sock_client,buf,sizeof(buf));
	while ( !isspace(buf[i]) && (j < sizeof(method) - 1))
	{

		method[j] = buf[i];
		i++,j++;
	}	
	method[j] = '\0';
	if(strcasecmp(method ,"GET") && strcasecmp(method ,"POST"))
	{
		unimplement(sock_client);
		return;
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
            execute_cgi(url);
        }
        int pos = 0;
        std::string para;
        while(*parameter != ' ' && *parameter != '\0')
        {
            para[pos++] = *(parameter++);
        }

		execute_get(url,para);
	}
    if ( !strcasecmp(method,"POST"))
    {
        query_string = url;
        while(*query_string != '\0' && query_string != '?')
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
            execute_post(url);
        }
        int pos = 0;
        std::string para;
        while(*parameter != ' ' && *parameter != '\0')
        {
            para[pos++] = *(parameter++);
        }
        execute_post(url,para);

    }
    close(sock_client);
/*	if ( !strcasecmp(method,"POST"))
	{
		cgi = 1;
	}

	sprintf(path,"htdocs%s",url);
	if (path[strlen(path)-1] == '/')
	{//if the path is a dir then return the static file
		strcat(path,"index.html");
	}

	if (stat(path,&st) == -1)
	{
		while ((numbers >0) && strcmp("\n",buf))
		{
			numbers = get_line(sock_client,buf,sizeof(buf));//this line is throwed the head information
		}
		not_found(sock_client);
	}
	else
	{
		if ((st.st_mode & S_IFMT) == S_IFDIR)//the path is a dir or a file
		{
			strcat(path,"index.html");
		}
		if ((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH))
		{
			cgi = 1;
		}*/

/*		if (cgi == 0)
		{
			send_file(sock_client,path,st.st_size);
			reset_oneshot(epollfd,sock_client);
			syslog(LOG_DEBUG,"accept_request success send a html");
			close(sock_client);
		}
		else
		{
			int ret;
			pthread_t new_thread;
			struct arg arg;
			arg.a_fd.listen_sock = sock_client;
			arg.a_fd.epollfd = epollfd;
			arg.path = path;
			arg.method = method;
			arg.query_string = query_string;
			ret = pthread_create(&new_thread,NULL,&execute_cgi,(void *)&arg);
		//	reset_oneshot(epollfd,sock_client);
			//execute_cgi(sock_client,path,method,query_string);
			syslog(LOG_DEBUG,"accept_request,success exec cgi program");
		}

	}	*/
//	reset_oneshot(epollfd,sock_client);
//	close(sock_client);
}
void accept_cli(int sockfd)
{
    char space;
    char line[3];
    int flag = recv(sockfd,&space,1,NULL);
    if (flag == -1)
    {
        return;
    }
    flag = recv(sockfd,line,3,NULL);
    if (flag == -1)
    {
        return;
    }
    switch(hash_(line))
    {
        case "get_gps"_hash://get the gps information
            {
                //get the record from gps  so we should call the connect gps interface
            }
        case "get_gpd"_hash://get the orbit gps information
            {
                //get the gps record from database 
            }
        case "get_pID"_hash://get the person ID information
	        {
		
	        }
        case "get_car"_hash:
            {

            }
        case "reg_per"_hash:
            {

            }
        case "reg_car"_hash:
            {

            }
        case "test_in"_hash:
            {

            }
        case "dis_wor"_hash:
            {
                
            }
        case "con_wor"_hash:
            {

            }
        
    }
        
}

void accept_pli(int sockfd)
{
    char space;
    char line[3];
    int flag = recv(sockfd,&space,1,NULL);
    if (flag == -1)
    {
        return;
    }
    flag = recv(sockfd,line,3,NULL);
    if (flag == -1)
    {
        return;
    }
    switch(hash_(line))
    {
        case ""
    }

}

void accept_gps(int sockfd)
{
    char space;
    char line[3];
    int flag = recv(sockfd,&space,1,NULL);

}

void exec(void* arg)
{
    int sockfd = (args)arg->sockfd;
    char line[3];
    int flag = recv(sockfd,line,3,NULL);//maybe the gps return number is two double number ,so we need to deal it spiceal.
    if (flag == -1)
    {
        return;
    }
    switch(hash_(line))
    {
        case "cli"_hash:
            {
                accept_cli(sockfd);
                break;
            }

        case "pli"_hash:
            {
                accept_pli(sockfd);
                break;
            }
        case "gps"_hash:
            {
                accept_gps(sockfd);///
                break;
            }
        default :
            {
                print_log("get client wrong");
            }
    }


}



int main()
{
    tcp_server tcp;
    tcp.init();
    listen_ret = listen(tcp.listen_sock,5);
    if ( listen_ret == -1 )
    {
        print_log("listen sock failed!");
        print_log("errno is %d ,error is %s",errno,strerror(errno));
    }
    print_log("listen sock success");

    struct sockaddr_in local_address;
    bzero(&local_address,sizeof(local_address));
    socklen_t client_addr_len = sizeof(local_address);

    while(true)
    {
        int sockfd = accept(tcp.listen_sock,(struct sockaddr *)&local_address,client_addr_len);
        if (sockfd == -1)
        {
            print_log("accept socket failed");
            print_log("errno is %d,error is %s",errno,strerror(errno));
        }
        print_log("accpet socked success!")

        pthread_t new_client;
        args arg;
        arg.sockfd = sockfd
        int ret = pthread_create(&accept_request,NULL,&exec,NULL,*arg); 

    }
        
    
}


