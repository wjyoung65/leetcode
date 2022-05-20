// From https://leetcode.com/tag/hash-table/discuss/1068545/HASH-TABLE-and-MAP-POWERFUL-GUIDE-!!!
// Pasting it in here to step through it with a debugger to better
// understand how it works.

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> q;
        for(int i=0;i<nums.size();i++){
            if(q.count(nums[i])>0){
                q.at(nums[i])=q.at(nums[i])+1;         //my value is the frequncy of key
            }
            else{
                q.insert(make_pair(nums[i], 1));
            }
        }
        unordered_map<int, int>:: iterator z;
        for(z=q.begin();z!=q.end();z++){
cout << __LINE__ << ": " << z->first << ", " << z->second << endl;
            if ( target%2 == 0 &&               // even number
                 target == (z->first * 2) &&    // any input number plus itself qualifies
                 z->second > 1 )                // the number is actually in the map
            {
               // corner case where num[x] + num[x] == target
			   return true;
            }
            else
            {
cout << __LINE__ << ": " << target - z->first << ", " << q.count(target-z->first) << endl;

               // Suppose 'target' is 9 and z->first is 7.
               // If the number of elements with key '2' is > 0, then
               // there are 2 numbers in the map that add up to the target.
               if (q.count(target - z->first) > 0)
               {
			    return true;
               }
            }
        }
        return false;
    }
};

int main(void)
{
  vector<int> nums = {1,2,3,4,5,6,7};
  Solution s;

  cout << s.twoSum(nums, 9) << endl;
}
