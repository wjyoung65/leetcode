#include <iostream>
#include <algorithm>
//#include <string>
using namespace std;

class Solution
{
public:
    bool inString(string::iterator start, string::iterator end, const char c) {
      bool rval = false;
      for (string::iterator i = start; i < end; i++)
      {
        if ( *i == c )
        {
          rval = true;
          break;
        }
      }

      return rval;
    }

    int lengthOfLongestSubstring(string s) {
      // Sliding window algorithm
      string::iterator curStart = s.begin();
      unsigned longest = 0;
      for (string::iterator i = curStart; i < s.end(); i++)
      {
        while (inString(curStart,i,*i))
        {
          ++curStart;  // slide the left side of the window over
        }
        unsigned len = i-curStart+1;
        longest = max(longest, len);
      }

      return longest;
    }
};

struct tests
{
  string   s;
  unsigned exp;
};

int main(void)
{
  Solution sol;
  vector<tests> t;

  t.resize(3);

  t[0].s = "pwwkew";
  t[0].exp = 3;

  t[1].s = " ";
  t[1].exp = 1;

  t[2].s = "";
  t[2].exp = 0;

  for (unsigned i = 0; i < t.size(); i++ )
  {
    unsigned longest = sol.lengthOfLongestSubstring(t[i].s);
    if ( longest != t[i].exp)
    {
      cout << "Failed: string " << t[i].s << '\n';
      cout << "Expected " << t[i].exp << '\n';
      cout << "Got      " << longest << '\n';
    }
  }
}

