#include "Generator.h"
#include <sstream>
#include "Memory_manager.h"
using namespace std;
int main(int argc, char *argv[])
{
	Generator start;
	memManger my;
	srand(time(NULL));//seed time

 

	int print=1;
	int pid=1000;
	int limit=0;
	int cycl,Mem,times;
	stringstream value;
	if(argc!=2)
	{
	cout<<"You need to enter fill out all of the data to run"<<endl;
	}
	vector<node> s (25);

	for(int j=0;j<25;j++){
	s[j].ID = 0;
	s[j].cycle = 0;
	s[j].mallocSpeed = 0;
	s[j].remaining = 0;
	s[j].freeSpeed = 0;
	s[j].mem = 0;
	s[j].state = 0;
	}
	value<<argv[1];
	value>>limit;
	cout<<"limit is: "<<limit<<endl;
	start.Gen(s);
    my.systemAlloc(s,1,print);
	
	my.limited(s,1,print,limit);
	s.clear();
	s.resize(25);
	
	

	
	return 0;
}
