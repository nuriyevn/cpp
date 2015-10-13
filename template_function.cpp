#include <iostream>
//www.codeproject.com/Articles/257589/An-Idiots-Guide-to-Cplusplus-Templates-Part-1
using namespace std;
template<typename TYPE>
TYPE Twice(TYPE data)
{
    return data * 2;

}

template<class T>
void TwiceIt(T& tData)
{
	tData *= 2;
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
	int& operator*()
	{
		return *data;
	}
	
	MyInt& operator+=(const MyInt& right)
	{
		*data = *data + *(right.data);
		return *this;
	}

	MyInt operator*(MyInt& right)
	{
		MyInt r = *data * *(right.data);
		cout << "MyInt operator*(MyInt& right); is called";
		cout << endl;
		return r;
	}


	MyInt& operator*=(const MyInt& right)
	{
		cout << "MyInt& operator*=(const MyInt& right)" << endl;
		*data = *data * *(right.data);
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
		cout << "MyInt(int d); is called. d = " << d << endl;
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
	int& get() const
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


/*MyInt operator*(int x, const MyInt& mint)
{
	MyInt r;
	r =  x * mint.get();
	return r;
}*/

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
	cout << GetAverage(array, 2) << endl;;

	int ti = 6;

	MyInt brand_new(78);

	TwiceIt(brand_new);
	cout << "ti = " << *brand_new << endl;


	cout << "Multiplication example:" << endl;

	MyInt m1(7);
	MyInt m2(10);
	MyInt m3;
	m3 = m1 * m2;

	cout << "Result of : " << *m1 << " * " << *m2 << " = " << *m3;
	cout << endl;

	MyInt m4;
	m4 = m3 * 5;
	MyInt m5;
	m5 = 6 * m3;

	cout << "m4 = " << *m4 << "; m5 = " << *m5 << endl;
	MyInt m6;
	m6 = m5 * m4;
	cout << "m6 = " << *m6 << endl;

}
