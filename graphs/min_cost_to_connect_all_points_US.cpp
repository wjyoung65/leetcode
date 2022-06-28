// Using UnionSet is slightly faster than DFS
// Beats 41% of cpp submissions
class Solution {

  class weightedEdge
  {
  public:
    int weight;
    int vertex1;
    int vertex2;

    weightedEdge( int w, int v1, int v2 )
      : weight(w)
      , vertex1(v1)
      , vertex2(v2)
    {
    }
  };

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
    int minCostConnectPoints(vector<vector<int>>& points) {
      int minCost = 0;
      int n = points.size();
      UnionFind uf(n);
      vector< weightedEdge > we;

      if ( n == 1 )
      {
        return 0;
      }

      // Calculate cost between all points
      for ( unsigned i = 0; i < n-1; i++)
      {
        vector<int> &a = points[i];
        for ( unsigned j = i+1; j < n; j++)
        {
          vector<int> &b = points[j];
          int d = abs(a[0] - b[0]) + abs(a[1] - b[1]);
          we.push_back( weightedEdge(d, i, j) );
        }
      }
      // Sort the weightedEdge list in ascending order
      std::sort(we.begin(), we.end(),
                [](weightedEdge &a, weightedEdge &b){return a.weight < b.weight;});

      // debug the weighted edge list
      //for ( auto &i : we )
      //{
      //  cout << i.weight << ": " << i.vertex1 << "," << i.vertex2 << endl;
      //}

      // Start from the smallest weighted edge
      int numSaved = 0;
      for ( auto &i : we )
      {
        // If this edge forms a cycle, ignore it.
        if ( uf.connected(i.vertex1, i.vertex2) )
        {
          //cout << "cycle detected: " << i.vertex1 << "," << i.vertex2 << endl;
          continue;
        }

        // Save edge in the union set for loop detection
        uf.unionSet( i.vertex1, i.vertex2 );

        //cout << "keep : " << i.vertex1 << "," << i.vertex2 << ", d " << i.weight << endl;

        // Keeping this edge
        minCost += i.weight;

        // Stop when enough edges have been collected
        if ( ++numSaved >= (n-1) )
        {
          break;
        }
      }

      return minCost;
    }
};
