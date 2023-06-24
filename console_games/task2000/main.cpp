#include <iostream>
#include <random>
#include <ncurses.h>
#include <cstdlib>
// Linux specific

#include <unistd.h>
#include <time.h>

//sudo apt-get install libncurses-dev

using namespace std;


class Side
{
public:
    int operand1;
    char operation;
    int operand2;
    int result;
    Side(int operand1, char operation,int operand2, int result)
        : operand1(operand1), operation(operation), operand2(operand2), result(result)
    {
    }
};


class Complexity
{
public:
    int numberStart;
    int numberEnd;
    int resultStart;
    int resultEnd;

    string name;
    Complexity(int numberStart, int numberEnd, int resultStart, int resultEnd,  string name)
        : numberStart(numberStart), numberEnd(numberEnd),
         resultStart(resultStart), resultEnd(resultEnd), name(name)
    {
    }
};

class Dice
{
public:
    vector<Side> sides;
    Complexity complexity;
    Dice(Complexity& complexity)
        : complexity(complexity)    {    }

    vector<Side>& getSides()
    {
        return sides;
    }

    int roll()
    {
        //int random = rand() % 12;
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        //std::ranlux48 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(complexity.numberStart, complexity.numberEnd);
        return dis(gen);
    }
    int sign()
    {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        //std::ranlux48 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);
        return dis(gen);  // 0 is - , 1 is +
    }
    int calculatePart(int operand1, int operand2, int operation)
    {
        if (operation == 0) // minus
            return operand1 - operand2;
        else
            return operand1 + operand2;
    }

    bool checkPart(int result)
    {
        if (result >= complexity.resultStart && result <= complexity.resultEnd)
            return true;
        else
            return false;
    }

    int generateCalculateCheck()
    {
        int result = -1;
        int operand1, operand2;
        int operation;
        char opSign = '\0';

        // check
        do
        {
            // generate
            operand1 = roll();
            operand2 = roll();
            operation = sign();
            opSign = (operation == 1) ? '+' : '-';

            // calculate
            result = calculatePart(operand1, operand2, operation);
        }
        while (!checkPart(result));
        Side *side = new Side(operand1, opSign, operand2, result);
        sides.push_back(*side);
        delete side;
    }


    char generateCompleteTest()
    {
        generateCalculateCheck();
        generateCalculateCheck();

        int totalResult = 0; // 0 is  equal, -1 is < ,   1 is >
        char totalSign = '\0';

        if (sides[0].result < sides[1].result)
        {
            totalResult = -1;
            totalSign = '<';
        }
        else if (sides[0].result > sides[1].result)
        {
            totalResult = 1;
            totalSign = '>';
        }
        else
        {
            totalResult = 0;
            totalSign = '=';
        }


        Side& side0 = sides[0];
        Side& side1 = sides[1];




        mvprintw(0,0,  "%2d %c %2d   %2d %c %2d",
                 side0.operand1,side0.operation,side0.operand2,
                 side1.operand1,side1.operation,side1.operand2);

        return totalSign;

    }
};

int main()
{
    Complexity easy(1, 19, 1, 20, "easy");
    Dice dice(easy);
    initscr();

    const int penalty = 50;

    int h, w;
    getmaxyx(stdscr, h, w);
    //getch();


    int c;
    string lastResult = "";
    int score = 0;
    int consequent = 0;
    int generatedTests = 0;
    int correctTest = 0;
    int wrongTest = 0;
    int skippedTest = 0;

    while (c != 27)
    {


        char studentAnswer = '\0';
        clear();

        mvprintw(0, 40, lastResult.c_str());
        mvprintw(0, 50, "Score: %d", score);
        mvprintw(0, 60, "Correct/Wrong/Skipped/Overall: %d/%d/%d/%d",
                 correctTest, wrongTest,skippedTest, generatedTests);

        char correctAnswer = dice.generateCompleteTest();

        move(0, 8);

        timespec ts,ts2;
        ts.tv_sec = 0;
        ts.tv_nsec = 199999999L;

        c = getch();
        if (c == '>' || c == '<' || c == '=')
        {
            if (c == correctAnswer)
            {
                printw("%c",c);
                lastResult = "Yes!:)";
                consequent++;

                correctTest++;

                score = score + consequent;
            }
            else
            {
                wrongTest++;

                printw("%c",c);
                lastResult = "No!:(";
                consequent = 0;
                score = score - penalty;
                if (score < 0)
                    score = 0;
            }

            nanosleep(&ts,&ts2);
        }
        else
        {
            skippedTest++;
            printw("Wrong input");
            nanosleep(&ts,&ts2);
        }

        generatedTests++;

        refresh();
        /*
        cout << endl << '\t';
        cin >> studentAnswer;

        if (correctAnswer == studentAnswer)
            cout << "YES!! :)" << endl;
        else
            cout << "NO! :(" << endl;
*/
        dice.getSides().pop_back();
        dice.getSides().pop_back();
    }


    endwin();
    return 0;
}
