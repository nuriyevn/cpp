#include <stdio.h>


int main()
{
	int x = 5;
	int z = 7;

	int y = x * z++;
	printf("y = %d\n\nz= %d\n\n", y, z );
}
