CC = gcc
LD = gcc
CFLAGS = -I.
DFLAGS = -g -DDEBUG
STATIC_LIB = libzc.a
TEST_EXE = ztest

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

all: $(STATIC_LIB) $(TEST_EXE)

$(STATIC_LIB): $(zvec_obj) $(zcmp_obj)
	ar rcs $@ $^

$(TEST_EXE): $(test_obj) $(STATIC_LIB)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(obj) $(STATIC_LIB) $(TEST_EXE)

.PHONY: clean_objs
clean_objs:
	rm -f $(obj)
