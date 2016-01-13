#include "Processor.h"
using namespace std;


int Processor::insert(int list,int ID, int mem, unsigned long long cycle)//helper
{
    if(list==1)
    {
    P1->Linsert(ID,mem,cycle);
    }
    
    else if(list==2)
    {
     P2->Linsert(ID,mem,cycle);   
    }
    
    else if(list==3)
    {
     P3->Linsert(ID,mem,cycle);  
    }
    
    else if(list==4)
    {
     P4->Linsert(ID,mem,cycle); 
    }
    
    else if(list==5)
    {
     P5->Linsert(ID,mem,cycle);   
    }
    
    else if(list==6)
    {
     P6->Linsert(ID,mem,cycle);   
    }
	return 0;
}

unsigned long long Processor::Turn(int list)//helper
{
     if(list==1)
    {
   return P1->Lturn();
    }
    
    else if(list==2)
    {
    
    return P2->Lturn();   
    }
    
    else if(list==3)
    {
  
   return  P3->Lturn();  
    }
    
    else if(list==4)
    {
  
   return  P4->Lturn(); 
    }
    
    else if(list==5)
    {
   return  P5->Lturn();   
    }
}

unsigned long long Processor::getWait(int opt)
{
return P6->LgetWait(opt);
}

int Processor::Update(int list,int slice)//helper
{
     if(list==1)
    {
   return P1->Lupdate(slice);
    }
    
    else if(list==2)
    {
    return  P2->Lupdate(slice);   
    }
    
    else if(list==3)
    {
    return  P3->Lupdate(slice);  
    }
    
    else if(list==4)
    {
    return  P4->Lupdate(slice); 
    }
    
    else if(list==5)
    {
    return  P5->Lupdate(slice);   
    }
    else if(list==6)
    {
    return  P6->Lupdate(slice);   
    }
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
    
    else if(list==3)
    {
    cout<<"P3"<<endl<<endl;
     P3->Lprint();  
    }
    
    else if(list==4)
    {
    cout<<"P4"<<endl<<endl;
     P4->Lprint(); 
    }
    
    else if(list==5)
    {
    cout<<"P5"<<endl<<endl;
     P5->Lprint();   
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
        cout<<"P3"<<endl;
        P3->Lprint();
        cout<<"P4"<<endl;
        P4->Lprint();
        cout<<"P5"<<endl;
        P5->Lprint();
        
        cout<<"Total number of cycles on P1:"<<endl<<Size(1)<<endl;
        cout<<"Total number of cycles on P2:"<<endl<<Size(2)<<endl;
        cout<<"Total number of cycles on P3:"<<endl<<Size(3)<<endl;
        cout<<"Total number of cycles on P4:"<<endl<<Size(4)<<endl;
        cout<<"Total number of cycles on P5:"<<endl<<Size(5)<<endl;
    }
    
    else if(list==-1)
    {
    	unsigned long long mean1=Mean(1);
        unsigned long long mean2=Mean(2);
        unsigned long long mean3=Mean(3);
        unsigned long long mean4=Mean(4);
        unsigned long long mean5=Mean(5);
        //cout<<"printing"<<endl;
        cout<<"Mean of P1: "<<mean1<<endl;
        cout<<"Mean of P2: "<<mean2<<endl;
        cout<<"Mean of P3: "<<mean3<<endl;
        cout<<"Mean of P4: "<<mean4<<endl;
        cout<<"Mean of P5: "<<mean5<<endl<<endl;
        cout<<"Total number of cycles on P1:"<<endl<<Size(1)<<endl;
        cout<<"Total number of cycles on P2:"<<endl<<Size(2)<<endl;
        cout<<"Total number of cycles on P3:"<<endl<<Size(3)<<endl;
        cout<<"Total number of cycles on P4:"<<endl<<Size(4)<<endl;
        cout<<"Total number of cycles on P5:"<<endl<<Size(5)<<endl;
    }
}

int Processor::save(int list,int schedule,int times)//helper
{
     if(list==1)
    {
    P1->Lsave(schedule,0,times);
    }
    
    else if(list==2)
    {
     P2->Lsave(schedule,1,times);   
    }
    
    else if(list==3)
    {
     P3->Lsave(schedule,2,times);  
    }
    
    else if(list==4)
    {
     P4->Lsave(schedule,3,times); 
    }
    
    else if(list==5)
    {
     P5->Lsave(schedule,4,times);   
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
        save<<"Mean of P3: "<<mean3<<endl;
        save<<"Mean of P4: "<<mean4<<endl;
        save<<"Mean of P5: "<<mean5<<endl<<endl;
        
        /*save<<"Std. Div of P1: "<<Div(1,mean1)<<endl;
        save<<"Std. Div of P2: "<<Div(2,mean2)<<endl;
        save<<"Std. Div of P3: "<<Div(3,mean3)<<endl;
        save<<"Std. Div of P4: "<<Div(4,mean4)<<endl;
        save<<"Std. Div of P5: "<<Div(5,mean5)<<endl<<endl;
        */
        save<<"Total number of cycles on P1:"<<endl<<Size(1)<<endl;
        save<<"Total number of cycles on P2:"<<endl<<Size(2)<<endl;
        save<<"Total number of cycles on P3:"<<endl<<Size(3)<<endl;
        save<<"Total number of cycles on P4:"<<endl<<Size(4)<<endl;
        save<<"Total number of cycles on P5:"<<endl<<Size(5)<<endl<<endl;
        save.close();
        }
        else
        {
            cout<<"error opening file"<<endl;
        }
        P1->Lsave(schedule,0,times);
        P2->Lsave(schedule,1,times);
        P3->Lsave(schedule,2,times);
        P4->Lsave(schedule,3,times);
        P5->Lsave(schedule,4,times);
    }
	return 0;
}
void Processor::deleteAll()
{
    
    P1->Ldelete();
    P2->Ldelete();
    P3->Ldelete();
    P4->Ldelete();
    P5->Ldelete();
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
    
    else if(list==3)
    {
     return P3->Lmean();  
    }
    
    else if(list==4)
    {
     return P4->Lmean(); 
    }
    
    else if(list==5)
    {
     return P5->Lmean();   
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
    
    else if(list==3)
    {
     return P3->Ldiv(mean);  
    }
    
    else if(list==4)
    {
     return P4->Ldiv(mean); 
    }
    
    else if(list==5)
    {
     return P5->Ldiv(mean);   
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
    
    else if(list==3)
    {
     return P3->Lsize();  
    }
    
    else if(list==4)
    {
     return P4->Lsize(); 
    }
    
    else if(list==5)
    {
     return P5->Lsize();   
    }
    
    else if(list ==0)
    {
        return P1->Lsize()+P2->Lsize()+P3->Lsize()+P4->Lsize()+P5->Lsize();
    }
}
