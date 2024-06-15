all:
	gcc list.c list.h test.c -o test
clean:
	rm -rf test *.o
