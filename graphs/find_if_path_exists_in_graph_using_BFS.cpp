// Forced myself to use BFS
// Disjoint sets solved this much faster.
class Solution {
    // using BFS
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
      unordered_map<int, vector<int>> aj;
      if ( n == 1 )
        return true;

      for ( auto e : edges ) {
        aj[ e[0] ].push_back( e[1] );
        aj[ e[1] ].push_back( e[0] );
      }

      #ifdef DEBUG
      for ( auto a : aj ) {
        cout << "adjacencyList " << a.first << ":";
        for ( auto i : a.second ) {
          cout << " " << i;
        }
        cout << endl;
      }
      #endif

      vector<bool> seen(n);
      seen.clear();
      std::queue<int> q;
      q.push(source);
      seen[source] = true;
      while ( !q.empty() )
      {
        int curNode = q.front();
        q.pop();
        for ( auto & i : aj[curNode] )
        {
          if ( i == destination )
          {
            return true;
          }
          if ( seen[i] == false )
          {
            q.push(i);
            seen[i] = true;
          }
        }
      }

      return false;
    }
};
