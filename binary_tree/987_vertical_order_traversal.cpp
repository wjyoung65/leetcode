/*

Given the root of a binary tree, calculate the vertical order traversal of the
binary tree.

For each node at position (row, col), its left and right children will be at
positions (row + 1, col - 1) and (row + 1, col + 1) respectively. The root of
the tree is at (0, 0).

The vertical order traversal of a binary tree is a list of top-to-bottom
orderings for each column index starting from the leftmost column and ending
on the rightmost column. There may be multiple nodes in the same row and same
column. In such a case, sort these nodes by their values.

Return the vertical order traversal of the binary tree.

 */
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
  //#define DEBUG

  // first: column
  // second: rows of vectors
  map< int, map<int, vector<int> > > m;

  void solve( TreeNode * root, const int row, const int column )
  {
    if ( root == nullptr )
      return;

    map<int, vector<int> > & rows = m[column];

    rows[row].push_back(root->val);

    solve(root->left, row+1, column-1);
    solve(root->right, row+1, column+1);
  }

public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {

      solve(root, 0, 0);
      vector< vector<int> > output;
      for ( auto & col : m )
      {
        vector<int> v;
        for ( auto & row: col.second )
        {
          // row.first is row number
          // row.second is vector<int> for that row number

          #ifdef DEBUG
          cout << "intermediate vector for col " << col.first << ", row " << row.first << endl;
          for ( auto & i : row.second )
            cout << i << " ";
          cout << endl;
          #endif

          sort(row.second.begin(), row.second.end());
          for ( auto & i : row.second )
          {
            v.push_back(i);
          }
        }

        #ifdef DEBUG
        cout << "final vector for column " << col.first << ":" << endl;
        for ( auto &i : v )
        {
          cout << i << " ";
        }
        cout << endl;
        #endif

        output.push_back(v);
        v.clear();
      }

      return output;
    }
};
