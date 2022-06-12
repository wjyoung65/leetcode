// Solving the Number of Provinces problem using disjoint sets
// where the disjoint sets have the rank optimization for quick union
// and path compression for find.

class Solution {
private:

    class UnionFind
    {
      private:
        vector<int> mRoots;
        vector<int> mRanks;

      public:
        UnionFind( const int sz )
        : mRoots(sz)
        , mRanks(sz)
        {
          // initialize the disjoint set so array[n] = n (each node is its own root)
          int j = 0;
          for ( auto &i : mRoots )
          {
            i = j++;
          }
        }

        int find(const int x)
        {
          if ( x == mRoots[x] )
          {
            return x;
          }
          return mRoots[x] = find(mRoots[x]);
        }

        void unionSet(const int x, const int y)
        {
          int rootX = find(x);
          int rootY = find(y);
          //cout << "x " << x << " root " << rootX << endl;
          //cout << "y " << y << " root " << rootY << endl;
          if ( rootX == rootY )
          {
            return;
          }
          else if ( mRanks[x] > mRanks[y] )
          {
            //cout << "1: connect " << mRoots[rootY] << " to " << rootX << endl;
            mRoots[rootY] = rootX;
          }
          else if ( mRanks[x] < mRanks[y] )
          {
            //cout << "2: connect " << mRoots[rootX] << " to " << rootY << endl;
            mRoots[rootX] = rootY;
          }
          else
          {
            //cout << "3: connect " << y << " to " << rootX << endl;
            mRoots[rootY] = rootX;
            mRanks[rootX] += 1;
          }
        }

        bool connected( const int x, const int y )
        {
          return find(x) == find(y);
        }

        int numUniqueRoots(void)
        {
          int rval = 0;
          vector<int> roots(mRoots.size(), 0);
          for ( unsigned i = 0; i < mRoots.size(); i++ )
          {
            int root = find(i);
            //cout << "counting: node " << i << " root is " << root << endl;
            if ( roots[root] == 0 )
            {
              roots[root] = 1;
              ++rval;
              //cout << "counting: new root " << root << ", rval " << rval << endl;
            }
          }
          return rval;
        }
    };
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
      //cout << "matrix size " << isConnected.size() << endl;

      // Initialize the disjoint set
      UnionFind disjointSet(isConnected.size());

      // Populate the disjoint set
      for ( unsigned i = 0; i < isConnected.size(); i++ )
      {
        for ( unsigned j = i; j < isConnected.size(); j++ )
        {
          if ( i != j && isConnected[i][j] )
          {
            disjointSet.unionSet(i,j);
          }
        }
      }
      return disjointSet.numUniqueRoots();
    }
};
