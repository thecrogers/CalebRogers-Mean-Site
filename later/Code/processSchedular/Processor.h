#ifndef PROCESSORHEADERFILE
#include<iostream>
#include<fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include "node.h"
#define PROCESSORHEADERFILE
using namespace std;
class Processor
{

public:
  
  
  
   Processor()
   {
       P1=new List();
       P2=new List();
       P3=new List();
       P4=new List();
       P5=new List();
       P6=new List();
   }
    ~Processor()
    {
        
        
    }
    int insert(int,int,int,unsigned long long);//first int is the list to enter into.
    void print(int);//list to print from
    int save(int,int,int);//save all
    unsigned long long Size(int);
    unsigned long long Mean(int);
    unsigned long long Turn(int);
    unsigned long long getWait(int);
    int Update(int, int);
    long double Div(int,unsigned long long);
    void deleteAll();

class List
        {
          public:
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
                head->next=NULL;
                head->prev=NULL;
                last=head;
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
                  tmp->state=0;
                  tmp->cycle=cycle;
                  curr->next=tmp;
                  tmp->next=NULL;
                  tmp->prev=curr;
                  last=tmp;
              }
              return 0;
          }
          
          unsigned long long LgetWait(int opt)
          {
              node* tmp;
              tmp=new node;
              tmp = head;
              unsigned long long value=0;
              if(head!=NULL)
              {
              if(opt==1)//ie process is running.
              {
                  cout<<"pram 1 "<<tmp->ID<<endl;
               return tmp->ID;
              }
              else if(opt==2)
              {
                  cout<<"pram 2 "<<tmp->mem<<endl;
                  return tmp->mem;
              }
              else if(opt==3)
              {
                  cout<<"pram 3 "<<tmp->cycle<<endl;
                  value=tmp->cycle;
                  return value;
              }
              
               else if(opt==0)
              {
                  if(tmp->next==NULL)
                  {
                      head=NULL;
                      delete tmp;
                  }
                  else
                  {
                  head=tmp->next;
                 
                  delete tmp;
                  }
                  return 0;
              }
             else
             {
                 return 0;
             }
          }
          }
          
          
          unsigned long long Lturn()
          {
              node* tmp;
              tmp=new node;
              tmp = last;
              if(last==NULL||tmp->state==0)
              {
                  return 0;
              }
              
              else if(tmp->state==1)//ie process is running.
              {
               return tmp->turnTime;
              }
          }
          
           int Lupdate(int slice)
          {
              node* tmp;
              tmp=new node;
              tmp = last;
              if(last==NULL||tmp->state==0)
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
              }
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
              unsigned long long value=0;
			  if(tmp!=NULL)
              {
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
			  }
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
                 cout<<"avg-cycle^2 "<<pow(tmp->cycle-mean,2)<<endl;
                  div[Nprocess]=pow(tmp->cycle-mean,2);
                  tmp=tmp->next;
                  Nprocess++;
                   
                  
              }
             
              if(tmp!=NULL)
                 {
                  div[Nprocess]=pow(mean-tmp->cycle,2);
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
			 if(tmp!=NULL)
              {
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
			 }
              }
              
              else
              {
                  cout<<"unable to save file.";
              }
          return 0;
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