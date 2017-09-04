
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
# include <stdbool.h>

uint64_t set(uint64_t adress);

// given 64 bit unsigned integer adress in the main memory, this function determines the tag 
uint64_t Determine_Tag(uint64_t adress_in_memory);
uint64_t HextoInt(char *hexvalue);

//define the property of the cache
struct Set_Associative_cache
{
	uint64_t tag;
	int isempty;
	int lastused;
};
// we are implementing 8 way associative cache. number of sets needed 512/8= 64 and this is specified by 6 bits
uint64_t set(uint64_t adress){
	uint64_t shifted_adress= adress>>6;
	uint64_t mask=0x3f;
	uint64_t set_adress= shifted_adress& mask;
	return set_adress;


}

uint64_t Determine_Tag(uint64_t adress_in_memory){

	uint64_t tag= adress_in_memory>>12;
	return tag;
}


	

//function that converts the hex value to  64 bit unsigned  integer
uint64_t HextoInt(char *hexvalue){
uint64_t Int_val = 0;
 {

  Int_val= (int)strtol(hexvalue,NULL,16);
 }
 
 return Int_val;
}



	int main(int argc, char *argv[])
{
    
    int counter=0; 
    uint64_t hits=0;
    uint64_t misses=0;
   char buffer [25];
   struct Set_Associative_cache  cache[512];
   int recentlyused=0; // variable used to keep track of recenty used entry in the cache
   int i=0;
   for ( i = 0; i < 512; ++i)
   {
   	cache[i].tag=0;
   	cache[i].isempty=1;
   	cache[i].lastused=0;
   }

   while(fgets(buffer,25,stdin)!=NULL)
   {
  	counter++;
  	int written=1; // to check if an adress just read is written to a cache
  	//uint64_t value_read= HextoInt(buffer);
    uint64_t value_read= HextoInt(buffer);
  	uint64_t tag= Determine_Tag(value_read); // decided the tag of the adress
  	uint64_t set_number =set(value_read);
  	uint64_t set= set_number *8;//  this specifies where index of a given set starts. for example the second starts at the index i= 16;
    int i;
  	for ( i = set; i < set+8; ++i)
  	{
  	int latest= cache[i].lastused;
  	if (cache[i].tag==tag)
  	{
  		hits++;
  		cache[i].isempty=0;
  		cache[i].lastused=counter;
  		written=1;
  		break;
  	}
  	if (cache[i].isempty==1)
  	{
  		cache[i].tag=tag;
  		cache[i].isempty=0;
  		cache[i].lastused=counter;
  		misses++;
  		written=1;
  		break;
  	}
    
  	if (latest <cache[recentlyused].lastused)

  		{
  			recentlyused=i;

  		}

  	}
  	if (written=1)
  	{
  		cache[recentlyused].tag=tag;
  		cache[recentlyused].lastused=counter;
  		misses++;
  	}
      // printf("Total number of cache hits  : %d\n", hits);

 	}
 	
 	int sum= misses+hits;
   float Per_hits= (float)hits/sum*100;
   float Per_misses= (float)misses/sum*100;
    printf("Total number of cache hits  : %d\n", hits);
    printf("Total number of cache misses  : %d\n", misses);
     printf("percentage  of  hits  : %0.2f\n", Per_hits);
    printf("percentage of  misses  : %0.2f\n", Per_misses);

}