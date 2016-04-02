# Makefile template
# Copied from : https://github.com/rishdas/routing_information_protocol/blob/master/Assignment3/src/Makefile

INCDIR=../include
DEPS = fpp_common.h fpp_unibit_tries.h
OBJ = fpp_test.o fpp_unibit_tries.o
CFLAGS=-I. -I$(INCDIR) -ggdb -gdwarf-2 
CC=gcc

all: $(OBJ)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


clean:
	rm -f *.o *~ 
