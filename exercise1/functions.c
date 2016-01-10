#include <stdio.h>
#include "functions.h"

/* The function num_unique_values() should return the number of unique
 * values that its three integer parameters have.  In particular, all three
 * parameters may have the same value (in which case there is only one
 * unique value, so the function should return 1), or two of them may have
 * the same value (in which case there are two unique values), or they may
 * all have different values (in which case there are three unique values.
 * For example, num_unique_values(7, 8, 9) should return 3, while
 * num_unique_values(4, 8, 4) should return 2.
 *
 * Do not try to use an array.  Just compare the numbers using conditional
 * statements.
 */
int num_unique_values(int w, int x, int y) {
  if (w == x && w == y && x == y) {
    return 1;
  } else if ((w != x && w == y) && x != y) {
    return 2;
  } else if ((w != x && w != y) && x == y) {
    return 2;
  } else if ((w == x && w != y) && x != y) {
    return 2;
  } else if ((w != x && w != y) && x != y) {
    return 3;
  }
}

/*
 * The function leftmost_digit() should return the first or leftmost numeric
 * digit of its parameter num.  num may have any positive or negative
 * integer value; the return value should always be positive.  Note that any
 * integer has a leftmost digit, even an integer that has just one digit.
 *
 * You may NOT use any C library functions.  (For example, do NOT try to
 * turn the number into a string.)  You may ONLY use arithmetic operators.
 */
int leftmost_digit(int num) {
  int x;
  if (num < 0) {
    x = num * -1;
  } else {
    x = num;
  }
    
  while (x >= 10) {
    x = x/10;
  }
  return x;
  
}
