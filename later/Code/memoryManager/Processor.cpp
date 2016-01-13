#include "Processor.h"
#include "Memory_manager.h"
using namespace std;

int Processor::insert(int list,int ID, int mem, unsigned long long cycle)//helper
{
    if(list==1)
    {
    return P1->Linsert(ID,mem,cycle);
    }
    
    else if(list==2)
    {
    return P2->Linsert(ID,mem,cycle);   
    }
    
    else if(list==6)
    {
     return P6->Linsert(ID,mem,cycle);   
    }
}

int Processor::Turn(int list)//helper
{
     if(list==1)
    {
      return P1->Lturn();
    }
    
}

int Processor::getWait(int opt,node** start)
{
return P6->LgetWait(opt,start);
}

int Processor::Update(int list,int slice,int size,block *start,node **times,node**top)//helper
{
	resu* outcome=new resu;
	double mtimeStart=0,mtimeEnd=0;
     if(list==1)
    {
		P1->Lupdate(slice,start,*times,&outcome);
    }
	 if(outcome->state>-1)
	 {
		 setTime(1,outcome->ID,outcome->speed,(times));
	   
		mtimeStart = Time.start();
		my.alloc(start,getWait(1,top),getWait(2,top),size,getWait(3,top));
		mtimeEnd = Time.end(mtimeStart);
		
		setTime(0,getWait(1,top),mtimeEnd,top);
		(*top)->state=0;
		if(((*top)->next->next)!=NULL)
		{*top=((*top)->next->next);}
	 }
  return 1;
}

 int Processor::getTimeSize(node**top)
 {
	return P1->lgetTimeSize(top);
 }

node* Processor::getHead()
{
	return P6->lgetHead();
	  
}

void Processor::setTime(int pick,int id, double time,node **top)
{
	P1->lsetTime(pick,id,time,top);

}

double Processor::getTime(int pick, int id,node *top)
{
	return P1->lgetTime(pick,id,top);
}

void Processor::print(int list)//helper
{
     if(list==1)
    {
    cout<<"P1"<<endl<<endl;  
    P1->Lprint();
    }
    
    else if(list==2)
    {
    cout<<"P2"<<endl<<endl;    
     P2->Lprint();   
    }
     else if(list==6)
    {
    cout<<"P5"<<endl<<endl;
     P6->Lprint();   
    }
    else if(list ==0)
    {        
        cout<<"P1"<<endl;
        P1->Lprint();
        cout<<"P2"<<endl;
        P2->Lprint();
        
        
        cout<<"Total number of cycles on P1:"<<endl<<Size(1)<<endl;
        cout<<"Total number of cycles on P2:"<<endl<<Size(2)<<endl;
        
    }
    
    else if(list==-1)
    {
        cout<<"printing"<<endl;
        cout<<"Total number of cycles on P1:"<<endl<<Size(1)<<endl;
        cout<<"Total number of cycles on P2:"<<endl<<Size(2)<<endl;
        
    }
}

int Processor::save(int list,int schedule,int times)//helper
{
     if(list==1)
    {
    P1->Lsave(schedule,0,times);
	return 1;
    }
    
    else if(list==2)
    {
     P2->Lsave(schedule,1,times);   
	 return 1;
    }
    
    else if(list==0)
    {
        stringstream num;
        num<<times;
        string Num = num.str();
        string Fname;
              if(schedule==0)
              {
                  Fname="Identical"+Num+".txt";
              }
              else if(schedule==1)
              {
                  Fname="MemoryBased"+Num+".txt";
              }
              else if(schedule==2)
              {
                  Fname="SpeedBased"+Num+".txt";
              }
              else
              {
                  Fname="RealTime"+Num+".txt";
              }
        
      ofstream save(Fname.c_str(),ios::trunc);
      if (save.is_open()) 
        {
        unsigned long long mean1=Mean(1);
        unsigned long long mean2=Mean(2);
        unsigned long long mean3=Mean(3);
        unsigned long long mean4=Mean(4);
        unsigned long long mean5=Mean(5);
        
        save<<"Mean of P1: "<<mean1<<endl;
        save<<"Mean of P2: "<<mean2<<endl;
        
        
        /*save<<"Std. Div of P1: "<<Div(1,mean1)<<endl;
        save<<"Std. Div of P2: "<<Div(2,mean2)<<endl;
        save<<"Std. Div of P3: "<<Div(3,mean3)<<endl;
        save<<"Std. Div of P4: "<<Div(4,mean4)<<endl;
        save<<"Std. Div of P5: "<<Div(5,mean5)<<endl<<endl;
        */
        save<<"Total number of cycles on P1:"<<endl<<Size(1)<<endl;
        save<<"Total number of cycles on P2:"<<endl<<Size(2)<<endl;
      
        save.close();
        }
        else
        {
            cout<<"error opening file"<<endl;
        }
        P1->Lsave(schedule,0,times);
        P2->Lsave(schedule,1,times);
       return 1;
    }
}
void Processor::deleteAll()
{
    
    P1->Ldelete();
    P2->Ldelete();
    P6->Ldelete();
}
unsigned long long Processor::Mean(int list)
{
  if(list==1)
    {    
    return P1->Lmean();
    }
    
    else if(list==2)
    {
     return P2->Lmean();   
    }
   
    
}

long double Processor::Div(int list,unsigned long long mean)
{
  if(list==1)
    {    
    unsigned long long var;
    cout<<"here"<<endl;
    var=P1->Ldiv(mean);
    cout<<"var"<<var;
    return var;
    }
    
    else if(list==2)
    {
     return P2->Ldiv(mean);   
    }
    
}

unsigned long long Processor::Size(int list)
{
if(list==1)
    {    
    return P1->Lsize();
    }
    
    else if(list==2)
    {
     return P2->Lsize();   
    }
    
    else if(list ==0)
    {
        return P1->Lsize()+P2->Lsize()+P3->Lsize()+P4->Lsize()+P5->Lsize();
    }
}
