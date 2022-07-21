// Given a grid of letters and a word, return true if word
// can be found in the grid.
//
// The solution is an example of the "backtrace" alg.
// I had to peek at the solution to get this because it's my
// first exposure to the backtrace template. Should have
// studied leetcode's recursion "explore" card.
class Solution {

  // implements backtrack algorithm
  bool explore( vector<vector<char>>& board, int row, int col, string word, int index )
  {
    //cout << "input: row " << row << ", col " << col << ", index " << index << endl;
    if ( index >= word.length() )
    {
      //cout << "end of word at index " << index << ", row " << row << ", col " << col << endl;
      return true;  // reached end of word
    }

    // check boundaries
    if ( row < 0 || row >= board.size() || col < 0 || col >= board[0].size() )
    {
      //cout << "row " << row << ", col " << col << " out of bounds" << endl;
      return false;  // out of bounds
    }

    // check letter matches
    if ( board[row][col] != word[index] )
    {
      //cout << "row " << row << ", col " << col << " no match on letter " << word[index] << endl;
      return false;
    }

    // place: mark the cell as explored
    board[row][col] = '#';

    // next candidates are either above, below, left, or right of current cell
    int dx[] = {-1, 0, 1,  0};
    int dy[] = { 0, 1, 0, -1};

    for ( int i = 0; i < 4; i++ )
    {
      // DFS explore the next candidate
      if ( explore(board, row + dy[i], col + dx[i], word, index+1) )
      {
        return true;
      }
    }

    // restore
    //cout << "restore row " << row << ", col " << col << endl;
    board[row][col] = word[index];
    return false;
  }
public:
    bool exist(vector<vector<char>>& board, string word) {

      // Find a cell with first letter
      int i, j;
      for ( i = 0; i < board.size(); i++ )
      {
        for (j = 0; j < board[0].size(); j++ )
        {
          if ( board[i][j] == word[0] )
          {
            if ( explore(board, i, j, word, 0) )
            {
              return true;
            }
          }
        }
      }
      return false;
    }
};
