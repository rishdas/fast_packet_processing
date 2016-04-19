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
#include<sys/time.h>

/*Hash Defines*/
#define bool_t char
#define TRUE (bool_t)1
#define FALSE (bool_t)0
#define MAX_ALGO 10
#define MAX_LOOKUP_ENTRY 200

typedef enum lpm_algo_ {
    UNIBIT_TRIES,
    PATRICIA_TRIES
}lpm_algo_t;

/*Structures*/
typedef struct lookup_test_time_
{
    unsigned long time_taken;
    bool_t is_sec;
}lookup_test_time_t;

typedef struct lookup_test_time_arr_
{
    lookup_test_time_t l_time[MAX_LOOKUP_ENTRY];
    uint32_t count;
}lookup_test_time_arr_t;

typedef struct routing_tab_entry_
{
    struct in_addr next_hop;
    struct in_addr route;
    uint32_t  prefix;
}routing_tab_entry_t;

typedef struct routing_tab_
{
    routing_tab_entry_t *routingtab;
    uint32_t count;
}routing_tab_t;

typedef struct lookup_test_tab_
{
    struct in_addr *d_addr_tab;
    lookup_test_time_arr_t l_time_arr[MAX_ALGO];
    uint32_t count;
    uint32_t a_count;
}lookup_test_tab_t;

typedef struct fpp_config_
{
    FILE   *r_table;
    FILE   *l_file;
    bool_t debug;
    routing_tab_t rout_tab;
    lookup_test_tab_t lookup_data;
    uint32_t a_count;
}fpp_config_t;


/*Global Variables*/
fpp_config_t fpp_config;

/*Function Signatures*/

int fpp_test_parse_arguments(int argc, char **argv);
int fpp_test_parse_routing_table();
int fpp_test_conduct_tests();
int fpp_test_parse_lookup_file();
int fpp_test_lookup_test_init();


