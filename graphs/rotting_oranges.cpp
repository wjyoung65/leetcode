// Faster than 65%, but memory usage higher than I'd expect

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid)
    {
      queue< vector<int> > q;   // queue of nodes to explore

      int m = grid.size();
      int n = grid[0].size();
      int numRottenFoundThisMinute = 0;
      int numFresh = 0;

      // Find rotten oranges using nested loops
      // Time complexity O(m * n ). Could be optimized?
      for ( int i = 0; i < m; i++ )
      {
        for ( int j = 0; j < n; j++ )
        {
          if ( grid[i][j] == 2 )
          {
            vector<int> curNode = {i,j};
            q.push( curNode );
            ++numRottenFoundThisMinute;
          }
          else if ( grid[i][j] == 1 )
          {
            ++numFresh;
          }
        }
      }
      if ( numFresh > 0 && q.empty() )
      {
        return -1;
      }
      if ( q.empty() )
      {
        return 0; // no fresh or no rotten oranges to start
      }

      int numMinutes = -1;
      int numRottenTarget = numRottenFoundThisMinute;
      //cout << "start: numRottenTarget " << numRottenTarget << endl;
      numRottenFoundThisMinute = 0;
      vector<int> curNode;

      while ( !q.empty() )
      {
        curNode = q.front();
        q.pop();

        int x = curNode[0];
        int y = curNode[1];
        //cout << "minute " << numMinutes << ": " << x << ", " << y << endl;
        ++numRottenFoundThisMinute;

        // Visit neighbours in m x n matrix
        #define doit(a,b) \
        {\
          if ( a >= 0 && a < m && b >= 0 && b < n && grid[a][b] == 1 ) \
          { \
            vector<int> newNode; \
            newNode.push_back(a); \
            newNode.push_back(b); \
            q.push(newNode); \
            grid[a][b] = 2; \
            --numFresh; \
          } \
        }

        // Only need to do 4-way connections: left, right, above, below
        //doit(x+1,y+1)
        doit(x+1,y)
        doit(x,y+1)
        //doit(x-1,y-1)
        doit(x-1,y)
        doit(x,y-1)
        //doit(x+1,y-1)
        //doit(x-1,y+1)

        if ( numRottenFoundThisMinute == numRottenTarget )
        {
          ++numMinutes;
          numRottenFoundThisMinute = 0;
          numRottenTarget = q.size();
          //cout << "minute " << numMinutes << ": numRottenTarget " << numRottenTarget << endl;
        }
      } // end flood fill

      if ( numFresh > 0 )
      {
        return -1; // Still some fresh oranges
      }

      return numMinutes;
    }
};
