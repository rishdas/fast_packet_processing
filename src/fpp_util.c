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
    if (is_sec) {
	printf("Time Taken(in secs): %10u ", time_taken);
    } else {
	printf("Time Taken(in usecs): %10u ", time_taken);
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
unsigned long fpp_util_prefix_to_mask(uint32_t prefix)
{
    unsigned long mask;
    unsigned long remainder;
    unsigned long no_octets;

    no_octets = prefix/8;
    remainder = prefix%8;
    switch(no_octets) {
    case 0:
	mask = 0x00000000;
	break;
    case 1:
	mask = 0xff000000;
	break;
    case 2:
	mask = 0xffff0000;
	break;
    case 3:
	mask = 0xffffff00;
	break;
    case 4:
	mask = 0xffffffff;
	return mask;
    default:
	perror("Prefix to mask conversion error");
	exit(1);
    }
    /*TODO fix it*/
//    mask = mask | fpp_util_get_rem_mask(remainder);
}
unsigned long fpp_util_get_rem_mask(unsigned long rem)
{
    unsigned long mask = 0x00000000;
    switch(rem) {
    case 0:
	mask = 0x00000000;
	break;
    case 1:
	mask = 0x00000001;
	break;
    case 2:
	mask = 0x00000003;
	break;
    case 3:
	mask = 0x00000007;
	break;
    case 4:
	mask = 0x0000000F;
	break;
    case 5:
	mask = 0x0000001F;
	break;
    case 6:
	mask = 0x0000003F;
	break;
    case 7:
	mask = 0x0000007F;
	break;
    default:
	perror("Rem Prefix to mask conversion error");
	exit(1);
    }
    return mask;
}
/* void fpp_util_print_addr(unsigned long s_addr) */
/* { */
/*     char           str[INET_ADDRSTRLEN]; */
/*     struct in_addr addr; */

/*     addr.s_addr = s_addr; */
/*     inet_ntop(AF_INET, &(addr), str, INET_ADDRSTRLEN); */
/*     printf("Addr: %17s \n", str); */
/* } */
