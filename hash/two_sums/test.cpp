#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        unordered_map<int,int> remainderToIndexMapper;

        for(int i=0; i<nums.size(); i++)
        {
            int remainder = target - nums[i];
            if(remainderToIndexMapper.count(nums[i]))
            {
                return {remainderToIndexMapper[nums[i]], i};
            }
            remainderToIndexMapper[remainder] = i;
        }
        return {-1, -1};
    }
};

int main(void)
{
  vector<int> nums = {2,7,11,15};
  Solution s;

  vector<int> out = s.twoSum(nums, 22);

  cout << out[0] << ", " << out[1] << endl;
}
