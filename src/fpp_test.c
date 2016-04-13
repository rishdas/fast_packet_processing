#include<fpp_common.h>
#include<fpp_unibit_tries.h>
#include<fpp_obj.h>
#include<fpp_util.h>

int fpp_test_parse_arguments(int c, char **v)
{
    char *r_table = NULL;
    char *l_file = NULL;
    int o;
    
    while ((o = getopt (c, v, "r:l:d")) != -1) {
	switch (o){
	case 'r': 
	    r_table = strdup (optarg);
	    assert (r_table != NULL);
	    break;
	case 'd':
	    fpp_config.debug = TRUE;
	    break;
	case 'l':
	    l_file = strdup (optarg);
	    assert (l_file != NULL);
	    break;
	default:
	    fprintf(stderr, "Error option !!!!\n\n");
	    exit(1);
	}
    }
    /*TODO Remove*/
    fpp_config.a_count = 1;
    
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
    /*Lookup Table*/
    if (!l_file){
	fprintf (stderr,"%s: must give the lookup ip address file!\n",v[0]);
	exit (1);
    }
    if ((fpp_config.l_file = fopen (l_file, "r")) == NULL ){
	perror ("fopen");
	exit (1);
    }
    if (fpp_test_parse_lookup_file()) {
	fprintf(stderr, "%s: error parsing routing table file\n", v[0]);
    }
    return 0;
}
int fpp_test_parse_routing_table()
{
    char            line[128];
    char            *tk, *l;
    char c;
    int  count = 0;

    while ( (c=fgetc(fpp_config.r_table)) != EOF ) {
	if ( c == '\n' ) {
            count++;
	}
    }
    fpp_config.rout_tab.count = count;
    count = 0;
    fpp_config.rout_tab.routingtab =
	fpp_obj_new_route_tab(fpp_config.rout_tab.count);
    fseek(fpp_config.r_table, 0, SEEK_SET);
    
    while (count < fpp_config.rout_tab.count){
	fgets (line, 128, fpp_config.r_table);
    	l = line;
	
    	tk = strsep (&l, " ");
	printf("Route: %17s ", tk);
    	fpp_util_fill_in_addr(&(fpp_config.rout_tab.routingtab[count].route),
			      tk);
	
    	tk = strsep (&l, " ");
	printf("Prefix: %3s ", tk);
	fpp_util_fill_prefix(&(fpp_config.rout_tab.routingtab[count].prefix),
			     tk);

	tk = strsep (&l, "\n");
	printf("Next Hop: %17s\n", tk);
	fpp_util_fill_in_addr(&(fpp_config.rout_tab.routingtab[count].next_hop),
			      tk);
	
	count++;
    }
    fclose (fpp_config.r_table);
    return 0;
}
int fpp_test_parse_lookup_file()
{
    char            line[128];
    char            *tk, *l;
    char            c;
    int             count = 0;
    char            str[INET_ADDRSTRLEN];//DEBUG

    while ( (c=fgetc(fpp_config.l_file)) != EOF ) {
	if ( c == '\n' ) {
            count++;
	}
    }
    fpp_config.lookup_data.count = count;
    count = 0;
    fpp_config.lookup_data.d_addr_tab =
	fpp_obj_new_lookup_test_tab(fpp_config.lookup_data.count);
    fseek(fpp_config.l_file, 0, SEEK_SET);

    fpp_test_lookup_test_init();

    while (count < fpp_config.lookup_data.count){
	fgets (line, 128, fpp_config.l_file);
    	l = line;
	
    	tk = strsep (&l, "\n");
	printf("Lookup String: %17s\n", tk);
    	fpp_util_fill_in_addr(&(fpp_config.lookup_data.d_addr_tab[count]),
			      tk);
	count++;
    }
    
    fpp_test_conduct_tests();
    fclose (fpp_config.l_file);
    return 0;
    
}
int fpp_test_lookup_test_init()
{
    int i = 0;
    fpp_config.lookup_data.l_time_arr =
	fpp_obj_new_lookup_time_arr();
    for (i = 0; i < fpp_config.a_count; i++) {
	fpp_config.lookup_data.l_time_arr[i].l_time =
	    fpp_obj_new_lookup_time();
	fpp_config.lookup_data.l_time_arr[i].count =
	    fpp_config.lookup_data.count;
    }
}

int fpp_test_conduct_tests()
{
    struct in_addr addr;
    int            i = 0;
    char           str[INET_ADDRSTRLEN];
    uint32_t       count = fpp_config.lookup_data.count;

    fpp_unibit_tries_init(fpp_config.rout_tab);
    printf("Count: %u\n", count);
    for (i = 0; i < count; i++) {
	addr = fpp_config.lookup_data.d_addr_tab[i];
    
	fpp_unibit_tries_lookup(addr, i);
    }
    return 0;
}
int main(int argc, char **argv)
{
    fpp_test_parse_arguments(argc, argv);
    
}
