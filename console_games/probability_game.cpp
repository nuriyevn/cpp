#include <iostream>
#include <iomanip>
#include <random>
#include <tuple>
#include <vector>
using namespace  std;

class Reputation
{
    public:
        Reputation(int standardInrement = 4) : points(0), lotteryTickets(0) {};
        void increase(double bonus = 1.0)
        {
            points +=  static_cast<int>(bonus * standardIncrement);
            lotteryTickets += static_cast<int>(bonus * 1);
        }
        int getRP() { return points; }
        int getLotteryTickets() { return lotteryTickets; }
    private:
        int points;
        int lotteryTickets;
        int standardIncrement;
};

class BasicSimulation
{
public:
    BasicSimulation(int _seed = 0, int _minimum = MIN, int _maximum = MAX )
    {
        seed = _seed;
        engine.seed(seed);
        SetMinMax(_minimum, _maximum);
    }
    virtual ~BasicSimulation() { cout << "BasicSimulation::dtor()" << endl; }

    void SetMinMax(int _minimum, int _maximum)
    {
        minimum = _minimum;
        maximum = _maximum;
        randomNumber = std::uniform_int_distribution<int>(minimum, maximum);
    }

    int getIntRandomNumber()
    {
        return randomNumber(engine);
    }

    virtual void run() = 0;
protected:
    unsigned int seed;
    default_random_engine engine;
    uniform_int_distribution<> randomNumber;
    int minimum;
    int maximum;
    static const int MIN = 0;
    static const int MAX = 10000;
};

class BetSimulation : public BasicSimulation
{
public:
    BetSimulation(int _seed, int _minimum = MIN, int _maximum = MAX)
        : BasicSimulation(_seed, _minimum, _maximum)
    {
        max_strike= 0;
        balance = 100;
    }
    ~BetSimulation() { cout << "BetSimulation::dtor()" << endl; }

    void run() {
        int longest_unluck_strike = 0;

        for (int i = 0; i < 10000000; i++)
        {
            if (i % 1000000 == 0)
                cout << (i / 1000000) << endl;

            int r = getIntRandomNumber();

            if (r > 4750)
                longest_unluck_strike++;
            else
            {
                if (longest_unluck_strike > max_strike) 
                {
                    max_strike = longest_unluck_strike;
                }
                longest_unluck_strike = 0;       
            }
        }
    }

    int getMaxUnluckyStrike() { return max_strike; }

private:
    int max_strike;
    int balance; // this time in satoshi, not double
};

class AccumulationSimulation : public BasicSimulation
{
public:
    AccumulationSimulation(int _seed, int _verbose = false, double _bonus = 1.0)
        : BasicSimulation(_seed)
    {
        frequency[DICE_MAX] = {0};
        rewardRankFrequency[RANK_MAX] = {0};
        accumulated = 0.0;
        bonus = _bonus; // no bonus; 
        verbose = _verbose;
        round = 0;
        setRunCriterion(); // default criterions
    }
    ~AccumulationSimulation() { cout << "AccumulationSimulation::dtor()" << endl; }

    void setBonus(double b) { bonus = b;}
    double getBonus() { return bonus; }
    double getAccumulated() { return accumulated; }
    int getRound() { return round; }

    void setRunCriterion(double _untilAccumulated = 100000, int _rounds =  DICE_MAX)
    {
        untilAccumulated = _untilAccumulated;
        rounds = _rounds;
    }

    void run()
    {
        for (; round <= rounds; round++)
        {
            int r = getIntRandomNumber();
            frequency[r]++;
            auto currentReward = reward(r);
            accumulated += get<0>(currentReward);
            int rewardRank = get<1>(currentReward);

            if (verbose)        
                cout << round << "-th interartion reward is " << get<0>(currentReward) << " rank is " << rewardRank << endl;
            rewardRankFrequency[rewardRank]++;

            if (rewardRank > 0)
                if (verbose)
                    cout << "reward rank = " << rewardRank << endl;

            if (accumulated >= untilAccumulated)
            {
                break;
            }
        }   
    }
    
private:
    static const int DICE_MAX = 10000;
    static const int RANK_MAX = 6;
    int frequency[DICE_MAX];
    int rewardRankFrequency[RANK_MAX];
    double accumulated;
    double bonus;
    bool verbose;
    int round;
    double untilAccumulated;
    int rounds;

    std::tuple<double, int> reward(int n)
    {
        if (n >=0 && n <= 9885)
        {
            return make_tuple(bonus*0.00000006, 0);
        }
        else if (n >= 9886 && n <= 9985)
        {
            return make_tuple(bonus*0.00000063, 1);
        }
        else if (n >= 9986 && 9993 >= n)
        {
            return make_tuple(bonus*0.00000633, 2);
        }
        else if (n >= 9994 && 9997 >= n)
        {
            return make_tuple(bonus*0.00006330, 3);
        }
        else if (n == 9998 || n == 9999)
        {
            return make_tuple(bonus*0.00063295, 4);
        }
        else if (n == 10000)
        {
            return make_tuple(bonus*0.00632951, 5);
        }
        else{
            if (verbose)
                cout << "WHAT THE FUCK? N IS " <<  n << endl;
        }
        return make_tuple(0.0, 0);
    }

};


class SimulationManager
{
public:
    SimulationManager() {
        highestAverage = 0;
        lowestAverage = 10000000;

        lowestAccumulated = 100000;
        highestAccumulated = 0;
    };

    ~SimulationManager() {
        for (auto simulation : simulations)
            delete simulation;
    }

    void addSimulation(BasicSimulation* simulation){
        simulations.push_back(simulation);
    }

    double recalculateAverageRounds()
    {
        double averageRoundCount = 0;
        int i = 0;
        for (auto simulation : simulations)
        {
            i++;
            int rounds = dynamic_cast<AccumulationSimulation*>(simulation)->getRound();
            lowestAverage = (rounds < lowestAverage) ? rounds : lowestAverage;
            highestAverage = (rounds > highestAverage) ? rounds : highestAverage;

            double accumulated = dynamic_cast<AccumulationSimulation*>(simulation)->getAccumulated();
            lowestAccumulated = (accumulated < lowestAccumulated) ? accumulated : lowestAccumulated;
            highestAccumulated = (accumulated > highestAccumulated) ? accumulated : highestAccumulated;
            averageRoundCount+= rounds;
        }
        if (i != 0)
            averageRoundCount = averageRoundCount / i;
        return averageRoundCount;
    }

    int getLowestAverage() { return lowestAverage;}
    int getHighestAverage() { return highestAverage;}
    double getLowestAccumulated() { return lowestAccumulated;}
    double getHighestAccumulated() { return highestAccumulated;}
public:
    vector<BasicSimulation*> simulations;
    int lowestAverage;
    int highestAverage;
    double lowestAccumulated;
    double highestAccumulated;
};

int main()
{
    SimulationManager simulationManager;

    for (int i = 0; i < 100; i++)
    {
        AccumulationSimulation *simulation = new AccumulationSimulation(i, false); // deleted in the manager
        simulation->setBonus(2);
        simulation->setRunCriterion(0.00003700, 2400); // run till 0.0003 or till 10000 whatever comes first
        simulation->run();  
        simulationManager.addSimulation(simulation);
        cout << fixed << setprecision(8) << "After " << simulation->getRound() 
             << " rounds Accumulated amount = " << simulation->getAccumulated() << endl;
    }

    cout << "Average round amount " << simulationManager.recalculateAverageRounds() << endl;
    cout << "Lowest Average round amount " << simulationManager.getLowestAverage() << endl;
    cout << "Highest Average round amount " << simulationManager.getHighestAverage() << endl;

    cout << "Lowest Accumulated round amount " << simulationManager.getLowestAccumulated() << endl;
    cout << "Highest Accumulated round amount " << simulationManager.getHighestAccumulated() << endl;


    BetSimulation *betSimulation = new BetSimulation(0); // deleted in the manager

    betSimulation->run();
    cout << "Max unlucky strike is " << betSimulation->getMaxUnluckyStrike();
    simulationManager.addSimulation(betSimulation);
}