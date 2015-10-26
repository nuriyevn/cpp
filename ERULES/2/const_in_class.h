#include <iostream>

// The only way to declare constants in classs

class GamePlayer
{
public:
	enum {
		NumTurns = 5
	};

//public:
//	static const int NumTurns = 5; // Declaring constant (IT'S NOT A DEFINITION)
private:
	int score[GamePlayer::NumTurns];
};


class CostEstimate
{
	static const double FudgeFactor;
};

class EnumHack
{
private:
	enum { NumTurns = 5};
	int scores[NumTurns];
};

