#include<fpp_common.h>
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
