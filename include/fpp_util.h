/*Includes*/


/*Function Signatures*/
void fpp_util_fill_in_addr(struct in_addr *in_addr, const char *cp);

void fpp_util_fill_prefix(uint32_t *p, const char *cp);

uint32_t fpp_util_find_bit_kth_pos(uint32_t n, uint32_t k);

bool_t fpp_util_find_time_diff(struct timeval start_time,
			       struct timeval finish_time,
			       unsigned long *time_taken);

int fpp_util_record_time_taken(struct timeval start_time,
			       struct timeval finish_time,
			       lpm_algo_t al, uint32_t index);
