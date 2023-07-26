#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

class Solution {
  public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> got_votes(n, 0);
        vector<int> trust_somebody(n, 0);
        for (auto t : trust)
        {
            int who = t[0];
            int to_whom = t[1];

            got_votes[to_whom]++;
            trust_somebody[who]++;
        }

        int judge_is_found = 0;
        int judge_index = 0;
        int i = 0;
        for (auto c = got_votes.begin(); c != got_votes.end(); c++)
        {
            if (*c == n - 1 && trust_somebody[i] == 0)
            {
                judge_index = i;
                judge_is_found++;
            }
            i++;
        }

        if (judge_is_found == 1)
            return judge_index;
    }
}; 


vector<int> ParseAndFillVector(string s) {
    s += " ";
    string delimiter = " ";
    vector<int> res;
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        string token = s.substr(0, pos);
        res.push_back(atoi(token.c_str()));
        s.erase(0, pos + delimiter.length());
    }
    return res;
}

int main()
{
    vector<vector<int>> trusts;
    string s;
    getline(cin, s);
    int n = atoi(s.c_str());

    string sTrusts;
    getline(cin, sTrusts);
    std::string delimiter = ",";
    size_t pos = 0;
    sTrusts += ","; // adding ',' for last item delimiter
    string token;
    while ((pos = sTrusts.find(delimiter)) != std::string::npos)
    {
        token = sTrusts.substr(0, pos);
        trusts.push_back(ParseAndFillVector(token));
        sTrusts.erase(0, pos+ delimiter.length());
    }

    Solution solution;
    cout << solution.findJudge(n, trusts);
}