// Given a string (e.g. "dcab") and a list of number-pairs where each pair
// represents letter positions that can be swapped, construct the smallest
// string.
// hints:
// - disjoint sets
// - sort the sub strings
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

    class Bundle
    {
    private:
      string        mString;
      vector<int>   mNodes;

    public:
      Bundle() {}
      ~Bundle() {}

      void append( const char c, const int i )
      {
        mString.push_back(c);
        mNodes.push_back(i);
      }

      void fini()
      {
        mString.push_back('\0');
      }

      void sort()
      {
        std::sort(mString.begin(), mString.end());
      }

      int getSize()
      {
        return mNodes.size();
      }

      int getNode(const unsigned i)
      {
        return mNodes[i];
      }

      char getChar(const unsigned i)
      {
        return mString[i];
      }
    };
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
      UnionFind uf(s.size());

      // Create disjoint sets
      for ( auto &i : pairs )
      {
        uf.unionSet( i[0], i[1] );
      }

      // Create a collection of Bundles based on the disjoint sets
      unsigned numBundles = uf.numUniqueRoots();
      cout << "numBundles " << numBundles << endl;
      std::map<int, Bundle *> b;
      for ( unsigned i = 0; i < s.size(); i++ )
      {
        int root = uf.find(i);
        //cout << "i " << i << ": root " << root << ", char " << s[i] << endl;
        if ( b.find(root) == b.end() )
        {
          b.insert(std::pair(root, new(Bundle)));
        }
        b[root]->append(s[i], i);
      }

      // Sort the string in each Bundle
      for ( auto & i : b )
      {
        //i.fini();
        i.second->sort();
      }

      // Output
      string outStr(s);  // yeah, initializing a new string from existing

      for ( auto & i : b )
      {
        //cout << "bundle size " << i.second->getSize() << endl;
        for ( unsigned j = 0; j < i.second->getSize(); j++ )
        {
          //cout << "j " << j << ": node " << i.second->getNode(j) << ", char " << i.second->getChar(j) << endl;
          outStr[i.second->getNode(j)] = i.second->getChar(j);
        }
      }
      return outStr;
    }
};
