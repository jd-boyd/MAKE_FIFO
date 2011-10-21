#include <stdio.h>
#include <assert.h>

#include "fifo.h"

int main(void)
{
  MAKE_FIFO(tf, 4);
  int i;
  assert(DEPTH(tf)==0);
  assert(FREE(tf)==4);
  
  for (i=0; i<3; i++)
  {
    PUT(tf, i);
    assert(DEPTH(tf)==i+1);
    assert(FREE(tf)==4-i-1);
  }
  
  assert(!IS_FULL(tf));
  assert(IS_NOT_FULL(tf)); 
  assert(!OVFL(tf)); 
  PUT(tf, 5);
  
  assert(DEPTH(tf)==4);
  assert(FREE(tf)==0);
  
  assert(IS_FULL(tf));
  assert(!IS_NOT_FULL(tf));

  assert(!OVFL(tf)); 
  
  REMOVE(tf);
  REMOVE(tf);
  assert(DEPTH(tf)==2);
  
  for (i=0; i<2; i++)
  {
    PUT(tf, i);
    assert(DEPTH(tf)==3+i);
  }
  
  REMOVE(tf);
  REMOVE(tf);
  REMOVE(tf);
  REMOVE(tf);
  
  assert(DEPTH(tf)==0);
  assert(FREE(tf)==4);

  for (i=0; i<4; i++)
  {
    PUT(tf, i);
    assert(DEPTH(tf)==i+1);
    assert(FREE(tf)==4-i-1);
  }
  assert(!OVFL(tf));
  PUT(tf, 5);
  assert(OVFL(tf));

  return 0;
}
