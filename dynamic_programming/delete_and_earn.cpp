class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
      unordered_map<int, int> gross;
      int n = nums.size();
      int arraySize = max( 2, n );

      int maxNumber = 0;

      // populate gross points hashmap
      for ( auto &i : nums )
      {
        if ( gross.find(i) == gross.end() )
        {
          gross.insert( pair( i, i ) );
        }
        else
        {
          gross[i] += i;
        }
        maxNumber = max( maxNumber, i );
      }
      //cout << "maxNumber " << maxNumber << endl;

      // Populate net values array
      int * net = new int[ maxNumber + 1 ] {0};
      net[0] = 0;
      net[1] = gross.find(1) != gross.end() ? gross[1] : 0;
      for ( unsigned num = 2; num <= maxNumber; num++ )
      {
        int g = 0;
        if ( gross.find(num) != gross.end() )
          g = gross[num];
        net[num] = max(net[num-1], net[num-2] + gross[num]);
        //cout << "num " << num << ": net " << net[num] << endl;
      }

      // Sum up all net values
      return net[maxNumber];
    }
};
