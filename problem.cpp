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

void problem::sortByRj() {
    std::sort(zadania.begin(), zadania.end(), [](const zadanie& a, const zadanie& b) {
        return a.rj < b.rj;
    });
}

void problem::sortByQj() {
    std::sort(zadania.begin(), zadania.end(), [](const zadanie& a, const zadanie& b) {
        return a.qj > b.qj;
    });
}

int problem::getTime() const {
    int time = 0, completionTime = 0;
    for (const auto& z : zadania) {
        if (time < z.rj) {
            time = z.rj;
        }
        time += z.pj;
        completionTime = std::max(completionTime, time + z.qj);
    }
    return completionTime;
}

void problem::showSequence() const {
    for (const auto& z : zadania) {
        std::cout << "rj: " << z.rj << ", pj: " << z.pj << ", qj: " << z.qj << std::endl;
    }
}
