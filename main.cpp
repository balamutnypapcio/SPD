#include <iostream>
#include "zadanie.h"
#include "problem.h"
#include <string>

#define FILE_NAME "data/SCHRAGE1.dat"

int main() {
    problem problem;
    const std::string fileName = FILE_NAME;

    if (!problem.loadFile(fileName) == 0) {
        std::cerr << "Error loading file " << fileName << std::endl;
        return 1;
    }
    problem.sortByRj();
    problem.showSequence();
    std::cout<<"Time by rj: "<<problem.getTime()<<std::endl;

    problem.sortByQj();
    problem.showSequence();
    std::cout<<"Time by qj: "<<problem.getTime()<<std::endl;


    return 0;
}