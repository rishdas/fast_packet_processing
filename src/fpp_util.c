#include<fpp_common.h>
#include<fpp_util.h>

void fpp_util_fill_in_addr(struct in_addr *in_addr,
			   const char *cp)
{
    inet_pton(AF_INET, cp, in_addr);
    return;
}

void fpp_util_fill_prefix(uint32_t *p, const char *cp)
{
    *p = atoi(cp);
}
uint32_t fpp_util_find_bit_kth_pos(uint32_t n, uint32_t k)
{
    return ((n & (1<<k)) >> k);
}
bool_t fpp_util_find_time_diff(struct timeval start_time,
			       struct timeval finish_time,
			       unsigned long *time_taken)
{
    *time_taken = finish_time.tv_sec - start_time.tv_sec
        + (finish_time.tv_usec - start_time.tv_usec)/1000000;
    if (*time_taken == 0) {
        *time_taken = (finish_time.tv_sec - start_time.tv_sec)*1000000
	    + finish_time.tv_usec - start_time.tv_usec;
        return FALSE;
    }
    return TRUE;

}
int fpp_util_record_time_taken(struct timeval start_time,
			       struct timeval finish_time,
			       lpm_algo_t al, uint32_t index)
{
    unsigned long time_taken;
    bool_t is_sec;
    
    is_sec = fpp_util_find_time_diff(start_time, finish_time,
				     &time_taken);
    printf("Index: %u\n", index);
    if (is_sec) {
	printf("Time Taken(in secs): %u\n", time_taken);
    } else {
	printf("Time Taken(in usecs): %u\n", time_taken);
    }
    /* fpp_config.lookup_data.l_time_arr[al].l_time[index].time_taken */
    /* 	= time_taken; */
    /* fpp_config.lookup_data.l_time_arr[al].l_time[index].is_sec */
    /* 	= is_sec; */
    
}
