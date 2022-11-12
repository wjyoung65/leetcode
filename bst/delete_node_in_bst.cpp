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
private:
  int findInOrderSuccessor(TreeNode * root)
  {
    TreeNode * node = root->right;
    while ( node->left )
    {
      node = node->left;
    }
    return node->val;
  }
  int findInOrderPredecessor(TreeNode * root)
  {
    TreeNode * node = root->left;
    while ( node->right )
    {
      node = node->right;
    }
    return node->val;
  }

public:
  TreeNode* deleteNode(TreeNode* root, int key) {
    if ( root == nullptr )
    {
      return root;
    }
    if ( key > root->val && root->right )
    {
      // the key is somewhere on the right side of the BST
      root->right = deleteNode( root->right, key );
    }
    else if ( key < root->val && root->left )
    {
      root->left = deleteNode( root->left, key );
    }
    else if ( key == root->val )
    {
      if ( root->left == nullptr && root->right == nullptr )
      {
        // this is a leaf node
        delete root;
        return nullptr;  // to fixup previous node's left or right pointer
      }
      else if ( root->left != nullptr )
      {
        // replace node's value with in-order predecessor
        int p = findInOrderPredecessor(root);
        root->val = p;
        // recursively find and delete the old node containing p
        root->left = deleteNode(root->left, p);
      }
      else
      {
        // replace node's value with in-order successor
        int p = findInOrderSuccessor(root);
        root->val = p;
        // recursively find and delete the old node containing p
        root->right = deleteNode(root->right, p);
      }
    }
    // else key was not found

    return root;
  }
};
