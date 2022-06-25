class Solution {
    bool isInPath( vector<vector<int>> &path, int x, int y )
    {
      for ( auto & i : path )
      {
        if ( i[0] == x && i[1] == y )
        {
          return true;
        }
      }
      return false;
    }
    void printPath( char * prefix, vector<vector<int>> &path)
    {
      cout << prefix;
      for ( auto & i : path )
      {
        cout << "[" << i[0] << "," << i[1] << "] ";
      }
      cout << endl;
    }
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
      queue< vector<int> > q;   // queue of nodes to explore
      vector<int> curNode = {0,0};
      int n = grid.size();
      int shortestPath = -1;

      if ( grid[0][0] != 0 )
        return -1;

      q.push(curNode);
      grid[0][0] = 1;

      while ( !q.empty() )
      {
        curNode = q.front();
        q.pop();

        int x = curNode[0];
        int y = curNode[1];
        int curLength = grid[x][y];

        if ( x == (n-1) && y == (n-1) )
        {
          return curLength;
        }

        #define doit(a,b) \
        {\
          if ( a >= 0 && a < n && b >= 0 && b < n && grid[a][b] == 0 ) \
          { \
            vector<int> newNode; \
            newNode.push_back(a); \
            newNode.push_back(b); \
            q.push(newNode); \
            grid[a][b] = curLength+1; \
          } \
        }
        doit(x+1,y+1)
        doit(x+1,y)
        doit(x,y+1)
        doit(x-1,y-1)
        doit(x-1,y)
        doit(x,y-1)
        doit(x+1,y-1)
        doit(x-1,y+1)
      } // end flood fill
      
      return shortestPath;
    }
};
