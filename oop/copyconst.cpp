#include <iostream>

using namespace std;

class Line
{
public:
	int getLength(void);
	Line(int len);
	Line(const Line &obj);
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

Line::~Line(void)
{
	cout << "Freeing memory!" << endl;
	delete ptr;
}

int Line::getLength(void)
{
	return *ptr;
}

void display(Line obj)
{
	cout << "Length of line : " << obj.getLength() << endl;
}

int main()
{
	Line line1(10);
	Line line2 = line1;
	display(line1);
	display(line2);
	return 0;
}
