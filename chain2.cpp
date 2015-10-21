#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Component
{
	int value;
	Component *next;
public:
	Component(int v, Component *n)
	{
		value = v;
		next = n;
	}

	void setNext(Component *n)
	{
		next = n;
	}
	virtual void traverse()
	{
		cout << value << ' ';
	}
	virtual void volunteer()
	{
		next->volunteer();
	}
};

class Primitive : public Component
{
public:
	Primitive(int val, Component *n = 0): Component(val, n) {}
	void volunteer()
	{
		Component::traverse();
		if (rand() * 100 % 6 != 0)
			Component::volunteer();
	}
}

class Composite : public Component
{
	vector <Component * > children;
public:
	Composite(int val, Component *n = 0)
		: Component(val, n) {}
	void add(Component *c)
	{
		children.push_back(c);
	}
	void traverse()
	{
		Component::traverse()
		for (int i = 0; i < children.size(); i++)
			children[i]->traverse();
	}
	void volunteer()
	{
		Component::volunteer();
	}
};

int main()
{
	srand(time(0));
	Primitive seven(7);
	Composite three(3, &six);
	three.add(&six);
	three.add(&seven);
	Primitive five(5, &three);
	Primitive four(4, &five);
	Composite two(2, &four);
	two.add(&four);
	two.add(&five);
	Composite one(1, &two);
	Primitive nine(9, &one);
	Primitive eight(8, &nine);

	one.add(&two);
	one.add(&three);
	one.add(&eight);
	one.add(&nine);

	seven.setNext(&eight);
	cout << "traverse: ";
	one.traverse();
	cout << "\n";
	for (int i = 0; i < 8; i++)
	{
		one.volunteer();
		cout << "\n";
	}	
}



