#ifndef MEMTREEHEADERFILE
#include "node.h"
#include <math.h>  
#include<iostream>
#define MEMTREEHEADERFILE

class memTree
{
    
  public:

  block* root;
  memTree()
  {

      root=NULL;
  }
  
  ~memTree()
  {
      
  }
    int alloc(block*,int,int,int,int);
	 int allocc(node**,int,int,int,int);
    int free(int,block *);
    void preOrder(block*,int ,int ,int,int,block **);
    void print(block*);
    int Size(block*);
};
#endif
