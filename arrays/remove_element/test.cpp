//#include <stdio.h>
//#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

class Solution {
public:
    Solution(){};
    ~Solution(){};

    int removeElement(vector<int>& nums, int val)
    {
      // Find the last element in 'nums' that is not equal the 'val'
      int last = nums.size() - 1;
      int i;

      for ( i = 0; i < last; i++ )
      {
        // Skip past any "vals" in the tail end of the array
        for ( ; last >= 0; last--)
        {
          if ( nums[last] != val )
            break;
        }
        if ( i >= last )
          break;
cout << __LINE__ << ": last " << last << ", i " << i << '\n';
print(nums);

        if ( nums[i] == val )
        {
          // get rid of 'val' by overwriting with the last entry
          nums[i] = nums[last];
          nums[last--] = val;
cout << __LINE__ << ": last " << last << ", i " << i << '\n';
print(nums);
        }
      }

cout << __LINE__ << ": last " << last << ", i " << i << '\n';
print(nums);
      // Corner case when 'last' is an element
      // that contains 'val' and the above loop
      // bailed because i > last.
      // e.g. [2,2,3] eliminate 2, last would be 1
      for ( ; last >= 0; last--)
      {
        if ( nums[last] != val )
          break;
      }

cout << __LINE__ << ": last " << last << ", i " << i << '\n';
print(nums);
      return last+1;
    }

    void print(vector<int>&nums)
    {
      for ( unsigned i = 0; i < nums.size(); i++ )
      {
        cout << nums[i] << ' ';
      }
      cout << '\n';
    }
};

struct testData
{
  vector<int> nums;
  int val;
  vector<int> expectedNums;
};

int main(void)
{
  vector<testData> td;

  td.resize(4);

  td[0].nums = {2,2,3};
  td[0].val = 3;
  td[0].expectedNums = {2,2};

  td[1].nums = {2,2,3};
  td[1].val = 2;
  td[1].expectedNums = {3};

  td[2].nums = {3,2,2,3};
  td[2].val = 3;
  td[2].expectedNums = {2,2};

  td[3].nums = {2,4,4,4,0};
  td[3].val = 4;
  td[3].expectedNums = {0,2};

  Solution s;

  for (unsigned i = 0; i < td.size(); i++)
  {
cout << "-------------\n";
cout << "in : ";
s.print(td[i].nums);
cout << "val: " << td[i].val << '\n';

    int k = s.removeElement(td[i].nums, td[i].val); // Calls your implementation
    cout << k << '\n';

    assert(k == td[i].expectedNums.size());

    sort(td[i].nums.begin(), td[i].nums.begin() + k); // Sort the first k elements of nums
cout << "got: ";
s.print(td[i].nums);
cout << "exp: ";
s.print(td[i].expectedNums);

    for (int j = 0; j < td[i].expectedNums.size(); j++)
    {
        assert(td[i].nums[j] == td[i].expectedNums[j]);
    }
  }

  cout << "passed\n";

}
