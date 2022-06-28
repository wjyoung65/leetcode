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

  bool validPath(int n, unordered_map<int, vector<int>> &aj, int source, int destination)
  {
    if ( n <= 1 )
      return false;

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

public:
    int minCostConnectPoints(vector<vector<int>>& points) {
      int minCost = 0;
      int n = points.size();
      unordered_map< int, vector<int> > aj; // collected edges in an adjacency list, for cycle detection
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
        // Wondering if this code is performing poorly because of cycle detection
        // using DFS
        if ( validPath( n, aj, i.vertex1, i.vertex2 ) )
        {
          //cout << "cycle detected: " << i.vertex1 << "," << i.vertex2 << endl;
          continue;
        }

        // Save edge in the adjacency list for loop detection
        aj[ i.vertex1 ].push_back( i.vertex2 );
        aj[ i.vertex2 ].push_back( i.vertex1 );

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
