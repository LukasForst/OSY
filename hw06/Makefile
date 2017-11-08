EXTRA_CFLAGS ?=-fsanitize=address -fno-omit-frame-pointer
FILES=main.o buffers.o job_provider.o workplace_chain.o commands.o workplace_provider.o worker_provider.o worker.o
CC=gcc
CFLAGS=-pthread -g -Wall -Iinclude

factory: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)

run: factory
	./factory

%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $(EXTRA_CFLAGS) $<

clean:
	rm $(FILES)
	rm factory
	rm hw06_osy.tgz

zip:
	zip hw06_osy.zip Makefile *.[ch]