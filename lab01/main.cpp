#include <iostream>
#include "zadanie.h"
#include "problem.h"
#include <string>
#include <chrono>


int main() {
    const char* FILE_NAMES[] = {
        "data/SCHRAGE1.dat",
        "data/SCHRAGE2.dat",
        "data/SCHRAGE3.dat",
        "data/SCHRAGE4.dat",
        "data/SCHRAGE5.dat",
        "data/SCHRAGE6.dat",
        "data/SCHRAGE7.dat",
        "data/SCHRAGE8.dat",
        "data/SCHRAGE9.dat"
    };
    for (int i = 0; i < 9; i++) {
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
        // problem.showSequence();
        std::cout<<"Time by qj: "<<problem.getTime()<<std::endl;
        std::cout << "sortByQj execution time: " << qj_time.count() << " ms" << std::endl;

        std::cout << std::endl<< std::endl;

        // Timing for sortByRj
        auto start_rj = std::chrono::high_resolution_clock::now();
        problem.sortByRj(problem.zadania);
        auto end_rj = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> rj_time = end_rj - start_rj;
        //problem.showSequence();
        std::cout<<"Time by rj: "<<problem.getTime()<<std::endl;
        std::cout << "sortByRj execution time: " << rj_time.count() << " ms" << std::endl;

        std::cout << std::endl;

        // Timing for sortMyMethode rj+qj+pj
        auto start_rpq = std::chrono::high_resolution_clock::now();
        problem.sortMyMethode();
        auto end_rpq = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> rpq_time = end_rpq - start_rpq;
        //problem.showSequence();
        std::cout<<"Time by rj+pj+qj: "<<problem.getTime()<<std::endl;
        std::cout << "sortMyMethode execution time: " << rpq_time.count() << " ms" << std::endl;

        std::cout << std::endl;

        if (fileName == "data/SCHRAGE1.dat" || fileName == "data/SCHRAGE2.dat") {
            // Timing for exhaustive search
            auto start_exhaustive = std::chrono::high_resolution_clock::now();
            problem.sortByExhaustiveSearch();
            auto end_exhaustive = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> exhaustive_time = end_exhaustive - start_exhaustive;
            //problem.showSequence();
            std::cout << "sortByExhaustiveSearch execution time: " << exhaustive_time.count() << " ms" << std::endl;
            std::cout << "Time by Exhaustive Search: " << problem.getTime() << std::endl;


            std::cout << std::endl;
        }

        // Timing for sortSCHRAGE
        auto start_schrage = std::chrono::high_resolution_clock::now();
        problem.sortSCHRAGE();
        auto end_schrage = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> schrage_time = end_schrage - start_schrage;
        //problem.showSequence();
        std::cout << "sortSCHRAGE execution time: " << schrage_time.count() << " ms" << std::endl;
        std::cout << "Time by SCHRAGE: " << problem.getTime() << std::endl;

        std::cout << std::endl;

        // Timing for sortSCHRAGE
        auto start_schrageElimination = std::chrono::high_resolution_clock::now();
        problem.sortSchrageEliminaiton();
        auto end_schrageElimination = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> schrageElimination_time = end_schrageElimination - start_schrageElimination;
        //problem.showSequence();
        std::cout << "sortSchrageElimination execution time: " << schrageElimination_time.count() << " ms" << std::endl;
        std::cout << "Time by SchrageElimination: " << problem.getTime() << std::endl;
        std::cout << std::endl;
    }


    return 0;
}