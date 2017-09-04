#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>



uint64_t Determine_Tag(uint64_t adress_in_memory);
uint64_t HextoInt(char *hexvalue);

//function that converts the hex value to  64 bit unsigned  integer
uint64_t HextoInt(char *hexvalue){
uint64_t Int_val = 0;
 {

  Int_val= (int)strtol(hexvalue,NULL,16);
 }
 
 return Int_val;
}

// given 64 bit unsigned integer adress in the main memory, this function determines the tag of the adress
uint64_t Determine_Tag(uint64_t adress_in_memory){

  uint64_t tag= adress_in_memory>>6;
  return tag;
  
}


//defines the property of Fully associative cache
struct FA_cache
{
  uint64_t tag;
  int isempty;
  int lastused; // keeps track of the last time  a given entry is cache is used
};
int main(int argc, char *argv[])
{
    

    int counter=0;  
    uint64_t hits=0;
    uint64_t misses=0;
   char buffer [25];
   struct FA_cache cache[512]; // the size of cache is 512 because  32,768 bytes/64= 512
   int recentlyused=0; // variable used to keep track of recenty used entry in the cache
   int i;

    for ( i = 0; i < 512; i++)
    {
      cache[i].isempty=1;
      cache[i].tag=0;
      cache[i].lastused=0;
      
    }
    while(fgets(buffer,25,stdin)!=NULL){
    counter++; 
    int written=0; // to check if an adress just read is written to a cache
   
    uint64_t value_read= HextoInt(buffer);
    

    uint64_t tag= Determine_Tag(value_read); 
    
    int i;
    for( i = 0; i < 512; i++)
    {
      int latest= cache[i].lastused; 

      if (tag==cache[i].tag)     // checks if the tag of the adress and the tag in the cache match 
      {
        hits++;
        cache[i].lastused=counter;

        written= 1;

        break;
      }
     

      if (cache[i].isempty==1) 
      {
        misses++;
        cache[i].tag=tag;
        cache[i].lastused=counter;
        cache[i].isempty=0;
        written=1;
       
        break;


      }
      if (latest <cache[recentlyused].lastused)

      {
        recentlyused=i;
              

      }

    }
    if (written==0)
      // this is the case, where the cache is full and we decided to get rid of something to make a room
    {
      cache[recentlyused].tag=tag;
      cache[recentlyused].lastused=counter;
      misses++;

    }
    
   
  }
  
  int sum= misses+hits;
  float Per_hits= (float)hits /sum*100.00;
   float Per_misses= (float)misses/sum *100.00;
    printf("Total number of cache hits  : %d\n", hits);
    printf("Total number of cache misses  : %d\n", misses);
     printf("percentage  of  hits  : %0.2f\n", Per_hits);
    printf("percentage of  misses  : %0.2f\n", Per_misses);

   }




  