
void addRandomJobMem(std::vector<Job*> *jobs) {
  int alg, t;
  alg = rand()%5;
  t = rand()%100+50;
  switch(alg){
    case 0:
      jobs->push_back(
        new Job(1,  // id
                "Gross-Pitaevskii", // name
                1,  // nCpu
                50,  // percentageDFE
                0,  // percentagePCIe
                t/10*82,  // tCPU            // x 8.2
                t,  // tDFE
                0,  // tInitDFE
                0,  // tRest
                4,  // memDFE
                20,  // memCPU
                1));  // memRest
      break;
    case 1:
      jobs->push_back(
        new Job(2,  // id
                "Odd-even merge network sort", // name
                1,  // nCpu
                50,  // percentageDFE
                100,  // percentagePCIe
                t*100/6,  // tCPU            // x 100
                t/6,  // tDFE
                0,  // tInitDFE
                0,  // tRest
                4,  // memDFE
                20,  // memCPU
                1));  // memRest
      break;
    case 2:
      jobs->push_back(
        new Job(3,  // id
                "Lattice-Boltzmann", // name
                1,  // nCpu
                20,  // percentageDFE
                0,  // percentagePCIe
                t/10*17,  // tCPU            // x 17
                t/10,  // tDFE
                0,  // tInitDFE
                0,  // tRest
                4,  // memDFE
                20,  // memCPU
                2));  // memRest
      break;
    case 3:
      jobs->push_back(
        new Job(4,  // id
                "Spherical code design", // name
                1,  // nCpu
                40,  // percentageDFE
                0,  // percentagePCIe
                t/2*18,  // tCPU            // x 18
                t/2,  // tDFE
                0,  // tInitDFE
                0,  // tRest
                8,  // memDFE
                40,  // memCPU
                1));  // memRest
      break;
    case 4:
      jobs->push_back(
        new Job(5,  // id
                "RSA", // name
                1,  // nCpu
                50,  // percentageDFE
                100,  // percentagePCIe
                t*1.25,  // tCPU            // x 1.25
                t,  // tDFE
                0,  // tInitDFE
                0,  // tRest
                8,  // memDFE
                40,  // memCPU
                1));  // memRest
      break;
  }
}

void addRandomJob(std::vector<Job*> *jobs) {
  int alg, t;
  alg = rand()%5;
  t = rand()%100+50;
  switch(alg){
    case 0:
      jobs->push_back(
        new Job(1,  // id
                "Gross-Pitaevskii", // name
                1,  // nCpu
                50,  // percentageDFE
                0,  // percentagePCIe
                t/10*82,  // tCPU            // x 8.2
                t,  // tDFE
                0,  // tInitDFE
                0,  // tRest
                4,  // memDFE
                20,  // memCPU
                1));  // memRest
      break;
    case 1:
      jobs->push_back(
        new Job(2,  // id
                "Odd-even merge network sort", // name
                1,  // nCpu
                50,  // percentageDFE
                100,  // percentagePCIe
                t*100/6,  // tCPU            // x 100
                t/6,  // tDFE
                0,  // tInitDFE
                0,  // tRest
                4,  // memDFE
                20,  // memCPU
                1));  // memRest
      break;
    case 2:
      jobs->push_back(
        new Job(3,  // id
                "Lattice-Boltzmann", // name
                1,  // nCpu
                20,  // percentageDFE
                0,  // percentagePCIe
                t/10*17,  // tCPU            // x 17
                t/10,  // tDFE
                0,  // tInitDFE
                0,  // tRest
                1,  // memDFE
                5,  // memCPU
                2));  // memRest
      break;
    case 3:
      jobs->push_back(
        new Job(4,  // id
                "Spherical code design", // name
                1,  // nCpu
                40,  // percentageDFE
                0,  // percentagePCIe
                t/2*18,  // tCPU            // x 18
                t/2,  // tDFE
                0,  // tInitDFE
                0,  // tRest
                2,  // memDFE
                10,  // memCPU
                1));  // memRest
      break;
    case 4:
      jobs->push_back(
        new Job(5,  // id
                "RSA", // name
                1,  // nCpu
                50,  // percentageDFE
                100,  // percentagePCIe
                t*1.25,  // tCPU            // x 1.25
                t,  // tDFE
                0,  // tInitDFE
                0,  // tRest
                2,  // memDFE
                10,  // memCPU
                1));  // memRest
      break;
  }
}

void initSpecifiedJobs(std::vector<Job*> *jobs) {
  jobs->push_back(
    new Job(1,  // id
            "Gross-Pitaevskii", // name
            1,  // nCpu
            50,  // percentageDFE
            0,  // percentagePCIe
            820,  // tCPU            // x 8.2
            100,  // tDFE
            0,  // tInitDFE
            0,  // tRest
            20,  // memDFE
            20,  // memCPU
            1));  // memRest
  jobs->push_back(
    new Job(2,  // id
            "Odd-even merge network sort", // name
            1,  // nCpu
            50,  // percentageDFE
            100,  // percentagePCIe
            1000,  // tCPU            // x 100
            10,  // tDFE
            0,  // tInitDFE
            0,  // tRest
            20,  // memDFE
            20,  // memCPU
            1));  // memRest
  jobs->push_back(
    new Job(3,  // id
            "Lattice-Boltzmann", // name
            1,  // nCpu
            20,  // percentageDFE
            0,  // percentagePCIe
            170,  // tCPU            // x 17
            10,  // tDFE
            0,  // tInitDFE
            0,  // tRest
            1,  // memDFE
            5,  // memCPU
            2));  // memRest
  jobs->push_back(
    new Job(4,  // id
            "Spherical code design", // name
            1,  // nCpu
            40,  // percentageDFE
            0,  // percentagePCIe
            1800,  // tCPU            // x 18
            100,  // tDFE
            0,  // tInitDFE
            0,  // tRest
            2,  // memDFE
            10,  // memCPU
            1));  // memRest
  jobs->push_back(
    new Job(5,  // id
            "RSA", // name
            1,  // nCpu
            50,  // percentageDFE
            100,  // percentagePCIe
            250,  // tCPU            // x 1.25
            200,  // tDFE
            0,  // tInitDFE
            0,  // tRest
            2,  // memDFE
            10,  // memCPU
            1));  // memRest

  jobs->push_back(
    new Job(6,  // id
            "Gross-Pitaevskii", // name
            1,  // nCpu
            50,  // percentageDFE
            0,  // percentagePCIe
            820,  // tCPU            // x 8.2
            100,  // tDFE
            0,  // tInitDFE
            0,  // tRest
            20,  // memDFE
            20,  // memCPU
            1));  // memRest
  jobs->push_back(
    new Job(7,  // id
            "Odd-even merge network sort", // name
            1,  // nCpu
            50,  // percentageDFE
            100,  // percentagePCIe
            1000,  // tCPU            // x 100
            10,  // tDFE
            0,  // tInitDFE
            0,  // tRest
            20,  // memDFE
            20,  // memCPU
            1));  // memRest
  jobs->push_back(
    new Job(8,  // id
            "Lattice-Boltzmann", // name
            1,  // nCpu
            20,  // percentageDFE
            0,  // percentagePCIe
            1700,  // tCPU            // x 17
            100,  // tDFE
            0,  // tInitDFE
            0,  // tRest
            1,  // memDFE
            5,  // memCPU
            2));  // memRest
  jobs->push_back(
    new Job(9,  // id
            "Spherical code design", // name
            1,  // nCpu
            40,  // percentageDFE
            0,  // percentagePCIe
            180,  // tCPU            // x 18
            10,  // tDFE
            0,  // tInitDFE
            0,  // tRest
            2,  // memDFE
            10,  // memCPU
            1));  // memRest
  jobs->push_back(
    new Job(10,  // id
            "RSA", // name
            1,  // nCpu
            50,  // percentageDFE
            100,  // percentagePCIe
            25,  // tCPU            // x 1.25
            20,  // tDFE
            0,  // tInitDFE
            0,  // tRest
            2,  // memDFE
            10,  // memCPU
            1));  // memRest
}

