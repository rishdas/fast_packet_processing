#include<fpp_common.h>
#include<fpp_util.h>

void fpp_util_fill_in_addr(in_addr_t *in_addr, const char *cp)
{
    *in_addr = inet_addr(cp);
    return;
}

void fpp_util_fill_prefix(uint32_t *p, const char *cp)
{
    *p = atoi(cp);
}
