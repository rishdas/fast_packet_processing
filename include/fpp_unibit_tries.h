/*Includes*/

/*Structures*/
typedef struct fpp_unibit_node_
{
    bool_t                  is_terminal;
    struct in_addr          next_hop;
    struct fpp_unibit_node_ *z_next;
    struct fpp_unibit_node_ *o_next;
}fpp_unibit_node_t;

typedef struct fpp_unibit_info_ {
    fpp_unibit_node_t *head;
    fpp_unibit_node_t *tail;
}fpp_unibit_info_t;

fpp_unibit_info_t unibit_info;

/*Function Signatures*/
int fpp_unibit_tries_init(routing_tab_t r);
int fpp_unibit_tries_insert(routing_tab_entry_t entry);
int fpp_unibit_tries_lookup(struct in_addr addr);
int fpp_unibit_tries_branch(uint32_t i);
void fpp_unibit_tries_reset_tail();
int fpp_unibit_tries_create_z_node();
int fpp_unibit_tries_create_o_node();
int fpp_unibit_tries_update_tail(struct in_addr addr);
