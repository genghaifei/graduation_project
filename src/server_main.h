#include <iostream>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <string>
#include <map>
#include <pthread.h>
#include <arpa/inet.h>


class tcp_server
{
    public:
        tcp_server(std::string _host_ip="127.0.0.1",unsigned int _host_port="8080");
        ~tcp_server();
        int init();
        int run();
        int recv_msg();
    private:
        int send_msg();
    private:
        int listen_sock;
        std::string _host_ip;
        unsigned int _host_port;
};

struct args
{
    int sockfd;
};
