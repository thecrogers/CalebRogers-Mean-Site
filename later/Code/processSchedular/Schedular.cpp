//Caleb Rogers
//FEB, 19, 2014
#include "Schedular.h"
#include "Processor.h"
#include "Generator.h"

Processor Pro;

using namespace std;

    int Schedular::indentical(vector<node>& list,int times,int Plist)//all 5 CPU's same
    {
        int rev=99;
       sort(list,0);
       for(int i=0;i<100;i++)
        {
            
            Pro.insert((i%5)+1,list[i].ID,list[i].mem,list[i].cycle);
        }
       if(Plist==1)
       {
           Pro.print(0);//print all processors list
       }
       else{Pro.print(-1);}
       Pro.save(0,0,times);//save processors list to identical file.
       Pro.deleteAll();
      
     return 1;//return 1 on success, and 0 on failuer.
    }
    
    int Schedular::memory_base(vector<node>& list,int times,int Plist)//CPU's with differing memory sizes.
    {
        //devide process into 3 groups bassed on memory.
        //then ballance run time. 
        int small=0, middle=0,end=0,eFirst=0,mFirst=0,Omiddle=0,Oend=0;
        unsigned long long Csmall=0,Cmiddle=0,Cbig=0,Ctotal=0;
        double Psmall=0,Pmiddle=0,Pbig=0,Dsmall=0,Dmiddle=0,Dbig=0,Odiff=0,Omid=0,set=0,cap=0;
        double DIFF=.5;
        sort(list,1);
        for(int i=0;i<100;i++)
        {
            if(list[i].mem<=1048576&&list[i+1].mem>1048576&&mFirst==0)
            {
                middle=i;
                mFirst=1;
            }
            
            else if(list[i].mem<=2097152&&list[i+1].mem>2097152&&eFirst==0)
            {
                end=i;
                eFirst=1;
                break;
            }
        }
        cout<<"middle is at position: "<<middle<<endl;
        cout<<"end is at position:" <<end<<endl;
        
        
        for(int i=0;i<100;i++)//find cycle for each 3 groups.
        {
            if(i<middle)//less than 1gb
            {
                Csmall+=list[i].cycle;//number of cycles in samll
                cout<<"Csmall:"<<Csmall<<endl;
            }
            else if (i>middle&&i<end)//1gb-2gb
            {
                Cmiddle+=list[i].cycle;//number of cycles in middle;
            }
            else//over 2gb
            {
                Cbig+=list[i].cycle;//number of cycles in big
            }
        }
        
        Ctotal=Csmall+Cmiddle+Cbig;
        Psmall=Csmall/Ctotal;//get percent of total cycles on this cpu
        Pmiddle=Cmiddle/Ctotal;//get percent of total cycles on this cpu
        Pbig=Cbig/Ctotal;//get percent of total cycles on this cpu
        //check percintage of each group. ie is it close to 1/3
        //assuming processors are all the same speed. 
       
        Dsmall=Psmall-.4;
        Dmiddle=Pmiddle-.4;//get how far off from the evan distibution.
        Dbig=Pbig-.2;
        Omid=middle;
        Oend=end;
        Odiff=Dsmall+Dmiddle+Dbig;
        
        if((abs(Dsmall)>DIFF)||(abs(Dmiddle)>DIFF)||(abs(Dbig)>DIFF))//distribution is too far off.
        {
        while(set==0&&cap<10)
        {
            //anything middle down can be moved up but end and up cannot be moved down.
            
            if(Dsmall>Dmiddle&&Dsmall>Dbig)//ok to move process to middle and end. 
            {
                if(Dmiddle<Dbig)//move new process to middle;
                {
                    --middle;//move the middle stack back by one process
                    //repeat this x many times. 
                }
                else//move process to big.
                {
                    //save end-1 to temp
                    list[100].ID=list[end-1].ID;
                    list[100].mem=list[end-1].mem;
                    list[100].cycle=list[end-1].cycle;
                    //set end-1 to first item in small list;
                    list[end-1].ID=list[0].ID;
                    list[end-1].mem=list[0].mem;
                    list[end-1].cycle=list[0].cycle;
                    //decrese end by one to now include moved item in last big group
                    --end;
                    //set moved item to mid item
                    list[0].ID=list[middle].ID;
                    list[0].mem=list[middle].mem;
                    list[0].cycle=list[middle].cycle;
                    //set mid itme to temp item.
                    list[middle].ID=list[100].ID;
                    list[middle].mem=list[100].mem;
                    list[middle].cycle=list[100].cycle;
                    //decrese mid range by one since one item was moved from behind mid.
                    --middle;
                }
            }
            if(Dsmall<Dmiddle&&Dmiddle>Dbig)//ok to move process from middle to big. 
            {
                --end;
            }
            
            for(int i=0;i<100;i++)//find cycle for each 3 groups.
            {
                if(i<middle)//less than 1gb
                {
                Csmall+=list[i].cycle;
                }
                else if (i>middle&&i<end)//1gb-2gb
                {
                Cmiddle+=list[i].cycle;
                }
                else//over 2gb
                {
                Cbig+=list[i].cycle;
                }
            }
            //retest ballance
            Psmall=Csmall/Ctotal;//get percent of total cycles on this cpu
            Pmiddle=Cmiddle/Ctotal;//get percent of total cycles on this cpu
            Pbig=Cbig/Ctotal;//get percent of total cycles on this cpu
            //check percintage of each group. ie is it close to 1/3
            //assuming processors are all the same speed. 
            Dsmall=Psmall-.4;
            Dmiddle=Pmiddle-.4;//get how far off from the evan distibution.
            Dbig=Pbig-.2;
        
        //check new order by original order.
        if(Odiff>(Dsmall+Dmiddle+Dbig))//new is better than old
        {
            Omid=middle;
            Oend=end;
            Odiff=Dsmall+Dmiddle+Dbig;
        }
        else//old is better
        {
            ++cap;
        }
        
        }
        
         if(((abs(Dsmall)<DIFF)&&(abs(Dmiddle)<DIFF))||((abs(Dbig)<DIFF)&&(abs(Dsmall)<DIFF))||((abs(Dbig)<DIFF)&&(abs(Dmiddle)<DIFF)))// statment to exit loop
            {
                set=1;
            }
        }
        
        
         for(int i=0;i<100;i++)//find cycle for each 3 groups.
            {
                if(i<middle)//less than 1gb
                {
                
                Pro.insert(((i%2)+1),list[i].ID,list[i].mem,list[i].cycle);
                }
                else if (i>middle&&i<end)//1gb-2gb
                {
                Pro.insert(((i%2)+3),list[i].ID,list[i].mem,list[i].cycle);
                }
                else//over 2gb
                {
                 Pro.insert(5,list[i].ID,list[i].mem,list[i].cycle);
                }
                //cout<<"insert: ID: "<<list[i].ID<<" mem: "<<list[i].mem<<" cycle: "<<list[i].cycle<<endl;
                
            }
           
             if(Plist==1)
            {
            Pro.print(0);//print all processors list
            }
            else{ cout<<"start print."<<endl;Pro.print(-1);}
            Pro.save(0,1,times);//save to memory based list.
             Pro.deleteAll();
        
     return 1;//return 1 on success, and 0 on failuer.   
    }
    
    int Schedular::cycle_base(vector<node>& list,int times,int Plist)//CPU's with differing cycle times.
    {
  

		//Processor Speeds
		float procSpeed1 = 1000.0; //Megahertz
              float procSpeed3 = 2000.0;
		float procSpeed5 = 4000.0;

		sort(list,0);
		//frequency = cycles/second;; seconds = cycles/frequency
		for(int i=99;i>=0;i--)
        {
			//Change the cycles to time; Milliseconds specifically
			if((i%5+1) == 5)
				list[i].cycle = (list[i].cycle/procSpeed5)*1000;
			else if((i%5+1) == 4 ||(i%5+1) == 3)
				list[i].cycle = (list[i].cycle/procSpeed3)*1000;
			else if((i%5+1) == 4 ||(i%5+1) == 3)
				list[i].cycle = (list[i].cycle/procSpeed1)*1000;

            Pro.insert((i%5)+1,list[i].ID,list[i].mem,list[i].cycle);
        }
        
        
        if(Plist==1)
        {
        Pro.print(0);//print all processor list
        }
        else{Pro.print(-1);}
        Pro.save(0,2,times);//save to cyclebased file
        Pro.deleteAll();
      return 1;//return 1 on success, and 0 on failuer.  
    }
    
    int Schedular::real_time(vector<node>& list,int times,int Plist)//schedualing as process come in. 
    {
        Generator process;
        unsigned long long lowTime;
        int slice =50;
        int index=0, open=1;
        unsigned long over;
       //  lowTime=Pro.Turn(1);
         int place,test=1;
         cout<<"enter while"<<endl;
       while(test)//loop until complete.
        {
            if(index<99)
           {
           open=process.pGen();
           }
            //cout<<"nmber of new Processes: "<<open<<endl;
           if(open>0)
           {
               
               //cout<<"new process"<<endl;
               for(int x=0; x<open;x++)
               {   if(index<99)
                    {
                    ++index;
                   addProcess(index,slice,2,list);
                    }
               }
               
           }
          if(index>15){Pro.print(6);}
          // cout<<"running updates 1"<<endl;
          over= Pro.Update(1,slice);
          cout<<"over: "<<over<<endl;
          if(over>0)//time slice left over and process waiting. 
          {
               cout<<"process complete"<<endl;
           addProcess(index,over,1,list);   
          }
           
           //cout<<"running updates 2"<<endl;
            over= Pro.Update(2,slice);
              cout<<"over: "<<over<<endl;
          if(over>0)//time slice left over and process waiting. 
          {
               cout<<"process complete"<<endl;
           addProcess(index,over,1,list);   
          }
          
          //cout<<"running updates 3"<<endl;
           over= Pro.Update(3,slice);
             cout<<"over: "<<over<<endl;
          if(over>0)//time slice left over and process waiting. 
          {
               cout<<"process complete"<<endl;
           addProcess(index,over,1,list);   
          }
          
         // cout<<"running updates 4"<<endl;
           over= Pro.Update(4,slice);
             cout<<"over: "<<over<<endl;
          if(over>0)//time slice left over and process waiting. 
          {
               cout<<"process complete"<<endl;
           addProcess(index,over,1,list);   
          }
          
         //cout<<"running updates 5"<<endl;
           over= Pro.Update(5,slice);
             cout<<"over: "<<over<<endl;
          if(over>0)//time slice left over and process waiting. 
          {
               cout<<"process complete"<<endl;
           addProcess(index,over,1,list);   
          }
          //cout<<"index is "<<index<<endl;
         /* for(int x=1;x<6;x++)
            {
            if(Pro.State(x)==0)//process is free. 
            {
                addProcess(index,slice,1,list);
            }
            
            } */   
          if(Pro.Turn(1)>=0&&Pro.Turn(2)>=0&&Pro.Turn(3)&&Pro.Turn(4)>=0&&Pro.Turn(5)>=0&&index==99)
          {
             break;
          }
        }
        
       
        if(Plist==1)
        {
        Pro.print(0);//print all processors list
        }
        else{Pro.print(-1);}
        Pro.save(0,3,times);//save to realtime file.
        Pro.deleteAll();
       return 1;//return 1 on success, and 0 on failuer. 
    }
    
    int Schedular::addProcess(int index,int slice,int special,vector<node>& list)//
    {
        int count=1;
        cout<<"add process"<<endl;
         if(index<=5)//ie just starting. 
            {
                cout<<"initial"<<endl;
                 Pro.insert((index%5)+1,list[index].ID,list[index].mem,list[index].cycle);
            }
           
            else if(special==1)//left over cpu time.
           {
               cout<<"left over cpu time"<<endl;
                for(int x=0;x<5;x++)//loop through processors;
                {
                    if(Pro.Turn(x)==0)
                    {
                        cout<<"found CPU"<<endl;
                    Pro.insert(x,Pro.getWait(1),Pro.getWait(2),Pro.getWait(3));
                    Pro.getWait(0);
                     x=5;
                     break;
                    }
                }
           }
           
           else if(Pro.getWait(1)!=0&&special==2)//processes already waiting.
           {
               cout<<"process is already waiting"<<endl;
              Pro.insert(6,list[index].ID,list[index].mem,list[index].cycle); //inset new process to wait.
              
              
            for(int x=0;x<5;x++)//loop through processors;
            {
              if(Pro.Turn(x)==0)
                {
                 Pro.insert(x,Pro.getWait(1),Pro.getWait(2),Pro.getWait(3));
                 Pro.getWait(0);
                 x=5;
                 break;
                }
               
            }
           }
          
            else if(special==2)
            {
            cout<<"normal exicution"<<endl;
            for(int x=0;x<5;x++)//loop through processors;
            {
              if(Pro.Turn(x)==0)
                {
                 Pro.insert(x,list[index].ID,list[index].mem,list[index].cycle);
                 x=5;
                 count=0;
                 break;
                }
               
            }
            
          if(count==0)//ie no open process
          {
              Pro.insert(6,list[index].ID,list[index].mem,list[index].cycle); //inset new process to wait.  
          }
          }
        return 0;
    }
    
    int Schedular::sort(vector<node>& list, int mode)//sort lest to greatest based on mode parameter
    {
        if(mode==0)//sort by cycles
        {
            int low=0;
            int tmp,Tmem,Tid;
            unsigned long long Tcycle;
        for(int i=0;i<99;i++)
        {
            for(int x=0;x<99-i;x++)
            {
                if(list[x].cycle>list[x+1].cycle)
                {
                    Tid=list[x].ID;
                    Tmem=list[x].mem;
                    Tcycle=list[x].cycle;
                  //cout<<"cycle on tmp: "<<Tcycle<<endl;
                    
                    list[x].ID=list[x+1].ID;
                    list[x].mem=list[x+1].mem;
                    list[x].cycle=list[x+1].cycle;
                  //cout<<"cycle on new X: "<<list[x].cycle<<endl;
                   
                    list[x+1].ID=Tid;
                    list[x+1].mem=Tmem;
                    list[x+1].cycle=Tcycle;
                    //cout<<"cycle on new x+1: "<<list[x+1].cycle<<endl;
                }
            }
        }
        }
        else if(mode==1)//sort by memory size
        {
           int low=0;
            int tmp,Tmem,Tid;
            unsigned long long Tcycle;
        for(int i=0;i<99;i++)
        {
            for(int x=0;x<99-i;x++)
            {
                if(list[x].mem>list[x+1].mem)
                {
                    Tid=list[x].ID;
                    Tmem=list[x].mem;
                    Tcycle=list[x].cycle;
                    //set item i to new low item. 
                    list[x].ID=list[x+1].ID;
                    list[x].mem=list[x+1].mem;
                    list[x].cycle=list[x+1].cycle;
                    //set low item to temp;
                    list[x+1].ID=Tid;
                    list[x+1].mem=Tmem;
                    list[x+1].cycle=Tcycle;
                    //i++ and x is not one greater to not allowed to check already sorted items. 
                }
            }
            //store item being replaced into temp
            
        } 
        }
        return 0;
    }
    
    