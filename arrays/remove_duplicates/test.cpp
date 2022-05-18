#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

class Solution {
public:
    Solution(){};
    ~Solution(){};

    /*

       1 1 2; dest 0, src 1
       nums[dest] == nums[src] so ++src, ++dest
       1 1 2; dest 1, src 2
       nums[dest] != nums[src] so num[dest] = nums[src], ++src, ++dest
       1 2 2
       dest 2, src 3
       src > size, so exit
       return dest (=2)

       0 0 1 1 1 2 2 3 3 4; dest 0, src 1
       nums[dest] == nums[src] so ++src, ++dest
       0 0 1 1 1 2 2 3 3 4; dest 1, src 2


     */
    int removeDuplicates(vector<int>& nums)
    {
      unsigned dest = 1;  // destination for moves
      unsigned checking;  // which element is being checking
      int curValue = nums[0];
      for ( checking = 1; checking < nums.size(); checking++ )
      {
        if ( nums[checking] == curValue )
        {
          continue; // fast-forward past duplicates of curValue
        }

        nums[dest] = curValue = nums[checking];
        dest++;
      }
      return dest;
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
  vector<int> expectedNums;
};

int main(void)
{
  vector<testData> td;

  td.resize(2);

  td[0].nums = {1,1,2};
  td[0].expectedNums = {1,2};

  td[1].nums = {0,0,1,1,1,2,2,3,3,4};
  td[1].expectedNums = {0,1,2,3,4};

  Solution s;

  for (unsigned i = 0; i < td.size(); i++)
  {
cout << "-------------\n";
cout << "in : ";
s.print(td[i].nums);

    int k = s.removeDuplicates(td[i].nums); // Calls your implementation
    cout << "returned: " << k << '\n';

    assert(k == td[i].expectedNums.size());

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
