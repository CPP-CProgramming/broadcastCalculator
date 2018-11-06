#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <arpa/inet.h>
#include <math.h>

#define IS_BIT_SET(n, pos)  ((n & (1 << (pos))) != 0)
#define TOGGLE_BIT(n, pos)  (n = n ^ (1 << (pos)))
#define COMPLEMENT(num)     (num = num ^ 0xFFFFFFFF)
#define UNSET_BIT(n, pos)   (n = n & ((1 << pos) ^ 0xFFFFFFFF))
#define SET_BIT(n, pos)     (n = n | 1 << pos)


#define PREFIX_LEN  15  /*Max length of IP address in A.B.C.D format*/
#define MAX_MASK_LEN 32  /*Maximum mask value in decimal notation*/


static unsigned int get_mask_value_in_integer_format(char mask_value)
{
    unsigned int mask = 0xFFFFFFFF;
    char n_trail_bits = MAX_MASK_LEN - mask_value;
    int i = 0;
    for(; i < n_trail_bits; i++)
    {
        UNSET_BIT(mask, i);
    }
    return mask;
}

void get_broadcast_address(char *ip_addr,
                           char mask,
                           char *output_buffer)
{
    unsigned int ip_addr_integer = 0;

    inet_pton(AF_INET, ip_addr, &ip_addr_integer);

    ip_addr_integer = htonl(ip_addr_integer);

    unsigned int mask_integer_format = get_mask_value_in_integer_format(mask);

    COMPLEMENT(mask_integer_format);

    unsigned int broadcast_addr = ip_addr_integer | mask_integer_format;
    broadcast_addr = htonl(broadcast_addr);

    inet_ntop(AF_INET, &broadcast_addr, output_buffer, PREFIX_LEN+1);
    output_buffer[PREFIX_LEN] = '\0';   
}

unsigned int get_ip_integer_equivalent(char * ip_address)
{
    unsigned int ip_addr_integer = 0;
    inet_pton(AF_INET, ip_address, &ip_addr_integer);
    return htonl(ip_addr_integer);
}

void get_abcd_ip_format(unsigned int ip_address,
                        char * output_buffer)
{
    inet_ntop(AF_INET, &ip_address, output_buffer, PREFIX_LEN + 1);
    output_buffer[PREFIX_LEN] = '\0';
}

void
get_network_id(char *ip_address, char mask, char *output_buffer){

    unsigned int mask_integer_format = get_mask_value_in_integer_format(mask);
    unsigned int ip_address_integer = 0 ;
    inet_pton(AF_INET, ip_address, &ip_address_integer);
    unsigned int network_id = ip_address_integer & mask_integer_format;
    network_id = htonl(network_id);
    inet_ntop(AF_INET, &network_id, output_buffer, PREFIX_LEN + 1);     
}

unsigned int get_subnet_cardinality(char mask_value)
{
    return pow(2, MAX_MASK_LEN - mask_value) - 2;   
}

int check_ip_subnet_member_ship(char *network_id,
                                char mask,
                                char * check_ip){
    unsigned int check_ip_integer = 0;
    inet_pton(AF_INET, check_ip, &check_ip_integer);
    unsigned int mask_integer = get_mask_value_in_integer_format(mask);
    unsigned int calculated_nw_id = check_ip_integer & mask_integer;
    unsigned int network_id_integer = 0;
    inet_pton(AF_INET, network_id, &network_id_integer);
    if(network_id_integer == check_ip_integer)
        return 0;

    return -1;    
}

int main (int argc, char **argv)
{
    {
        printf("Testing Q1");
        char ip_address[PREFIX_LEN + 1],
             output_buffer[PREFIX_LEN + 1];

        memset(ip_address, 0, PREFIX_LEN + 1);
        memcpy(ip_address, "192.168.2.10", strlen("192.168.2.10"));
        ip_address[strlen(ip_address)] = '\0';
        char mask = 24;
        memset(output_buffer, 0, PREFIX_LEN + 1);
        get_broadcast_address(ip_address, mask, output_buffer);
        printf("broadcast address = %s\n", output_buffer);
        printf("Testing Q1 Done.\n");
    }
    
}