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
#include "basic.h"


class tcp_server
{
    public:
        tcp_server(std::string _host_ip="127.0.0.1",unsigned int _host_port=8080);
        ~tcp_server();
        int init();
        int run();
        void* accept_request();
        void execute_post(char* ,std::string );
        void execute_get(char* ,std::string );
    private:
        int send_file(const std::string &);
        int get_line(char* ,int);
    public:
        int listen_sock;
        std::string _host_ip;
        unsigned int _host_port;
};

struct args
{
    int sockfd;
};
