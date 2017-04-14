#include "accept.h"

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
        case "act"_hash:
            {
                
            }
        case "con"_hash:
            {
                //get the gps record from database 
            }
    }

}

void accept_pli(sockfd)
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

