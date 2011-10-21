#include <stdio.h>

#include "fifo.h"


int main(void)
{
  MAKE_FIFO(tf, 4);
  int i;
  printf("START S %d\n", DEPTH(tf));
  printf("START FREE %d\n", FREE(tf));
  
  for (i=0; i<3; i++)
  {
    PUT(tf, i);
    printf("S %d\n", DEPTH(tf));
  }
  
  printf("FULL %d\n", IS_FULL(tf));
  printf("TEST OVFL %d\n", tf_ovfl);
  PUT(tf, 5);
  
  printf("FULL %d\n", IS_FULL(tf));
  printf("S %d\n", DEPTH(tf));
  printf("TEST OVFL %d\n", tf_ovfl);
  
  REMOVE(tf);
  REMOVE(tf);
  printf("S %d\n", DEPTH(tf));
  
  for (i=0; i<3; i++)
  {
    PUT(tf, i);
    printf("S %d\n", DEPTH(tf));
  }
  
  REMOVE(tf);
  REMOVE(tf);
  REMOVE(tf);
  REMOVE(tf);
  REMOVE(tf);
  
  printf("STOP S %d\n", DEPTH(tf));
  printf("STOP FREE %d\n", FREE(tf));

  return 0;
}
