class Solution {
  //#define DEBUG

public:
#ifdef POSTORDER_DFS_BACKTRACKING
    // graph
    unordered_map<int, unordered_set<int> > g;

    bool isCyclic(int courseIdx, int * checked, unordered_set<int>& path)
    {
        if ( checked[courseIdx] == true )
        {
          // node has been checked, no cycle could be formed with this node
          return false;
        }

        if (path.count(courseIdx) != 0)
        {
          // is cyclic because visited this node already
          return true;
        }

        if (g.count(courseIdx) == 0)
        {
          // course has no dependencies, so acyclic
          return false;
        }

        // Backtracking: breadcrumb the path, mark the node we visited.
        path.insert(courseIdx);

        int rval = false;  // result or return value
        auto& courses = g[courseIdx]; // look at dependencies for input courseIdx

        // for each course dependent on the given course
        for (auto newCourseIdx : courses)
        {
            if ((rval = isCyclic(newCourseIdx, checked, path)) == true)
            {
                // dependency has a cycle
                break;
            }
        }

        // Remove breadcrumb for this iteration. Backtracking.
        path.erase(courseIdx);

        // have visited downstream nodes: check of this node complete
        checked[courseIdx] = true;

        return rval;
    }
#else // topological sor
    struct GNode
    {
        int inDegrees;
        vector<int> outNodes;
    };
#endif
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
    {
        if (prerequisites.empty()) return true;

#ifdef POSTORDER_DFS_BACKTRACKING
        // Build a graph from given list of course dependencies
        // e.g. 0:1,2,3  course 0 depends on 1,2,3
        for (auto& e : prerequisites)
        {
            g[e[0]].insert(e[1]);
        }

        int * checked = new int[numCourses];

        unordered_set<int> path;

        for (int i = 0; i < numCourses; ++i)
        {
            if (isCyclic(i, checked, path))
            {
                return false; // cycle detected, cannot finish
            }
        }

        delete[] checked;
        return true;  // no cycle detected
#else // topological sort
        // Build the graph of course -> list of next courses.
        // course bi, next course ai.

        // first: course
        // second: node (info for that course, e.g. list of next courses)
        unordered_map< int, GNode > graph;
        for ( auto & p : prerequisites )
        {
          // build relationship dep -> course
          int course = p[0];
          int dep = p[1];
          graph[dep].outNodes.push_back(course);
          graph[course].inDegrees += 1;
        }

        // Find courses that have no prereqs, so we can start from them
        vector<int> noDepCourses;
        for ( auto & g : graph )
        {
          if ( g.second.inDegrees == 0 )
          {
            #ifdef DEBUG
            cout << "course " << g.first << " has no prereqs" << endl;
            #endif
            noDepCourses.push_back(g.first);
          }
        }

        int removedEdges = 0;
        while ( noDepCourses.size() > 0 )
        {
          int course = noDepCourses.back();
          noDepCourses.pop_back();

          for ( int nextCourse : graph[course].outNodes )
          {
            graph[nextCourse].inDegrees -= 1;
            removedEdges += 1;
            if ( graph[nextCourse].inDegrees == 0 )
            {
              #ifdef DEBUG
              cout << "add nextCourse " << nextCourse << " to noDeps list" << endl;
              #endif
              noDepCourses.push_back(nextCourse);
            }
          }
        }

        int totalDeps = prerequisites.size();
        if ( removedEdges != totalDeps )
          return false;  // still some edges left, so still some cycles. They could not be removed b/c of deadlock / dependencies

        return true;
#endif

    }
};
