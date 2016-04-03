#include<fpp_common.h>
#include<fpp_unibit_tries.h>
#include<fpp_obj.h>
#include<fpp_util.h>

int fpp_test_parse_arguments(int c, char **v)
{
    char *r_table = NULL;
    int o;
    
    while ((o = getopt (c, v, "r:d")) != -1) {
	switch (o){
	case 'r': 
	    r_table = strdup (optarg);
	    assert (r_table != NULL);
	    break;
	case 'd':
	    fpp_config.debug = TRUE;
	    break;
	}
    }
    if (!r_table){
	fprintf (stderr,"%s: must give the routing table file!\n",v[0]);
	exit (1);
    }
    if ((fpp_config.r_table = fopen (r_table, "r")) == NULL ){
	perror ("fopen");
	exit (1);
    }
    if (fpp_test_parse_routing_table()) {
	fprintf(stderr, "%s: error parsing routing table file\n", v[0]);
    }
    return 0;
}
int fpp_test_parse_routing_table()
{
    char            line[128];
    char            *tk, *l;
    /* node_info_t     info; */
    /* route_entry_t   entry; */
    char c;
    int  count = 0;

    while ( (c=fgetc(fpp_config.r_table)) != EOF ) {
	if ( c == '\n' ) {
            count++;
	}
    }
    printf("%d\n", count);
    fpp_config.rout_tab.count = count;
    count = 0;
    fpp_config.rout_tab.routingtab =
	fpp_obj_new_route_tab(fpp_config.rout_tab.count);
    fseek(fpp_config.r_table, 0, SEEK_SET);
    
    while (count < fpp_config.rout_tab.count){
	fgets (line, 128, fpp_config.r_table);
    	l = line;
	
    	tk = strsep (&l, " ");
	printf("Route: %s\t", tk);
    	fpp_util_fill_in_addr(&(fpp_config.rout_tab.routingtab[count].route),
			      tk);
	
    	tk = strsep (&l, " ");
	printf("Prefix: %s\t", tk);
	fpp_util_fill_prefix(&(fpp_config.rout_tab.routingtab[count].prefix),
			     tk);

	tk = strsep (&l, "\n");
	printf("Next Hop: %s\t\n", tk);
	fpp_util_fill_in_addr(&(fpp_config.rout_tab.routingtab[count].next_hop),
			      tk);
	
	count++;
    }
    fclose (fpp_config.r_table);
    return 0;
}
int fpp_test_conduct_tests()
{
    return 0;
}
int main(int argc, char **argv)
{
    fpp_test_parse_arguments(argc, argv);
    fpp_test_conduct_tests();
    
}
