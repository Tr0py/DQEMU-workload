all:offload_test.o
	arm-linux-gnueabihf-gcc-7 --static offload_test.c -l pthread -O0 -g -Wall
	gcc --static offload_test.c -l pthread -o my.out -O0 -g -Wall
