CC = gcc
LD = gcc
CFLAGS = -I.
DFLAGS = -g -DDEBUG

ifdef DEBUG
CFLAGS += $(DFLAGS)
endif

zvec_src = $(wildcard zvec/*.c)
zcmp_src = $(wildcard zcmp/*.c)
test_src = $(wildcard test/*.c)
src = $(zvec_src) $(zcmp_src) $(test_src)

zvec_obj = $(zvec_src:.c=.o)
zcmp_obj = $(zcmp_src:.c=.o)
test_obj = $(test_src:.c=.o)
obj = $(src:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(obj)
	echo "nothing"

clean:
	rm -f $(obj)
