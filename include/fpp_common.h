/*Includes*/
#include<stdio.h>
#include<stdint.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

/*Hash Defines*/
#define bool_t char
#define TRUE (bool_t)1
#define FALSE (bool_t)0

/*Structures*/
typedef struct routing_tab_entry_
{
    struct in_addr next_hop;
    struct in_addr route;
    uint32_t  prefix;
}routing_tab_entry_t;

typedef struct routing_table_
{
    routing_tab_entry_t *routingtab;
    uint32_t count;
}routing_tab_t;

typedef struct fpp_config_
{
    FILE   *r_table;
    bool_t debug;
    routing_tab_t rout_tab;
}fpp_config_t;


/*Global Variables*/
fpp_config_t fpp_config;

/*Function Signatures*/

int fpp_test_parse_arguments(int argc, char **argv);
int fpp_test_parse_routing_table();
int fpp_test_conduct_tests();


