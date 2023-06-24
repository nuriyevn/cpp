#include <iostream>
using namespace std;

int swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int find_mindex(int a[], int start, int end)
{
	int mindex = start;
	for (int j = start; j < end; j++) 
		if (a[mindex] > a[j])
			mindex = j;
	return mindex;	
}
void print(int a[], int start, int end)
{
	for (int i = start; i < end; i++)
		cout << a[i] << " ";
	cout << endl;
}

int main()
{
	int a[100];
	int n;
	// reading number of elements
	cin >> n;
	// reading elements
	for (int i = 0; i < n; i++)
		cin >> a[i];

	// insertion sorting
	for (int i = 0; i < n - 1; i++)
	{
		int mindex = find_mindex(a, i, n);
		cout << "mindex = " << mindex << "value=" << a[mindex] << endl;
		
		swap(&a[i], &a[mindex]);
		print(a, 0, n);
	}

	// printing
	for (int i = 0; i < n ; i++)
		cout << a[i] << " ";
	cout << endl; 
}
