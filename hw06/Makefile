EXTRA_CFLAGS ?=-fsanitize=address -fno-omit-frame-pointer
bin:
	gcc -Wall -g ${EXTRA_CFLAGS} -o factory main.c buffers.h buffers.c factory.h factory.c global.h workplace_chain.h workplace_chain.c