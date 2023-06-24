#include <iostream>
using namespace std;
class sedans
{
public:
	int total_num_sedans;
	int in_production_sedans;
	int ready_sedans;
	int get_total_num_sedans(void)
	{
		return total_num_sedans;
	}

	int get_num_sedans_in_production(void)
	{
		return in_production_sedans;
	}
	int get_num_sedans_ready(void)
	{
		return ready_sedans;
	}
};

class suvs
{
public:
	int total_num_suvs;
	int in_production_suvs;
	int ready_suvs;
	int get_total_num_suvs(void)
	{
		return total_num_suvs;
	}
	int get_num_suvs_in_production(void)
	{
		return in_production_suvs;
	}
	int get_num_suvs_ready(void)
	{
		return ready_suvs;
	}
};

class honda : public sedans, public suvs
{
public:
	int overall_total_cars;
	int overall_total_production;
	int overall_total_ready;
	int get_overall_num_cars(void)
	{
		return (overall_total_cars = total_num_suvs + total_num_sedans);
	}
	int get_overall_in_production(void)
	{
		return (overall_total_production = in_production_suvs + in_production_sedans);
	}
	int get_overall_ready(void)
	{
		return (overall_total_ready = ready_suvs + ready_sedans);	
	}

};

int main(void)
{
	honda company_stats;
	company_stats.total_num_sedans = 5;
	company_stats.total_num_suvs = 10;
	

	cout << "\n overall honda cars" << company_stats.get_overall_num_cars() << endl;

	return 0;
};

