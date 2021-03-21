/*
 * Random functions
*/

#include "aerostat_utils.h"
#include <string.h>
#include <Arduino.h>

/*
Pads a string with a desired character.

Param str: pointer to the string to be modified.
Param replacer: the character you want to pad with
Param special: has 2 uses depending on mode selected:
                Mode 0: every character will be replaced with the replacer until the first occurence of the special (special char will be ignored)
                Mode 1: every character will be replaced with the replacer until the first character that ISN'T the "special" is encountered
Parma mode: determines whether the "special" paremeter tells the function to stop or to continue. See description above.

*/
void charPadString(char str[], char replacer, char special, int mode)
{
  char c = str[0];
  int i = 0;

  if (mode == 0)
  {
    while (c != special && i < strlen(str))
      {
        str[i] = replacer;
        i++;
        c = str[i];
      }
  }
  else if (mode == 1)
  {
    while (c == special && i < strlen(str))
    {
      str[i] = replacer;
      i++;
      c = str[i];
    }
  }
}
