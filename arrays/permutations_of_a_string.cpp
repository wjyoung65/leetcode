#include <iostream>
#include <cstring>
using namespace std;

void swap( char &i, char &j )
{
  char temp = i;
  i = j;
  j = temp;
}

void perm( char * s, int lo, int hi )
{
  if ( lo == hi )
  {
    cout << s << endl;
  }
  else
  {
    for ( unsigned k = lo; k <= hi; k++ )
    {
      if ( k != lo )
      {
        // swap the letters to permutate letters at this level
        swap( s[k], s[lo] );
      }

      // recursively generate a permutation
      perm( s, lo+1, hi );

      if ( k != lo )
      {
        // put the letter back for the next iteration
        swap( s[k], s[lo] );
      }
    }
  }
}

int main(int argc, char * argv[] )
{
  const char * defaultStr = "abc";
  char * s = nullptr;
  if ( argc > 1 && strlen(argv[1]) > 0 )
  {
    s = (char *) malloc( strlen( argv[1] ) + 1 );
    strcpy(s, argv[1]);
  }
  else
  {
    s = (char *) malloc( strlen( defaultStr ) + 1 );
    strcpy(s, defaultStr);
  }

  cout << "permutate " << s << endl;

  perm( s, 0, strlen(s)-1 );

  return 0;
}
