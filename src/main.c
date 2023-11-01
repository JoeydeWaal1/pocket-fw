#include <netinet/ip.h>
#include <arpa/inet.h>
#include "if_card.h"
#include "socket.h"

#define BUFF_SIZE 4096

int main()
{
    char buffer[BUFF_SIZE];
    struct ip* ip = (struct ip*) buffer;
    int len, raw_server_socket;

    raw_server_socket = bind_interface("en1");
    if (raw_server_socket == -1){
        puts("error raw_server_socket");
    }
    puts("listening");
    len = recv(raw_server_socket, &buffer, sizeof(buffer), 0);
    puts("done");
    char* src = inet_ntoa(ip->ip_src);
    char* dest = inet_ntoa(ip->ip_dst);
    printf("src:  %s\ndest: %s\n",src,dest);
}

