/*Function Signatures*/
#include<patricia.h>
typedef struct fpp_patricia_info_{
    struct ptree *phead;
}fpp_patricia_info_t;

fpp_patricia_info_t ptrie;

int fpp_patricia_init(routing_tab_t r);
int fpp_patricia_head_init();
int fpp_patricia_insert(routing_tab_entry_t entry);
int fpp_patricia_tries_lookup(struct in_addr addr, uint32_t index);
