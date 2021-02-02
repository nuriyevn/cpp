#include <iostream>
#include <sstream>

using namespace std;

//Implement the class Box  
//l,b,h are integers representing the dimensions of the box

// The class should have the following functions : 
class Box
{
private:
	int l;
	int b;
	int h;
public:
	Box(int _l, int _b, int _h) : l(_l), b(_b), h(_h) {}
	Box() { l = b = h = 0; }
	Box(const Box &box) { l = box.l; b = box.b; h = box.h; }
	int getLength() { return l; }
	int getBreadth() { return b; }
	int getHeight() { return h; }
	long long CalculateVolume() { 
		return (long long)l * b * h; 
	}
	bool operator<(Box& b)
	{
		if (this->l < b.l)
		{
			return true;
		}

		if ((this->b < b.b) && (this->l == b.l)) {
			return true;
		}

		if ((this->h < b.h) && (this->b == b.b) && (this->h == b.h))
		{
			return true;
		}

		return false;
	}

	friend ostream& operator<<(ostream& out, const Box& b)
	{
		return out << b.l << " " << b.b << " " << b.h;
	}


};

int main()
{

	// Constructors: 
// Box();
// Box(int,int,int);
// Box(Box);


// int getLength(); // Return box's length
// int getBreadth (); // Return box's breadth
// int getHeight ();  //Return box's height
// long long CalculateVolume(); // Return the volume of the box

//Overload operator < as specified
//bool operator<(Box& b)

//Overload operator << as specified
//ostream& operator<<(ostream& out, Box& B)
	int lineCount = 0 ;
	int i = 0;
	cin >> lineCount;
	getchar();


	Box *box1 = nullptr;
	stringstream out;


	while (i < lineCount)
	{
		char str[1024];
		string str2;
		
		getline(cin, str2);
		//cin.getline(str, 1024, '\n');
		stringstream ss(str2);
		short op_code = 0;
		ss >> op_code;

		switch (op_code) // PRINT DIMENSIONS
		{
			case 2:
			{
				if (box1 != nullptr)
					delete box1;

				int l =0 , b = 0, h = 0;
				ss >> l >> b >> h;
				box1 = new Box(l, b, h);

				out << *box1 << endl;;
				break;
			}
			case 5:
			{
				out << *box1 << endl;;
				break;
			}
			case 3: // COMPARE
			{
				int l = 0, b = 0, h = 0;
				ss >> l >> b >> h;
				Box box2(l, b, h);
				if (*box1 < box2)
				{
					out << "Lesser" << endl;
				}
				else
				{
					out << "Greater" << endl;
				}
				break;
			}
			case 4: // VOLUME
			{
				if (box1 == nullptr)
				{
					exception e;
					throw e;
				}
				out << box1->CalculateVolume() << endl;
				break; // Read next line, ignore 
			}
		}
		i++;
	}

	cout << out.str();
	if (box1 != nullptr)
	{
		delete box1;
	}
}


/*
5
2 3 4 5
4
5
4
2 4 6 7
*/

/*
6
2 1039 3749 8473
4
3 1456 3836 283
3 729 3749 272
2 4839 283 273
4
*/
