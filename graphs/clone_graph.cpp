/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
    Node * dfs( Node * node, unordered_map<int, Node *> &seen )
    {
      Node * newNode = new Node(node->val);
      //cout << "allocated new node for value " << node->val << endl;

      seen.insert(pair<int, Node*>(newNode->val, newNode));

      for ( auto n : node->neighbors )
      {
        unordered_map<int, Node*>::iterator it = seen.find(n->val);
        if ( it == seen.end() )
        {
          //cout << "at node " << node->val << ": cloneGraph for " << n->val << endl;
          newNode->neighbors.push_back( dfs( n, seen ) );
        }
        else
        {
          //cout << "at node " << node->val << ": already seen " << n->val << endl;
          newNode->neighbors.push_back(it->second);
        }
      }

      //seen.erase(newNode->val);

      return newNode;
    }
public:
    Node* cloneGraph(Node* node)
    {
      if ( node == nullptr )
      {
        return nullptr;
      }

      unordered_map<int, Node *> seen;

      return dfs(node, seen);
    }
};
