#include <iostream>
using namespace std;

class IntVec 
{
public:
	IntVec(int n): data(new int[n]), size(n)
	{
	}
	~IntVec() 
	{
		delete[] data;
	}
	int& operator[] (int n)
	{
		return data[n];
	}
	const int& operator[] (int n) const
	{
		return data[n];
	}
	IntVec(const IntVec& v):
		data(new int[v.size]),
		size(v.size) 
	{
		std::copy(v.data, v.data + v.size, data);
	}
	IntVec& operator=(const IntVec& v)
	{
		int* newdata = new int[v.size];
		std::copy(v.data, v.data + v.size, newdata);
		delete[] data;
		data = newdata;
		size = v.size;
		return *this;
	}
private:
	int* data;
	int size;
	//IntVec(const IntVec&);
	//IntVec& operator=(const IntVec&);
};



int main()
{
	IntVec x(100);
	IntVec y = x;
	IntVec z;	
	return 0;
}



