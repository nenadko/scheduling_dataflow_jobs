
#ifndef _JOB_CPP_
#define _JOB_CPP_

#include <vector>
#include <string>

class Job {
  public:
  Job(int id,
      std::string name,
      int nCPU,
      int percentageDFEs,
      int percentagePCIe,
      int tCPU,
      int tDFE,
      int tInitDFEs,
      int tRest,
      int memDFEs,
      int memCPU,
      int memRest):
    _id(id),
    _name(name),
    _nCPU(nCPU),
    _percentageDFEs(percentageDFEs),
    _percentagePCIe(percentagePCIe),
    _tCPU(tCPU),
    _tDFE(tDFE),
    _tInitDFEs(tInitDFEs),
    _tRest(tRest),
    _memDFEs(memDFEs),
    _memCPU(memCPU),
    _memRest(memRest),
    _used(0),
    _FPGAimage(0){}

  void print();

  void print(int position);

  int notUsed();

  double score();

  // Tries to add job to the FPGA image, and updates FPGA image parameters; returns if it is possible
  int add(std::vector<Job*> *currentSchedule, int &sumPercentageDFEs, int &sumPercentagePCIe, int &sumMemDFEs, int &sumTDFE, int &sumTCPU, int &sumTInitDFEs, int &tDFEmax, int nFPGAimage);
	
  // removes the job from the FPGA image and updates FPGA image parameters
  int remove(std::vector<Job*> *currentSchedule, int &sumPercentageDFEs, int &sumPercentagePCIe, int &sumMemDFEs, int &sumTDFE, int &sumTCPU, int &sumTInitDFEs, int &tDFEmax, int nFPGAimage);
	
  void sum(int &sumPercentageDFEs, int &sumPercentagePCIe, int &sumTInitDFEs, int &sumMemDFEs, int &sumTDFE, int &sumTCPU, int &tDFEmax);

	
  int _id;  // id of the job
  std::string _name; // name of job
  int _nCPU;  // To which Cpu does the job belong
  int _percentageDFEs;  // Maxeler card percentage needed
  int _percentagePCIe;  // PCIe percentage needed
  int _tCPU;  // Time needed for CPU to execute "Maxeler" job
  int _tDFE;  // Time needed for Maxeler to execute the job
  int _tInitDFEs;  // Time needed to init Maxeler card with appropriate max file
  int _tRest;  // Time needed for CPU to do non-Maxeler related job
  int _memDFEs;  // Maxeler memory needed
  int _memCPU;  // CPU memory needed to execute "Maxeler" job
  int _memRest;  // Memory needed for non-Maxeler related job
  int _used;  // is this job in the schedule
  int _FPGAimage; // on which FPGA image is job scheduled
};

#endif
