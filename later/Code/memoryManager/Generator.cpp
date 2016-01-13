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
    int numProcs;
    int memMin;
    int memMax;
    unsigned long long cycMin, cycMax;
    
    numProcs = 25;
    
    memMin = 256; //Smallest mem size 256 Bytes
    memMax = 9961472; //Total mem possible to alloc 9.5MB, give or take 200000
    
    cycMin = 1;
    cycMax = 5000000;
    
	int memToAdd;
    
    //Add to each of 50 buckets 1 at a time until reaching 9961472, Random Distribution
	while(memMax > 0){ //While we have not used up all over our alloted memory
		for(int i=0;i<numProcs;i++){ //loop through the entire process list
			memToAdd = memMin+rand()%(memMax/10 - memMin + 1);// generate random Memory value bounded by memMax
			if((memMax - memToAdd) > -200000 || s[i].mem >5000000){ //Make sure doesn't go too negative
				s[i].mem += memToAdd; //Add the memory chunk to this process
				memMax -= memToAdd; //Subrract from total memor alloted
			}
		}
    }
    
    for(int i=0;i<numProcs;i++)
    {
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
