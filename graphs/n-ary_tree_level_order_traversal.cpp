// Example inputs:
// root = []
// root = [1,null]
// root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
      vector< vector<int> > outArray;
      queue<Node *> q;

      if ( root == nullptr )
        return outArray;

      q.push(root);
      int expectedLen = 1;
      vector<int> curVector;

      while ( !q.empty() )
      {
        Node * curNode = q.front();
        q.pop();

        curVector.push_back(curNode->val);

        for ( Node * child : curNode->children )
        {
          q.push( child );
        }

        if ( curVector.size() == expectedLen || q.empty() )
        {
          outArray.emplace_back( curVector );
          curVector.clear();
          expectedLen = q.size();
        }
      }

      return outArray;
    }
};
