#include <iostream>
#include "zadanie.h"
#include "problem.h"
#include <string>
#include <chrono>
#include <numeric>
#include <vector>


int main() {

    std::vector<int> timeCqj;

    std::vector<double> timeTqj;


    const char* FILE_NAMES[] = {
        "/home/mikolaj/studia/SPD/Lab02/data/SCHRAGE1.dat"
    };
    for(int k=0; k<1; k++) {
        for (int i = 0; i < 1; i++) {
            problem problem;
            const std::string fileName = FILE_NAMES[i];

            if (!problem.loadFile(fileName) == 0) {
                std::cerr << "Error loading file " << fileName << std::endl;
                return 1;
            }
            std::cout<<"--------------------------------------------------------"<<std::endl;
            std::cout << std::endl;
            std::cout<<"File: "<<FILE_NAMES[i]<<std::endl;
            std::cout << std::endl;
            std::cout<<"--------------------------------------------------------"<<std::endl;


            // Timing for sortByQj
            auto start_qj = std::chrono::high_resolution_clock::now();
            problem.sortByQj(problem.zadania);
            auto end_qj = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> qj_time = end_qj - start_qj;
            problem.showSequence();
            std::cout<<"Time by qj: "<<problem.getTime()<<std::endl;
            std::cout << "sortByQj execution time: " << qj_time.count() << " ms" << std::endl;

            timeCqj.push_back(problem.getTime());
            timeTqj.push_back(qj_time.count());


            //Timing for LSA Two machines
            auto [machine1, machine2] = problem.sortTwoMachineLSA(problem.zadania);
            problem.showSequence();
            std::cout<<"Time by TwoMachineLSA: "<<problem.getTimeTwoMachines(machine1, machine2)<<std::endl;


            //Timing for LPT Two Machines
            auto [machine1LPT, machine2LPT] = problem.sortTwoMachineLPT(problem.zadania);
            problem.showSequence();
            std::cout<<"Timeb by TwoMachineLPT: "<<problem.getTimeTwoMachines(machine1LPT, machine2LPT)<<std::endl;

        }
     //std::cout<<"Pętla numer: "<<k<<std::endl;
    }

    //std::cout<<"Average qj: "<< std::accumulate(timeTqj.begin(), timeTqj.end(), 0.0) / timeTqj.size() <<std::endl;
    //std::cout<<"C qj: " <<timeCqj.at(0) << std::endl;



    return 0;
}