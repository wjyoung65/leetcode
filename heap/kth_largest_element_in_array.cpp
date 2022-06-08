// Find kth largest element in an array
// Duplicates values are allowed: not returning the kth largest distinct element
//
// The naive approach is to sort the array in descending order.
// This approach creates a min heap implemented as an array with k elements.
// Instead of inserting new elements at the end of the array (last leaf) and
// then checking if the value is less than parents recursively,
// new elements are swapped into top of the minheap if the value is greater.
// Then check if parent is greater than children, and swap with smallest child.
// Recursively do this.

class Solution {
private:
    const int minValue = -10001;

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

    void printHeap( vector<int> nums )
    {
      for ( auto & i : nums )
      {
        cout << i << " ";
      }
      cout << endl;
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
    int findKthLargest(vector<int>& nums, int k)
    {
      // Implement minheap, with k'th largest value on top,
      // - replace head if new number is greather than it
      // - re-heapify so that larger values move toward leaf nodes
      vector<int> heap(k);  // implement max heap as an array
      unsigned heapCount = 0;

      // Populate the array
      for ( auto &i : nums )
      {
        add(heap, heapCount, i, k);
        //printHeap(heap);
      }

      return heap[0];
    }
};
