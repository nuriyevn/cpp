#include "LibraryCode.hpp"
#include <algorithm>


int add(int a, int b)
{
    return a + b;
}

bool isPositive(int x)
{
    return x >= 0;
}

int countPositives(std::vector<int> const& inputVector)
{
    return std::count_if(inputVector.begin(), inputVector.end(), isPositive);
}

void toUpper(char *inputString)
{
    for (unsigned i = 0; i < strlen(inputString); i++)
    {
        inputString[i] = toupper(inputString[i]); // a -> A, b -> B
    }
}