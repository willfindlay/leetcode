/***********

  William Findlay's regex(ish) implementation
  Works with . and * characters
  Written as a solution for https://leetcode.com/problems/regular-expression-matching/

***********/


#include <iostream>
#include <string>
using namespace std;

class Solution
{
    public:
        static bool isMatch(string s, string p)
        {
            int i = 0;
            int j = 0;
            char currS = '\0';
            char currP = '\0';
            bool wildcard = false;

            for(;;)
            {

                // take care of uneven lengths
                if(i == s.length() && j != p.length())
                    return false;

                if(i != s.length() && j == p.length())
                    return false;

                // if we made it to the end of both strings, we can return true
                if(i == s.length() && j == p.length())
                    return true;

                currS = s[i];
                currP = p[j];

                // are we on a wildcard?
                wildcard = (j < p.length() - 1 && p[j+1] == '*') ? true : false;

                if(wildcard)
                {
                    // if we don't have a match, hop over the wildcard and leave s where it is
                    if(!matchChars(currS, currP))
                    {
                        j += 2;
                        wildcard = false;
                        continue;
                    }
                    // if we have a match and we're about to be at the end of s, hop over the wildcard
                    else if(i + 1 == s.length())
                    {
                        j += 2;
                        wildcard = false;
                    }
                }
                else
                {
                    // if we don't have a match, get out and return false
                    if(!matchChars(currS, currP))
                    {
                        break;
                    }
                    j++;
                }

                i++;
            }

            return false;
        }

        static bool matchChars(char sc, char pc)
        {
            if(!sc || !pc)
                return false;

            if(pc == '.')
                return true;

            if(sc == pc)
                return true;

            return false;
        }
};

int main()
{
    string s = "aa";
    string p = "a";
    cout << Solution::isMatch(s, p) << endl << endl;

    s = "aa";
    p = "a*";
    cout << Solution::isMatch(s, p) << endl << endl;

    s = "ab";
    p = ".*";
    cout << Solution::isMatch(s, p) << endl << endl;

    s = "aab";
    p = "c*a*b*";
    cout << Solution::isMatch(s, p) << endl << endl;

    s = "mississippi";
    p = "mis*is*p*";
    cout << Solution::isMatch(s, p) << endl << endl;

    return 0;
}
