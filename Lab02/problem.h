//
// Created by jakub on 30.03.2025.
//

#ifndef PROBLEM_H
#define PROBLEM_H
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <climits>
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
    std::pair<std::vector<zadanie>, std::vector<zadanie>> sortTwoMachineLSA(std::vector<zadanie>& zad);
    std::pair<std::vector<zadanie>, std::vector<zadanie>> sortTwoMachineLPT(std::vector<zadanie>& zad);
    std::pair<std::vector<zadanie>, std::vector<zadanie>> sortTwoMachinePD(std::vector<zadanie>& zad);
    std::pair<std::vector<zadanie>, std::vector<zadanie>> sortTwoMachineExhaustive(std::vector<zadanie>& zad);
    void showSequence() const;
    int getTime() const;
    int getTimeTwoMachines(const std::vector<zadanie>& m1, const std::vector<zadanie>& m2) const;
};



#endif //PROBLEM_H
