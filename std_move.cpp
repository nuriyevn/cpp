#include <iostream>
#include <utility>
#include <vector>
#include <string>


int main()
{
	std::string str = "Hello";
	std::vector<std::string> v;

	v.push_back(str);
	std::cout << "After copy, std is \"" << str << "\"\n";
	v.push_back(std::move(str));
	std::cout << "After move, str is\"" << str << "\"\n";
	std::cout << "The contents of the vector are \"" << v[0] 				<< "\", \"" << v[1] << "\"\n";


	//string move assignment operator is often implemented as swap
	// in this case moved from object is NOT empty;
	std::string str2 = "Good-bye";
	std::cout << "Before move from str2, str2 = '" << str2 << "'\n";

	v[0] = std::move(str2);
	std::cout << "After move from str2, str2 = '" << str2 << "'\n";
}
