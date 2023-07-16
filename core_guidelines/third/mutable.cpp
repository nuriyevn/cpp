#include <iostream>
#include <cstring>
using std::cout;
using std::endl;
using std::size_t;


/*

https://stackoverflow.com/questions/5689366/is-it-possible-for-a-non-member-function-to-return-a-const-value

It can be done, but doesn't necessarily make a lot of sense. If you return something by value, 
what the caller receives is a temporary copy of what you returned, so they normally can't modify it anyway.
It can make more sense when you're returning a reference; if (for example) you receive something by reference, 
and return a reference to the same, you probably want to const-qualify what you return if what you received was const-qualified.
 This typically means overloading your function for const/non-const parameter, each with matching return type.
Edit: This can deal with (for example) a problem that arose in C with functions like strstr and strchr, 
which take a const-qualified pointer, but return a pointer into the same data (string, in this case) that's not const-qualified. 
In C, these form a hole in the type system, where you can accidentally modify (or at least try to) something that was intended to be const, 
without any (visible) cast.
char *s = strchr("Mystring", 'i');
*s = 'b'; // UB
*/
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
	size_t textLength;
	
};


int main()
{
	const CtextBlock cctb("Hello");
	char &pc = cctb[0]; // violates logical constancy
	pc =  'j'; // violates logical constancy

	cctb.print();
}
