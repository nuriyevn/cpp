#include <iostream>

using namespace std;

// Just a base class for all controls
// Kind of Widget class, doesn't matter here.
class AnimalToy
{
public:
	string name;
	AnimalToy(string n) : name(n)
	{
	}
};

// Button
class Cat : public AnimalToy
{
protected:
	Cat(string name) : AnimalToy(name)
	{
	} 	
};

// TextField
class Bear : public AnimalToy
{
protected:
	Bear(string name) : AnimalToy(name)
	{
	}	
};

// LinuxButton
class WoodenCat : public Cat
{
public:
	WoodenCat() : Cat("Wooden Cat")
	{
	}
};

//WinButton
class TeddyCat : public Cat
{
public:
	TeddyCat() : Cat("Teddy Cat")
	{
	}
};

// LinuxTextField
class WoodenBear : public Bear
{
public:
	WoodenBear() : Bear("Wooden Bear")
	{
	}
};

//WinTextField
class TeddyBear : public Bear
{
public:
	TeddyBear() : Bear("Teddy Bear")
	{
	}
};

// AbstractFactory
class IToyFactory
{
public:
	virtual Bear *GetBear() = 0;
	virtual Cat *GetCat() = 0;
};


// WinFactory
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

//LinuxFactory
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
