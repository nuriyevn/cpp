#include <iostream>
#include <set>

using namespace std;

class MyObserver
{
public:
	virtual void Notify() = 0;
};

class MyObservable
{	static MyObservable *instance;
	set<MyObserver*> observers;
	MyObservable() {};
public:
	static MyObservable* GetInstance();
	void AddObserver(MyObserver& o);
	void RemoveObserver(MyObserver& o);
	void NotifyObservers();
	void Trigger();
};

MyObservable* MyObservable::instance = NULL;

MyObservable* MyObservable::GetInstance()
{
	if (instance == NULL)
		instance = new MyObservable();
	return instance;
}

void MyObservable::AddObserver(MyObserver& o)
{
	observers.insert(&o);	
}

void MyObservable::RemoveObserver(MyObserver& o)
{	
	observers.erase(&o);
}

void MyObservable::NotifyObservers()
{
	set<MyObserver*>::iterator itr;
	for (itr = observers.begin();
		itr != observers.end(); ++itr)
		(*itr)->Notify();		
}

void MyObservable::Trigger()
{
	NotifyObservers();	
}	

class MyClass : public MyObserver
{
private:
	MyObservable* observable;
public:
	MyClass()
	{
		observable = MyObservable::GetInstance();
		observable->AddObserver(*this);	
	}
	~MyClass()
	{
		observable->RemoveObserver(*this);
	}
	void Notify()
	{
		cout << "Received a change event" << endl;
	}
};

int main()
{
	MyObservable* observable = MyObservable::GetInstance();
	MyClass *obj = new MyClass();
	observable->Trigger();	
}


