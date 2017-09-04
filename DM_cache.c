#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>



// this program is the simulation of direct mapped cache

uint64_t Determine_adress_in_cache(uint64_t adress_in_memory);
uint64_t HextoInt( char *hexvalue);
uint64_t Determine_Tag(uint64_t adress_in_memory);

int main(int argc, char *argv[])
{
    uint64_t cache[512];
    int counter=0; 
    uint64_t hits=0;
    uint64_t misses=0;
   char buffer [25];

  while(fgets(buffer,25, stdin)!=NULL)
  {

  	counter++;
  	
  	uint64_t value_read= HextoInt(buffer);

  	

  	uint64_t entry=Determine_adress_in_cache(value_read);
  	uint64_t tag= Determine_Tag(value_read);
  
  	if (cache[entry]==tag)
  	{
  		hits++;
  	}
  	else{
  		misses++;
  	}
  	
  cache[entry]=tag;
 
  }
  int sum= misses+hits;
  float Per_hits= (float)hits /sum*100.00;
   float Per_misses= (float)misses/sum *100.00;
    printf("Total number of cache hits  : %d\n", hits);
    printf("Total number of cache misses  : %d\n", misses);
     printf("percentage  of  hits  : %0.2f\n", Per_hits);
    printf("percentage of  misses  : %0.2f\n", Per_misses);

  }
//This function,  determines where in cache a given block is saved 
uint64_t Determine_adress_in_cache(uint64_t adress_in_memory){

	uint64_t shifted_adress= adress_in_memory>>6;
	uint64_t mask =0x1ff;
	uint64_t adress_in_cache= shifted_adress& mask;
	return adress_in_cache;

}
// given 64 bit unsigned integer adress in the main memory, this function determines the tag 
uint64_t Determine_Tag(uint64_t adress_in_memory){

	uint64_t tag= adress_in_memory>>15;
	return tag;	

}

uint64_t HextoInt(char *hexvalue){
uint64_t Int_val = 0;
 {

  Int_val= (int)strtol(hexvalue,NULL,16);
 }
 
 return Int_val;
}