#include <iostream>
#include <ctime>
#include <cstdlib>
using std::string;
using std::size_t;
using std::cout;
using std::endl;


class TextBlock
{
public:
	TextBlock(string t)
		: text(t)
	{
	}
	~TextBlock()
	{
	}
	TextBlock(const TextBlock& rhs)
	{	
		this->text = rhs.text;
			
	}
	const char & operator[](size_t position) const
	{
		return text[position];
	}
	char& operator[](size_t position)
	{
		return text[position];
	}
	int length() const
	{
		return text.length();
	}
private:
	string text;
};

// @todo - prove that const version of operator[] method at TexBlock class work faster than
// corresponding method with non-const version

void print(const TextBlock& ctb)
{
	cout << ctb[0]; // calling corresponding const operator method
}

int main()
{
	srand(time(0));
	clock_t start, end;
	int index;
	
	TextBlock tb("Hello");
	

	size_t sz = tb.length();

	start = clock();
	for (int i = 0; i < 10000000; i++)
	{
		index = rand() % sz;
		tb[index];
	}
	end = clock();
	cout << "Time spent non-constant " << end - start << endl;
	
	const TextBlock ctb("World") ;
	size_t csz = ctb.length();
	start = clock();
	for (int i = 0; i < 10000000; i++)
	{
		index = rand() % csz;
		ctb[index];
	}
	end = clock();
	cout << "Time spent constant " << end - start << endl;


//	ctb[0] = 'x'; // illegal
	tb[0] = 'h'; // legal

}
	
