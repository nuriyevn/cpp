#include <iostream>

using namespace std;

class AnimalToy
{
public:
	string name;
	AnimalToy(string n) : name(n)
	{
	}
};

class Cat : public AnimalToy
{
protected:
	Cat(string name) : AnimalToy(name)
	{
	} 	
};

class Bear : public AnimalToy
{
protected:
	Bear(string name) : AnimalToy(name)
	{
	}	
};

class WoodenCat : public Cat
{
public:
	WoodenCat() : Cat("Wooden Cat")
	{
	}
};


class TeddyCat : public Cat
{
public:
	TeddyCat() : Cat("Teddy Cat")
	{
	}
};

class WoodenBear : public Bear
{
public:
	WoodenBear() : Bear("Wooden Bear")
	{
	}
};

class TeddyBear : public Bear
{
public:
	TeddyBear() : Bear("Teddy Bear")
	{
	}
};


class IToyFactory
{
public:
	virtual Bear *GetBear() = 0;
	virtual Cat *GetCat() = 0;
};

class TeddyToysFactory : public IToyFactory
{
public:
	Bear *GetBear()
	{
		return new TeddyBear();
	}
	Cat *GetCat()
	{
		return new TeddyCat();
	}
};

class WoodenToysFactory : public IToyFactory
{
public:
	Bear *GetBear()
	{
		return new WoodenBear();
	}
	Cat *GetCat()
	{
		return new WoodenCat();
	}
};

int main()
{
	cout << "Wooden factory is working!" << endl;
	IToyFactory *wtFactory = new WoodenToysFactory();
	Bear *bear = wtFactory->GetBear();
	Cat *cat = wtFactory->GetCat();
	cout << "I have got " << bear->name << " and " << cat->name << endl;	

	cout << "Teddy factory is working!" << endl;
	IToyFactory *ttFactory = new TeddyToysFactory();
	Bear *bear2 = ttFactory->GetBear();
	Cat *cat2 = ttFactory->GetCat();
	cout << "I have got" << bear2->name << " and " << cat2->name << endl;		
}
