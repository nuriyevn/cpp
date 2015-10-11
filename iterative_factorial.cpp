#include <iostream>
#include <cstdio>
#include <sys/time.h>
using namespace std;

#define REC

long long int iter_fact(int n)
{
	long long int res = 1;
	for (int i = 1; i <= n; i++)
	{
		res = res * i;  	
	}
	return res;
}

long long int rec_fact(int n)
{
	long long int res = 1;
	if (n == 0)
		return 1;
	res = rec_fact(n - 1) * n;
	return res; 
}

int main()
{
	int n;
	long long res = 1;	
	struct timeval tim;
	cin >> n;
#if defined(REC)
	cout << "Calculating iteratively...\n";
	gettimeofday(&tim, NULL);
	double t1 = tim.tv_sec+(tim.tv_usec/1000000.0);
	res = iter_fact(n);
	gettimeofday(&tim, NULL);
	double t2 = tim.tv_sec+(tim.tv_usec/1000000.0);
	printf("%.6lf seconds elapsed\n", t2 - t1);
#elif defined(ITER)
	cout << "Caluculating recursively...\n";
	res = iter_fact(n);
#endif
	cout << rec_fact(n) << endl;
}
