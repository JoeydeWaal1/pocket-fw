#include "if_card.h"


int parse_line(
        FILE* config,
        struct if_card* iets
)
{
    char * line = NULL;
    size_t len = 0;
    char *ip_addr, *subnet, *if_card, *region, *overig, *default_gateway;

    if (getline(&line, &len, config) != -1)
    {
        ip_addr         = strtok(line,"/");
        subnet          = strtok(NULL," ");
        if_card         = strtok(NULL," ");
        region          = strtok(NULL, " ");
        overig          = strtok(NULL, " ");
        default_gateway = strtok(NULL, " ");

        if(!ip_addr || !subnet || !if_card || !region){
            puts("Fout in config bestand");
            return -1;
        }
        if (overig && !default_gateway)
        {
            puts("Fout met default gateway");
            return -1;
        } else if (default_gateway)
            default_gateway[strcspn(default_gateway, "\n")] = 0;
        else
            region[strcspn(region, "\n")] = 0;

        iets->ip_addr         = ip_addr;
        iets->if_name         = if_card;
        iets->subnet          = atoi(subnet);
        iets->region          = region;
        iets->default_gateway = default_gateway;
        return 1;
    }
    return -1;
}


// Van bestands naam naar 2 ip_addr structs
int parse_file(char* filename, struct interfaces* interfaces)
{
    FILE* config;
    config = fopen(filename, "r");
    if (config == NULL)
    {
        puts("Kon config.txt niet openen");
        return -1;
    }
    for (int i = 0; i < 2; i++) {
        struct if_card net;
        if (parse_line(config, &net) == -1){
            printf("fout in (%s), regel: %d\n", filename, i + 1);
            return -1;
        }
        interfaces_append(&net, interfaces);
    }
    fclose(config);
    print_interfaces(interfaces);
    return 1;
}

void print_if_card(struct if_card* net_kaart)
{
    printf("ip adres:        %s\n",  net_kaart->ip_addr);
    printf("subnet:          /%d\n", net_kaart->subnet);
    printf("if naam:         %s\n",  net_kaart->if_name);
    printf("region:          %s\n",  net_kaart->region);
    printf("default_gateway: %s\n",  net_kaart->default_gateway);
}

struct interfaces interfaces_new()
{
    unsigned short default_length = 2;
    struct interfaces interfaces;

    interfaces.capacity = default_length;
    interfaces.lengte   = 0;
    interfaces.data     = malloc(sizeof(interfaces) * default_length);
    return interfaces;
}

int interfaces_append(struct if_card* new_element, struct interfaces* interfaces)
{
    print_if_card(new_element);
    if (interfaces->lengte == interfaces->capacity)
    {
        puts("realoc\n");
        size_t new_cap = interfaces->capacity * 2;
        interfaces->data =
            realloc(
                interfaces->data,
                sizeof(struct interfaces) * new_cap
            );
        interfaces->capacity = new_cap;
    }
    puts("\n");
    printf("len: %zu, cap: %zu\n", interfaces->lengte, interfaces->capacity);
    memcpy(
            &interfaces->data[interfaces->lengte],
            new_element,
            sizeof(struct if_card)
          );
    interfaces->lengte++;
    return 1;
}

void print_interfaces(struct interfaces* interfaces)
{
    for (int i = 0; i < interfaces->lengte; i++)
    {
        print_if_card(&interfaces->data[i]);
    }
}
