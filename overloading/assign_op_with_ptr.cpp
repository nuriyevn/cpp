#include <iostream>

using namespace std;

class Line
{
public:
	int getLength(void) const;
	//Line() {} -> this constr doesn't exist, because we have defined another constructor
	// we can write = default; 
	// to explicitly define an empty constr  or we can specify = delete; to explicitly remove it
	Line(int len);
	Line(const Line &obj);
	Line& operator=(const Line& rhs);
	~Line();

private:
	int *ptr;
};

Line::Line(int len)
{
	cout << "Normal constructor allocating ptr" << endl;
	ptr = new int;
	*ptr = len;
};

Line::Line(const Line& obj)
{
	cout << "Copy constructor allocating ptr." <<  endl;
	ptr = new int;
	*ptr = *obj.ptr;
};


Line& Line::operator=(const Line& rhs)
{
	cout << "Copy assignment operator allocating ptr." <<  endl;
	if (this != &rhs)
	{
		if (ptr != NULL)
			delete ptr;
		
		ptr = new int;
		*ptr = *rhs.ptr;
	}
	return *this;
}

Line::~Line(void)
{
	cout << "Freeing memory!" << endl;
	delete ptr;
}

int Line::getLength(void) const
{
	return *ptr;
}

void display(const Line& obj)
{
	cout << "Length of line : " << obj.getLength() << endl;
}

int main()
{
	Line line1(10);
	Line line2 = line1;
	Line line3(15);
	//Line line4; // Line() is not declared because another constructor exists, 
	display(line1);
	display(line2);
	display(line3);

	line2 = line3;

	display(line1);
	display(line2);
	display(line3);
	return 0;
}