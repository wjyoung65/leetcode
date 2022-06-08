class KthLargest {
    unsigned mK;
    vector<int> mHeap;
    unsigned mHeapCount;

    unsigned left(const unsigned i)
    {
      return ((i+1)*2)-1;
    }
    unsigned right(const unsigned i)
    {
      return ((i+1)*2);
    }
    unsigned parent(const unsigned i)
    {
      return ((i+1)/2)-1;
    }
    bool isLeaf(const unsigned i, const unsigned k )
    {
      return ( (i+1) * 2 > k );
    }

    void swap( int &a, int &b)
    {
      //cout << "swap " << a << ", " << b << endl;
      int temp = a;
      a = b;
      b = temp;
    }

    void add
    (
      vector<int> &heap,
      unsigned &heapCount,
      const int num,     // new number
      const unsigned k
    )
    {
      if ( heapCount < heap.size() )
      {
        //cout << "1: add " << num << endl;
        // add number to the end of the heap and ensure it remains a minheap
        unsigned last = heapCount;
        heap[last] = num;
        for ( unsigned i = last; i > 0; i = parent(i) )
        {
          unsigned p = parent(i);
          if ( heap[p] > heap[i] )
          {
            swap( heap[p], heap[i] );
          }
        }
        ++heapCount;
      }
      else
      {
        // decide whether the new value should replace head
        if ( num > heap[0] )
        {
          heap[0] = num;

          // make sure it's still a minheap
          unsigned len = heap.size();
          for ( unsigned i = 0; i < len; )
          {
            unsigned a = left(i);
            unsigned b = right(i);
            if ( a < len && b < len && heap[a] < heap[i] && heap[b] < heap[i] )
            {
              //cout << "i " <<heap[i] << ", a "<< heap[a] << ", b " << heap[b] << endl;
              // swap with smallest
              if ( heap[a] < heap[b] )
              {
                swap(heap[a], heap[i]);
                i = a;
              }
              else
              {
                swap(heap[b],heap[i]);
                i = b;
              }
            }
            else if ( a < len && heap[a] < heap[i])
            {
              swap(heap[a], heap[i]);
              i = a;
            }
            else if ( b < len && heap[b] < heap[i])
            {
              swap(heap[b], heap[i]);
              i = b;
            }
            else
            {
              break;
            }
          }
        }
      }
    }
public:
    KthLargest(int k, vector<int>& nums)
    : mK(k)
    , mHeap(k)
    , mHeapCount(0)
    {
      // Build the tree
      // 0 <= nums.length <= 10000
      for ( auto &i : nums )
      {
        add(mHeap, mHeapCount, i, mK);
      }
    }

    int add(int val)
    {
      add(mHeap, mHeapCount, val, mK);
      return mHeap[0];
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
