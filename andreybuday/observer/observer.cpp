#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
class ISubject;
class BoxFight;

class IObserver
{	
public:
	virtual void Update(ISubject& subject);

};

class RiskyPlayer : IObserver
{
public:
	string BoxerToPutMoneyOn;
	void Update(ISubject& subject)
	{
		BoxFight& boxFight = subject;
		if (boxFight.BoxerAScore > boxFight.BoxerBScore)
			BoxerToPutMoneyOn = "I put on boxer B, if he win I get more!";
		else
			BoxerToPutMoneyOn = "I put on boxer A, if he win I get more!";
		cout << "RISKYPLAYER:{0}" << BoxerToPutMoneyOn;
	}	
};

class ConservativePlayer : IObserver
{
public:
	string BoxerToPutMoneyOn;
	void Update(ISubject& subject)
	{
		BoxFight& boxFight = dynamic_cast<(BoxFight&>(subject);
		if (boxFight.BoxerAScore < boxFight.BoxerBScore)
			BoxerToPutMoneyOn = "I put on boxerB, better be safe!";
		else 
			BoxerToPutMoneyOn = "I put on boxer A, better be safe!";
		cout << "CONSERVATIVEPLAYER:{0}" << boxerToPutMoneyOn;
	}
};

class ISubject
{
public:
	virtual void AttachObserver(IObserver observer);
	virtual void DetachObserver(IObserver observer);
	voidk Notify();
};

class BoxFight : ISubject
{
public:
	list<IObserver> Observers;
	int RoundNumber;
	int Random;

	int BoxerAScore;
	int BoxerBScore;
	BoxFight()
	{
		// 
	}
	void AttachObserver(IObserver observer)
	{
		Observer.push_back(observer);
	}
	void DetachObserver(IObserver observer)
	{
		Observer.remove(observer);
	}
	void NextRound()
	{
		RoundNumber++;
		BoxerAScore += rand() % 5;
		BoxerBScore += rand() % 5;
		Notify();
	}
	void Notify()
	{
		for (list<IObserver>::iterator it = Observers.begin(); it != Observers.end(); ++it)
			*it.Update(this);
	}
};

int main()
{
	srand(time(0));

	BoxFight boxFight;
	RiskyPlayer riskyPlayer;
	ConservativePlayer conservativePlayer;
	
	boxFight.AttachObserver(riskyPlayer);
	boxFight.AttachObserver(conservativePlayer);
	boxFight.NextRound();
	boxFight.NextRound();
	boxFight.NextRound();	
	boxFight.NextRound();	
}
