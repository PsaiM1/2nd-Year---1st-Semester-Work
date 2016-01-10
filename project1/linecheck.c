/*
  Author: PrasannaSai Meruga
  Class: CMSC216, Herman

  This program's function is to read lines from a file input and, then the 
  program will take the input and store it in an array and count the number of
  characters and characters produced by escape sequences. The program will then
  print the length of the input line and then the line itself.
 */

#include <stdio.h>

int main() {

  int line_length = 0;
  int index = 0;
  char line[1000] = {'@'};
  char in = '0';

  scanf("%c", &in);
  do {
    line[index++] = in;
    if (in != '\n' && in != '\t') { /*normal character hence increase length*/
      line_length++;
    } else if (in == '\t') {
      /*when theres a tab it will calculate the number of spaces remain
	until the next tab stop, it then adds the number of spaces to
	the line_length*/
      int tab_stop = (line_length % 8);
      int space_number = (8 - tab_stop);
      line_length = line_length +  space_number;
    } else {
      int x;
      /*print the line_length and the line itself and reset the line array*/
      printf("%4d: ", line_length);
      for (x = 0; x < index; x++) {
	 printf("%c",line[x]);
	 line[x] = '@';
      }
      /*reset line_length and index for the next input line*/
      line_length = 0;
      index = 0;
    }
    scanf("%c", &in);
  } while (!feof(stdin)); 
  return 0;
}



