/*
Author: PrasannaSai Meruga
Section: Majeed 10AM

This header file contains the definition
of the Commands structure
 */
#if !defined(SSS_IMPLEMENTATION_H)
#define SSS_IMPLEMENTATION_H
#include <stdio.h>
#include <stdlib.h>

typedef struct commands {
  /*compile commands list*/
  char **cmplist;
  /*compile list length*/
  int cmplength;
  /*test commands list*/
  char **testlist;
  /*test commands list*/
  int testlength;
} Commands;

#endif

