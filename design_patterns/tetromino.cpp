#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

enum Tetromino_ID { Stick_ID = 0, Square_ID, TTurn_ID, RightSnake_ID, LeftSnake_ID, LeftGun_ID, RightGun_ID};


class Tetromino 
{
public:
	virtual void info() = 0;
	virtual ~Tetromino() {};
	static Tetromino* createTetromino(Tetromino_ID id);
};

class Stick : public Tetromino
{
public:
	void info()
	{
		cout << "Stick" << endl;
	}
};

class Square : public Tetromino
{
public:
	void info()
	{
		cout << "Square" << endl;
	}
};

class TTurn : public Tetromino
{
public:
	void info()
	{
		cout << "TTurn" << endl;
	}
};

class RightSnake : public Tetromino
{
public:
	void info()
	{
		cout << "RightSnake" << endl;
	}
};

class LeftSnake : public Tetromino
{
public:
	void info()
	{
		cout << "LeftSnake" << endl;
	}
};

class RightGun : public Tetromino
{
public:
	void info()
	{
		cout << "RightGun" << endl;
	}	
};

class LeftGun : public Tetromino
{
public:
	void info()
	{
		cout << "LeftGun" << endl;
	}
};

Tetromino* Tetromino::createTetromino(Tetromino_ID id)
{
	Tetromino *t;
	switch (id)
	{
		case Stick_ID:
			t = new Stick();
			break;
		case Square_ID:
			t = new Square();
			break;
		case TTurn_ID:
			t = new TTurn();
			break;
		case RightSnake_ID:
			t = new  RightSnake();
			break;
		case LeftSnake_ID:
			t = new LeftSnake();
			break;
		case RightGun_ID:
			t = new RightGun();
			break;
		case LeftGun_ID:
			t = new LeftGun();
			break;
		default:
			assert(false); 
	}
	return t;	
}


int main()
{
	vector<Tetromino*> v;
	v.push_back(Tetromino::createTetromino(Stick_ID));
	v.push_back(Tetromino::createTetromino(Square_ID));
	v.push_back(Tetromino::createTetromino(TTurn_ID));
	v.push_back(Tetromino::createTetromino(RightSnake_ID));
	v.push_back(Tetromino::createTetromino(LeftSnake_ID));
	v.push_back(Tetromino::createTetromino(RightGun_ID));
	v.push_back(Tetromino::createTetromino(LeftGun_ID));

	for (int i = 0; i < v.size(); i++)
		v[i]->info();
	return 0;

}	



 
