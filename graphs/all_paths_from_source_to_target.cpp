// Directed acyclic graph problem
// Source node is always 0
// Destination node is alway n-1, where n is the size of 'graph', the input
//
// This did not perform well, only beating 18% of submissions
// But it passed "submission" rather quickly.
// Just dealt with a number of compile errors and one programming error
// checking if a number was in the seen set (!~ instead of == set.end())
class Solution {
private:
    // DAG = directed acyclic graph
    class WalkDag
    {
    private:
      stack<int>                      mNodesToVisit;
      unordered_map<int, vector<int>> mAdjacencyList;
      set<int>                        mSeen;

      vector<int>                     mCurPath;

      vector<vector<int>>             mOutput;

      int mSourceNode;
      int mDestNode;

      void buildAdjacencyList( vector<vector<int>>& graph )
      {
        for ( unsigned node = 0; node < graph.size(); node++ )
        {
          vector<int> v( graph[node] );
          //cout << "build adj list for node " << node << ":";
          //for ( auto & i : v)
          //  cout << " " << i;
          //cout << endl;
          mAdjacencyList.emplace( node, v );
        }
      }

      void buildPath()
      {
        // pop a node off the stack
        int curNode = mNodesToVisit.top();
        mNodesToVisit.pop();

        int numNodesAtThisLevel = 0;

        // Look in adjaency list and add those nodes to the stack
        vector<int> &v = mAdjacencyList[curNode];
        for ( auto & i : v )
        {
          //cout << "curNode " << curNode << ": check seen set for node " << i << endl;
          if ( mSeen.find(i) == mSeen.end() )
          {
            // node has not been seen, so allow a visit to it
            ++numNodesAtThisLevel;
            mNodesToVisit.push(i);
            //cout << "curNode " << curNode << ": pushed node " << i << ", num " << numNodesAtThisLevel << endl;
          }
        }
        //cout << "curNode " << curNode << ": numNodes " << numNodesAtThisLevel << endl;

        // Indicte the current node has been seen
        mSeen.insert(curNode);

        // Add curNode to the path being built
        mCurPath.push_back(curNode);

        if ( curNode == mDestNode )
        {
          // This is the destination node
          vector<int> output(mCurPath);
          mOutput.push_back(output);
        }
        else
        {
          // Recursively visit the next node in the stack
          for ( unsigned i = 0; i < numNodesAtThisLevel; i++ )
          {
            buildPath();
          }
        }
        //cout << "curNode " << curNode << endl;
        mSeen.erase(curNode);
        mCurPath.pop_back();
      }

    public:
      WalkDag
      (
          vector<vector<int>>& graph
        , const int src
        , const int dst
      )
        : mSourceNode(src)
        , mDestNode(dst)
      {
        buildAdjacencyList(graph);
      }

      void findPaths()
      {
        // Prime the stack with the start node, node 0
        mNodesToVisit.push(0);

        buildPath();
      }

      vector<vector<int>> getOutput() { return mOutput; }
    };

public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {

      int sourceNode = 0;
      int destNode = graph.size() - 1;

      WalkDag wd( graph, sourceNode, destNode );

      wd.findPaths();

      return wd.getOutput();
    }
};
