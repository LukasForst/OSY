#EXTRA_CFLAGS ?=-fsanitize=address -fno-omit-frame-pointer
FILES=main.o buffers.o job_provider.o workplace_chain.o commands.o workplace_provider.o
CC=gcc
CFLAGS=-g -Wall -Iinclude

factory: $(FILES)
	$(CC) -o $@ $(FILES)

run: factory
	./factory

%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $(EXTRA_CFLAGS) $<

clean:
	rm $(FILES)

tar: factory
	make clean
	tar czf hs06_osy.tgz Makefile *.[ch]