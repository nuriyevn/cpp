#include <iostream>
#include <map>

using namespace std;

int main()
{
	map<string, int> accountTypesMap = 
	{
		{"CashAccount", 0},
		{"PaymentCardAccount", 1},
		{"SavingsAccount", 2}
	};

	for (auto it = accountTypesMap.begin();
			  it != accountTypesMap.end();
			  ++it)
	{
		cout << it->second << " : " << it->first << endl;		
	}

	for (map<string, int>::iterator it = accountTypesMap.begin();
		it != accountTypesMap.end();
		++it)
	{
		cout << (*it).first << " : " << (*it).second << endl;
	}

	char c;
	map<char, int> mySecondMap;
	for (int i = 0, c = 'a'; i < 5; ++i, ++c)
	{
		mySecondMap.insert(pair<char, int> (c, i));
	}	
	for (auto it = mySecondMap.begin();
				it != mySecondMap.end();
				++it)
	{
		cout << (*it).first << " : " << (*it).second << endl;
	}
	for (auto it = mySecondMap.begin();
				it != mySecondMap.end();
				++it)
	{
		cout << it->second << " : " << it->first << endl;
	}
	
	
	cout << "Finding: " << endl;
	
	string key; 
	cin >> key;	
	
	auto it =  accountTypesMap.find(key);
	cout << "value = " << it->second << endl;
	
	return 0;
}
