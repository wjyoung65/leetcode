class Solution {

public:
    // using BFS

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
      int n = graph.size();
      int source = 0;
      int destination = n - 1;
      vector<vector<int>> paths;  // the output
      vector<int> curPath;

      queue< vector<int> > q;
      curPath.push_back(source);
      q.push(curPath);

      while ( !q.empty() )
      {
        // Explore a path in the queue
        vector<int> aPath = q.front();  // aPath = [0]
        q.pop();

        // Visit each neighbor of the node in 'aPath'
        // forming new paths and adding them to the queue
        for ( auto & neighbor : graph[aPath.back()] )
        {
          vector<int> newPath(aPath);       // make a copy of aPath
          newPath.push_back( neighbor );   // newPath = [0,4], then [0,3], then [0,1]
          if ( neighbor == destination )
          {
            paths.push_back( newPath );
          }
          else
          {
            q.push( newPath );
          }
        }
      }

      return paths;
    }
};
