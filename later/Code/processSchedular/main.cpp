#include "Generator.h"
#include "Schedular.h"
#include <sstream>
using namespace std;
int main(int argc, char* argv[])
{
	Generator start;
	srand(time(NULL));//seed time
    Schedular run;
	int choice=0;
	int print=-1;
	int pid=1000;
	int cycl,Mem,times;
	stringstream value;
	vector<node> s (101);
	cout<<"Welcome to the process schedular."<<endl<<endl;
	
	

	if(argc!=2)
	{
	cout<<"You need to enter fill out all of the data to run"<<endl;
	}
	
	value<<argv[1];
	value>>choice;
	cout<<"choice is :"<<choice<<endl;

	if(choice==1)//Run identical process schedular 
	{
	start.Gen(s);
	run.indentical(s,1,-1);
	}

	else if(choice==2)//run test on varying memory sizes
	{ 
	start.Gen(s);
	run.memory_base(s,1,-1);
	}

	else if(choice==3)//run test on process schedular for varying clock speeds. 
    {
	 start.Gen(s); 
	 run.cycle_base(s,1,-1);
	 
	 }

	else if(choice==4)//run test on process schedular varying arrival times. 
    {   
	 start.Gen(s);
	 run.real_time(s,1,-1);
     }

	else if(choice==5)//print all process
        {
	        cout<<"exiting program...."<<endl<<endl;
        }	

	return 0;
}
