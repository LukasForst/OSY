plain: hexconv.c
	gcc hexconv.c -o main -nostdlib -nostdinc -static -m32 -Wall -g -O2

test: test.c
	gcc test.c -o test -nostdlib -nostdinc -static -m32 -Wall -g -O2

run: plain
	./main