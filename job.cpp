
#include "job.h"

void Job::print() {
  printf("nCPU:%2d, ", _nCPU);
  printf("%2d, ", _id);
  printf("%%DFEs:%3d, ", _percentageDFEs);
  printf("%%PCIe:%3d, ", _percentagePCIe);
  printf("tCPU:%5d, ", _tCPU);
  printf("tDFE:%5d, ", _tDFE);
  printf("tInitDFEs:%5d, ", _tInitDFEs);
  printf("tRest:%5d, ", _tRest);
  printf("memDFEs:%5d, ", _memDFEs);
  printf("memCPU:%5d, ", _memCPU);
  printf("memRest:%5d,", _memRest);
  printf("used:%3d", _used);
  printf("FPGAimage:%2d, ", _FPGAimage);
  printf("%s, ", _name.c_str());
  printf("\n");
}

void Job::print(int position) {
  printf("nCPU:%2d, ", _nCPU);
  printf("%2d, ", _id);
  printf("%%DFEs:%3d, ", _percentageDFEs);
  printf("%%PCIe:%3d, ", _percentagePCIe);
  printf("tCPU:%5d, ", _tCPU);
  printf("tDFE:%5d, ", _tDFE);
  printf("tInitDFEs:%5d, ", _tInitDFEs);
  printf("tRest:%5d, ", _tRest);
  printf("memDFEs:%5d, ", _memDFEs);
  printf("memCPU:%5d, ", _memCPU);
  printf("memRest:%5d,", _memRest);
  printf("used:%3d", _used);
  printf("FPGAimage:%2d, ", position); // _FPGAimage
  printf("%s, ", _name.c_str());
  printf("\n");
}

int Job::notUsed() {
  // is the job included in the schedule
  return !_used;
}

double Job::score() {
  // how much does it worth to run this task on FPGA
  if (_percentageDFEs == 0) return 1;
  if (_tCPU == 0) return 0;
  return static_cast<double>(_tCPU) 
         / (_tDFE*(1-static_cast<double>(_tInitDFEs)/_tCPU) + _tInitDFEs)
         / _percentageDFEs;
}

// Tries to add job to the FPGA image, and updates FPGA image parameters; returns if it is possible
int Job::add(std::vector<Job*> *currentSchedule, int &sumPercentageDFEs, int &sumPercentagePCIe, int &sumMemDFEs, int &sumTDFE, int &sumTCPU, int &sumTInitDFEs, int &tDFEmax, int nFPGAimage){
  // If enough place on current FPGA image
  if(_used) return 0; // this job is already in the schedule
  if( (sumPercentageDFEs + _percentageDFEs > 100) ||
      (sumPercentagePCIe + _percentagePCIe > 100) ||
      (sumMemDFEs + _memDFEs > 100) )
    return 0; // not possible

    _used = 1;
    sumPercentageDFEs += _percentageDFEs;
    sumPercentagePCIe += _percentagePCIe;
    sumMemDFEs += _memDFEs;
    sumTDFE += _tDFE;
    sumTCPU += _tCPU;
    sumTInitDFEs += _tInitDFEs;
    _FPGAimage = nFPGAimage;
    currentSchedule->push_back(this); // add it
    if(_tDFE > tDFEmax)
      tDFEmax = _tDFE;
    return 1; // possible
}

// removes the job from the FPGA image and updates FPGA image parameters
int Job::remove(std::vector<Job*> *currentSchedule, int &sumPercentageDFEs, int &sumPercentagePCIe, int &sumMemDFEs, int &sumTDFE, int &sumTCPU, int &sumTInitDFEs, int &tDFEmax, int nFPGAimage){
  _used = 0;
  sumPercentageDFEs -= _percentageDFEs;
  sumPercentagePCIe -= _percentagePCIe;
  sumMemDFEs -= _memDFEs;
  sumTDFE -= _tDFE;
  sumTCPU -= _tCPU;
  sumTInitDFEs -= _tInitDFEs;
  currentSchedule->pop_back();
  tDFEmax = 0;
  for(auto &it : *currentSchedule)
    if( (it->_FPGAimage == nFPGAimage) &&
        (it->_tDFE > tDFEmax) )
      tDFEmax = it->_tDFE;
  return 1; // possible
}

void Job::sum(int &sumPercentageDFEs, int &sumPercentagePCIe, int &sumTInitDFEs, int &sumMemDFEs, int &sumTDFE, int &sumTCPU, int &tDFEmax){
  sumPercentageDFEs += _percentageDFEs;
  sumPercentagePCIe += _percentagePCIe;
  sumTInitDFEs += _tInitDFEs;
  sumMemDFEs += _memDFEs;
  sumTDFE += _tDFE;
  sumTCPU += _tCPU;
  if(_tDFE > tDFEmax)
    tDFEmax = _tDFE;
}
  
void printJobs(std::vector<Job*> jobs, char *comment) {
  std::vector<Job*> cii;
  if (comment)
    printf("%s:\n", comment);
  else
    printf("All jobs:\n");
  for (auto cii = jobs.begin(); cii != jobs.end(); cii++)
    (*cii)->print();
}

// Prints jobs using bestPositions instead of _FPGAimage from each job
void printJobs(std::vector<Job*> jobs, char *comment, std::vector<int> bestPositions) {
  std::vector<Job*> cii;
  if (comment)
    printf("%s:\n", comment);
  else
    printf("All jobs:\n");
  int i = 0;
  for (auto cii = jobs.begin(); cii != jobs.end(); cii++)
    (*cii)->print(bestPositions[i++]);
}

