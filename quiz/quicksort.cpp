#include <iostream>
using namespace std;
void quicksort(int [], int, int);
int partition(int[], int, int);

void quicksort(int a[], int left, int right)
{
	int j;
	if (left < right)
	{
		j = partition(a, left, right);
		quicksort(a, left, j-1);
		quicksort(a, j+1, right);
	}
}

int swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

int partition(int a[], int left, int right)
{
	int pivot, i, j, t;
	pivot = a[left];
	i = left; j = right + 1;

	while (1)
	{
		do ++i; while ( a[i] <= pivot && i <= right);
		do --j; while ( a[j] > pivot);
		if (i >= j) break;
		swap(a[i], a[j]);				
	}
	swap(a[left], a[j]);
	return j;
}

int main()
{
	int a[] = {7, 12, 1, -2, 0, 15, 4, 11, 9};
	
	int i;
	cout << "\nUnsorted array is: ";
	for (int i = 0; i < 9; ++i)
		cout << " " << a[i] << " ";

	quicksort(a, 0, 8);
	
	cout << "\nSorted array is: ";
	for (i = 0; i < 9; i++)
		cout << " " << a[i] << " ";

	return 0;
}
