#include <iostream>
using namespace std;
template<typename TYPE>
TYPE Twice(TYPE data)
{
    return data * 2;

}

template<class T>
T Add(T n1, T n2)
{
	T result;
	result = n1 + n2;
	return result;
}

template<class T>
double GetAverage(T tArray[], int nElements)
{
	T tSum = T();
	for (int nIndex = 0; nIndex < nElements; ++nIndex)
	{
		tSum += tArray[nIndex];
	}

	return double(tSum) / nElements;
}


class MyInt
{
public:

	//int operator*()
	MyInt& operator+=(const MyInt& right)
	{
		*data = *data + *(right.data);
		return *this;
	}
	operator double() const
	{
		return double(*data);
	}


	MyInt()
	{
		data = new int;
		*data = 0;
	}
	MyInt(int d)
	{
		data = new int;
		*data = d;
	}
	~MyInt()
	{
		delete data;
	}
	MyInt(const MyInt& mi)
	{
		data = new int;
		*data = *(mi.data);
	}
	MyInt& operator=(const MyInt& mi)
	{
		int *newdata = new int;
		*newdata =  *(mi.data);
		delete data;
		data = newdata;
		return *this;
	}
	void set(int v)
	{
		*data = v;
	}
	int& get()
	{
		return *data;
	}

	void print_addr(string name)
	{
		cout << "Pointer addr of" << name << ": " << hex << data << "; value = " << dec << *data << endl;
	}
private:
	int *data;	
};

int main()
{
    int result = Twice(2);
    double d = Twice(3.14159);

    std::cout <<  result << std::endl;
    std::cout << d << std::endl;


	int a = Twice(167);
	int b = Twice(Twice(8));

	int r = Add(a, b);

	std::cout << "r = " << r << std::endl;

	int IntArray[5] = {100, 200, 400, 500 , 1000};
	float FloatArray[3] = {1.55f, 5.44f, 12.36f};

	cout << GetAverage(IntArray, 5);
	cout << endl;
	cout << GetAverage(FloatArray, 3);
	cout << endl;

	MyInt i1(5);
	MyInt i2(45);
	
	i1.print_addr("i1");
	i2.print_addr("i2");
		
	i2 = i1;

	i1.print_addr("i1");
	i2.print_addr("i2");

	MyInt i3 = i2; // copy const;
	
	i2.print_addr("i2");
	i3.print_addr("i3");

	MyInt array[2];
	array[0].set(67);
	array[1].set(2);
	cout << GetAverage(array, 2);
	
}
