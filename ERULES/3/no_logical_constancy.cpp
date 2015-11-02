#include <iostream>
#include <cstring>
using std::cout;
using std::endl;
using std::size_t;

class CtextBlock
{
public:
	CtextBlock(char *t)
	{
		cout << "Custom constuctor" << endl;
		size_t sz = strlen(t) + 1;
		pText = new char[sz];
		strcpy(pText, t);
	}
	~CtextBlock() { delete pText; }
	char& operator[](size_t position) const
	{	
		return pText[position];
	}
	void print() const
	{
		int len = strlen(pText);
		for (int i = 0; i < len; i++)	
			cout << pText[i];
		cout << endl;

	}
private:
	char *pText;
};


int main()
{
	const CtextBlock cctb("Hello");
	char &pc = cctb[0]; // violates logical constancy
	pc =  'j'; // violates logical constancy

	cctb.print();
}
