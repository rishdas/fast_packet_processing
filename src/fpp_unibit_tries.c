#include<fpp_common.h>
#include<fpp_unibit_tries.h>

int fpp_unibit_tries_init(routing_tab_t r)
{
    int count = 0;
    unibit_info.head = NULL;
    unibit_info.tail = NULL;
    while (count < r.count) {
	printf("Insert :\n");
	fpp_unibit_tries_insert(r.routingtab[count++]);
    }
    return 0;
}

int fpp_unibit_tries_insert(routing_tab_entry_t entry)
{
    uint32_t ctr = 31;
    uint32_t bit = 0;
    static int c = 0;
//    printf("%d Prefix Length: %d\t", c++, entry.prefix);

    while (ctr >= (31 - entry.prefix)) {
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
	    exit(1);
	}
	ctr--;
    }
    printf("\n");
    fpp_unibit_tries_update_tail(entry.next_hop);
    fpp_unibit_tries_reset_tail();
}
int fpp_unibit_tries_lookup(struct in_addr addr)
{
    int            ctr = 31;
    struct in_addr next_hop;
    char           str[INET_ADDRSTRLEN];
    uint32_t       bit = 0;

    printf("Lookup :\n");
    next_hop.s_addr = 0;
    
    fpp_unibit_tries_reset_tail();
//    inet_pton(AF_INET, "192.168.3.8", &(addr));
    inet_ntop(AF_INET, &(addr), str, INET_ADDRSTRLEN);
    printf("%s:Lookup Addr: %s\n", "tries_lookup", str);

    while(unibit_info.tail != NULL && ctr>=0) {

	if (unibit_info.tail->is_terminal == TRUE) {
	    printf("True\n");
	    next_hop = unibit_info.tail->next_hop;
	}
	bit = fpp_util_find_bit_kth_pos(ntohl(addr.s_addr), ctr);

	switch(bit) {
	case 0:
	    unibit_info.tail = unibit_info.tail->z_next;
	    printf("0 ");
	    break;
	case 1:
	    printf("1 ");
	    unibit_info.tail = unibit_info.tail->o_next;
	    break;
	default:
	    fprintf(stderr, "Fatal Error!!! Bit not 1 or 0\n");
	    exit(1);
	}
	ctr--;
    }
    printf("\n");
    next_hop.s_addr = next_hop.s_addr;
    inet_ntop(AF_INET, &(next_hop), str, INET_ADDRSTRLEN);
    printf("Next Hop: %s\n", str);
    return 0;
}
int fpp_unibit_tries_branch(uint32_t i)
{
    if (unibit_info.head == NULL) {
	unibit_info.head = fpp_obj_new_unibit_node();
	fpp_unibit_tries_reset_tail();
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
    printf("0 ");
    unibit_info.tail = unibit_info.tail->z_next;
    return 0;
}
int fpp_unibit_tries_create_o_node()
{
    if (unibit_info.tail->o_next == NULL) {
	unibit_info.tail->o_next = fpp_obj_new_unibit_node();
    }
    unibit_info.tail = unibit_info.tail->o_next;
    printf("1 ");
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
