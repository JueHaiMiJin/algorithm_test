#include <istream>
#include <vector>
#include <string>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>

using namespace std;

class client
{
private:
    vector<int> m_socket;
    int m_ssocket = 0;
    bool state = false;
    bool connect_statu = false;

public:
    client(/* args */);
    ~client();

    static void *Connect(void *arg);
    static void *HeartBreakSend(void *arg);
    static void *SendMsg(void *arg);
    static void *RecvMsg(void *arg);
};

client::client(/* args */)
{
    pthread_t p_coneartbeat;
    pthread_attr_t con_attr;
    pthread_attr_init(&con_attr);
    pthread_attr_setdetachstate(&con_attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&p_coneartbeat, &con_attr, Connect, this);
    pthread_attr_destroy(&con_attr);

    pthread_t p_heartbeat;
    pthread_attr_t h_attr;
    pthread_attr_init(&h_attr);
    pthread_attr_setdetachstate(&h_attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&p_heartbeat, &h_attr, HeartBreakSend, this);
    pthread_attr_destroy(&h_attr);

    pthread_t p_sendmsg;
    pthread_attr_t s_attr;
    pthread_attr_init(&s_attr);
    pthread_attr_setdetachstate(&s_attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&p_heartbeat, &s_attr, SendMsg, this);
    pthread_attr_destroy(&s_attr);

    pthread_t p_recvmsg;
    pthread_attr_t r_attr;
    pthread_attr_init(&r_attr);
    pthread_attr_setdetachstate(&r_attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&p_recvmsg, &r_attr, RecvMsg, this);
    pthread_attr_destroy(&r_attr);
}

client::~client()
{
    close(m_ssocket);
}

void *client::Connect(void *arg)
{
    printf("do connect... \n");
    client *tmp = (client *)arg;
    while (tmp->connect_statu == false)
    {
        printf("create connect \n");
        int clientsocket = socket(AF_INET, SOCK_STREAM, 0); //创建套接字
        tmp->m_ssocket = clientsocket;
        struct sockaddr_in clientaddr;
        memset(&clientaddr, 0, sizeof(clientaddr));
        clientaddr.sin_family = AF_INET;
        clientaddr.sin_addr.s_addr = inet_addr("192.168.1.7");
        clientaddr.sin_port = htons(9998);
        int ret = -1;
        do
        {
            ret = connect(clientsocket, (struct sockaddr *)&clientaddr, sizeof(clientaddr));

        } while (ret == -1);

        tmp->connect_statu = true;
        tmp->state = true;

        printf("change status tmp->connect_statu:%d, tmp->state:%d\n", tmp->connect_statu, tmp->state);
    }
}

void *client::HeartBreakSend(void *arg)
{
    client *tmp = (client *)arg;
    while (!tmp->state)
    {
        sleep(5);
    }

    while (tmp->state)
    {
        char buff[128] = {0};
        memcpy(buff, "{\"CMD\":\"HeartBeat\"}", 128);
        if (tmp->m_ssocket > 0)
        {
            int ret = send(tmp->m_ssocket, buff, sizeof(buff), 0);
            if (ret == -1)
            {
                printf("can not send error \n");
            }
            else if (ret == 0)
            {
                printf("send success \n");
            }
            else
            {
                printf("Send errno:%d \n", errno);
            }
        }
        else
        {
            printf("tmp->m_ssocket > 0 failed \n");
            sleep(5);
        }

        sleep(5);
    }
}

void *client::SendMsg(void *arg)
{
    client *tmp = (client *)arg;
    while (!tmp->state)
    {
        sleep(5);
    }

    while (tmp->state)
    {
        char buff[128] = {0};
        memcpy(buff, "{\"CMD\":\"MSG\"}", 128);
        if (tmp->m_ssocket > 0)
        {
            int ret = send(tmp->m_ssocket, buff, sizeof(buff), 0);
            if (ret == -1)
            {
                printf("can not send error \n");
            }
            else if (ret == 0)
            {
                printf("send success \n");
            }
            else
            {
                printf("Send errno:%d \n", errno);
            }
        }
        else
        {
            printf("tmp->m_ssocket > 0 failed \n");
            sleep(5);
        }

        sleep(30);
    }
}

void *client::RecvMsg(void *arg)
{
    client *tmp = (client *)arg;
    while (!tmp->state)
    {
        sleep(5);
    }

    while (tmp->state)
    {
        char buff[128] = {0};
        recv(tmp->m_ssocket, buff, sizeof(buff), 0); //接收
        if (strlen(buff) > 0)
            printf("*** Recv : %s ****\n", buff);
    }
}

int main(int argc, char const *argv[])
{
    client test;
    while (1)
    {
        /* code */
    }

    return 0;
}
