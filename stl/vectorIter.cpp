#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
You are keeping score for a baseball game with strange rules. The game consists of several rounds, where the scores of past rounds may affect future rounds' scores.
At the beginning of the game, you start with an empty record. You are given a list of strings ops, where ops[i] is the ith operation you must apply to the record and is one of the following:
An integer x - Record a new score of x.
"+" - Record a new score that is the sum of the previous two scores. It is guaranteed there will always be two previous scores.
"D" - Record a new score that is double the previous score. It is guaranteed there will always be a previous score.
"C" - Invalidate the previous score, removing it from the record. It is guaranteed there will always be a previous score.
Return the sum of all the scores on the record.
Example 1:

Input: ops = ["5","2","C","D","+"]
Output: 30
Explanation:
"5" - Add 5 to the record, record is now [5].
"2" - Add 2 to the record, record is now [5, 2].
"C" - Invalidate and remove the previous score, record is now [5].
"D" - Add 2 * 5 = 10 to the record, record is now [5, 10].
"+" - Add 5 + 10 = 15 to the record, record is now [5, 10, 15].
The total sum is 5 + 10 + 15 = 30.

Example 2:
Input: ops = ["5","-2","4","C","D","9","+","+"]
Output: 27
Explanation:
"5" - Add 5 to the record, record is now [5].
"-2" - Add -2 to the record, record is now [5, -2].
"4" - Add 4 to the record, record is now [5, -2, 4].
"C" - Invalidate and remove the previous score, record is now [5, -2].
"D" - Add 2 * -2 = -4 to the record, record is now [5, -2, -4].
"9" - Add 9 to the record, record is now [5, -2, -4, 9].
"+" - Add -4 + 9 = 5 to the record, record is now [5, -2, -4, 9, 5].
"+" - Add 9 + 5 = 14 to the record, record is now [5, -2, -4, 9, 5, 14].
The total sum is 5 + -2 + -4 + 9 + 5 + 14 = 27.

Example 3:
Input: ops = ["1"]
Output: 1
Constraints:
1 <= ops.length <= 1000
ops[i] is "C", "D", "+", or a string representing an integer in the range [-3 * 104, 3 * 104].
For operation "+", there will always be at least two previous scores on the record.
For operations "C" and "D", there will always be at least one previous score on the record.
*/

class Solution {
  private:
    vector<string> ops;
  public:
    Solution(std::initializer_list<string> args)
    {
        for (string i: args) 
            ops.push_back(i);
    }

    int calPoints(/*vector<string > ops*/)
    {
        vector<int> ints;
        for (auto iter = ops.begin(); iter != ops.end(); iter++)
        {
            char command = (*iter)[0];
            if (command == '+')
            {
                /*auto i = ints.end() - 1; // last element
                int sum = *i;
                i--;
                sum += *i;
                ints.push_back(sum); */
                // or can be next way
                ints.push_back(ints.end()[-1] + ints.rbegin()[1]);
            }
            else if (command == 'C')
            {
                ints.pop_back();
            }
            else if (command == 'D')
            {
                int back = ints.back();
                ints.push_back(back*2);
            }
            else
            {
                ints.push_back(stoi(*iter));
            }
        }
        int total = 0;
        for (auto i = ints.begin(); i != ints.end(); i++)
        {
            cout << "ints elem " << *i << endl;
            total += *i;
        }
        return total;
    }
};

int main()
{
    /*
    vector<string> ops;
    string item;
    string line;
    getline(cin, line);
    istringstream is(line);
    while (is >> item)
    {
        items.push_back(item);
    }
    */

    Solution solution({"5", "2", "C", "D", "+"});
    Solution solution2( { "5", "-2", "4", "C", "D", "9", "+", "+"});
    Solution solution3( { "1"});
    //solution.print();
    cout << solution.calPoints();
    cout << solution2.calPoints();
    cout << solution3.calPoints();

    return 0;
}