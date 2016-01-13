#ifndef SCHEDULARHEADERFILE
#include<iostream>
#include <vector>
#include <cmath>  
#include "node.h"
#define SCHEDULARHEADERFILE

using namespace std;
class memManger
{

public:
	memManger()
	{
	}
	int systemAlloc(vector<node>& list,int times,int Plist);
    int myAlloc(vector<node>& list,int times,int Plist);
    int limited(vector<node>& list,int times,int Plist,int limit);

private:
	
};
#endif
