CC=gcc
SOURCEDIR = src/app/c
SOURCES = $(wildcard $(SOURCEDIR)/*.c)

PROGS = $(patsubst %.c,%,$(SOURCES))

all: $(PROGS)

%: %.c

	$(CC) $(CFLAGS)  -o $@ $<
clean: 
	rm -f $(PROGS)