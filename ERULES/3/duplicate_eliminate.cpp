#include <iostream>
#include <cstring> // strlen
using std::cout;
using std::endl;
using std::size_t;

class CtextBlock
{
public:
	CtextBlock(char *t)
	{
		const size_t len  = strlen(t) + 1;
		pText = new char[len];
		strcpy(pText, t);
		textLength = length();
	}
	~CtextBlock()
	{
		delete[] pText;
	}
		
	const char& operator[](size_t position) const
	{
		if (position < 0 && position > textLength - 1)
		{
			cout << "Range checking error" << endl;
		}
			
		return pText[position];
	}
	char& operator[](size_t position)
	{
		return pText[position];
	}
	size_t length() const
	{
	}
private:
	char *pText;
	mutable	size_t textLength;
	mutable bool lengthIsValid;
};

size_t CtextBlock::length() const
{
	if (!lengthIsValid)
	{
		textLength = strlen(pText);
		lengthIsValid = true;
	}

	return textLength;
}

int main()
{
	
	CtextBlock tb("Hello World");

}

