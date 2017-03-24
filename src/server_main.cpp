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

void accept_cli()
{
    
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
    switch(line)
    {
        case "cli":
            {
                accept_cli(sockfd);
                break;
            }

        case "pli":
            {
                accept_pli(sockfd);
                break;
            }
        case "gps":
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
        int ret = pthread_create(&new_client,NULL,&exec,NULL,*arg); 

    }
        
    
}


