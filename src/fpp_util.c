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
    fpp_config.lookup_data.l_time_arr[al].l_time[index].time_taken
    	= time_taken;
    fpp_config.lookup_data.l_time_arr[al].l_time[index].is_sec
    	= is_sec;
    
}
int fpp_util_print_stats()
{
    int           i = 0, j = 0;
    unsigned long sum = 0;
    unsigned long avg = 0;
    uint32_t      a_count = fpp_config.a_count;
    uint32_t      count = fpp_config.lookup_data.count;
    unsigned long time_taken;
    bool_t        is_sec;


    for (i = 0; i<a_count; i++) {
	sum = 0;
	for (j = 0; j<count; j++) {
	    time_taken =
		fpp_config.lookup_data.l_time_arr[i].l_time[j].time_taken;
		
	    is_sec =
		fpp_config.lookup_data.l_time_arr[i].l_time[j].is_sec;
	    if (is_sec) {
		printf("Time Taken(in secs): %u\n", time_taken);
		time_taken = time_taken*1000000;
	    } else {
		printf("Time Taken(in usecs): %u\n", time_taken);
	    }
	    sum = sum + time_taken;
	}
	avg = sum/count;
	printf("Avg time(in usecs): %u\n", avg);
    }
}
