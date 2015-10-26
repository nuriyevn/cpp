#include <iostream>
#include <cstring> // strlen
/*
Bitwise and Logical contancy philosophy sample
*/

using std::cout;
using std::endl;
using std::string;
using std::size_t;
using std::hex;
class CtextBlock
{

public:
	CtextBlock()
	{
		cout << "I'm empty constructor" << endl;
	}
	CtextBlock(char *t)
	{
		const size_t len = strlen(t) + 1;
		pText = new	char[len];
		strcpy(pText, t);
	}
	~CtextBlock()
	{
		delete[] pText;
	}

	CtextBlock(const CtextBlock& rhs)
	{
		cout << "I'm copy constructor" << endl;
		const size_t len = strlen(rhs.pText) + 1;
		pText = new char[len];
		strcpy(pText, rhs.pText);
	}
	
	const CtextBlock&  operator=(const CtextBlock& rhs)
	{
		if (this != &rhs)
		{
			const size_t len = strlen(rhs.pText) + 1;
			delete[] pText;
			pText = new char[len];
			strcpy(pText, rhs.pText);
		}	
		return *this;
	}
	char& operator[](size_t position) const
	{
		return pText[position];
	}
/*	const char& operator[](size_t position) const
	{
		return pText[position];
	}*/
	size_t length() const;
	void print() const
	{
		int len = length();
		for (int i = 0; i < len; i++)
			cout << this->operator[](i);
		cout << endl;
	}
private:
	char *pText;
	mutable size_t textLength; // can be modified in const methods
	mutable bool lengthIsValid; // can be modified in const methods 
};

size_t CtextBlock::length() const
{
	if (!lengthIsValid)
	{
		// We will loose bitwise constancy but we will get logical
		// constancy.
		// from the user point of view we are also bitwise constant method
		textLength = strlen(pText); // need to add mutable in order to
		lengthIsValid = true; // make compiler happy
	}
	return textLength;
}


int main()
{
	
	CtextBlock tb("This is SPARTAAAAAAAA!")	;

	cout << "tb address = " << hex << &tb << endl;

	CtextBlock tb2(tb);
	cout << "tb2 addr = " << hex << &tb2 << endl;
	tb2[0] = 't';

	tb2.print();


	const CtextBlock tb3("Hello");
	tb = tb2;	
	cout << "tb3 addr = "  << hex << &tb3 << endl;
	//tb3 = tb2; // illegal, as bitwise constancy is at work

	 char ptb = &tb3[0];
	 ptb = 'H'; // legal, compiler won't complain, but ruins logical constancy
	
	//tb3.print();

}
