//
// Created by jakub on 30.03.2025.
//

#ifndef PROBLEM_H
#define PROBLEM_H
#include <vector>
#include <fstream>
#include <iostream>
#include "zadanie.h"

class problem {
public:
    std::vector<zadanie> zadania;

    int loadFile(const std::string& fileName);
    void sortByRj(std::vector<zadanie>& zad);
    void sortByQj(std::vector<zadanie>& zad);
    void sortByExhaustiveSearch();
    void sortMyMethode(); // rj+pj+qj
    void sortSCHRAGE();
    void sortSchrageEliminaiton();
    void showSequence() const;
    int getTime() const;
};



#endif //PROBLEM_H
