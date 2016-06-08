
/*
Scheduling algorithm:

Input:
  n jobs that are currently available for scheduling,
Chooses up to MAX_SCHED_JOBS jobs to schedule.
After rescheduleAfterJobs jobs are ran, schedules available jobs.

*/

#ifndef _SCHED_CPP_
#define _SCHED_CPP_

#include <vector>
#include <deque>

#define MAX_SCHED_JOBS 5

// Avalilable scoring modes:
#define TIMEGAIN 1
#define THROUGHPUT 2
#define FCFS 4

int PRINT_DFEs = 0; // how many potential schedules should be printed
int printed = 0;  // how many currentSchedule-s are printed

std::vector<Job*> bestSchedule;
std::vector<int> bestScheduleFPGAs;

void printSchedule(std::vector<Job*> currentSchedule, char *textMessage, double currentScore);

// Checks if there is enough place on a FPGA image to place another job, without extending tDFEmax
int cantFit(std::vector<Job*> jobs, int sumPercentageDFEs, int sumPercentagePCIe, int sumMemDFEs, int tDFEmax);

void schedJobs(int mode,
               std::vector<Job*> jobs,
               std::vector<Job*> currentSchedule,
               double currentScore, double &bestScore, 
               int nFPGAimage, // current FPGA image where adding new jobs is tried
               double factor);

#endif
