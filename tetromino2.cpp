#include <iostream>
#include <vector>

using namespace std;

class Tetromino
{
public:
	virtual void info() = 0;
	virtual ~Tetromino();
};

class Stick : public Tetromino
{
public:
	void info()
	{
		cout << "Stick" << endl;
	};
};

class Square :  public Tetromino
{
public:
	void info()
	{
		cout << "Sqaure" << endl;
	};
};

class TTurn : public Tetromino
{
public:
	void info()
	{
		cout << "TTurn" << endl;
	};
};

// Factory is an abstract  class
class Factory
{
public:
	virtual Tetromino* createTetromino() = 0;
	virtual ~Factory() {}
};

class StickFactory : public Factory
{
public:
	Tetromino* createTetromino()
	{
		return new Stick; 
	}
};

class SquareFactory : public Factory
{
public:
	Tetromino* createTetromino()
	{
		return new Square;
	}
};

class TTurnFactory : public Factory
{
public:
	Tetromino* createTetromino()
	{
		return new TTurn;
	}	
};

int main()
{
	StickFactory *stick_factory = new StickFactory;
	SquareFactory *square_factory = new SquareFactory;
	TTurnFactory *tturn_factory = new TTurnFactory;

	vector<Tetromino*> v;

	v.push_back(stick_factory->createTetromino());
	v.push_back(square_factory->createTetromino());
	v.push_back(tturn_factory->createTetromino());

	for (int i = 0; i < v.size(); i++)
		v[i]->info();

	return 0;				
}
