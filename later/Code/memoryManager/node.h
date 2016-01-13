#ifndef NODEHEADERFILE

#define NODEHEADERFILE

struct node
	{
	 int ID;
	 unsigned long long cycle;
	 double mallocSpeed;
	 int remaining;
	 double freeSpeed;
	 int mem;
	 int state;
	 node* next;
	 node* prev;
	};
	
	struct block
	{
	    int size;
	    int ID;
	    int state;
	    int pSize;
	    block* sibling;
	    block* right;
	    block* left;
	    block* parent;
	    
	};

	struct resu
	{
		int state;
		int ID;
		double speed;
	};
#endif
