#include <iostream>
#include <stack>
using namespace std;

class Solution
{
  private:
    string input;
  public:
    Solution(string _input) : input(_input) { }
    bool isValid()
    {   
        stack<char> stk;
        char x;
        
        for (auto c : input)
        {
            if (c=='(' || c == '{' || c == '[')
            {
                stk.push(c);
                continue;
            }
            if (stk.empty())
                return false;
            
            switch (c)
            {
            case ')':
                x = stk.top();
                stk.pop();
                if (x == '{' || x == '[')
                    return false;
                break;
            case '}':
                x = stk.top();
                stk.pop();
                if (x == '(' || x == '[')
                    return false;
                break;
            case ']':
                x = stk.top();
                stk.pop();
                if (x == '(' || x == '{')
                    return false;
                break;
            
            default:
                break;
            }
        }

        return stk.empty();
    }
    void setInput(string _input) { input = _input; }
    const string& getInput() { return input; }
};

int main()
{
    string input;
    //cin >> input;
    Solution solution("(){}");
    cout << solution.getInput() << solution.isValid();
    solution.setInput("([])");
    cout << solution.getInput() << solution.isValid();
    solution.setInput("(){}[]");
    cout << solution.getInput() << solution.isValid();
    solution.setInput("([)]");
    cout << solution.getInput() << solution.isValid();

    /*if (solution.isValid(input));
        cout << "valid";
    else
        cout << "invalid";*/
    return 0;
}