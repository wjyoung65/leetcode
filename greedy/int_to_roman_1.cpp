class Solution {
  void handleThousands( int num, string & output)
  {
    for ( int k = 0; k < num; k++ )
    {
      output += "M";
    }
  }

  void handleHundreds( int num, string & output )
  {
    if ( num == 9 )
    {
      output += "CM";
      return;
    }
    if ( num >= 5 )
    {
      output += "D";
      num -= 5;
    }
    if ( num == 4 )
    {
      output += "CD";
      return;
    }
    for ( int k = 0; k < num; k++ )
    {
      output += "C";
    }
  }

  void handleTens( int num, string & output )
  {
    if ( num == 9 )
    {
      output += "XC";
      return;
    }
    if ( num >= 5 )
    {
      output += "L";
      num -= 5;
    }
    if ( num == 4 )
    {
      output += "XL";
      return;
    }
    for ( int k = 0; k < num; k++ )
    {
      output += "X";
    }
  }

  void handleOnes( int num, string & output )
  {
    if ( num == 9 )
    {
      output += "IX";
      return;
    }
    if ( num >= 5 )
    {
      output += "V";
      num -= 5;
    }
    if ( num == 4 )
    {
      output += "IV";
      return;
    }
    for ( int k = 0; k < num; k++ )
    {
      output += "I";
    }
  }
public:
    string intToRoman(int num) {
      string output;

      handleThousands( num / 1000, output );

      int h = num % 1000;

      handleHundreds( h / 100, output );

      int d = h % 100;

      handleTens( d/10, output );

      int s = d % 10;

      handleOnes( s, output );

      return output;
    }
};
