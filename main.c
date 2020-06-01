#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./lib/command-line-validation.h"
#include "./lib/application.h"

#define FIRST_ELEMENT 1	//constant for index at position 1

int main(int argc, char* argv[])
{
	int count = 0;
	int count_arrival = 0;
	int count_burst = 0;
	bool is_valid = true;

	bool advance = true;

	//indexes for arrival and burst
	int j = 0; 
	int k = 0;

	//malloc - allocation of memory
	//pointer varibale for array of arival times
	int *arrival_times = malloc(count_arrival * sizeof(int));

	int *burst_times = malloc(count_burst * sizeof(int));

	for (int i = FIRST_ELEMENT; i< argc ;++i)
	{

		  if (!is_number(argv[i])) //if the element at the current index is not a number
			{
				is_valid = false;
				advance = false;
			}

			count++; //count the number of elements

			if (i % 2 == 1)//get 1st,3rd,5th...
			{
				count_arrival++;
			}

			//count everysecond value
			if (i % 2 == 0)
			{
				count_burst++;
			}

 	}

 	 if (!is_valid)
 	 {
 	   printf("All Elements must be integers\n");
 	   advance = false;
 	 }

 	 if (!is_count_valid(count))
 	 {
 	    printf("The number of elements must be greater than 0 and evenly divisible by 2\n");
 	    advance = false;
 	 }

	//reallocate memory for array
 	arrival_times = realloc(arrival_times, count_arrival * sizeof(int));
	burst_times = realloc(burst_times, count_burst * sizeof(int));


	for (int i = FIRST_ELEMENT; i < argc; i+=2)
	{
			arrival_times[j] = atoi(argv[i]);//get ascii to integer value of arrival times
			j++;
	}


	if(!is_arrival_valid(arrival_times,count_arrival))
	{
		printf("Arrival times must be whole numbers greater than or equal to 0\n");
		advance = false;
	}

	for(int i = 2; i < argc; i+=2)
	{
		burst_times[k] = atoi(argv[i]);
		k++;
	}

	if(!is_burst_valid(burst_times,count_burst))
	{
	  printf("Burst times must be whole numbers greater than 0\n");
	  advance = false;
	}

	//if advance returns false exit with non zero code
	if(!advance)
	{
		exit(1);
	}
	else
	{
		run(arrival_times,burst_times,count);//start the application
	}

	//taken from notes in labs - if the arrival times pointer is not null
	if(arrival_times != NULL)
	{
	   //deallocate memory
	   free(arrival_times);
	   arrival_times = NULL;
	}


	if(burst_times != NULL)
	{
		free(burst_times);
	  burst_times = NULL;
	}

	return 0;
}
