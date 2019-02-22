#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#define  PACK  __attribute__  ((packed))
typedef int cache_line_int __attribute__((aligned(0)));
// FS: [page__pad]	fast
// NONFS: [page]	slow
#define NONFS
#ifdef NONFS
struct data
{
	cache_line_int a;
	cache_line_int b;
};
#endif
#ifdef FS
struct data
{
	int a;
	int b;
};
#endif

//global foos
int ta,tb;
int done1,done2;

#define MAX_NUM 500000000

void* thread_func_1(void* param)
{
	//while (1);
	struct timeval start, end;
	gettimeofday(&start, NULL);
	struct data* d = (struct data*)param;
	for (int i=0; i<MAX_NUM; ++i)
	{
		++d->a;
	}
	gettimeofday(&end, NULL);
	//printf("thread 1, time=%d\n", (int)(end.tv_sec-start.tv_sec)*1000000+(int)(end.tv_usec-start.tv_usec));
	ta = ((int)(end.tv_sec-start.tv_sec)*1000000+(int)(end.tv_usec-start.tv_usec));
	//while (1);
	done1=1;
	return NULL;
}

void* thread_func_2(void* param)
{
	//while (1);
	struct timeval start, end;
	gettimeofday(&start, NULL);
	struct data* d = (struct data*)param;
	for (int i=0; i<MAX_NUM; ++i)
	{
		++d->a;
	}
	gettimeofday(&end, NULL);
	tb = ((int)(end.tv_sec-start.tv_sec)*1000000+(int)(end.tv_usec-start.tv_usec));
	//printf("thread 2, time=%d\n", (int)(end.tv_sec-start.tv_sec)*1000000+(int)(end.tv_usec-start.tv_usec));
	//while (1);
	done2=1;
	return NULL;
}

int main()
{
	
	struct data d = {a:0, b:0};
	printf("sizeof(data) : %d\n", sizeof(struct data));
	pthread_t t1, t2;
	struct timeval start, end;
	gettimeofday(&start, NULL);
	pthread_create(&t1, NULL, thread_func_1, &d);
	pthread_create(&t2, NULL, thread_func_2, &d);
	//pthread_join(t1, NULL);
	//pthread_join(t2, NULL);
	while (done1 == 0 || done2 == 0);
	gettimeofday(&end, NULL);
	printf("main time=%fms\n", ((float)(end.tv_sec-start.tv_sec)*1000000+(float)(end.tv_usec-start.tv_usec))/1000);
	printf("ta: %d\ntb: %d\n",ta,tb);
	printf("end,done1=%d,done2=%d, a=%d,b=%d\n",done1,done2, d.a, d.b);
	//pthread_kill(&t1,0);
	//pthread_kill(&t2,0);
	return 0;
}
