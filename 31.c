#include <stdio.h>

int postincrement(int *z)
{
	int temp = *z;
	*z++;
	return temp;
}


int main()
{
	int i[] = {3, 5};
	int *p = i;
	int j = postincrement(--*p);

	printf ("j = %d\n\n; *p = %d\n\n", j, *p);

}
