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
