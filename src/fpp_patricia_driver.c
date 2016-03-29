#include<fpp_common.h>
#include<fpp_unibit_tries.h>
#include<fpp_patricia_driver.h>

int fpp_patricia_init(routing_tab_t r)
{
    int count = 0;
    fpp_patricia_head_init();
    while (count < r.count) {
	printf("Patricia Insert :\n");
	fpp_patricia_insert(r.routingtab[count++]);
    }
    return 0;
}
/*Code copied and modified from patricia_test.c(LLVM code base)*/
int fpp_patricia_head_init()
{
    /*
     * Initialize the Patricia trie by doing the following:
     *   1. Assign the head pointer a default route/default node
     *   2. Give it an address of 0.0.0.0 and a mask of 0x00000000
     *      (matches everything)
     *   3. Set the bit position (p_b) to 0.
     *   4. Set the number of masks to 1 (the default one).
     *   5. Point the head's 'left' and 'right' pointers to itself.
     * NOTE: This should go into an intialization function.
     */
    ptrie.phead = fpp_obj_new_ptree();
    ptrie.phead->p_mlen = 1;
    ptrie.phead->p_left = ptrie.phead->p_right = ptrie.phead;
}
int fpp_patricia_insert(routing_tab_entry_t re)
{
    struct ptree *p, *pfind;
    p = fpp_obj_new_ptree();
    p->p_key = re.route.s_addr;
    p->p_m->pm_mask = htonl(fpp_util_prefix_to_mask(re.prefix));

    pfind=pat_search(re.route.s_addr, ptrie.phead);
    if(pfind->p_key==re.route.s_addr) {
	printf("%08x: ", re.route.s_addr);
	printf("Found.\n");
    }
    else {
	/*
	 * Insert the node.
	 * Returns the node it inserted on success, 0 on failure.
	 */
	//printf("%08x: ", addr.s_addr);
	//printf("Inserted.\n");
	p = pat_insert(p, ptrie.phead);
    }
    if (!p) {
	fprintf(stderr, "Failed on pat_insert\n");
	exit(1);
    }
}
int fpp_patricia_tries_lookup(struct in_addr addr, uint32_t index)
{
    struct ptree *pfind;
    pfind=pat_search(addr.s_addr, ptrie.phead);
    if(pfind->p_key == addr.s_addr) {
	printf("Patricia Found.\n");
    } else {
	printf("Patricia Routing miss\n");
    }
}
