/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    #define DEBUG

public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

      vector< vector<int> > output;
      queue<TreeNode *> nodes;
      bool is_order_left = true;

      if ( root == nullptr )
        return output;

      // add root element with a delimiter to prime the BFS algo
      nodes.push(root);
      nodes.push(nullptr);

      vector<int> level_list;

      while ( !nodes.empty() )
      {
        TreeNode * n = nodes.front();
        nodes.pop();
        #ifdef DEBUG
        if ( n )
          cout << "n " << n->val << endl;
        else
          cout << "n nullptr" << endl;
        #endif

        if ( n != nullptr )
        {
          if ( is_order_left )
          {
            level_list.push_back(n->val);
          }
          else
          {
            level_list.insert(level_list.begin(), n->val);
          }

          if ( n->left != nullptr )
          {
            #ifdef DEBUG
            cout << "from n " << n->val << ", push n->left " << n->left->val << endl;
            #endif
            nodes.push(n->left);
          }
          if ( n->right != nullptr )
          {
            #ifdef DEBUG
            cout << "from n " << n->val << ", push n->right " << n->right->val << endl;
            #endif
            nodes.push(n->right);
          }
        }
        else
        {
          // finished scan of one level
          output.emplace_back( level_list );
          level_list.clear();

          if ( nodes.size() > 0 )
          {
            #ifdef DEBUG
            cout << "push a nullptr" << endl;
            #endif

            // Push nullptr only if queue has content, else infinite loop
            nodes.push(nullptr);
          }

          is_order_left = !is_order_left;
        }
      }

      return output;
    }
};
