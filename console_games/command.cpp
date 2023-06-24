#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Game
{
public:
	void create()
	{
		cout << "Create game " << endl;
	}
	void open(string file)
	{
		cout << "Open game from" << file << endl;
	}
	void save(string file)
	{
		cout << "Save game in " << file << endl;
	}
	void make_move(string move)
	{	
		cout << "Make move" << move << endl;
	}
};

string getPlayerInput(string prompt)
{
	string input;
	cout << prompt;
	cin >> input;
	return input;
}

// Базовый класс

class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
protected:
	Command(Game* p) : pgame(p) {}
	Game* pgame;
};

class CreateGameCommand: public Command
{
public:
	CreateGameCommand(Game *p) : Command(p) {}
	void execute() {
		pgame->create();		
	}
};

class OpenGameCommand: public Command
{
public:
	OpenGameCommand(Game *p) : Command(p) {}
	void execute()
	{
		string file_name;
		file_name = getPlayerInput("Enter file name:");
		pgame->open(file_name);
	}
};

class SaveGameCommand : public Command
{
public:
	SaveGameCommand(Game *p) : Command(p) {}
	void execute()
	{
		string file_name;
		file_name = getPlayerInput("Enter file name:");
		pgame->save(file_name);
	}
};

class MakeMoveCommand: public Command
{
public:
	MakeMoveCommand(Game *p)	 : Command(p) {}
	void execute()
	{
		pgame->save("TEMP_FILE");
		string move;
		move = getPlayerInput("Enter your move:");
		pgame->make_move(move);
	}
};

class UndoCommand: public Command
{
public:
	UndoCommand(Game *p) : Command(p) {}
	void execute() 
	{
		pgame->open("TEMP_FILE");
	}
};

int main()
{
	Game game;
	vector<Command*> v;
	// Create new game
	v.push_back(new CreateGameCommand(&game));
	// Do several step
	v.push_back(new MakeMoveCommand(&game));
	v.push_back(new MakeMoveCommand(&game));
	// Cancel last step
	v.push_back(new UndoCommand(&game));
	// Save game
	v.push_back(new SaveGameCommand(&game));

	for (size_t i = 0; i < v.size(); ++i)
		v[i]->execute();
	for (size_t i = 0; i < v.size(); ++i)
		delete v[i];
	
	return 0;
}

