#include <iostream>
#include <cstring> // strlen
/*
Bitwise and Logical contancy philosophy sample
*/

using std::cout;
using std::endl;
using std::string;
using std::size_t;

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
		const size_t len = strlen(rhs.pText) + 1;
		char *newText = new char[len];
		strcpy(newText, rhs.pText);
		delete[] pText;
		pText = newText;
	}
	const CtextBlock&  operator=(const CtextBlock& rhs)
	{
		if (this != &rhs)
		{
			const size_t len = strlen(rhs.pText) + 1;
			char *newText = new char[len];
			strcpy(newText, rhs.pText);
			delete[] pText;
			pText = newText;
		}	
		return *this;
	}
	char& operator[](std::size_t position) const
	{
		return pText[position];
	}
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
	CtextBlock tb2(tb);
	tb2[0] = 't';
	tb2.print();


	const CtextBlock tb3("Hello");
	tb = tb2;	
	//tb3 = tb2; // illegal, as bitwise constancy is at work

	//char& ptb = tb3[1];
	//ptb = 'H'; // legal, compiler won't complain, but ruins logical constancy
	
	tb3.print();

}
