#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

class CBeing
{
public:
	string mName; 
	int mAge; 
public:
	virtual void eat() = 0; // pure virtual method which make this class abstract
	virtual void makeNoise() = 0; // all virtual method should be defined in some serived classes
};

class CAnimal : public CBeing
{
// not yet implemented
};

class CPerson : public CBeing
{
// not yet implemented
};

class CGazelle : public CAnimal
{
public:
	void eat()
	{
		cout << "I'm eating the grass. " << endl;
	}
	void makeNoise()
	{
		cout << "Meeee!" << endl;
	}
};

class CLion : public CAnimal
{
	void eat()
	{
		cout << "I'm hungry lion" << endl;	
	}
	void makeNoise()
	{
		cout << "Raaaaawwwwwrrrr! " << "Metro Goldvyn Mayer" << endl;
	}
};

class CStaff : public CPerson
{
// Not yet implemented
};
class CGuest : public CPerson
{
// Not yet implemented
};

int main()
{
	CAnimal *animal[2]; // creating array of animals, but not initializing
	
	animal[0] = new CLion; // create CLion object from generic CAnimal (it's pointer, but in Java should be regular object)	
	cout << "Please input name of the 1-st animal: " << endl;
	getline(cin, animal[0]->mName); // reading the name of the animal
	cout << "now the age" << endl;
	cin >> animal[0]->mAge; // reading the age of the animal

	animal[1] = new CGazelle; // crerate CGazelle object from generic CAnimal
	cin.get();
	cout << "Please input the name of the 2-nd animal: " << endl;
	getline(cin, animal[1]->mName);
	cout << "now the age" << endl;
	cin >> animal[1]->mAge;

	for (int i = 0; i < 2; i++)
	{
		cout << "/*****************" << endl;
		cout << "Animal[" << i << "]. Name of the animal: " << animal[i]->mName << "; Age: " << animal[i]->mAge << endl;
		cout << "Behavior: " << endl;
		cout << "eat: ";
		animal[i]->eat();
		cout << "makeNoise: ";
		animal[i]->makeNoise();
	}

	return 0;
}
