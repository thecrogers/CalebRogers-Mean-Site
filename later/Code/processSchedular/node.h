#ifndef NODEHEADERFILE

#define NODEHEADERFILE

struct node
	{
	 int ID;
	 unsigned long long cycle;
	 unsigned long long turnTime;
	 int mem;
	 int state;
	 node* next;
	 node* prev;
	};
	
#endif