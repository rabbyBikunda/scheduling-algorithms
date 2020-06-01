#pragma once
void sjf( int *arrival_times,int* burst_times,int count, bool do_compare);
void fifo(int *arrival_times, int* burst_times, int count, bool do_compare);
void run(int arrival_times[],int burst_times[], int count);
void stcf( int *arrival_times,int *burst_times,int count, bool do_compare);
void print_menu();
