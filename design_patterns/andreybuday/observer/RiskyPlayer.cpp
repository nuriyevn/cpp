#include "RiskyPlayer.h"
#include "BoxFight.h"

void RiskyPlayer::Update(ISubject& subject)
{
	BoxFight& boxFight = subject;
	if (boxFight.BoxerAScore > boxFight.BoxerBScore)
		BoxerToPutMoneyOn = "I put on boxer B, if he win I get more!";
	else
		BoxerToPutMoneyOn = "I put on boxer A, if he win I get more!";
	cout << "RISKYPLAYER:{0}" << BoxerToPutMoneyOn<< endl;
}


