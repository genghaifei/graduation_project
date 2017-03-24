#include <iostream>
using namespace std;

typedef struct tagIPInfo  
    {  
        char ip[30];  
    }IPInfo;  
      
bool GetLocalIPs(IPInfo* ips,int maxCnt,int* cnt)  
    {  
        //1.��ʼ��wsa  
        WSADATA wsaData;  
        int ret=WSAStartup(MAKEWORD(2,2),&wsaData);  
        if (ret!=0)  
        {  
            return false;  
        }  
        //2.��ȡ������  
        char hostname[256];  
        ret=gethostname(hostname,sizeof(hostname));  
        if (ret==SOCKET_ERROR)  
        {  
            return false;  
        }  
        //3.��ȡ����ip  
        HOSTENT* host=gethostbyname(hostname);  
        if (host==NULL)  
        {  
            return false;  
        }  
        //4.���ת��Ϊchar*����������  
        *cnt=host->h_length<maxCnt?host->h_length:maxCnt;  
        for (int i=0;i<*cnt;i++)  
        {  
            in_addr* addr=(in_addr*)*host->h_addr_list;  
            strcpy(ips[i].ip,inet_ntoa(addr[i]));  
        }  
        return true;  
    }  

int main()
{
    IPInfo ip;
    int haha;
    int heihei;
    GetlocalIPs(&ip,haha,&heihei);
    cout<<ip<<endl;
}
