# Makefile
# Copied from Source: https://github.com/rishdas/routing_information_protocol/blob/master/Assignment3/Makefile

INCDIR=../include
SRCDIR=./src
PROG = fpp
CFLAGS=-I. -I$(INCDIR) -ggdb -gdwarf-2 
LDFLAGS=
CC=gcc

all: $(PROG)

$(PROG):
	make -C src
	$(CC) -o $@ $^ $(SRCDIR)/*.o $(CFLAGS) $(LDFLAGS)

clean:
	make -C src clean
	rm -f *.o *~ $(PROG) core *.log
