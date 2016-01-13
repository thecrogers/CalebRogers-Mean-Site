//Caleb Rogers
//FEB, 19, 2014
#include<iostream>
#include "Generator.h"
#include <time.h>
using namespace std;

void Generator::Gen(vector<node>& s)
{
   // Schedular run;
    
    int ID=1100;
    int memMin, memMax;
    int cycMin, cycMax;
    
    memMin = 256;
    memMax = 4194304;
    
    cycMin = 1;
    cycMax = 5000000;
    
    for(int i=0;i<100;i++)
    {
    s[i].mem=memMin+rand()%(memMax - memMin + 1);
    s[i].cycle=cycMin+rand()%(cycMax - cycMin + 1);
    s[i].ID=ID;
    ++ID;
    }
  
}

int Generator::pGen()
{
    int num;
    num=rand()%5;//needs work;
    return num;
}
