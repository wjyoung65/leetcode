// Question was posed in the DFS section of Explore Graphs,
// but could also be solved with UnionFind
// This was faster and more space effient than most solutions.
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
    };
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
      UnionFind uf(n);
      for ( auto &i : edges )
      {
        uf.unionSet(i[0], i[1]);
      }
      return uf.connected(source, destination);
    }
};
