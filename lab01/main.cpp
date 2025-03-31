#include <iostream>
#include "zadanie.h"
#include "problem.h"
#include <string>

#define FILE_NAME "data/SCHRAGE3.dat"

int main() {
    problem problem;
    const std::string fileName = FILE_NAME;

    if (!problem.loadFile(fileName) == 0) {
        std::cerr << "Error loading file " << fileName << std::endl;
        return 1;
    }


    problem.sortByQj(problem.zadania);
    problem.showSequence();
    std::cout<<"Time by qj: "<<problem.getTime()<<std::endl;


    problem.sortByRj(problem.zadania);
    problem.showSequence();
    std::cout<<"Time by rj: "<<problem.getTime()<<std::endl;


    problem.sortSCHRAGE();
    problem.showSequence();
    std::cout<<"Time by SCHRAGE: "<<problem.getTime()<<std::endl;

    return 0;
}