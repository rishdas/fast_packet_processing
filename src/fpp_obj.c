#include<fpp_common.h>
#include<fpp_unibit_tries.h>
#include<fpp_obj.h>
void *fpp_malloc (size_t l)
{
    void *m;
    m = malloc(l);
    assert(m != NULL);
    memset(m, 0, l);

    return m;
}
routing_tab_entry_t *fpp_obj_new_route_tab(int count)
{
    routing_tab_entry_t *ret;

    ret = (routing_tab_entry_t *)
	fpp_malloc(count*sizeof(routing_tab_entry_t));
    return ret;
}
struct in_addr *fpp_obj_new_lookup_test_tab(int count)
{
    struct in_addr *ret;

    ret = (struct in_addr *)
	fpp_malloc(count*sizeof(struct in_addr));
    return ret;
}
fpp_unibit_node_t *fpp_obj_new_unibit_node()
{
    fpp_unibit_node_t *ret;
    ret =(fpp_unibit_node_t *)
	fpp_malloc(sizeof(fpp_unibit_node_t));
    ret->z_next = NULL;
    ret->o_next = NULL;
    ret->is_terminal = FALSE;
    return ret;
}
lookup_test_time_arr_t *fpp_obj_new_lookup_time_arr()
{
    lookup_test_time_arr_t *ret;
    uint32_t count = fpp_config.lookup_data.a_count;

    ret = (lookup_test_time_arr_t *)
	fpp_malloc(count*sizeof(lookup_test_time_arr_t));

    return ret;   
}
lookup_test_time_t *fpp_obj_new_lookup_time()
{
    lookup_test_time_t *ret;
    uint32_t           count = fpp_config.lookup_data.count;

    ret = (lookup_test_time_t *)
	fpp_malloc(sizeof(count*sizeof(lookup_test_time_t)));

    return ret;
}
