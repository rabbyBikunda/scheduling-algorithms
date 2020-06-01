#include <ctype.h>
#include <stdbool.h>

#define MIN_ARRIVAL_TIME 0
#define MIN_BURST_TIME 0

//function which determines if argument is a number
//Reference: https://stackoverflow.com/questions/29248585/c-checking-command-line-argument-is-integer-or-not
bool is_number(char number[])
{
   int i = 0;

   i = 1;
   for (; number[i] != 0; i++)
   {
    if (!isdigit(number[i]))
       return false;
   }
       return true;
}

//returns false if count for number of arguments is zero or not evenly divisble by two
bool is_count_valid(int count)
{
   if (count == 0 || count % 2 != 0)
      {
        return false;
      }

        return true;
}

//returns false if the arrival times are less than  0
bool is_arrival_valid(int arrival_times[], int count)
{
    for (int i = 0; i < count; ++i)
    {
      if(arrival_times[i] < MIN_ARRIVAL_TIME)
        {
           return false;
        }
    }

   return true;
}

bool is_burst_valid(int burst_times[], int count)
{
	for (int i = 0; i < count; ++i)
	{
		if(burst_times[i] <= MIN_BURST_TIME)
		{
			return false;
		}
	}
	return true;
}
