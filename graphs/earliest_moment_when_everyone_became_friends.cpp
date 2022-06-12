// Inputs: a vector of vector<int>, where each vector<int> contains [a,b,c]
//   a = a timestamp when A knew B and vice-versa (undirected)
//   b = vertex (friend A)
//   c = vertex (friend B)
// Hints:
// Sort the logs by timestamp
// Use a union set
// The moment occurs when the number of connected components drops to 1
// "connected components" means unique roots
class Solution {
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
          for ( unsigned ctr = 0; ctr < sz; ctr++ )
          {
            mRoots[ctr] = ctr;
            mRanks[ctr] = 1;
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
    int earliestAcq(vector<vector<int>>& logs, int n) {
      // sort the logs by timestamp
      std::sort(logs.begin(), logs.end(),
                [](vector<int> &x, vector<int> &y){return x[0] < y[0];});

      // Populate the disjoint set
      UnionFind uf(n);
      for ( auto &i : logs )
      {
        uf.unionSet( i[1], i[2] );
        if ( uf.numUniqueRoots() == 1 )
        {
          // found the moment when everyone knew each other: return the timestamp
          return i[0];
        }
      }
      return -1; // timestamp not found
    }
};
