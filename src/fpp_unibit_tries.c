#include<fpp_common.h>
#include<fpp_unibit_tries.h>

int fpp_unibit_tries_init(routing_tab_t r)
{
    int count = 0;
    unibit_info.head = NULL;
    unibit_info.tail = NULL;
    while (count < r.count) {
	fpp_unibit_tries_insert(r.routingtab[count++]);
    }
    return 0;
}

int fpp_unibit_tries_insert(routing_tab_entry_t entry)
{
    uint32_t ctr = 32;
    uint32_t bit = 0;
    static int c = 0;
//    printf("%d Prefix Length: %d\t", c++, entry.prefix);

    while (ctr >= (32 - entry.prefix)) {
	bit = fpp_util_find_bit_kth_pos(ntohl(entry.route.s_addr), ctr);
	switch(bit) {
	case 0:
	    fpp_unibit_tries_branch(0);
	    break;
	case 1:
	    fpp_unibit_tries_branch(1);
	    break;
	default:
	    fprintf(stderr, "Fatal Error!!! Bit not 1 or 0\n");
	}
	ctr--;
    }
    fpp_unibit_tries_update_tail(entry.next_hop);
    fpp_unibit_tries_reset_tail();
}
int fpp_unibit_tries_lookup(struct in_addr addr)
{
    return 0;
}
int fpp_unibit_tries_branch(uint32_t i)
{
    if (unibit_info.head == NULL) {
	unibit_info.head = fpp_obj_new_unibit_node();
	fpp_unibit_tries_reset_tail();
	return;
    }
    switch(i) {
    case 0:
	fpp_unibit_tries_create_z_node();
	break;
    case 1:
	fpp_unibit_tries_create_o_node();
    }
}
int fpp_unibit_tries_create_z_node()
{
    if (unibit_info.tail->z_next == NULL) {
	unibit_info.tail->z_next = fpp_obj_new_unibit_node();
    }
//    printf("Zero\n");
    unibit_info.tail = unibit_info.tail->z_next;
    return 0;
}
int fpp_unibit_tries_create_o_node()
{
    if (unibit_info.tail->o_next == NULL) {
	unibit_info.tail->o_next = fpp_obj_new_unibit_node();
    }
    unibit_info.tail = unibit_info.tail->o_next;
//    printf("One\n");
    return 0;
}
void fpp_unibit_tries_reset_tail()
{
    unibit_info.tail = unibit_info.head;
}
int fpp_unibit_tries_update_tail(struct in_addr addr)
{
    unibit_info.tail->is_terminal = TRUE;
    unibit_info.tail->next_hop = addr;
    return 0;
}
