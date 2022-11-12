class Solution {
  //#define DEBUG

  enum STATE
  {
    START = 0,
    COUNTING_ONES_A,  // first set of ones
    COUNTING_ONES_B   // second set of ones
  };

  // Beginning or hit two 0's: START
  // State was START and see a 1: COUNTING_ONES_A
  // State was COUNTING_ONES_A and see a 0: COUNTING_ONES_B and keep track of the index of the 0

public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
      enum STATE state = START;
      int zero = INT_MIN;
      int numOnes = 0;
      int maxOnes = INT_MIN;

      for ( int i = 0; i < nums.size(); i++ )
      {
        int b = nums[i];

        switch ( state )
        {
          case START:
            if ( b == 1 )
            {
              state = COUNTING_ONES_A;
              numOnes = 1;
            }
            break;

          case COUNTING_ONES_A:
            if ( b == 0)
            {
              zero = i; // remember where the zero is
              ++numOnes; // pretend we flipped it from 0 to 1
              state = COUNTING_ONES_B;  // started second set of ones
            }
            else
            {
              ++numOnes;
            }
            #ifdef DEBUG
            cout << "A: numOnes " << numOnes << endl;
            #endif
            break;
          case COUNTING_ONES_B:
            if ( b == 0 )
            {
              if ( i == zero + 1 )
              {
                // this is the second 0 in a row: reset the state machine
                state = START;
                zero = INT_MIN;
                maxOnes = max(numOnes, maxOnes);
                numOnes = 0;
                #ifdef DEBUG
                cout << "B1: second zero in a row: maxOnes " << maxOnes << endl;
                #endif
              }
              else
              {
                // not the second 0 in a row, but the we cannot flip any more zeroes to ones
                // to include it in the current run.
                maxOnes = max(numOnes, maxOnes);  // record the length of the current run

                // shorten maxOnes according to position of prev zero
                //   0 1 2 3 4 5 6 7 8 9
                //   1 1 0 1 1 1 0 1 1 1
                //       z       ^-- maxOnes = 5 - 2 = 3
                numOnes -= zero;  // includes flipping this 0 to a 1
                zero = i;
                // state remains COUNTING_ONES_B: counting second set of 1s
                #ifdef DEBUG
                cout << "B2: first zero in a row: numOnes " << numOnes << endl;
                #endif
              }
            }
            else
            {
              ++numOnes;
            }
            break;
          default:
            cout << "bad state " << state << endl;
            break;
        }
        maxOnes = max(numOnes, maxOnes);
      }

      return maxOnes;
    }
};
