#include <stdio.h>
#include <string.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
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
    int socket_desc = socket(AF_INET, SOCK_RAW, htons(ETHERTYPE_IP));
    if (socket_desc == -1){
        puts("Kon geen socket maken, (geen sudo rechten?)");
        return -1;
    }
    int on = 1;
    if (setsockopt(socket_desc, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) == -1) {
        perror("setsockopt() failed");
        return 2;
    }


    /* struct sockaddr_in server; */
    /* server.sin_family = AF_INET; */
    /* server.sin_addr.s_addr = inet_addr(ip_addr); */
    /* server.sin_port = 250; */

    /* int result = bind( */
    /*         socket_desc, */
    /*         (struct sockaddr *) &server, */
    /*         sizeof(server) */
    /* ); */

    /* if (result == -1){ */
    /*     puts("BIND mislukt"); */
    /*     return -1; */
    /* } */

    /* listen(socket_desc, 3); */
    return socket_desc;
}


int bind_interface(const char* if_card)
{
    const char* ip = find_ip(if_card);
    if (ip == NULL){
        puts("geen if kaart gevonden");
        return -1;
    }
    return server_bind_socket(ip);
}
