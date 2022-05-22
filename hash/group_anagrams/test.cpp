class Solution {
public:
#ifdef FIRST_ATTEMPT
  // This exceeded the time limit on a huge input

  // Every integer is a prime or can be represented as a product of primes
  // and this representation is unique.
  // All anagram of a sequence of letters have the same
  // product of prime numbers
    unsigned long strToPrime(string s)
    {
      vector<int> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101};
      unsigned long rval = 1;
      for (string::iterator it = s.begin(); it != s.end(); it++)
      {
        rval *= primes[int(*it) - int('a')];
      }
      return rval;
    }

    vector<vector<string>> groupAnagrams(vector<string>& strs) {
      vector<vector<string>> rval;
      vector<int> pushed( strs.size(), 0 );

      for (unsigned i = 0; i < strs.size(); i++)
      {
        if ( pushed[i] )
        {
          continue;
        }

        vector<string> cur;

        cur.push_back(strs[i]);
        pushed[i] = 1;

        unsigned long p1 = strToPrime(strs[i]);
        //cout << __LINE__ << ": " << strs[i] << " -> " << p1 << endl;
        for (unsigned j = i+1; j < strs.size(); j++)
        {
          if ( strs[j].length() != strs[i].length() )
            continue;

          unsigned long p2 = strToPrime(strs[j]);
          //cout << __LINE__ << ": " << strs[j] << " -> " << p2 << endl;
          if (p1 == p2)
          {
            cur.push_back(strs[j]);
            pushed[j] = 1;
          }
        }
        rval.push_back(cur);
      }
      return rval;
    }
#else
    // Wrote this after peeking at
    // https://leetcode.com/problems/group-anagrams/discuss/2056861/C%2B%2B-oror-Unordered_Map-oror-Easy
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
      // map sorted string to vector of anagrams
      unordered_map <string,vector<string>> q;

      for (auto &i : strs)
      {
        string s = i;
        sort(s.begin(),s.end());
        cout << "i " << i << ", s " << s << endl;
        q[s].push_back(i);
      }

      // Generate output
      vector<vector<string>> rval;
      for ( auto &i : q )
      {
        rval.push_back( i.second );
      }
      return rval;
    }
#endif
};
