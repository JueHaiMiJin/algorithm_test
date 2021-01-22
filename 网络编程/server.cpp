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
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/epoll.h>

using namespace std;

class server
{
private:
    int m_ssocket;
    int m_csocket;

    //epoll
    int epollfd;
    struct epoll_event event;
    std::vector<int> clients;
    std::vector<struct epoll_event> events;

public:
    server(/* args */);
    ~server();
    //static void *HeartBreakReceive(void *arg) = 0;
    static void *ReceiveMsg(void *arg);
    static void *EpollRecvMsg(void *arg);
};

server::server(/* args */)
{
    m_ssocket = socket(AF_INET, SOCK_STREAM, 0); //创建套接字

    struct sockaddr_in serveraddr, clientaddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("192.168.1.7");
    serveraddr.sin_port = htons(9998);

    bind(m_ssocket, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in));
    listen(m_ssocket, 5);

    vector<int> clients;
    epollfd = epoll_create1(EPOLL_CLOEXEC);
    //struct epoll_event event;
    event.data.fd = m_ssocket;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, m_ssocket, &event);
    events.resize(16);

    // int len = sizeof(struct sockaddr);
    // m_csocket = accept(m_ssocket, (struct sockaddr *)&clientaddr, (socklen_t *)&len);
    // printf("m_csocket : %d \n", m_csocket);

    // pthread_t p_heartbeat;
    // pthread_attr_t h_attr;
    // pthread_attr_init(&h_attr);
    // pthread_attr_setdetachstate(&h_attr, PTHREAD_CREATE_DETACHED);
    // pthread_create(&p_heartbeat, &h_attr, ReceiveMsg, this);
    // pthread_attr_destroy(&h_attr);

    pthread_t p_heartbeat;
    pthread_attr_t h_attr;
    pthread_attr_init(&h_attr);
    pthread_attr_setdetachstate(&h_attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&p_heartbeat, &h_attr, EpollRecvMsg, this);
    pthread_attr_destroy(&h_attr);
}

server::~server()
{
    close(m_ssocket);
}

void *server::EpollRecvMsg(void *arg)
{
    server *tmp = (server *)arg;
    struct sockaddr_in peeraddr;
    socklen_t peerlen;
    int count = 0;
    while (1)
    {
        int nready = epoll_wait(tmp->epollfd, &*tmp->events.begin(), static_cast<int>(tmp->events.size()), -1);
        if (nready == -1)
        {
            if (errno == EINTR)
                continue;
            else
                printf("epoll wailt \n");
        }
        else if (nready == 0)
            continue;
        if ((size_t)nready == tmp->events.size())
            tmp->events.resize(tmp->events.size() * 2);
        for (int i = 0; i < nready; i++)
        {
            if (tmp->events[i].data.fd == tmp->m_ssocket)
            {
                peerlen = sizeof(struct sockaddr_in);
                int conn = accept(tmp->m_ssocket, (struct sockaddr *)&peeraddr, &peerlen);
                if (conn == -1)
                {
                    printf("accept failed \n");
                }
                printf("ip=%s port=%d conn:%d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port), conn);
                printf("count = %d\n", ++count);
                tmp->clients.push_back(conn);

                //activate_nonblock(conn);
                //setUnBlock(conn, true);
                tmp->event.data.fd = conn;
                tmp->event.events = EPOLLIN | EPOLLET;
                epoll_ctl(tmp->epollfd, EPOLL_CTL_ADD, conn, &tmp->event);
            }
            else if (tmp->events[i].data.fd & EPOLLIN)
            {
                int conn = tmp->events[i].data.fd;
                if (conn < 0)
                    continue;

                char recvbuf[128] = {0};
                int ret = recv(conn, recvbuf, 128, 0);
                if (ret == -1)
                    printf("read failed \n");
                if (ret == 0)
                {
                    printf("client closed\n");
                    close(conn);

                    struct epoll_event tmp_event = tmp->events[i];
                    epoll_ctl(tmp->epollfd, EPOLL_CTL_DEL, conn, &tmp_event);
                    vector<int>::iterator it = tmp->clients.begin();
                    for (; it != tmp->clients.end(); it++)
                    {
                        if (*it == conn)
                        {
                            printf("prepare erase : %d\n", *it);
                            tmp->clients.erase(it);
                        }
                    }
                }
                else
                {
                    printf("RECV: %s \n", recvbuf);
                }
            }
        }
    }
}

void *server::ReceiveMsg(void *arg)
{
    server *tmp = (server *)arg;
    char recvbuf[128] = {0};
    char msg[128] = {0};
    memcpy(msg, "I have Receive Msg...", 128);
    while (1)
    {
        memset(recvbuf, 0, sizeof(recvbuf));
        recv(tmp->m_csocket, recvbuf, sizeof(recvbuf), 0); //接收
        if (strlen(recvbuf) > 0)
        {
            printf("*** Recv : %s ****\n", recvbuf);
            send(tmp->m_csocket, msg, strlen(msg) + 1, 0);
        }
    }
}

int main(int argc, char const *argv[])
{
    server test;
    while (1)
    {
        /* code */
    }

    return 0;
}
