#include <sys/time.h>
#include <stdio.h>

int main()
{
	struct timeval tim;
	gettimeofday(&tim, NULL);
	double t1 = tim.tv_sec+(tim.tv_usec/1000000.0);
	gettimeofday(&tim, NULL);
	double t2 = tim.tv_sec + (tim.tv_usec/1000000.0);
	printf("%.6lf seconds elapsed\n", t2-t1);
	return 0;
}
