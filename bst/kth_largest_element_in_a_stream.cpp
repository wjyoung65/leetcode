// Implemented this with BST because the challenge was posed in the
// "Explore BST" section. It would be faster to implement as a heap.

class KthLargest {
private:
    class TreeNode2
    {
    public:
      int         val;
      unsigned    count;    // number of vals at this node
      unsigned    numLeft;  // number of vals on the left subtree
      unsigned    numRight; // number of vals on the right subtree
      TreeNode2 * left;
      TreeNode2 * right;
    };

    // Root of our BST;
    TreeNode2 *  mRoot;

    // The Kth element to return every time a node is added
    unsigned    mK;

    // Kth largest value. An optimization is to return this value
    // if the inserted value is less than or equal to this one.
    // If it's greater than, we'll need to re-evaluate.
    int mKthLargestValue;

    /// Insert 'val' into the tree
    void insert(const int val)
    {
      if ( mRoot == nullptr )
      {
//cout << "root val is " << val << endl;
        mRoot = new(TreeNode2);
        mRoot->val = val;
        mRoot->count = 1;
        mRoot->numLeft = mRoot->numRight = 0;
        mRoot->left = mRoot->right = nullptr;
      }
      else
      {
        // Iteratively insert the value into the tree
        for ( TreeNode2 * cur = mRoot; cur; )
        {
          if ( val == cur->val )
          {
            // insert an existing value by increasing the count
            cur->count += 1;
//cout << "val " << val << " count " << cur->count << endl;
            break;
          }

          if ( val < cur->val && cur->left != nullptr )
          {
            // explore left side
            cur->numLeft += 1;
            cur = cur->left;
          }
          else if ( val > cur->val && cur->right != nullptr )
          {
            // explore right side
            cur->numRight += 1;
            cur = cur->right;
          }
          else
          {
            // cur is a leaf node
            TreeNode2 * n = new(TreeNode2);
            n->val = val;
            n->count = 1;
            n->numLeft = n->numRight = 0;
            n->left = n->right = nullptr;
            if ( val < cur->val )
            {
//cout << "new val " << val << " to left side of " << cur->val << endl;
              cur->left = n;
              cur->numLeft += 1;
            }
            else
            {
//cout << "new val " << val << " to right side of " << cur->val << endl;
              cur->right = n;
              cur->numRight += 1;
            }
            break;
          }
        }
      }
    } // end insert routine

    // Return kth largest value in the tree
    int findKthLargest( TreeNode2 * root, unsigned k )
    {
//cout << "Find from node " << root->val << ": k " << k
//     << ", c " << root->count << ", l " << root->numLeft << ", r " << root->numRight  << endl;
      if ( k == 0 )
      {
        cout << "invalid k" << endl;
        return -1;
      }
      else if ( (root->count + root->numLeft + root->numRight) < k )
      {
        // Failed sanity check: requested kth largest is more
        // than there are values in this tree
        cout << "Error: k " << k
             << ", count " << root->count
             << ", numLeft " << root->numLeft
             << ", numRight " << root->numRight
             << " at node " << root->val << endl;
        return -2;
      }

      if ( root->numRight >= k )
      {
//cout << "explore right" << endl;
        // explore right subtree without altering k
        return findKthLargest( root->right, k );
      }
      else if ( (root->numRight + root->count) >= k )
      {
//cout << "found the node" << endl;
        // Found the node
        return root->val;
      }
      else
      {
        // explore the left tree
        if ( root->left == nullptr )
        {
          // this shouldn't happen
          cout << "Error: k " << k
               << ", count " << root->count
               << ", numLeft " << root->numLeft
               << ", numRight " << root->numRight
               << " at node " << root->val << endl;
          return -3;
        }
//cout << "explore left" << endl;
        return findKthLargest( root->left, k - root->count - root->numRight );
      }
    }

public:
    KthLargest(int k, vector<int>& nums)
    : mRoot(nullptr)
    , mKthLargestValue(-20000)
    , mK(0)
    {
      mK = k;  // remember this for the 'add' routine

      // Build the tree
      // 0 <= nums.length <= 10000
      for ( auto &i : nums )
      {
        insert(i);
      }

      // Sneaky... make sure we were given a tree
      if ( mRoot != nullptr )
      {
        mKthLargestValue = findKthLargest( mRoot, mK );
      }
    }

    int add(int val)
    {
      insert(val);

      if ( val > mKthLargestValue )
      {
        mKthLargestValue = findKthLargest( mRoot, mK );
      }

      return mKthLargestValue;
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
