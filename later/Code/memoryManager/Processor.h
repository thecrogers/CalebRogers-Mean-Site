#ifndef PROCESSORHEADERFILE
#include<iostream>
#include<fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include "node.h"
#include "memTree.h"
#include "timer.h"
#define PROCESSORHEADERFILE
using namespace std;
class Processor
{

public:

  memTree my;
  Timer Time;
  //Processor *p;
   Processor()
   {
	   //p=new Processor;
       P1=new List();//Process 1
       P2=new List();//tree
       P6=new List();//waiting list
   }
    ~Processor()
    {
        
        
    }
    int insert(int,int,int,unsigned long long);//first int is the list to enter into.
    void print(int);//list to print from
    int save(int,int,int);//save all
    unsigned long long Size(int);
    unsigned long long Mean(int);
    int Turn(int);
    node* getHead();
    void setTime(int,int,double,node**);
    double getTime(int,int,node*);
    void Free(char**,int,int);
    int getWait(int,node**);
    int Update(int,int,int,block*,node**,node**);
    long double Div(int,unsigned long long);
	int getTimeSize(node**);
    void deleteAll();

class List
        {
          public:
          memTree my;
          Timer Time;

          node* head;
          node* last;
          List()
          {

              head=NULL;
              last=NULL;
          }
          
          int Linsert(int ID,int mem,unsigned long long cycle)//insert into the list.
          {
              //cout<<"insert: ID: "<<ID<<" mem: "<<mem<<" cycle:"<<cycle<<endl;
              if(head==NULL)
              {
                head=new node;
                head->ID=ID;
                head->mem=mem;
                head->state=1;
                head->cycle=cycle;
				head->remaining=cycle;
                head->next=NULL;
                head->prev=NULL;
                last=head;
				return 1;
              }
              else
              {
                  node* tmp;
                  node* curr;
                  curr=new node;
                  curr=last;
                  tmp=new node;
                  tmp->ID=ID;
                  tmp->mem=mem;
				  tmp->remaining=cycle;
                  tmp->state=1;
                  tmp->cycle=cycle;
                  curr->next=tmp;
                  tmp->next=NULL;
                  tmp->prev=curr;
                  last=tmp;
				  return 1;
              }
              
          }
          
		 node* lgetHead()
		 {
			 return head;
		 }
		 
		 int lgetTimeSize(node**top)
		 {
			 int count=0;
			 node* tmp=new node;
			 tmp=*top;
			 while(1)
			 {
				 if(tmp->next!=NULL)
				 {
					 ++count;
					 tmp=tmp->next;
				 }
				 else
				 {
					 break;
				 }
			 }
			 if(tmp!=NULL)
			 {
				 count=1;
			 }
			 return count;
			 
		 }
		 void lsetTime(int pick,int id,double time,node**top)
		 {
			 int found=0;

			 while(found==0)
			 {
				 if(pick==0)
				 {
					
					      node* tmp;
					      node* curr;
					      curr=new node;
					      curr=*top;
					      tmp=new node;

					      tmp->ID=id;
					      tmp->mallocSpeed=time;
					      tmp->next=*top;
					      *top=tmp;
						  found=1;

				 }
				 else if(pick==1)
				 {
					 node* tmp=new node;
					 
					 tmp=*top;
					 while(tmp->ID!=id)
					   {
					 	tmp=tmp->next;
					   }
					 if(tmp->ID=id)
					 {
					 tmp->freeSpeed=time;
					  found=1;
					 }
					 else
					 {
						 break;
					 }
				 }

				 }

		 }

		 double lgetTime(int pick,int id,node*top)
		 {
			 node* tmp=new node;
			 			 tmp=top;
			 			 int found=0;

			 			 while(found==0)
			 			 {
			 				 if(tmp->ID==id&&pick==0)
			 				 {
			 					 found=1;
			 					return tmp->mallocSpeed;

			 				 }
			 				 else if(tmp->ID==id&&pick==1)
			 				 {
			 					 found=1;
			 					 return tmp->freeSpeed;

			 				 }
			 				 tmp=tmp->next;
			 			 }
		 }

          int LgetWait(int opt,node **start)
          {
              node* tmp, *use;
              tmp=new node;
              use=new node;
              tmp = *start;
              int value=0;
              if(tmp!=NULL)
              {
              if(opt==1&&tmp->state==1)//ie process is running.
              {
                 
               return tmp->ID;
              }
              else if(opt==2&&tmp->state==1)
              {
                  
                  return tmp->mem;
              }
              else if(opt==3&&tmp->state==1)
              {
                 
                  value=tmp->cycle;
                  return value;
              }
              
               else if(opt==0)
              {
                  if(tmp->next==NULL)
                  {
                      start=NULL;
                      delete tmp;
                  }
                  else
                  {
                  use=tmp->next;
                  //*start=use;
                  //delete tmp;
                  }
                  return 0;
              }
             else
             {
                 return 0;
             }
          }
          }
          
          int Lturn()
          {
              node* tmp;
              tmp=new node;
              tmp = head;
              int count=0;
              
              while(tmp->next!=NULL)
              {
                  if(tmp->state==1)//still running. 
                  {
                      count++;
                  }
                  tmp=tmp->next;
              }
              return count;
          }
          
           int Lupdate(int slice,block *start,node *top,resu** res)
          {
              node* tmp;
              tmp=new node;
              tmp = head;
              int count=0;
              double mtimeStart, mtimeEnd; //Malloc Time Variables
              double ftimeStart, ftimeEnd;
              if(tmp->next!=NULL)
			  {
              while(tmp->next!=NULL)
              {
				  if(tmp==NULL||tmp->state==0)//process does not exist or process is not running.
                {
                  
                }
                else
                {
                    tmp->remaining-=slice;
                    if(tmp->remaining<=0)
                    {
                        ftimeStart = Time.start(); //Start time
                        my.free(tmp->ID,start);
						ftimeEnd = Time.end(ftimeStart);

						//setTime(1,tmp->ID,mtimeEnd,top);
                        tmp->state=0;
						
						(*res)->state=1;
						(*res)->speed=ftimeEnd;
						(*res)->ID=tmp->ID;
						return 1;
                    }
                   
                }
                 tmp=tmp->next;
                ++count;
              }
			  }
			  else
			  {
				tmp->remaining-=slice;
			  }
			  (*res)->state=-1;
			  return 1;
              
             /* if(last==NULL||tmp->state==0)
              {
                  return 1;
              }
              else if(tmp->turnTime==NULL)
              {
                  tmp->turnTime=slice;
                  return 0;
              }
             
              else
              {
              tmp->turnTime+=slice;
              //cout<<"turn time: "<<tmp->turnTime<<endl;
              if(tmp->turnTime>=tmp->cycle)
              {
                  tmp->state=0;
                  tmp->prev;
                  cout<<tmp->turnTime-tmp->cycle<<endl;
                  return tmp->turnTime-tmp->cycle+1;
              }
              
              else{return 0;}
              }*/
          }
          
          
          unsigned long long Lsize()
          {
              node* tmp;
              tmp=new node;
              tmp=head;
              unsigned long long size=0;
              if(tmp!=NULL)
              {
              while(tmp->next!=NULL)
              {
                  size+=tmp->cycle;
                  tmp=tmp->next;
              }
              if(tmp!=NULL)
                 {
                   size+=tmp->cycle;
                 }
                 return size;
              }
              return 0;
          }
          
          unsigned long long Lmean()
          {
              node* tmp;
              tmp=new node;
              tmp=head;
              int Nprocess=0;
              unsigned long long total=0;
              unsigned long long value;
              while(tmp->next!=NULL)
              {
                  ++Nprocess;
                  total+=tmp->cycle;
                  tmp=tmp->next;
              }
              if(tmp!=NULL)
                 {
                     ++Nprocess;
                   total+=tmp->cycle;
                 }
               
                 value=total/Nprocess;
                 Nprocess =0;
                 return value;
          }
          
           long double Ldiv(unsigned long long mean)
          {
              node* tmp;
              tmp=new node;
              tmp=head;
              
              int Nprocess=0;
              unsigned long long total=0;
              long double value;
              vector<unsigned long long> div(100);
              
              while(tmp->next!=NULL)
              {
                 //cout<<"avg-cycle^2 "<<pow(tmp->cycle-mean,2)<<endl;
                  div[Nprocess]=0;//pow(tmp->cycle-mean,2);
                  tmp=tmp->next;
                  Nprocess++;
                   
                  
              }
             
              if(tmp!=NULL)
                 {
                  div[Nprocess]=0;//pow(mean-tmp->cycle,2);
                  ++Nprocess;
                 }

                 for(int i=Nprocess;i>0;i--)
                 {
                    total+=div[i];
                    cout << total << endl;
                 }
                 
                 cout << total << endl;
                 cout << Nprocess << endl;
                 value = total/Nprocess;
                 cout << value << endl;
                 value = sqrt(value);
                 cout << value << endl;
                 
                 return value;
          }
          
          void Lprint()//print list to screen.
          {
              node* tmp;
              tmp=new node;
              tmp=head;
              if(head!=NULL)
              {
             while(tmp->next!=NULL)
             {
                 cout<<"****************"<<endl;
                 cout<<"ID: "<<tmp->ID<<endl;
                 cout<<"Memory: "<<tmp->mem<<endl;
                 cout<<"Cycle: "<<tmp->cycle<<endl;
                 cout<<"****************"<<endl;
                 tmp=tmp->next;
             }
                 if(tmp!=NULL)
                 {
                 cout<<"****************"<<endl;
                 cout<<"ID: "<<tmp->ID<<endl;
                 cout<<"Memory: "<<tmp->mem<<endl;
                 cout<<"Cycle: "<<tmp->cycle<<endl;
                 cout<<"****************"<<endl;
                 }
              }
          }
         
          int Lsave(int id,int pro,int times)//save list to file.
          { 
              stringstream num;
              num<<times;
              string Num = num.str();
              string Fname;
              if(id==0)
              {
                  Fname="Identical"+Num+".txt";
              }
              else if(id==1)
              {
                  Fname="MemoryBased"+Num+".txt";
              }
              else if(id==2)
              {
                  Fname="SpeedBased"+Num+".txt";
              }
              else
              {
                  Fname="RealTime"+Num+".txt";
              }
              
              ofstream save(Fname.c_str(),ios::app);
              if (save.is_open()) 
              {
                  if(pro==0)
                    {
                    save<<"Processor 1"<<endl<<endl;
                    }
                  else if(pro==1)
                    {
                    save<<"Processor 2"<<endl<<endl;
                    }
                  else if(pro==2)
                    {
                    save<<"Processor 3"<<endl<<endl;
                    }
                  else if(pro==3)
                    {
                    save<<"Processor 4"<<endl<<endl;
                    }
                  else
                    {
                    save<<"Processor 5"<<endl<<endl;
                    }
                  
                  
              node* tmp;
              tmp=new node;
              tmp=head;
             while(tmp->next!=NULL)
             {
                 save<<"****************"<<endl;
                 save<<"ID: "<<tmp->ID<<endl;
                 save<<"Memory: "<<tmp->mem<<endl;
                 save<<"Cycle: "<<tmp->cycle<<endl;
                 save<<"****************"<<endl;
                 tmp=tmp->next;
             }
                 if(tmp!=NULL)
                 {
                 save<<"****************"<<endl;
                 save<<"ID: "<<tmp->ID<<endl;
                 save<<"Memory: "<<tmp->mem<<endl;
                 save<<"Cycle: "<<tmp->cycle<<endl;
                 save<<"****************"<<endl;
                 }
                 save.close();
				 return 1;
              }
              
              else
              {
                  cout<<"unable to save file.";
				  return 0;
              }
          }
          
          int Ldelete()//clear all.
          {
             node *q;
             if( head == NULL )
             return 0;
            cout<<"deleting list..."<<endl;
            while( head != NULL )
            {
                q = head->next;
                delete head;
                head = q;
            }
			return 1;
          }
        };

private:



    List* P1;
    List* P2;
    List* P3;
    List* P4;
    List* P5;
    List* P6;




};
#endif
