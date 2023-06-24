#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int increase(int i ) { return ++i;}
int sum(int i, int j) { return i+j;}

void output_vectors(vector<int>& vectorOne, vector<int>& vectorTwo)
{
	cout << "\nAfter transform:" << endl;
	cout << "vectorOne elements are:";
	for (unsigned int i = 0; i < vectorOne.size(); i++)
		cout << vectorOne[i] << " ";
	cout << endl;	
	cout << "vectorTwo elements are: ";
	for (unsigned int i = 0; i < vectorTwo.size(); i++)
		cout << vectorTwo[i] << " ";
	cout << endl; 
}

int main()
{
	int someNums[] = {10, 20, 30, 40, 50};
	vector<int> vectorOne(someNums, someNums + sizeof(someNums) / sizeof(int));
	vector<int> vectorTwo;
	vector<int>::iterator it;

	output_vectors(vectorOne, vectorTwo);	

	vectorTwo.resize(vectorOne.size()); //allocate space

	std::transform(vectorOne.begin(), vectorOne.end(), vectorTwo.begin(), increase);
	
	output_vectors(vectorOne, vectorTwo);

	transform(vectorOne.begin(), vectorOne.end(), vectorTwo.begin(), vectorOne.begin(), sum);

	output_vectors(vectorOne, vectorTwo);

	transform(vectorOne.begin(), vectorOne.end(), vectorTwo.begin(), vectorTwo.begin(), sum);
	
	output_vectors(vectorOne, vectorTwo);
	return 0;
}


