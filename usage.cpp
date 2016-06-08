
#include "usage.h"

void usage(char *program){ // prints help screen
  printf("Usage: %s -m [mode - sum of the following numbers: %d-TIMEGAIN, %d-THROUGHPUT, %d-FCFS] -k [CPU to DFE workload ratio: 0..k] -i [iterations]\n", program, TIMEGAIN, THROUGHPUT, FCFS);
  printf("Additional options:\n"
         "-h -?; shows this help screen\n"
         "-s; prints summary of each iteration\n"
         "-g; prints output for gnuplot\n"
         "-e; prints example scheduling\n"
         "-v; verbose mode\n"
         "-s [for examining details of the scheduler: needs a number - how many current schedules to print]\n");
  printf("Example: %s -m 7 -k 10 -i 10\n", program);
  exit(1);
}

void parseCommandLineOptions(int argc, char **argv, int &mode){   //* Parse command line options
  int i = 1; // current argument
  if(argc<2)
    usage(argv[0]);
  while(i<argc){
    if(argv[i][0]=='-')
      switch (argv[i][1]){
        case '?':
        case 'h':
          usage(argv[0]); // shows help screen
          break;
        case 't':
          mode |= TIMEGAIN; // scheduling mode that maximizes the difference in execution time using the CPU and the dataflow hardware
          break;
        case 'r':
          mode |= THROUGHPUT;  // scheduling mode that maximizes the ratio of execution time using the CPU and the dataflow hardware
          break;
        case 'f':
          mode |= FCFS;  // First Come First Serve scheduling mode
          break;
        case 'm':
          i++;
          if(i==argc) 
            usage(argv[0]);
          mode = atoi(argv[i]); // user might input the mode in the form -m <number>,
                                // where each of lowest three bits represents a mode (0-TIMEGAIN, 1-THROUGHPUT, 2-FCFS)
          break;
        case 'k':
          i++;
          if(i==argc) 
            usage(argv[0]);
          MAXK = atoi(argv[i]); // maximal ratio between amount of CPU jobs and amount of dataflow hardware jobs
          break;
        case 'i':
          i++;
          if(i==argc) 
            usage(argv[0]);
          MAXITERATIONS = atoi(argv[i]); // maximum number of iterations
          if(MAXITERATIONS > 100)
            MAXITERATIONS = 100;
          break;
        case 'g':
          GNUPLOT = 1; // for printing output that is used by gnuplot for drawing graphs
          SUMMARY = 0;
          VERBOSE = 0;
          break;
        case 'e':
          EXAMPLE = 1; // prints a scheduling example
          break;
        case 'v':
          VERBOSE = 1; // detailed printing
          break;
        case 's':
          i++;
          if(i==argc) 
            usage(argv[0]);
          PRINT_DFEs = atoi(argv[i]); // for examining details of the scheduler: how many current schedules to print
          break;          
        default:
          printf("Unexpected argument: -%c\n", argv[i][1]);
          usage(argv[0]);
          break;
      }
    i++;
  }
}
