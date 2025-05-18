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
        "/home/mikolaj/studia/SPD/repo/SPD/Lab02/data/SCHRAGE9.dat"
    };
    for(int k=0; k<1; k++) {
        for (int i = 0; i < 1; i++) {
            problem problem;
            const std::string fileName = FILE_NAMES[i];

            if (!problem.loadFile(fileName) == 0) {
                std::cerr << "Error loading file " << fileName << std::endl;
                return 1;
            }
            std::cout<<"------------------File: "<<FILE_NAMES[i]<<"------------------"<<std::endl;
            std::cout << std::endl;
            std::cout << std::endl;

            // Timing for sortByQj
            std::cout<<"------------------Sort By Qj------------------"<<std::endl;
            auto start_qj = std::chrono::high_resolution_clock::now();
            problem.sortByQj(problem.zadania);
            auto end_qj = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> qj_time = end_qj - start_qj;
            std::cout<<"Time by qj: "<<problem.getTime()<<std::endl;
            std::cout << "sortByQj execution time: " << qj_time.count() << " ms" << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;

            timeCqj.push_back(problem.getTime());
            timeTqj.push_back(qj_time.count());


            //Timing for LSA Two machines
            std::cout<<"------------------Two Machine LSA------------------"<<std::endl;
            auto start_lsa = std::chrono::high_resolution_clock::now();
            auto [machine1, machine2] = problem.sortTwoMachineLSA(problem.zadania);
            auto end_lsa = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> lsa_time = end_lsa - start_lsa;
            std::cout<<"Time by TwoMachineLSA: "<<problem.getTimeTwoMachines(machine1, machine2)<<std::endl;
            std::cout << "sortTwoMachineLSA execution time: " << lsa_time.count() << " ms" << std::endl;
            std::cout << std::endl;


            //Timing for LPT Two Machines
            std::cout<<"------------------Two Machine LPT------------------"<<std::endl;
            auto start_lpt = std::chrono::high_resolution_clock::now();
            auto [machine1LPT, machine2LPT] = problem.sortTwoMachineLPT(problem.zadania);
            auto end_lpt = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> lpt_time = end_lpt - start_lpt;
            std::cout<<"Time by TwoMachineLPT: "<<problem.getTimeTwoMachines(machine1LPT, machine2LPT)<<std::endl;
            std::cout << "sortTwoMachineLPT execution time: " << lpt_time.count() << " ms" << std::endl;
            std::cout << std::endl;


            //Timing for Dynamic Programming Two Machines
            std::cout<<"------------------Two Machine Dynamic Programming------------------"<<std::endl;
            auto start_pd = std::chrono::high_resolution_clock::now();
            auto [machine1PD, machine2PD] = problem.sortTwoMachinePD(problem.zadania);
            auto end_pd = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> pd_time = end_pd - start_pd;
            std::cout<<"Time by TwoMachinePD: "<<problem.getTimeTwoMachines(machine1PD, machine2PD)<<std::endl;
            std::cout << "sortTwoMachinePD execution time: " << pd_time.count() << " ms" << std::endl;
            std::cout << std::endl;


            //Timing for Exhaustive Search Two Machines
            std::cout<<"------------------Two Machine Exhaustive Search------------------"<<std::endl;
            auto start_ex = std::chrono::high_resolution_clock::now();
            auto [machine1EX, machine2EX] = problem.sortTwoMachineExhaustive(problem.zadania);
            auto end_ex = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> ex_time = end_ex - start_ex;
            std::cout<<"Time by TwoMachineExhaustive: "<<problem.getTimeTwoMachines(machine1EX, machine2EX)<<std::endl;
            std::cout << "sortTwoMachineExhaustive execution time: " << ex_time.count() << " ms" << std::endl;
            std::cout << std::endl;


            //Timing for PTAS Search Two Machines
            std::cout<<"------------------Two Machine PTAS Search------------------"<<std::endl;
            int deep = 8;
            auto start_ptas = std::chrono::high_resolution_clock::now();
            auto [machine1PTAS, machine2PTAS] = problem.sortTwoMachinePTAS(problem.zadania, deep);
            auto end_ptas = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> ptas_time = end_ptas - start_ptas;
            std::cout<<"Time by twoMachinePTAS: "<<problem.getTimeTwoMachines(machine1PTAS, machine2PTAS)<<std::endl;
            std::cout << "sortTwoMachinePTAS execution time: " << ptas_time.count() << " ms" << std::endl;
            std::cout << std::endl;


            //Timing for FPTAS Search Two Machines
            std::cout<<"------------------Two Machine FPTAS Search------------------"<<std::endl;
            int deepF = 8;
            auto start_fptas = std::chrono::high_resolution_clock::now();
            auto [machine1FPTAS, machine2FPTAS] = problem.sortTwoMachineFPTAS(problem.zadania, deepF);
            auto end_fptas = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> fptas_time = end_ptas - start_ptas;
            std::cout<<"Time by twoMachineFPTAS: "<<problem.getTimeTwoMachines(machine1FPTAS, machine2FPTAS)<<std::endl;
            std::cout << "sortTwoMachineFPTAS execution time: " << fptas_time.count() << " ms" << std::endl;
            std::cout << std::endl;

        }
    }

    return 0;
}