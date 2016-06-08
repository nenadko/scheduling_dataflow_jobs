
#ifndef _MAIN_CPP_
#define _MAIN_CPP_

#include <stdio.h>
#include <vector>
#include <ctime>
#include "job.cpp"  // defines the job class
#include "init.cpp"  // initializes jobs
#include "sched.cpp"  // scheduling algorithm
#include "usage.cpp"


void example(){ // prints an example schedule
  std::vector<Job*> jobs, currentSchedule;
  double bestScore;
  double elapsed_secs;

  initSpecifiedJobs(&jobs); // Example jobs
  printJobs(jobs, const_cast<char *>("All jobs"));
    
  bestScore = 0;
  currentSchedule.clear();
  bestSchedule.clear();

  // Schedule and measure time
  clock_t begin = clock();
  schedJobs(TIMEGAIN, jobs, currentSchedule, 0, bestScore, 1, 1.0); // TIMEGAIN or THROUGHPUT or FCFS, score, bestScore, nFPGAimage, factor
  int ind = 0; for(auto it: bestScheduleFPGAs) bestSchedule[ind++]->_FPGAimage = it;
  clock_t end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  // Print results
  printf("Duration: %lf\n\n", elapsed_secs);
  printJobs(bestSchedule, const_cast<char *>("Best schedule"), bestScheduleFPGAs);  
  printf("bestScore = %2.2lf\n", bestScore);
  
  for(auto it : jobs)
    free(it);
}


int main(int argc, char **argv) {
  std::vector<Job*> jobs, currentSchedule;
  double bestScore;
  int i, j;
  srand (time(NULL));
  int mode = TIMEGAIN; 

  parseCommandLineOptions(argc, argv, mode);
  
  if(VERBOSE){
    printf("VERBOSE = %d\n", VERBOSE);
    printf("THROUGHPUT = %d\n", THROUGHPUT);
    printf("MAXK = %d\n", MAXK);
    printf("MAXITERATIONS = %d\n", MAXITERATIONS);
  }
  
  if(EXAMPLE)
    example();

  //* Simulate multiple FPGA images
  std::vector<Job*> jobs_vector[100];
  int tCPU[100]; // tCPU for FPGA images
  int tDFE[100]; // tDFE for FPGA images
  int percentage_maxeler; // percentage of streaming (DFE) jobs
  int tCPUjobs; // how long will eventually CPU be working on jobs scheduled to it
  int tCPUtotal, tDFEtotal, tGainTotal, 
      tCPUforAllNeeded; // time needed for the CPU to process all jobs
  
  // Init all jobs
  int tCPUforAllDFEjobs = 0;
  int memCPUforAllDFEjobs = 0;
  for(int iter = 0;iter<MAXITERATIONS;iter++){
    for(j=0;j<MAX_SCHED_JOBS;j++){
      addRandomJob(&jobs_vector[iter]); // Random jobs
//      addRandomJobMem(&jobs_vector[iter]); // Random jobs, assuming that the memory is the bottleneck.
    }
    for(auto it: jobs_vector[iter]){
      tCPUforAllDFEjobs+=it->_tCPU;
      memCPUforAllDFEjobs+=it->_memCPU;
		}
		if(VERBOSE)
      printJobs(jobs_vector[iter], const_cast<char *>("All jobs"));
  }
  if(VERBOSE){
    printf("tCPUforAllDFEjobs = %d\n", tCPUforAllDFEjobs);
    printf("memCPUforAllDFEjobs = %d\n", memCPUforAllDFEjobs);
	}
	
  // For diferent modes
  for(int iterMode = 1; iterMode <= 4; iterMode<<=1) if(iterMode & mode){
    if(!GNUPLOT)
      switch(iterMode){
        case TIMEGAIN: printf("\nTIMEGAIN\n"); break;
        case THROUGHPUT: printf("\nTHROUGHPUT\n"); break;
        case FCFS: printf("\nFCFS\n"); break;
      }
    tCPUtotal = 0;
    tDFEtotal = 0;
    tGainTotal = 0;
    tCPUjobs = 0;
    tCPUforAllNeeded = 0;

    // For different CPU workload
    for(int k = 0; k<MAXK; k++){ // k<MAXK; k: 0 - no CPU jobs, 2 - equal workload on CPU and DFE
      // Iterate iterations times
      for(int iter = 0;iter<MAXITERATIONS;iter++){ // iter<MAXITERATIONS; Repeat scheduling
        if(VERBOSE) 
          printJobs(jobs_vector[iter], const_cast<char *>("All jobs"));
        // Reset schedule
        bestScore = 0;
        currentSchedule.clear();
        bestSchedule.clear();
        bestScheduleFPGAs.clear();
       
        // Add CPU jobs
        tCPUjobs += k*140; // average time needed for the DFE to execute a job is 280
        tCPUforAllNeeded = tCPUforAllDFEjobs + tCPUjobs;

        if(iterMode == FCFS){
          bestSchedule = jobs_vector[iter];
          int sumPercentageDFEs = 0;
          int sumPercentagePCIe = 0;
          int sumTInitDFEs = 0;
          int sumMemDFEs = 0;
          int ind = 0; for(auto it: bestScheduleFPGAs) bestSchedule[ind++]->_FPGAimage = it;
        }else
          schedJobs(iterMode, jobs_vector[iter], currentSchedule, 0, bestScore, 1, 1.0); // mode, job vector, empty schedule, score, bestScore, nFPGAimage, factor
        int ind = 0; for(auto it: bestScheduleFPGAs) bestSchedule[ind++]->_FPGAimage = it; // updating FPGA images numbers for jobs from the best schedule
        if(VERBOSE){
          printJobs(bestSchedule, const_cast<char *>("Best schedule"));
          printf("bestScore = %2.2lf\n", bestScore);
        }

        // Statistics
        for(j = 0;j<100;j++){
          tCPU[j] = 0;
          tDFE[j] = 0;
        }
        for (auto cii : bestSchedule){
          tCPU[cii->_FPGAimage] += cii->_tCPU;
          if(cii->_tDFE > tDFE[cii->_FPGAimage])
            tDFE[cii->_FPGAimage] = cii->_tDFE;
        }
        for(int j = 1; j<MAX_SCHED_JOBS; j++){ // per FPGA image
          tCPUtotal += tCPU[j];
          tDFEtotal += tDFE[j];
        }
        if(VERBOSE)
          printf("tCPUjobs: %5d, tCPUtotal:%5d tDFEtotal:%5d difference:%5d accelFactor:%5lf\n", tCPUjobs, tCPUtotal, tDFEtotal, tCPUtotal-tDFEtotal, 1.0*tCPUtotal/tDFEtotal); 
        // assume all jobs are on DFE and try to put them on CPU in order to minimize the total execution time
        j = 1; // FPGA image 1;
        while( tCPU[j+1] ) j++; // now at the last image
        while( j // has more images
              && (tCPUjobs+tCPU[j] < tDFEtotal) ){ // it is better to schedule job j to the CPU
          tCPUjobs += tCPU[j]; // move the job from the best schedule to the CPU
          tDFEtotal-= tDFE[j];
          tCPUtotal -= tCPU[j];
          j--;
        }
        if(VERBOSE)
          printf("Iter: %2d - tCPUjobs: %5d | tDFEjobs: %5d\n", iter, tCPUjobs, tDFEtotal); // per iteration
      }
      
      // Summary statistics
      int max = tCPUjobs > tDFEtotal ? tCPUjobs : tDFEtotal;
      if(SUMMARY)
        printf("k = %2d: tCPUforAllNeeded: %5d, tCPUjobs: %5d | tDFEjobs: %5d, %5lf\n", k, tCPUforAllNeeded, tCPUjobs, tDFEtotal, 1.0*tCPUforAllNeeded/max);
      if(GNUPLOT)
        printf("%2.1f %lf\n", k*140.0/280, 1.0*tCPUforAllNeeded/max); // Total acceleration comparing to the CPU only
    }
  }
  for(int iter = 0;iter<MAXITERATIONS;iter++)
    for(auto it : jobs_vector[iter])
      free(it);
  return 0;
}

#endif

