class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
#ifdef NESTED_LOOPS_IMPLEMENTATION
// time complexity O(n^2)
      bool found = false;
      unsigned i, j;
      // quick and dirty implementation using nested loops
      for ( i = 0; !found && i < nums.size(); i++ )
      {
        for ( j = i+1; !found && j < nums.size(); j++ )
        {
          if (target == nums[i] + nums[j])
          {
            found = true;
          }
        }
      }

      vector<int> rval(2);
      rval[0] = i-1;
      rval[1] = j-1;

      return rval;
#endif

#define HASH_MAP_SOLUTION
#ifdef HASH_MAP_SOLUTION

    unordered_map<int, int> hm;
    vector<int> output;

    // one-pass scan using a hash map
    // if the complement is already in the hash map, we have the answer
    for ( int i = 0; i < nums.size(); i++ )
    {
      int complement = target - nums[i];
      if ( hm.find(complement) != hm.end() )
      {
        return {i, hm[complement]};
      }
      hm[nums[i]] = i;;
    }

    return {-1,-1};
#endif
  }
};

