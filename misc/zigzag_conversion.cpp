// Runtime 5ms, faster than 92.83% of C++ online submissions
// Mem usage: 8.3MB, less than 80.98% of C++ online submissions
class Solution {
public:
    string convert(string s, int numRows) {
      unsigned length = s.length();
      string out;
      int diff = max(1, numRows + (numRows-1) - 1);
      int runningDiff = diff - 2;
      int curIn = 0;

      for ( unsigned i = 0; i < numRows && i < length; i++ )
      {
        if ( i == 0 || i == (numRows-1) )
        {
          // Top or bottom of the zigzag
          // Only have to include the numbers at the peak
          curIn = i;

          for ( curIn = i; curIn < length; curIn += diff )
          {
            out += s[curIn];
          }
        }
        else
        {
          // Middle sections use an alternating increment or
          // "diff" from the target index to the current index.
          curIn = i;
          out += s[curIn];
          while ( curIn < length )
          {
            unsigned alt = curIn + runningDiff;
            curIn += diff;
            if ( alt < length )
            {
              out += s[alt];
            }
            if ( curIn < length )
            {
              out += s[curIn];
            }
          }

          runningDiff -= 2;
        }
      }

      return out;
    }
};
