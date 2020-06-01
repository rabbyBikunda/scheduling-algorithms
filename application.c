#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "input-utils.h"

#define MAX_INPUT_CHARS 35
#define EQUIVALENT 0
#define HALF 2
#define FIRST_INDEX 0
#define TEMP_SMALL 3200

//Defining a struct for a process
typedef struct process{

int id;
int arrival;
int burst;

}processes;

void fifo(int *arrival_times, int* burst_times,int count, bool do_compare);
void sjf( int *arrival_times,int* burst_times,int count, bool do_compare);
void stcf(int *arrival_times,int* burst_times,int count, bool do_compare);

void print_menu()
{
	printf("\nMAIN MENU OPTIONS:\n");
  printf("fifo\nsjf\nstcf\ncompare\nquit\n\n");
  printf("Please enter an option\n");
}


//STCF code
//REFERENCE:  https://www.quora.com/How-do-I-write-a-C-program-to-implement-a-SRTF-Shortest-Remaining-Time-First-scheduling-algorithm-along-with-displaying-the-Gantt-chart
void stcf(int *arrival_times,int *burst_times,int count, bool do_compare)
{
	//divide the arrival and burst times to get the number of processes
	int process_count = count / HALF;
	processes p [process_count];
	int id_count = 0;

	int temp;
	int total = 0;
	int small;
	int k;

	//create an array for the processes and finish times
	int *processes = malloc(100 * sizeof(int));
	int *finish = malloc(10 * sizeof(int));

	float avg_turnaround = 0;

	for(int x = FIRST_INDEX; x <process_count; x++)
	{
	  id_count++;
	  p[x].id = id_count;
	  p[x].arrival = arrival_times[x];
	  p[x].burst = burst_times[x];
	}


	//sort the burst times
	for(int i = 0; i < process_count;i++)
	{
		//add all the bursts;
		total = total + p[i].burst;
		for(int j = i + 1; j < process_count; j++)
		{
			if(p[i].arrival > p[j].arrival)
			{
				temp = p[i].arrival;
				p[i].arrival = p[j].arrival;
				p[j].arrival = temp;

				temp = p[i].burst;
				p[i].burst = p[j].burst;
				p[j].burst = temp;
			}
		}
	}


	//loop through whole queue
	for(int i = 0; i < total;i++)
	{
		small = TEMP_SMALL;

		for(int j = 0; j < process_count;j++)
		{
			//compare the current burst and the arrival to get the smallest value;
			if((p[j].burst != 0) && (p[j].arrival <= i) && (p[j].burst < small))
			{
				small = p[j].burst;
				//store the index of j for the processes in k;
				k = j;
			}
		}

		//reduce value of burst
		p[k].burst--;
		processes[i] = k;
	}
	
	k = 0;

	for(int i =0; i < total;i++)
	{
		for (int j = 0; j < process_count; j++)
		{
			if(processes[i] == j)
			{
				//insert the current completion
				finish[j] = i;
			}
		}
	}


	for(int i = 0; i < process_count;i++)
	{
		if(!do_compare)
		{
			printf("P%d  Tcompletion: %d\n",p[i].id,finish[i] + 1);
		}

		avg_turnaround = avg_turnaround + ((finish[i] - p[i].arrival) + 1);
	}

	 printf("--------------\n");

	printf("Average Turnaround Time: %.2f\n",(avg_turnaround/process_count) );

}

void run(int *arrival_times,int *burst_times, int count)
{
	// if set to true then compare will occur
	bool is_comparing = false;
	char user_input[MAX_INPUT_CHARS];
	print_menu();
	//fgets function from notes in labs
	fgets_str_stdin(user_input, MAX_INPUT_CHARS);

	//execute while the user input is not "quit" and ignore case - strcasecmp
	//REFERENCE - https://en.wikibooks.org/wiki/C_Programming/C_Reference/nonstandard/strcasecmp
	while ((strcasecmp(user_input, "quit") != EQUIVALENT))
	{
		if (strcasecmp(user_input, "fifo") == EQUIVALENT)
		{
			printf("--------------\n");
			printf("FIFO TIMELINE:\n");
			printf("--------------\n");
			fifo(arrival_times,burst_times, count,is_comparing);
			print_menu();
		}
		else if (strcasecmp(user_input, "sjf") == EQUIVALENT)
		{
			printf("--------------\n");
			printf("SJF TIMELINE:\n");
			printf("--------------\n");
			sjf(arrival_times,burst_times,count,is_comparing);
			print_menu();
		}
		else if (strcasecmp(user_input, "stcf") == EQUIVALENT)
		{
			printf("--------------\n");
			printf("STCF TIMELINE:\n");
			printf("--------------\n");
			stcf(arrival_times,burst_times,count,is_comparing);
			print_menu();
		}
		else if (strcasecmp(user_input, "compare") == EQUIVALENT)
		{
     	printf("--------------\n");
     	printf("COMPARE:\n");
     	printf("--------------\n");
     	is_comparing = true;//set to true which will result in comparing

     	printf("\nFIFO\n");
			fifo(arrival_times,burst_times,count,is_comparing);
			printf("\nSJF\n");
     	sjf(arrival_times,burst_times,count,is_comparing);
     	printf("\nSTCF\n");
     	stcf(arrival_times,burst_times,count,is_comparing);
			is_comparing = false;
     	print_menu();
		}
		else
		{
			printf("Sorry, that is not a valid option. Please try again.\n");
		}
	//exit(0);
			fgets_str_stdin(user_input, MAX_INPUT_CHARS);
	}
	exit(0);
}

void fifo(int *arrival_times, int *burst_times, int count,bool do_compare)
{
	 int completion = 0;
	 int turnaround = 0;
	 int sum_turnaround = 0;
	 int first_turn = 0;
	 int response_time =  0;
	 int sum_response = 0;
	 int id_count = 0;
	 int process_count = count / HALF;
	 float avg_response = 0;
	 float avg_turnaround = 0;

	 processes p[process_count];

	 //iterate over processes and insert values for id,burst and arrival
	 for(int x = FIRST_INDEX; x <process_count; x++)
	 {
			id_count++;
			p[x].id = id_count;
			p[x].arrival = arrival_times[x];
			p[x].burst = burst_times[x];
	 }


	 for(int i = FIRST_INDEX; i < process_count; ++i)
	 {
    	first_turn = completion;
    	completion = p[i].burst + first_turn;//add the current burst is added to the previous values i the queue

    	turnaround = completion - p[i].arrival;

    	sum_turnaround = turnaround + sum_turnaround;

    	response_time = first_turn - p[i].arrival;
    	sum_response = response_time + sum_response;

			//if  do_compare is set to false do not display the timeline
			if(!do_compare)
			{
				printf("P%d: T = %d - T = %d \n",p[i].id,first_turn,completion);
			}
	 }

	 printf("--------------\n");

	 //calculating averages and casts int to float
	 avg_turnaround = sum_turnaround / (float) process_count;
	 avg_response= sum_response / (float) process_count;

	 printf("Average Response Time: %.2f\n",avg_response);
	 printf("Average Turnaround Time: %.2f\n",avg_turnaround);

}

void sjf( int *arrival_times,int* burst_times,int count,bool do_compare)
{
	int completion = 0;
	int tmp_arrival;
	int process_count = count / HALF;
	processes p [process_count];
	int tmp;
	int id_count = 0;
	int first_turn = 0;
	int  tmp_pos;
	int turnaround = 0;
	int sum_turnaround = 0;
	int sum_response = 0;
	int response_time = 0;
	float avg_response = 0;
	float avg_turnaround = 0;

	
	for(int x = FIRST_INDEX; x <process_count; x++)
	{
		id_count++;
		p[x].id = id_count;
		p[x].arrival = arrival_times[x];
		p[x].burst = burst_times[x];
	}

	//sort the burst times Ascending Order
	//this loop is for the current processes
	for(int i = FIRST_INDEX; i < process_count; ++i)
	{
	//this loop is for the next process and comparing current value to prebious value
		for(int j = i + 1; j < process_count; ++j)
		{
			if(p[i].burst > p[j].burst)
			{
				tmp_arrival = p[i].arrival;
				tmp_pos = p[i].id;
				tmp = p[i].burst;

				p[i].arrival = p[j].arrival;
        p[i].id = p[j].id;
        p[i].burst = p[j].burst;

			  p[j].arrival = tmp_arrival;
				p[j].id = tmp_pos;
				p[j].burst = tmp;
			}
		}

		first_turn = completion;
		completion = p[i].burst + first_turn;

		turnaround = completion - p[i].arrival;

		sum_turnaround = turnaround + sum_turnaround;

		response_time = first_turn - p[i].arrival;
		sum_response = response_time + sum_response;

		if(!do_compare)
		{
			 printf("P%d: T = %d - T = %d \n",p[i].id,first_turn,completion);
		}
	}
		avg_turnaround = sum_turnaround / (float) process_count;
		avg_response = sum_response/ (float) process_count;

		printf("--------------\n");
		printf("Average Turnaround Time: %.2f\n",avg_turnaround);
		printf("Average Response Time: %.2f\n",avg_response);
}

