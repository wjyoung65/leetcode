// Implementation of Prim's algorithm using a single edge
// list rather than an adjaceny matrix as Prof Abdul used.
// Did that because the input is a set of vertices, and
// all vertices connect to each other.
class Solution {
//#define DEBUG 1
    class Edge
    {
    public:
      int vertex1;
      int vertex2;
      long cost;

      Edge( int v1, int v2, long c )
      : vertex1(v1)
      , vertex2(v2)
      , cost(c)
      {
      }
    };

    vector< Edge > edges;
    int numVertex;

    static const long MY_INFINITY = 4294967295;
    static const long ALREADY_DONE = -1;

    long lookup( const int vertex1, const int vertex2 )
    {
      if ( vertex1 == vertex2 )
        return MY_INFINITY;
      int v1, v2;
      if ( vertex1 < vertex2 )
      {
        v1 = vertex1;
        v2 = vertex2;
      }
      else
      {
        v1 = vertex2;
        v2 = vertex1;
      }
      // Came up with this index calculation all by myself!
      /*
       * The edge list is calculated in a pair of nested loops, so take
       * advantage of that to do a "2d" lookup with simple linear array
       *
       * Suppose number of vertices n = 5. The edge list will be:
       *  index v1 v2  weight
       *   0     0  1  w1
       *   1     0  2  w2
       *   2     0  3  w3
       *   3     0  4  w4
       *   4     1  2  w5
       *   5     1  3  w6
       *   6     1  4  w7
       *   7     2  3  w8
       *   8     2  4  w9
       *   9     3  4  w10
       * Lookup v1=0 v2=0 is not allowed because there is no edge between
       * identical vertices.
       * Lookup v1=0 v2=1 is index 0
       * Lookup v1=1 v2=2 is index 4
       * Lookup v1=2 v2=3 is index 7
       * There are 4 (=n-1) pairs for v1=0
       * There are 3 (=n-2) pairs for v1=1
       * There are 2 (=n-3) pairs for v1=2
       * There are 1 (=n-4) pairs for v1=3
       * Suppose v1=a=3, v2=b=4, n=5
       *   index = (n-1) + (n-2) + (n-3) + b - (a+1)
       *         = 3n - (1+2+3) + b - (a+1)
       *         = n(a) - (a(a+1)/2) + b - (a+1)
       *         = n(a) - a - (a(a+1)/2) + b - 1
       *         = a(n-1) - (a(a+1)/2) + b - 1
      */
      int index = v1 * (numVertex -1) - ((v1 * (v1+1))/2) + v2 - 1;
      long cost = edges[index].cost;
#ifdef DEBUG
      cout << "v1 " << v1 << ", v2 " << v2 << ", index " << index << ", cost " << cost << endl;
#endif
      return cost;
    }
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
      long minCost = 0;
      int n = points.size();

      numVertex = n;

      if ( n == 1 )
      {
        return 0;
      }

      // Calculate cost between all points
      for ( int i = 0; i < n-1; i++)
      {
        vector<int> &a = points[i];
        for ( unsigned j = i+1; j < n; j++)
        {
          vector<int> &b = points[j];
          int cost = abs(a[0] - b[0]) + abs(a[1] - b[1]);
          edges.push_back( Edge(i, j, cost) );
        }
      }

#ifdef DEBUG
      // debug the edge list lookup function
      for ( int i = 0; i < n; i++ )
      {
        for ( int j = 0; j < n; j++ )
        {
          lookup(i, j);
        }
      }
#endif

      // Start Prim's algorithm

      int k = 0;
      long min = MY_INFINITY;

      long *near = new long[n];
      for ( int i = 0; i < n; i++ )
        near[i] = MY_INFINITY;

      // Only need to save n-1 edges
      int *t[2]; // save tree edges
      for ( unsigned i = 0; i < 2; i++ )
      {
        t[i] = new int[n-1];
      }

      // Start from vertex 0, find smallest edge connected to it
      // Due to the nature of this graph, vertex 0 is connected to
      // all other nodes.
      for ( int i = 0; i < n; i++ )
      {
        long cost = lookup(0, i);
        if ( cost < min )
        {
          min = cost;
          k = i;  // remember the closest vertex
        }
      }
      // save the edge to "t"
      t[0][0] = 0;
      t[1][0] = k;
#ifdef DEBUG
      cout << "1: closest to 0 is " << k << endl;
#endif
      near[0] = near[k] = ALREADY_DONE;

      // Set up the near array. Up to this point each element contains
      // either 0 or infinity. After this each element will contain
      // 0 or t[0][0] or t[1][0], whichever is closest to i.
      for ( int i = 0; i < n; i++ )
      {
        if ( near[i] == ALREADY_DONE )
          continue;  // i is a vertex already in the 't' array
        near[i] = (lookup(t[0][0], i) < lookup(t[1][0], i)) ? t[0][0] : t[1][0];
      }

#ifdef DEBUG
      // dump the near array
      cout << "dump near array: ";
      for ( int i = 0; i < n; i++ )
        cout << near[i] << " ";
      cout << endl;
#endif
      // Find the remaining edges
      for ( int i = 1; i < n-1; i++ )
      {
        min = MY_INFINITY;
        // step through the near array
        for ( int j = 0; j < n; j++ )
        {
          if ( near[j] == ALREADY_DONE )
            continue;  // already done vertex j
          long cost = lookup( j, near[j] );
          if ( cost < min )
          {
            min = cost;
            k = j;  // remember which gives min cost
          }
        }
        t[0][i] = k;
        t[1][i] = near[k];
#ifdef DEBUG
        cout << "next edge: " << k << ", " << near[k] << ", cost " << min << endl;
#endif
        near[k] = ALREADY_DONE;

        // update near array
        for ( int j = 0; j < n; j++ )
        {
          if ( near[j] == ALREADY_DONE )
            continue;
          if ( lookup(j, k) < lookup(j, near[j]) )
          {
            near[j] = k;
          }
        }
#ifdef DEBUG
        // dump the near array
        cout << "dump near array: ";
        for ( int i = 0; i < n; i++ )
          cout << near[i] << " ";
        cout << endl;
#endif
      }

      // add up the cost
#ifdef DEBUG
      cout << "add minCost" << endl;
#endif
      for ( int i = 0; i < n-1; i++ )
      {
        minCost += lookup(t[0][i], t[1][i]);
      }

      return minCost;
    }
};
