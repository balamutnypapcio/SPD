//
// Created by jakub on 30.03.2025.
//

#include "problem.h"


int problem::loadFile(const std::string& fileName) {
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

void problem::sortByRj(std::vector<zadanie>& zad) {
    std::sort(zad.begin(), zad.end(), [](const zadanie& a, const zadanie& b) {
        return a.rj < b.rj;
    });
}

void problem::sortByQj(std::vector<zadanie>& zad) {
    std::sort(zad.begin(), zad.end(), [](const zadanie& a, const zadanie& b) {
        return a.qj > b.qj;
    });
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
        for (int i = 0; i < last+1; i++) {
            if (zadania[i].qj > zadania[biggestQj].qj) {
                biggestQj = i;
            }
        }
        zadaniaSCHROUD.push_back(zadania[biggestQj]);
        time = std::max(time,zadania[biggestQj].rj)+zadania[biggestQj].pj;
        zadania.erase(zadania.begin()+biggestQj);
    }
    zadania.clear();
    zadania = zadaniaSCHROUD;
}



int problem::getTime() const {
    int time = 0, completionTime = 0, Cmax = 0;
    for (const auto& z : zadania) {
        time = std::max(time,  z.rj) + z.pj;
        completionTime = time + z.qj;
        if (completionTime > Cmax) {
            Cmax = completionTime;
        }
    }
    return Cmax;
}

void problem::showSequence() const {
    for (const auto& z : zadania) {
        std::cout << "rj: " << z.rj << ", pj: " << z.pj << ", qj: " << z.qj << std::endl;
    }
}
