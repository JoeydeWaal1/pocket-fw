#include <stdio.h>
#include <string.h>
#include <ifaddrs.h>
#include <arpa/inet.h>

# include "socket.h"

const char* find_ip(const char* if_card)
{
    struct ifaddrs* if_ap, *ifa;
    struct sockaddr_in *sa;
    char *addr;

    getifaddrs(&if_ap);

    for (ifa = if_ap; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr && ifa->ifa_addr->sa_family==AF_INET) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);

            if (strcmp(ifa->ifa_name, if_card) == 0){
                freeifaddrs(if_ap);
                return addr;
            }
        }
    }
    freeifaddrs(if_ap);
    return NULL;
}

int server_bind_socket(const char* ip_addr)
{
    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        puts("Kon geen socket krijgen");
        return -1;
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip_addr);
    /* server.sin_port = htons(80); */ // mag nie binden aan poort 80?
    server.sin_port = 0;

    int result = bind(
            socket_desc,
            (struct sockaddr *) &server,
            sizeof(server)
    );
    printf("result: %d\n", result);
    if (result == -1)
    {
        puts("BIND mislukt");
        return -1;
    }
    listen(socket_desc, 3);
    return socket_desc;
}


int listen_if_card(const char* if_card)
{
    const char* ip = find_ip(if_card);
    if (ip == NULL){
        puts("geen if kaart gevonden");
        return -1;
    }
    printf("ip: %s\n", ip);
    return server_bind_socket(ip);
}
