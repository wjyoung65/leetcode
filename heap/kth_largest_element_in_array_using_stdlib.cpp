// Implemented using std::priority_queue
// just to practice using std::lib

#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k)
    {
#ifdef HEAPIFY_ALL_THE_NUMBERS
      priority_queue<int> q;

      // Populate the priority queue
      // Time complexity O(NlogN), where N = nums.size()
      for ( auto &i : nums )
      {
        q.push(i);
      }

      // Pop off elements until we reach the kth one
      // Time complexity O(k)
      for ( unsigned i = 0; i < k-1; i++ )
      {
        q.pop();
      }
#else
      priority_queue<int, vector<int>, std::greater<int>> q;

      for ( unsigned i = 0; i < k; i++ )
      {
        q.push(nums[i]);
        //cout << "1: pushed " << nums[i] << ", top " << q.top() << endl;
      }
      for ( unsigned i = k; i < nums.size(); i++ )
      {
        //cout << "2: compare " << nums[i] << ", top " << q.top() << endl;
        if ( nums[i] > q.top() )
        {
          q.pop();
          q.push(nums[i]);
          //cout << "2: pushed " << nums[i] << ", top " << q.top() << endl;
        }
      }
#endif
      return q.top();
    }
};
