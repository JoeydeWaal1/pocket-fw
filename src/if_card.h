#include <stdio.h>  // puts
#include <stdlib.h> // malloc, realloc
#include <string.h> // memcpy

struct if_card
{
     char* if_name;
     char* ip_addr;
     uint8_t subnet;
     char* region;
     char* default_gateway;
};

void print_if_card(struct if_card* net_kaart);

struct interfaces
{
    size_t lengte;
    size_t capacity;
    struct if_card* data;
};

int parse_file(char* filename, struct interfaces* interfaces);
struct interfaces interfaces_new();
void print_interfaces(struct interfaces* interfaces);
int interfaces_append(struct if_card* new_element, struct interfaces* interfaces);
