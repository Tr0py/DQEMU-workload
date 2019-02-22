all:offload_test.o
	arm-linux-gnueabihf-gcc --static offload_test.c -l pthread -O0 -g -Wall
	gcc --static offload_test.c -l pthread -o my.out -O0 -g -Wall
