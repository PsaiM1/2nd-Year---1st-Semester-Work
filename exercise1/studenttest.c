#include<stdio.h>
#include"functions.h"

int main() {
  printf("test 1 functions 1 (4,4,4) is %d\n", num_unique_values(4, 4, 4));
  printf("test2 functions 1 (3,3,4) is %d\n", num_unique_values(3, 3, 4));
  printf("test 3 functions 2 num 31567837 is %d\n", leftmost_digit(31567837));
  printf("test 4 functions 2 num 10 is %d\n", leftmost_digit(10));
  printf("test 5 functions 2 num 1 is %d\n", leftmost_digit(1));
  printf("test 5 functions 2 num -145 is %d\n", leftmost_digit(-145));

  return 0;

}
