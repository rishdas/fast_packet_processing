#include<stdint.h>
typedef struct routing_table_
{
    uint32_t next_hop;
    uint32_t route;
    uint32_t prefix;
} routing_table_t;
int fpp_convert_text_to_table(FILE *fp, routing_table_t *rout_table,
			      int no_routes);
int fpp_test_parse_arguments(int argc, char **argv);
int fpp_test_conduct_tests();

