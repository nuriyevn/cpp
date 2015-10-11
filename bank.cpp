#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class Profit
{
public:
	double initial_amount;
	double current_amount;
	double per_year;
	double all_taxes;
	Profit(double amount, double per_year, double tax = 20.5) 
	{
		double	
	}
	~Profit() {}
	virtual void iterateSinglePeriod()
	{
		
	}
	virtual void iterateYear()
	{
	}
			
};

class DailyProfit
{
	void iterateSinglePeriod()
	{
	}
	void iterateYear()
	{
	}
	
};

class MonthlyProfit
{
	void 	
};



int main()
{
	double ppy = 17; // percent per year;
	double tax_percent = 20.5;
	
	double initial_amount = 20000;
	double current = initial_amount;

	double real_percent_per_year = ppy * (100.0-tax_percent) / 100.0; // per day

	cout << "real_percent_per_yaer = " << real_percent_per_year << endl;
	double real_percent = real_percent_per_year / 365.0 / 100.0;
	
	cout << "real_percent = " << real_percent << endl; 
	
	for (int month = 1; month <= 12; month++)
	{	
		initial_amount = current;
		for (int day = 1; day < 31; day++)
		{
			double daily_profit = initial_amount * real_percent;
			current = current + daily_profit;
			cout << month << "-th month; " << day << "-th day = " << current << " +" << daily_profit<< endl;  
		}
	}	
}


