#include "memTree.h"
#include "Processor.h"
using namespace std;
Processor pro;
    int memTree::alloc(block *Root,int ID,int size,int total,int cycle)//need to send correct porinter for waiting list. 
    {
        int found =1,end=0;
        int lPsize=total;
        
        if(Root==NULL)//list is empty.
        {
            block *lBlock, *rBlock,*nLeft,*nRight;
            lBlock = new block;
            rBlock=new block;
            Root=new block;


            Root->pSize=total;//set root size to 10 mb.
            
            if(size>(Root->pSize/2))//size is bigger than next partion.
            {
                Root->size=size;
                Root->ID=ID;
				Root->state=1;
                Root->left=NULL;
                Root->right=NULL;  
                return 1;
            }
            else//partition the block.
            {
                Root->right=rBlock;//set root right pointer
                Root->left=lBlock;//set root left pointer
                Root->state=-1;
                
                lBlock->parent=root;//set lblock parent
                rBlock->parent=root;//set rblock parent
                
                lBlock->sibling=rBlock;//set siblings
                rBlock->sibling=lBlock;//set siblings
                
				lBlock->state=0;
				rBlock->state=0;

                lBlock->left=NULL;
                lBlock->right=NULL;
                
                rBlock->left=NULL;
                rBlock->right=NULL;
                
                lPsize=(total)/2;
                
                while(found==1)
                {
                    rBlock->pSize=lPsize;//set the rblock partition size to last partition size
                    lBlock->pSize=lPsize;//set the lblock partition size to last partition size
                    
					if(size>lBlock->pSize && (lBlock->parent)->pSize>size &&lBlock->state==0)//if the size is greater than the current left partition divied by 2
                    {
						lBlock=lBlock->parent;
                        lBlock->size=size;
                        lBlock->ID=ID;
						lBlock->state=1;
                        lBlock->left=NULL;
                        lBlock->right=NULL;
                        found=0;
                        return 1;
                    }
                    
                    else//break up the partition
                    {
                      
                      lPsize=(lPsize/2);//divide current last part size by two 
                        
                        lBlock->state=-1;//set partitions state to divided.
                        nRight=new block;
                        nLeft=new block;
                        lBlock->right=nRight;//set children of rBlock
                        lBlock->left=nLeft;
                      
                        nRight->parent=lBlock;//set new childrens parent
                        nLeft->parent=lBlock;
                            
                        nRight->sibling=nLeft;//set siblings 
                        nLeft->sibling=nRight;
                        
                        nRight->right=NULL;
                        nRight->left=NULL;
						
						nRight->state=0;
						nLeft->state=0;

                        nLeft->right=NULL;
                        nLeft->left=NULL;
                            
                        rBlock=new block;//not sure if this will work
                        lBlock=new block;
                        rBlock=nRight;//set rBlock to new block
                        lBlock=nLeft;//set lBlock to new block
                        
                    }
                }
            }
        }
        
        
        else
        {
          block *curr=new block;
          block *nRight,*nLeft,*lBlock, *rBlock;
          nRight=new block;
          nLeft=new block;
		  lBlock=new block;
		  rBlock=new block;
          block *opt=new block;
		  opt->ID=-10;
          curr=root;
          int p=0,icount=0,loop=2,i=0;
          double comps=0.0,count=0.0;
          
          preOrder(Root,1,0,size,Size(root),&opt);
          curr=opt;
		  if(opt->state==-3)
		  {
              if(curr->pSize>size)
			  {
			  curr->ID=ID;
              curr->size=size;
              curr->state=1;
			  return 1;
			  }
		  }
		  else//need to partition
		  {

			    lBlock->parent=curr;//set lblock parent
                rBlock->parent=curr;//set rblock parent
                
				curr->left=lBlock;
				curr->right=rBlock;
				curr->state=-1;

                lBlock->sibling=rBlock;//set siblings
                rBlock->sibling=lBlock;//set siblings
                
				lBlock->state=0;
				rBlock->state=0;

                lBlock->left=NULL;
                lBlock->right=NULL;
                
                rBlock->left=NULL;
                rBlock->right=NULL;

			  lPsize=curr->pSize;
			  lPsize/=2;

			while(found==1)
                {
                    rBlock->pSize=lPsize;//set the rblock partition size to last partition size
                    lBlock->pSize=lPsize;//set the lblock partition size to last partition size
                    
					if(size>(lBlock->pSize)/2 && lBlock->pSize>size &&lBlock->state==0)//if the size is greater than the current left partition divied by 2
                    {
						
                        lBlock->size=size;
						//(lBlock->parent)->left=lBlock;
						lBlock->ID=ID;
						lBlock->state=1;
                        lBlock->left=NULL;
                        lBlock->right=NULL;
                        found=0;
                        return 1;
                    }
                    
					else if(size>(rBlock->pSize)/2 && rBlock->pSize>size &&rBlock->state==0)//if the size is greater than the current left partition divied by 2
                    {
						
                        rBlock->size=size;
                        rBlock->ID=ID;
						rBlock->state=1;
                        rBlock->left=NULL;
                        rBlock->right=NULL;
                        found=0;
                        return 1;
						
                    }

					else if(size>rBlock->pSize&&end!=1)
					{
						 preOrder(Root,2,0,size,Size(root),&opt);
						 
						 if(opt->state==-3)
							{
							  if(curr->pSize>size)
								{
									curr->ID=ID;
									curr->size=size;
									curr->state=1;
									return 1;
								}
							}

						 else
						 {
							 lBlock->parent=curr;//set lblock parent
							rBlock->parent=curr;//set rblock parent
                
							curr->state=-1;

			                lBlock->sibling=rBlock;//set siblings
			                rBlock->sibling=lBlock;//set siblings
	                
							lBlock->state=0;
							rBlock->state=0;

							lBlock->left=NULL;
							lBlock->right=NULL;
                
							rBlock->left=NULL;
							rBlock->right=NULL;

							lPsize=curr->pSize;
							lPsize/=2;
						 }
						 end=1;
						 
					}
					else if(end==1)
					{
					    node *tmp=new node;
					    tmp=pro.getHead();
						pro.insert(6,ID,size,cycle);
						pro.getWait(0,&tmp);
						return 0;
					}

                    else//break up the partition
                    {
                      
                      lPsize=(lPsize/2);//divide current last part size by two 
                        
                        lBlock->state=-1;//set partitions state to divided.
                        nRight=new block;
                        nLeft=new block;
                        lBlock->right=nRight;//set children of rBlock
                        lBlock->left=nLeft;
                      
                        nRight->parent=lBlock;//set new childrens parent
                        nLeft->parent=lBlock;
                            
                        nRight->sibling=nLeft;//set siblings 
                        nLeft->sibling=nRight;
                        
                        nRight->right=NULL;
                        nRight->left=NULL;
						
						nRight->state=0;
						nLeft->state=0;

                        nLeft->right=NULL;
                        nLeft->left=NULL;
                            
                        rBlock=new block;//not sure if this will work
                        lBlock=new block;
                        rBlock=nRight;//set rBlock to new block
                        lBlock=nLeft;//set lBlock to new block
                        
                    }
                }




		  }
        }
    }

	int memTree::allocc(node**gHead,int ID,int size,int total,int cycle)
    {
        int found =1,end=0;
        int lPsize=total;
        
        if(root==NULL)//list is empty.
        {
            block *lBlock, *rBlock,*nLeft,*nRight;
            lBlock = new block;
            rBlock=new block;
            


            root=new block;
			root->pSize=total;//set root size to 10 mb.
            
            if(size>(root->pSize/2))//size is bigger than next partion.
            {
                root->size=size;
                root->ID=ID;
				root->state=1;
                root->left=NULL;
                root->right=NULL;  
                return 1;
            }
            else//partition the block.
            {
                root->right=rBlock;//set root right pointer
                root->left=lBlock;//set root left pointer
                root->state=-1;
                
                lBlock->parent=root;//set lblock parent
                rBlock->parent=root;//set rblock parent
                
                lBlock->sibling=rBlock;//set siblings
                rBlock->sibling=lBlock;//set siblings
                
				lBlock->state=0;
				rBlock->state=0;

                lBlock->left=NULL;
                lBlock->right=NULL;
                
                rBlock->left=NULL;
                rBlock->right=NULL;
                
                lPsize=(total)/2;
                
                while(found==1)
                {
                    rBlock->pSize=lPsize;//set the rblock partition size to last partition size
                    lBlock->pSize=lPsize;//set the lblock partition size to last partition size
                    
                    if(size>(lBlock->pSize)/2 && lBlock->pSize>size &&lBlock->state==0)//if the size is greater than the current left partition divied by 2
                      {
                    	lBlock->size=size;
     					//(lBlock->parent)->left=lBlock;
      					lBlock->ID=ID;
                    	lBlock->state=1;
                        lBlock->left=NULL;
                        lBlock->right=NULL;
                        found=0;
                        return 1;
                      }//if the size is greater than the current left partition divied by 2
                    
                    else//break up the partition
                    {
                      
                      lPsize=(lPsize/2);//divide current last part size by two 
                        
                        lBlock->state=-1;//set partitions state to divided.
                        nRight=new block;
                        nLeft=new block;
                        lBlock->right=nRight;//set children of rBlock
                        lBlock->left=nLeft;
                      
                        nRight->parent=lBlock;//set new childrens parent
                        nLeft->parent=lBlock;
                            
                        nRight->sibling=nLeft;//set siblings 
                        nLeft->sibling=nRight;
                        
                        nRight->right=NULL;
                        nRight->left=NULL;
						
						nRight->state=0;
						nLeft->state=0;

                        nLeft->right=NULL;
                        nLeft->left=NULL;
                            
                        rBlock=new block;//not sure if this will work
                        lBlock=new block;
                        rBlock=nRight;//set rBlock to new block
                        lBlock=nLeft;//set lBlock to new block
                        
                    }
                }
            }
        }
        
        
        else
        {
          block *curr=new block;
          block *nRight,*nLeft,*lBlock, *rBlock;
          nRight=new block;
          nLeft=new block;
		  lBlock=new block;
		  rBlock=new block;
          block *opt=new block;
		  opt->ID=-10;
          curr=root;
          int p=0,icount=0,loop=2,i=0;
          double comps=0.0,count=0.0;
          
          preOrder(root,1,0,size,Size(root),&opt);
          curr=opt;
		  if(opt->state==-3)
		  {
              if(curr->pSize>size)
			  {
			  curr->ID=ID;
              curr->size=size;
              curr->state=1;
			  }
		  }
		  else//need to partition
		  {

			    lBlock->parent=curr;//set lblock parent
                rBlock->parent=curr;//set rblock parent
                
				curr->left=lBlock;
				curr->right=rBlock;
				curr->state=-1;

                lBlock->sibling=rBlock;//set siblings
                rBlock->sibling=lBlock;//set siblings
                
				lBlock->state=0;
				rBlock->state=0;

                lBlock->left=NULL;
                lBlock->right=NULL;
                
                rBlock->left=NULL;
                rBlock->right=NULL;

			  lPsize=curr->pSize;
			  lPsize/=2;

			while(found==1)
                {
                    rBlock->pSize=lPsize;//set the rblock partition size to last partition size
                    lBlock->pSize=lPsize;//set the lblock partition size to last partition size
                    
					if(size>(lBlock->pSize)/2 && lBlock->pSize>size &&lBlock->state==0)//if the size is greater than the current left partition divied by 2
                    {
						
                        lBlock->size=size;
						//(lBlock->parent)->left=lBlock;
						lBlock->ID=ID;
						lBlock->state=1;
                        lBlock->left=NULL;
                        lBlock->right=NULL;
                        found=0;
                        return 1;
                    }
                    
					else if(size>(rBlock->pSize)/2 && rBlock->pSize>size &&rBlock->state==0)//if the size is greater than the current left partition divied by 2
                    {
						
                        rBlock->size=size;
                        rBlock->ID=ID;
						rBlock->state=1;
                        rBlock->left=NULL;
                        rBlock->right=NULL;
                        found=0;
                        return 1;
						
                    }

					else if(size>rBlock->pSize&&end!=1)
					{
						 preOrder(root,2,0,size,Size(root),&opt);
						 curr=opt;
						 if(opt->state==-3)
							{
							  if(curr->pSize>size)
								{
									curr->ID=ID;
									curr->size=size;
									curr->state=1;
									return 1;
								}
							}

						 else
						 {

							 lBlock=new block;
							 rBlock=new block;
							 lBlock->parent=curr;//set lblock parent
							 rBlock->parent=curr;//set rblock parent
                
							curr->state=-1;

			                lBlock->sibling=rBlock;//set siblings
			                rBlock->sibling=lBlock;//set siblings
	                
							lBlock->state=0;
							rBlock->state=0;

							lBlock->left=NULL;
							lBlock->right=NULL;
                
							rBlock->left=NULL;
							rBlock->right=NULL;

							lPsize=curr->pSize;
							lPsize/=2;
							lBlock->pSize=lPsize;
							rBlock->pSize=lPsize;
						 }
						 end=1;
						 
					}
					else if(end==1)
					{
						pro.insert(6,ID,size,cycle);
						*gHead=pro.getHead();
						return 0;
					}

                    else//break up the partition
                    {
                      
                      lPsize=(lPsize/2);//divide current last part size by two 
                        
                        lBlock->state=-1;//set partitions state to divided.
                        nRight=new block;
                        nLeft=new block;
                        lBlock->right=nRight;//set children of rBlock
                        lBlock->left=nLeft;
                      
                        nRight->parent=lBlock;//set new childrens parent
                        nLeft->parent=lBlock;
                            
                        nRight->sibling=nLeft;//set siblings 
                        nLeft->sibling=nRight;
                        
                        nRight->right=NULL;
                        nRight->left=NULL;
						
						nRight->state=0;
						nLeft->state=0;

                        nLeft->right=NULL;
                        nLeft->left=NULL;
                            
                        rBlock=new block;//not sure if this will work
                        lBlock=new block;
                        rBlock=nRight;//set rBlock to new block
                        lBlock=nLeft;//set lBlock to new block
                        
                    }
                }




		  }
        }
    }

    int memTree::free(int ID,block *start)
    {
        int found=1,count=0,i=0,p=0,loop=2;
        block *curr=new block;
        block *tmp=new block;
        block *rem=new block;
		block *opt=new block;

        curr=start;
        
       preOrder(start,0,ID,0,Size(curr),&opt);//will return pointer to block of memory.
       curr=opt;
	   
	   if(curr->state==-3)
       {

          if(curr->sibling!=NULL)
          {
		   if((curr->sibling)->state==0||(curr->sibling==NULL))//join to children
		   {
            tmp=curr->parent;
            tmp->left=NULL;
            tmp->right=NULL;
            tmp->state=0;
            tmp->pSize=2*curr->pSize;
            
            rem=curr->sibling;
            delete rem;
            delete curr;
            return 1;
        }
        else
        {
            curr->left=NULL;
            curr->right=NULL;
            curr->state=0;
            curr->ID=0;
            curr->size=0;
            
            return 1;
        }
       }

       else
       {
           cout<<"could not find memory"<<endl;
           return -1;
       }
       }
    }
    
    void memTree::preOrder(block* obj,int funct,int ID,int size,int numBlock,block **opt)
    {
		
        if(funct==0)
        {
            if(obj)
            {
				if(obj->ID==ID&&(*opt)->state!=-3)
                {
					*opt=obj;
					(*opt)->state=-3;
                }
                preOrder(obj->left,0,ID,0,numBlock,opt);
                preOrder(obj->right,0,ID,0,numBlock,opt);
            }
          
        }


        else if(funct==1)
        {
			if(obj)//still not returning what I need. 
			{
				if(size>(obj->pSize)/2 && obj->pSize>size &&obj->state==0)
				{
					*opt=obj;
					(*opt)->state=-3;
				}
				else if(((obj->left==NULL)||(obj->right==NULL))&&(*opt)->state!=-5&&(*opt)->state!=-3&&obj->state!=1)
				{
					*opt=obj;
					(*opt)->state=-5;
				}
				  preOrder(obj->left,1,++ID,size,numBlock,opt);
				  preOrder(obj->right,1,++ID,size,numBlock,opt);
				
			} 
            
		}

		else
		{
			if(obj)
			{
				if(size>(obj->pSize)/2 && obj->pSize>size &&obj->state==0)
				{
					*opt=obj;
					(*opt)->state=-3;
				}

				else if(((obj->left==NULL)||(obj->right==NULL))&&(*opt)->state!=-5&&(*opt)->state!=-3&&obj->state==0)
				{
					*opt=obj;
					(*opt)->state=-5;
				}
					preOrder(obj->right,1,++ID,size,numBlock,opt);
	    		    preOrder(obj->left,1,++ID,size,numBlock,opt);
				 
				
			}
		}

    }
    
    void memTree::print(block *obj)
    {
       
		if(obj)
		{
        print(obj->left);
        
		if(obj->ID>0)
		{
		cout<<endl<<"Block"<<endl;
        cout<<"ID: "<<obj->ID<<endl;
        cout<<"acutal memory size: "<<obj->size<<endl;
        cout<<"partition size: "<<obj->pSize<<endl;
		}
		print(obj->right);
		}
    }
    
    int memTree::Size(block* obj)
    {
        if(obj)
        {
        return(Size(obj->left) + 1 + Size(obj->right));
        }
        else
        {
            return 0;
        }
    }
    
    
    
    
    
    /*



	 if(curr->ID==0)//needs partition
          {
              curr->state=-1;
              
              nRight->parent=curr;//set new childrens parent
              nLeft->parent=curr;
                            
              nRight->sibling=nLeft;//set siblings 
              nLeft->sibling=nRight;
                        
              nRight->right=NULL;
              nRight->left=NULL;
                
              nLeft->right=NULL;
              nLeft->left=NULL;
              
              nLeft->pSize=curr->pSize/2;
              nRight->pSize=curr->pSize/2;
              
              nLeft->ID=ID;
              nLeft->size=size;
              nLeft->state=1;
              
              curr->right=nRight;
              curr->left=nLeft;
              return 1;
          }
          else if(curr->ID==-1)//already partitioned
          {




                if((obj->pSize/2)<size&&obj->pSize>size&&obj->state==0)//found open partition
                {
					obj->ID=-1;
					opt=obj;
                    return obj;
                }
                else if(obj->state==-1&&(obj->pSize/2)<size&&obj->pSize>size&&obj->ID!=-1)//partition already created.
                {
                    if((obj->left)->state==0)//left child is open;
                    {
						(obj->left)->ID=-1;
						opt=obj->left;
                        return opt;
                    }
                    else if((obj->right)->state==0)//right child is open
                    {
						(obj->right)->ID=-1;
						opt=obj->right;
                        return opt;
                    }
                }
				if(opt->pSize<0)
				{
				else if(obj->ID==-1)
			{
				return obj;
			}
            else if(!obj&&numBlock==ID)//no fit in the tree
            {
                block *fail=new block;
                fail->left=NULL;
                fail->right=NULL;
                fail->sibling=NULL;
                fail->parent=NULL;
                fail->ID=-2;
                
                return fail; 
            }     

				*/
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
    
    
    
    
     while(1)//get depth of block we need. 
          {
              total/=2;//devide total by 2 every loop
              if(size>total)
              {
               break;    
              }
              else
              {
                  ++count;
              }
          }
          
          comps=pow(2.0,count);//set the total number of compairisons
          
          for(int i=0;i<count;i++)//move curr to that depth
          {
              if(curr->left!=NULL)//all good advance to next level
              {
                curr=curr->left;
              }
              else//area not yet partitioned
              {
                curr->state=-1; 
                lPsize=(curr->pSize)/2;
                nRight=new block;
                nLeft=new block;
                curr->right=nRight;//set children of rBlock
                curr->left=nLeft;
                      
                nRight->parent=curr;//set new childrens parent
                nLeft->parent=curr;
                            
                nRight->sibling=nLeft;//set siblings 
                nLeft->sibling=nRight;
                
                nRight->right=NULL;
                nRight->left=NULL;
                
                nLeft->right=NULL;
                nLeft->left=NULL;
                
                nRight->pSize=lPsize;
                nLeft->pSize=lPsize;
                
                curr=curr->left;//move curr to newly created block
              }
          }
          
          count=0;
          
          while(comps>icount)
            {
                if(curr->state==0)//place memory here
                {
                    curr->size=size;
                    curr->ID=ID;
                    //might need to set left, right, parent, and sibling
                    icount=comps;//get out of loop
                }
                
                else
                {
                    
                    
                    if(i%2==0)
                    {
                        curr=curr->sibling;
                    }
                
                    else
                    {
                        if(p%2==0)
                        {
                           curr=curr->parent;
                           curr=curr->sibling;
                       
                           if(curr->left!=NULL)
                           {
                               curr=curr->left;
                           }
                           else//go up one more level;
                           {
                           /**TODO**
                           }
                        }
                    
                        else
                        {  
                           for(int x=0;x<loop;x++)
                            {
                                curr=curr->parent;
                            }
                        
                            curr=curr->sibling
                            
                            if(curr-left!=null)
                            {
                               for(int x=0;x<loop;x++)
                                {
                                    curr=curr->left;
                                } 
                            }
                            else
                            {
                            /**TODO**
                            }
                    
                            if(loop<(count-1))
                            {
                             ++loop;    
                            }
                            else
                            {
                                loop=2;
                            }
                        }
                    }
                }
            }
         
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    while(found==1)
        {
            if(size>tsize)
            {
                /**TODO
                 * remove memory from block
                 **
                found=0;
            }
            else
            {
                tsize/=2;
              ++count;  
            }
            
        }
        
        while(i<count)//count is the total number of possible checks. 
        {
            if(curr->ID==ID)//found the item
            {
             /**TODO
                 * remove memory from block
                 **   
            }
            else
            {
                if(i%2==0)
                {
                    curr=curr->sibling;
                }
                
                else
                {
                    if(p%2==0)
                    {
                       curr=curr->parent;
                       curr=curr->sibling;
                       
                       if(curr->left!=NULL)
                       {
                           curr=curr->left;
                       }
                       else//go up one more level;
                       {
                         /**TOD** 
                       }
                    }
                    
                    else
                    {  
                       for(int x=0;x<loop;x++)
                        {
                            curr=curr->parent;
                        }
                        
                        curr=curr->sibling
                        
                        if(curr-left!=null)
                        {
                           for(int x=0;x<loop;x++)
                            {
                                curr=curr->left;
                            } 
                        }
                        else
                        {
                            /**TOD**
                        }
                        
                        
                        if(loop<(count-1))
                        {
                         ++loop;    
                        }
                        else
                        {
                            loop=2;
                        }
                    }
                }
            }
            
            ++i;
       }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
                    if(icount%2==0)//on left child on correct depth
                    {
                       curr=curr->sibling;//curr is on left child node 
                    }
                    
                    else//on right child of correct depth need to move up and over
                    {
                        if(par%2==0)//need to go up n many parents and then to sibling
                        {
                            /**To Do**
                             * figure out way to know how many parent calls
                             * are needed to get to new set. 
                             **/
                            /* 
                            for(int x=0;x<loop;x++)
                            {
                                curr=curr->parent;
                            }
                        
                            curr=curr->sibling
                        
                            if(curr-left!=null)
                            {
                               for(int x=0;x<loop;x++)
                                {
                                    curr=curr->left;
                                } 
                            }
                            else
                            {
                            
                            }
                        
                            if(loop<(count-1))
                            {
                             ++loop;    
                            }
                            else
                            {
                                loop=2;
                            }
                             
                        }
                        
                        else//only need to go up one parent and then to sibling
                        {
                            curr=curr->parent;
                            curr=curr->sibling;
                        }
                        ++par;
                    }
                    
                    ++icount;
    */
    
    
    
    
    
    
    
    /* old code
    
    
    
     block *lBlock, *rBlock,*nLeft,*nRight;
            lBlock = new block;
            rblock=new block;
            
            lBlock=root->left;
            rBlock=root->right;
        
            if(size>(rBlock->pSize/2)&&->state==0)//size is bigger than next partion.
            {
                
            }
            
             else if(size>(lBlock->pSize/2)&&->state==0)//size is bigger than next partion.
            {
                
            }
            
            else//partition the block.
            {`
                lPsize=(10485760)/2;
                
                    rBlock->pSize=lPsize;//set the rblock partition size to last partition size
                    lBlock->pSize=lPsize;//set the lblock partition size to last partition size
                    
                    if(size>((rBlock->pSize)/2)&&rBlock->state==0)//if the size is greater than the current right partition divied by 2
                    {
                        
                        found=0;
                    }
                    
                    
                   else if(size>((lBlock->pSize)/2)&&lBlock->state==0)//if the size is greater than the current left partition divied by 2
                    {
                        
                        found=0;
                    }
                    
                    else//break up the partition
                    {
                      
                      lPsize=(lPsize/2);//divide current last part size by two 
                        
                        if()
                        {
                            rBlock->state=-1;//set partitions state to divided.
                            nRight=new block;
                            nLeft=new block;
                            rBlock->right=nRight;//set children of rBlock
                            rBlock-left=nLeft;
                      
                            nRight->parent=rBlock;//set new childrens parent
                            nLeft->parent=rBlock;
                            
                            nRight->sibling=nLeft;//set siblings 
                            nLeft->sibling=nRight;
                            
                            rBlock=new block;//not sure if this will work
                            lBlock=new block;
                            rBlock=nRight;//set rBlock to new block
                            lBlock=nLeft;//set lBlock to new block
                        }
                        
                        
                        else//go left;
                        {
                            lBlock->state=-1;
                            nRight=new block;
                            nLeft=new block;
                            lBlock->right=nRight;//set children of lBlock;
                            lBlock->left=nLeft;
                      
                            nRight->parent=lBlock;//set childrens parents
                            nLeft->parent=lBlock;
                            
                            nRight->sibling=nLeft;//set siblings 
                            nLeft->sibling=nRight;
                            
                            rBlock=new block;//not sure if this will work;
                            lBlock=new block;
                            rBlock=nRight;//set rBlock to new block
                            lBlock=nLeft;//set lBlock to new block
                        }    
                       
                    }
                }
            }*/
    
    
