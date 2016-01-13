#ifndef SCHEDULARHEADERFILE
#include<iostream>
#include <vector>
#include <cmath>  
#include "node.h"
#include "Processor.h"
#define SCHEDULARHEADERFILE

using namespace std;
class Schedular
{

public:
	Schedular()
	{
	
	}
	int indentical(vector<node>&,int,int);//all 5 CPU's same
	int memory_base(vector<node>&,int,int);//CPU's with differing memory sizes.
	int cycle_base(vector<node>&,int,int);//CPU's with differing cycle times.
    int real_time(vector<node>&,int,int);//schedualing as process come in. 
    int addProcess(int,int,int,vector<node>&);
    int sort(vector<node>& list, int mode);//sort. 

private:
	
};
#endif