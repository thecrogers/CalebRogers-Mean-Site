#include "Processor.h"
#include "Generator.h"
#include "Memory_manager.h"
#include "memTree.h"
#include "timer.h"

using namespace std;
Processor Pro;
Timer Time;
memTree My;
int memManger::systemAlloc(vector<node>& list,int times,int Plist)
{
    unsigned long long totMem = 0; //Total Memory Variable
    double mtimeStart, mtimeEnd; //Malloc Time Variables
    double ftimeStart, ftimeEnd; //Free time Variables
    double totSpeed = 0.0f; //Total Speed Variable
    void * buffer; //Void buffer in which to Malloc and Free
    int toalloc = 0; //Placeholder to hold Mem amount to Malloc

    //For every Process
    for(int i = 0; i < 25; i++){
        
    toalloc = list[i].mem; //Store size to Malloc

	mtimeStart = Time.start(); //Start time
    buffer = (void*) malloc(toalloc); //System Alloc memory
	mtimeEnd = Time.end(mtimeStart); // Total Run Time

	list[i].mallocSpeed = mtimeEnd; //Store the Total Run Time to MALLOC this Memory Chunk
       
	ftimeStart = Time.start(); //Start time
	free(buffer);//System Free memory
	ftimeEnd = Time.end(ftimeStart); //Total Run Time
	
	list[i].freeSpeed = ftimeEnd; //Store the Total Run Time to FREE memory Chunk	
		
	totMem += list[i].mem;
	totSpeed += (list[i].mallocSpeed + list[i].freeSpeed);

    //Reset our Floats...bad behavior if we don't
	mtimeStart = 0;
	mtimeEnd = 0;
	ftimeStart =0;
	ftimeEnd = 0;
    }
    
    //Print out the raw data!
    //Going to copy/paste into Excel and delimit by :
    
    if(Plist == 1){
    cout << "Results for Simulation System Alloc " << times << endl;
    cout << "Total Memory Allocated and Freed: " << totMem <<endl;
    cout << "Total Simulation Time: " << totSpeed << endl;
    for(int i = 0; i < 25; i++){
        cout << " Memory Chunk: " << list[i].mem << " : ";
        cout << " Time to Malloc: " << list[i].mallocSpeed << " : ";
        cout << " Time to Free: " << list[i].freeSpeed << " : ";
        cout << endl;
    }
    }
    else if(Plist == 0){
        stringstream num;
        num<<times;
        string Num = num.str();
        string Fname;
        Fname="System_Malloc_Free "+Num+".txt";
        ofstream save(Fname.c_str(),ios::trunc);
            save << "Results for Simulation " << times << endl;
            save << "Total Memory Allocated and Freed: " << totMem <<endl;
            save << "Total Simulation Time: " << totSpeed << endl;
            for(int i = 0; i < 25; i++){
                save << " Memory Chunk: " << list[i].mem << " : ";
                save << " Time to Malloc: " << list[i].mallocSpeed << " : ";
                save << " Time to Free: " << list[i].freeSpeed << " : ";
                save << endl;
            }
        save.close();
    }
	
	//Reset more Floats
    totSpeed = 0;
    totMem = 0;    
    
    return 1;
}

int memManger::myAlloc(vector<node>& list,int times,int Plist)
{
    double mtimeStart, mtimeEnd; //Malloc Time Variables
    double ftimeStart, ftimeEnd; //Free time Variables
    double totSpeed = 0.0f; //Total Speed Variable
    block *object = new block;
	object=(My.root);
	unsigned long long totMem = 0;
    int size=0,ID=0,count=0, complete=1,success=-1,slice=50;
   node *top=new node;
   node* tTime;
	node *gHead;
	gHead=new node;
	//top=(Pro.getHead());
   
    //int *memory =malloc(10485760);//allocate size of memroy;
    
    //Tstart=Time.start();//starts timer
    while(complete==1)
    {
        if(count<25)//will only add 50 new process 
        {
			
            Pro.insert(1,list[count].ID,list[count].mem,list[count].cycle);
           
			mtimeStart = Time.start(); //Start time
            success=My.allocc(&gHead,list[count].ID,list[count].mem,10485760,list[count].cycle);//allocate from memory of size for process ID; 
            mtimeEnd = Time.end(mtimeStart); // Total Run Time
           cout<<"memalloc time:" <<mtimeEnd<<endl;
			top=gHead;
            
			if(success==1)
            {Pro.setTime(0,list[count].ID,mtimeEnd,&tTime);}
            else
            {Pro.setTime(0,list[count].ID,mtimeEnd,&tTime);}
           
			totMem+=list[count].mem;
         //   cout<<endl<<endl<<"current list"<<endl;
			object=(My.root);
			//My.print(object);
            ++count;

        }

        Pro.Update(1,slice,10485760,object,&tTime,&top);//update all process remaining cycles;
        

        if(count>=25)//speed up exicution
        {
        	//cout<<endl<<endl<<"current list"<<endl;
        	object=(My.root);
        	//My.print(object);
            slice =50000;
        }
        
        if(Pro.Turn(1)==0&&count>=25)
        {
            complete=0;
        }
        
        
    }
   
for(int i = 0; i < 25; i++)
	 {
		 totSpeed +=(Pro.getTime(0,list[i].ID,tTime)+ 
Pro.getTime(1,list[i].ID,tTime));
	 }

    if(Plist == 1){
    cout << "Results for Simulation " << times << endl;
    cout << "Total Memory Allocated and Freed: " << totMem <<endl;
    cout << "Total Simulation Time: " << totSpeed << endl;
    for(int i = 0; i < 25; i++){
        cout << " Memory Chunk: " << list[i].mem << " : ";
        cout << " Time to Malloc: " << Pro.getTime(0,list[i].ID,tTime) << " : ";
        cout << " Time to Free: " << Pro.getTime(1,list[i].ID,tTime) << " : ";
        cout << endl;
    }
    }
    else if(Plist == 0){
        stringstream num;
        num<<times;
        string Num = num.str();
        string Fname;
        Fname="My_Malloc_Free "+Num+".txt";
        ofstream save(Fname.c_str(),ios::trunc);
            save << "Results for Simulation " << times << endl;
            save << "Total Memory Allocated and Freed: " << totMem <<endl;
            save << "Total Simulation Time: " << totSpeed << endl;
            for(int i = 0; i < 50; i++){
                save << " Memory Chunk: " << list[i].mem << " : ";
                save << " Time to Malloc: " << Pro.getTime(0,list[i].ID,tTime) << " : ";
                save << " Time to Free: " << Pro.getTime(1,list[i].ID,tTime) << " : ";
                save << endl;
            }
        save.close();
    }
	
	
    Pro.deleteAll();
    return 1;
}

int memManger::limited(vector<node>& list,int times,int Plist,int limit)
{
    double mtimeStart, mtimeEnd; //Malloc Time Variables
    double ftimeStart, ftimeEnd; //Free time Variables
    double totSpeed = 0.0f; //Total Speed Variable
     block *object = new block;
	object=(My.root);
	unsigned long long totMem=0;
    int size=0,ID=0,count=0, complete=1,slice=50,success=-1,len;
   node *top=new node;
   node* tTime;
	node *gHead;
	gHead=new node;
	//top=(Pro.getHead());
   
    //int *memory =malloc(10485760);//allocate size of memroy;
    
    //Tstart=Time.start();//starts timer
    while(complete==1)
    {
        if(count<25)//will only add 50 new process 
        {
			
            Pro.insert(1,list[count].ID,list[count].mem,list[count].cycle);
            mtimeStart = Time.start(); //Start time
            mtimeStart = Time.start(); //Start time
            success=My.allocc(&gHead,list[count].ID,list[count].mem,10485760,list[count].cycle);//allocate from memory of size for process ID;
            mtimeEnd = Time.end(mtimeStart); // Total Run Time
            top=gHead;
            if(success==1)
            {Pro.setTime(0,list[count].ID,mtimeEnd,&tTime);}
            else
            {Pro.setTime(0,list[count].ID,mtimeEnd,&tTime);}
            totMem+=list[count].mem;
          
			object=(My.root);
			
            ++count;
        }
		top=gHead;
        Pro.Update(1,slice,limit,object,&tTime,&top);//update all process remaining cycles;
        
         if(count>=25)//speed up exicution
        {
            slice =5000;
        }
        
        if(Pro.Turn(1)==0&&count>=25)
        {
            complete=0;
        }

  }

for(int i = 0; i < 25; i++)
	 {
		 totSpeed +=(Pro.getTime(0,list[i].ID,tTime)+Pro.getTime(1,list[i].ID,tTime));
	 }
    if(Plist == 1)
	{
    	cout <<endl<<endl<<endl<< "Results for Simulation My Malloc " << times << endl;
    	cout << "Total Memory Allocated and Freed: " << totMem <<endl;
    	cout << "Total Simulation Time: " << totSpeed << endl;
    		for(int i = 0; i < 25; i++)
		{
       		cout << " Memory Chunk: " << list[i].mem << " : ";
        	cout << " Time to Malloc: " << Pro.getTime(0,list[i].ID,tTime)<< " : ";
       		cout << " Time to Free: " << Pro.getTime(1,list[i].ID,tTime) << " : ";
        	cout << endl;
    		}
	}
	else if(Plist == 0)
	{
        stringstream num;
        num<<times;
        string Num = num.str();
        string Fname;
        Fname="My_Malloc_Free_Limited "+Num+".txt";
        ofstream save(Fname.c_str(),ios::trunc);
            save << "Results for Simulation " << times << endl;
            save << "Total Memory Allocated and Freed: " << totMem<<endl;
            save << "Total Simulation Time: " << totSpeed << endl;
            for(int i = 0; i < 25; i++)
            {
                save << " Memory Chunk: " << list[i].mem << " : ";
                save << " Time to Malloc: " <<Pro.getTime(0,list[i].ID,tTime) << " : ";
                save << " Time to Free: " << Pro.getTime(1,list[i].ID,tTime) << " : ";
                save << endl;
            }
        save.close();
	}

    Pro.deleteAll();
return 1;
}
