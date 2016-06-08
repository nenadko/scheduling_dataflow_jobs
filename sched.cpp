
/*
Scheduling algorithm:

Input:
  n jobs that are currently available for scheduling,
Chooses up to MAX_SCHED_JOBS jobs to schedule.
After rescheduleAfterJobs jobs are ran, schedules available jobs.

*/

#include "sched.h"

void printSchedule(std::vector<Job*> currentSchedule, char *textMessage, double currentScore){
  char label[100];
  printed++;
  snprintf(label, sizeof(label), "%s, score = %2.2lf", textMessage, currentScore);
  printJobs(currentSchedule, label);
}

// Checks if there is enough place on a FPGA image to place another job, without extending tDFEmax
int cantFit(std::vector<Job*> jobs, int sumPercentageDFEs, int sumPercentagePCIe, int sumMemDFEs, int tDFEmax){
  for(auto &it : jobs)
    if( (it->notUsed()) &&
        (sumPercentageDFEs + it->_percentageDFEs <= 100) &&
        (sumPercentagePCIe + it->_percentagePCIe <= 100) &&
        (sumMemDFEs + it->_memDFEs <= 100) &&
        (tDFEmax > it->_tDFE) )
      return 1; // can fit
  return 0; // can't fit
}

void schedJobs(int mode,
               std::vector<Job*> jobs,
               std::vector<Job*> currentSchedule,
               double currentScore, double &bestScore, 
               int nFPGAimage, // current FPGA image where adding new jobs is tried
               double factor) { // multiply score for this FPGA image by factor, e.g., *1/1.1

  // Assigns the best score of possible combinations of currentSchedule jobs on FPGA images
  double score1 = 0; // current FPGA image score
  int sumPercentageDFEs = 0;
  int sumPercentagePCIe = 0;
  int sumTInitDFEs = 0;
  int sumMemDFEs = 0;
  int tDFEmax = 0;
  int sumTDFE = 0;
  int sumTCPU = 0;

  if(printed < PRINT_DFEs)
    printSchedule(currentSchedule, const_cast<char *>("currentSchedule"), currentScore);

  if (currentScore > bestScore) {
    bestScore = currentScore;
    bestSchedule = currentSchedule;
    bestScheduleFPGAs.clear();
    for (auto &it : currentSchedule)
      bestScheduleFPGAs.push_back(it->_FPGAimage);
  }

  if(currentSchedule.size() == MAX_SCHED_JOBS) return;

  // Calculate occupation of the nFPGAimage
  for (auto &it : currentSchedule)
    if( it->_FPGAimage==nFPGAimage )
      it->sum(sumPercentageDFEs, sumPercentagePCIe, sumTInitDFEs, sumMemDFEs, sumTDFE, sumTCPU, tDFEmax);
  
  // Adding each job separately to the currentSchedule
  for (auto &it : jobs) { // for each job
    if( it->add(&currentSchedule, sumPercentageDFEs, sumPercentagePCIe, sumMemDFEs, sumTDFE, sumTCPU, sumTInitDFEs, tDFEmax, nFPGAimage) ){
      score1 += it->score(); // increasing by the it job score

      double scoreForMode;
      if(mode == THROUGHPUT)
        scoreForMode = 1.0*sumTCPU/tDFEmax;
      else // (mode == TIMEGAIN) || (mode == FCFS)
        scoreForMode = sumTCPU-tDFEmax;

      // If no other job can fit on nFPGAimage
      if(cantFit(jobs, sumPercentageDFEs, sumPercentagePCIe, sumMemDFEs, tDFEmax))
        // Schedule the rest of jobs on nFPGAimage+1
        schedJobs(mode, jobs, currentSchedule, currentScore + factor*(score1 + scoreForMode), bestScore, nFPGAimage+1, factor/1.1);
      else
        // Schedule on the same FPGA image
        schedJobs(mode, jobs, currentSchedule, currentScore + factor*score1, bestScore, nFPGAimage, factor);
      
      if(mode!=FCFS)
        it->remove(&currentSchedule, sumPercentageDFEs, sumPercentagePCIe, sumMemDFEs, sumTDFE, sumTCPU, sumTInitDFEs, tDFEmax, nFPGAimage);
    }else{
      if(mode==FCFS) 
        // Schedule the rest of jobs on nFPGAimage+1
        schedJobs(mode, jobs, currentSchedule, currentScore + 1, bestScore, nFPGAimage+1, factor); 
    }
  }
}

