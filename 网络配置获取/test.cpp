#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <net/route.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

#define PATH_ROUTE "/proc/net/route"

bool GetIPV4Gateway(const char *pNICName, char *pGateway, unsigned long len)
{
    char buffer[200] = {0};
    unsigned long bufLen = sizeof(buffer);

    unsigned long defaultRoutePara[4] = {0};
    FILE *pfd = fopen(PATH_ROUTE, "r");
    if (NULL == pfd)
    {
        return false;
    }

    while (fgets(buffer, bufLen, pfd))
    {
        sscanf(buffer, "%*s %x %x %x %*x %*x %*x %x %*x %*x %*x\n", (unsigned int *)&defaultRoutePara[1], (unsigned int *)&defaultRoutePara[0], (unsigned int *)&defaultRoutePara[3], (unsigned int *)&defaultRoutePara[2]);

        if (NULL != strstr(buffer, pNICName))
        {
            //如果FLAG标志中有 RTF_GATEWAY
            if (defaultRoutePara[3] & RTF_GATEWAY)
            {
                unsigned long ip = defaultRoutePara[0];
                snprintf(pGateway, len, "%d.%d.%d.%d", (ip & 0xff), (ip >> 8) & 0xff, (ip >> 16) & 0xff, (ip >> 24) & 0xff);
                break;
            }
        }

        memset(buffer, 0, bufLen);
    }

    fclose(pfd);
    pfd = NULL;
    return true;
}


int main(int argc, char** argv)
{
    char pGateway[32] = {0};
    char buffer[200] = {0};
    unsigned long bufLen = sizeof(buffer);

    unsigned long defaultRoutePara[4] = {0};
    FILE *pfd = fopen(PATH_ROUTE, "r");
    if (NULL == pfd)
    {
        return false;
    }

    while (fgets(buffer, bufLen, pfd))
    {
        sscanf(buffer, "%*s %x %x %x %*x %*x %*x %x %*x %*x %*x\n", (unsigned int *)&defaultRoutePara[1], (unsigned int *)&defaultRoutePara[0], (unsigned int *)&defaultRoutePara[3], (unsigned int *)&defaultRoutePara[2]);

        if (NULL != strstr(buffer, "eth1"))
        {
            cout << "buffer: " << endl;
            cout << buffer << endl;
            //如果FLAG标志中有 RTF_GATEWAY
            //if (defaultRoutePara[3] & RTF_GATEWAY)
            {
                unsigned long ip = defaultRoutePara[0];
                snprintf(pGateway, 32, "%d.%d.%d.%d", (ip & 0xff), (ip >> 8) & 0xff, (ip >> 16) & 0xff, (ip >> 24) & 0xff);
                break;
            }
        }

        memset(buffer, 0, bufLen);
    }

    fclose(pfd);
    pfd = NULL;
    cout << "gateway: " << pGateway << endl; 
    return 0;
}


#if 0
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>

int main(int argc, char *argv[])
{
    struct ifaddrs *ifaddr_lst;
    struct ifaddrs *ifaddr_node;
    int family;
    char host[NI_MAXHOST];

    if (getifaddrs(&ifaddr_lst) < 0)
    {
        perror("getifaddrs");
        return -1;
    }

    for (ifaddr_node = ifaddr_lst; ifaddr_node != NULL; ifaddr_node = ifaddr_node->ifa_next)
    {
        /* ifa_addr可能为空，*/
        if (NULL == ifaddr_node->ifa_addr)
        {
            continue;
        }

        struct sockaddr_in *addr = (struct sockaddr_in *)ifaddr_node->ifa_addr;
        family = addr->sin_family;

        printf("----------------------------------------\n");
        printf("interface name: %s\n", ifaddr_node->ifa_name);
        printf("address family: %d(%s)\n", family, (family == AF_PACKET) ? "AF_PACKET" : (family == AF_INET) ? "AF_INET"
                                                                                     : (family == AF_INET6)  ? "AF_INET6"
                                                                                                             : "");
        if (family == AF_INET || family == AF_INET6)
        {
            int ret = getnameinfo(ifaddr_node->ifa_addr, (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if (ret != 0)
            {
                printf("getnameinfo failed:%s\n", strerror(ret));
                return -1;
            }

            printf("address: %s\n", host);
        }
        printf("----------------------------------------\n");
    }

    freeifaddrs(ifaddr_lst);
    return 0;
}

#if 0
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <map>
#endif
#if 0
void getAllEth(std::map<std::string, std::string ip> &m_map)
{
    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    char host[NI_MAXHOST];

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        return;
    }

    int i = 0;
    for (ifa = ifaddr, i = 0; ifa != NULL; ifa = ifa->ifa_next, i++)
    {
        //跳过环路
        if (strcmp(ifa->ifa_name, "lo") == 0)
            continue;

        std::string tmp;
        std::string ip;
        std::string eth_name = ifa->ifa_name;
        family = ifa->ifa_addr->sa_family;

        if (family == AF_INET)
        {
            //LogOut("Web", L_INFO, "%s  address family: %d\n", ifa->ifa_name, family);
            //获取网卡名

            //获取IPV4的ip地址
            s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), ip.c_str(), NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if (s != 0)
            {
                //获取失败
                //LogOut("Web", L_INFO, "Get %s IP failed", tmp.ip)
                printf()
            }
        }

        m_map[eth_name] = tmp;
    }
    freeifaddrs(ifaddr);
}
#endif

#if 0
int main(int argc, char *argv[])
{

    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    char host[NI_MAXHOST];

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    /* Walk through linked list, maintaining head pointer so we
     *               can free list later */

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        // if (ifa->ifa_addr == NULL)
        //     continue;
        
        if (strcmp(ifa->ifa_name, "lo") == 0)
            continue;

        family = ifa->ifa_addr->sa_family;
        /* Display interface name and family (including symbolic
         *                   form of the latter for the common families) */

        if (family == AF_INET)
            printf("%s  address family: %d\n", ifa->ifa_name, family);
                /*
        printf("%s  address family: %d%s\n",
               ifa->ifa_name, family,
               (family == AF_PACKET) ? " (AF_PACKET)" : (family == AF_INET) ? " (AF_INET)"
                                                    : (family == AF_INET6)  ? " (AF_INET6)"
                                                                            : "");
        */

                /* For an AF_INET* interface address, display the address */

            //     if (family == AF_INET || family == AF_INET6)
            // {
            //     s = getnameinfo(ifa->ifa_addr,
            //                     (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
            //                     host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            //     if (s != 0)
            //     {
            //         printf("getnameinfo() failed: %s\n", gai_strerror(s));
            //         exit(EXIT_FAILURE);
            //     }
            //     printf("\taddress: <%s>\n", host);
            // }

            if (family == AF_INET)
            {
                s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
                if (s != 0)
                {
                    printf("getnameinfo() failed: %s\n", gai_strerror(s));
                    exit(EXIT_FAILURE);
                }
                printf("\taddress: <%s>\n", host);
            }
    }

    freeifaddrs(ifaddr);
    exit(EXIT_SUCCESS);
#endif


#if 0
    int fd;
    struct ifreq ifr;
    char *iface = "enp5s0";
    unsigned char *mac;

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, iface, IFNAMSIZ - 1);

    ioctl(fd, SIOCGIFHWADDR, &ifr);

    close(fd);

    mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;

    //display mac address
    char newMac[64] = {0};
    snprintf(newMac, 64, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    printf("Mac : %s\n", newMac);
    //printf("Mac : %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);


    return 0;
}
#endif
#endif