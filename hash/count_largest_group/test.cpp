class Solution {
public:
    unsigned sumOfDigits( int n )
    {
      unsigned sum = 0;

      do
      {
        sum += n % 10;
        n /= 10;
      } while (n > 0);
      return sum;
    }

    int countLargestGroup(int n) {
      // Group according the sum of digits 1 to n
      unordered_map<int, int> q;
      unsigned largestCount = 0;

      for ( unsigned i = 1; i <= n; i++ )
      {
        unsigned sum = sumOfDigits(i);
        if ( q.count(sum) > 0 )
        {
          //cout << "one more for " << sum << endl;
          q[sum] += 1;
        }
        else
        {
          //cout << "insert new " << sum << endl;
          q.insert(make_pair(sum, 1));
        }

        if ( q[sum] > largestCount )
        {
          largestCount = q[sum];
        }
      }

      //cout << "largestCount " << largestCount << endl;

      unsigned numLargest = 0;
      for (unordered_map<int,int>::iterator it = q.begin(); it != q.end(); ++it)
      {
        if ( it->second == largestCount )
          ++numLargest;
      }
      return numLargest;
    }
};
