// Generate letter combinations from digits entered into a phone pad.
// Constraints: 4 digits at most, all digits from 2-9
class Solution {
  void foo(string digits, int index, string a, vector<string> &output )
  {
    string keypad[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    int key = digits[index] - '2';
    //cout << "digits " << digits << ", index " << index << ", key " << key << endl;

    if ( index == digits.length()-1 )  // last digit
    {
      for (int i = 0; i < keypad[key].length(); i++)
      {
        a.push_back( keypad[key][i] );
        //cout << "accumulated: " << a << endl;
        output.push_back(a);
        a.pop_back();
      }
    }
    else
    {
      for (int i = 0; i < keypad[key].length(); i++)
      {
        a.push_back( keypad[key][i] );
        foo( digits, index+1, a, output );
        a.pop_back();
      }
    }
  }
public:
    vector<string> letterCombinations(string digits) {
      vector<string> output;
      string a;  // working buffer for accumulated characters

      if ( digits.length() > 0 )
        foo( digits, 0, a, output );

      return output;
    }
};
