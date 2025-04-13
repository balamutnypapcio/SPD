//
// Created by jakub on 30.03.2025.
//

#include "problem.h"


int problem::loadFile(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Nie można otworzyć pliku: " << fileName << std::endl;
        return -1;
    }

    int n;
    file >> n;
    zadania.clear();
    zadania.reserve(n);

    for (int i = 0; i < n; ++i) {
        int rj, pj, qj;
        file >> rj >> pj >> qj;
        zadania.emplace_back(rj, pj, qj);
    }

    return 0;
}

void problem::sortByRj(std::vector<zadanie> &zad) {
    std::sort(zad.begin(), zad.end(), [](const zadanie &a, const zadanie &b) {
        return a.rj < b.rj;
    });
}

void problem::sortByQj(std::vector<zadanie> &zad) {
    std::sort(zad.begin(), zad.end(), [](const zadanie &a, const zadanie &b) {
        return a.qj > b.qj;
    });
}

void problem::sortMyMethode() {
    std::sort(zadania.begin(), zadania.end(), [](const zadanie &a, const zadanie &b) {
        int scoreA = a.rj + a.pj + a.qj;
        int scoreB = b.rj + b.pj + b.qj;
        return scoreA < scoreB;
    });
}


void problem::sortByExhaustiveSearch() {
    // Make a copy of the original tasks
    std::vector<zadanie> zadaniaExhaustive = zadania;
    std::vector<zadanie> zadaniaTMP = zadania;
    int bestCmax = getTime();

    std::vector<int> indices(zadania.size());

    for (int i = 0; i < indices.size(); i++) {
        indices[i] = i;
    }

    while (std::next_permutation(indices.begin(), indices.end())) {
        for (int i = 0; i < zadania.size(); ++i) {
            zadaniaTMP[i] = zadania[indices[i]];
        }
        zadania = zadaniaTMP;
        if (getTime() < bestCmax) {
            bestCmax = getTime();
            zadaniaExhaustive = zadania;
        }
    }
    zadania = zadaniaExhaustive;
}

void problem::sortSCHRAGE() {
    sortByRj(zadania);
    std::vector<zadanie> zadaniaSCHROUD;
    int time = zadania.begin()->rj;

    while (!zadania.empty()) {
        int last = 0;
        for (int i = 0; i < zadania.size(); i++) {
            if (zadania[i].rj > time) break;
            last = i;
        }
        int biggestQj = 0;
        for (int i = 0; i < last + 1; i++) {
            if (zadania[i].qj > zadania[biggestQj].qj) {
                biggestQj = i;
            }
        }
        zadaniaSCHROUD.push_back(zadania[biggestQj]);
        time = std::max(time, zadania[biggestQj].rj) + zadania[biggestQj].pj;
        zadania.erase(zadania.begin() + biggestQj);
    }
    zadania.clear();
    zadania = zadaniaSCHROUD;
}


void problem::sortSchrageEliminaiton() {
    sortByRj(zadania);
    std::vector<zadanie> zadTMP = zadania;
    std::vector<zadanie> zadaniaShroudEl;
    int currentIndex = 0;
    int time = zadTMP.begin()->rj;

    while (!zadTMP.empty()) {
        std::vector<zadanie> zadTMPAvaible;
        for (int i = 0; i < zadTMP.size(); i++) {
            if (time + zadTMP[currentIndex].pj > zadTMP[i].rj ) {
                zadTMPAvaible.push_back(zadTMP[i]);
                if (zadTMP[currentIndex].qj >= zadTMP[i].qj) {
                    zadTMPAvaible.pop_back();
                }
            }
        }
        if (zadTMPAvaible.empty()) {
            zadaniaShroudEl.push_back(zadTMP[currentIndex]);
            time = std::max(time, zadTMP[currentIndex].rj) + zadTMP[currentIndex].pj;
            zadTMP.erase(zadTMP.begin() + currentIndex);

            currentIndex=0;
            continue;
        }
        sortByQj(zadTMPAvaible);
        zadanie biggestQj = zadTMPAvaible[0];
        if(time <= biggestQj.rj) {
            zadanie partDone = zadTMP[currentIndex];
            partDone.pj = biggestQj.rj - partDone.rj;
            zadanie partNotDone = zadTMP[currentIndex];
            partNotDone.pj -= partDone.pj;
            zadTMP.push_back(partNotDone);
            zadaniaShroudEl.push_back(partDone);
            int partDoneIndex = 0;
            for (int i = 0; i < zadTMP.size(); i++) {
                if (partDone.rj == zadTMP[i].rj &&
                    partDone.qj == zadTMP[i].qj) {
                    partDoneIndex= i;
                    break;
                    }
            }
            zadTMP.erase(zadTMP.begin() + partDoneIndex);
            time += partDone.pj;
        }else {
            //zadaniaShroudEl.push_back(biggestQj);
            for (int i = 0; i < zadTMP.size(); i++) {
                if (biggestQj.rj == zadTMP[i].rj &&
                    biggestQj.pj == zadTMP[i].pj &&
                    biggestQj.qj == zadTMP[i].qj) {
                    currentIndex = i;
                    break;
                    }
            }
        }
        if (zadTMP[currentIndex].pj == 0) {
            zadTMP.erase(zadTMP.begin() + currentIndex);
        }



        // if (zadTMP[currentIndex].rj < biggestQj.rj) {
        //     biggestQj.pj = zadTMP[currentIndex].pj-biggestQj.rj;
        // }
        // zadaniaShroudEl.push_back(biggestQj);
        // zadTMP[currentIndex].pj -= biggestQj.rj;
        // if (zadTMP[currentIndex].pj == 0) {
        //     zadania.erase(zadania.begin() + currentIndex);
        // }


    }
    zadania.clear();
    zadania = zadaniaShroudEl;
}


int problem::getTime() const {
    int time = 0, completionTime = 0, Cmax = 0;
    for (const auto &z: zadania) {
        time = std::max(time, z.rj) + z.pj;
        completionTime = time + z.qj;
        if (completionTime > Cmax) {
            Cmax = completionTime;
        }
    }
    return Cmax;
}

void problem::showSequence() const {
    for (const auto &z: zadania) {
        std::cout << "rj: " << z.rj << ", pj: " << z.pj << ", qj: " << z.qj << std::endl;
    }
}
