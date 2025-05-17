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
        sortByRj(zadTMP);
        std::vector<zadanie> zadTMPAvaible;
        for (int i = 0; i < zadTMP.size(); i++) {
            if (std::max(time,zadTMP[currentIndex].rj) + zadTMP[currentIndex].pj > zadTMP[i].rj ) {
                zadTMPAvaible.push_back(zadTMP[i]);
                if (zadTMP[currentIndex].qj >= zadTMP[i].qj) {
                    zadTMPAvaible.pop_back();
                }
            }
        }
        if (zadTMPAvaible.empty()) {
            if (zadTMP[currentIndex].pj == 0) {
                zadTMP.erase(zadTMP.begin() + currentIndex);
                currentIndex=0;
                continue;
            }
            zadaniaShroudEl.push_back(zadTMP[currentIndex]);
            //std::cout << "rj: " << zadTMP[currentIndex].rj << ", pj: " << zadTMP[currentIndex].pj << ", qj: " << zadTMP[currentIndex].qj << "  C: "<< time<<std::endl;
            time = std::max(time, zadTMP[currentIndex].rj) + zadTMP[currentIndex].pj;
            zadTMP.erase(zadTMP.begin() + currentIndex);

            currentIndex=0;
            continue;
        }
        sortByQj(zadTMPAvaible);
        zadanie biggestQj = zadTMPAvaible[0];
        if(time < biggestQj.rj) {
            zadanie partDone = zadTMP[currentIndex];
            partDone.pj = biggestQj.rj - std::max(time, partDone.rj);
            zadanie partNotDone = zadTMP[currentIndex];
            partNotDone.pj -= partDone.pj;
            zadTMP.push_back(partNotDone);
            zadaniaShroudEl.push_back(partDone);
            //std::cout << "rj: " << partDone.rj << ", pj: " << partDone.pj << ", qj: " << partDone.qj <<  "  C: "<< time<<std::endl;

            int partDoneIndex = 0;
            for (int i = 0; i < zadTMP.size(); i++) {
                if (partDone.rj == zadTMP[i].rj &&
                    partDone.qj == zadTMP[i].qj) {
                    partDoneIndex= i;
                    break;
                    }
            }
            zadTMP.erase(zadTMP.begin() + partDoneIndex);
            time = std::max(time, partDone.rj) + partDone.pj;
        }else { //nothing done with currentIndex task
            for (int i = 0; i < zadTMP.size(); i++) {
                if (biggestQj.rj == zadTMP[i].rj &&
                    biggestQj.pj == zadTMP[i].pj &&
                    biggestQj.qj == zadTMP[i].qj) {
                    currentIndex = i;
                    break;
                    }
            }
        }
    }
    zadania.clear();
    zadania = zadaniaShroudEl;
}

std::pair<std::vector<zadanie>, std::vector<zadanie>> problem::sortTwoMachineLSA(std::vector<zadanie>& zad) {
    std::vector<zadanie> machine1, machine2;
    int time1=0, time2=0;

    for (const auto& zadanie : zad) {
        if (time1 <= time2) {
            machine1.push_back(zadanie);
            time1+=zadanie.pj;
        }
        else {
            machine2.push_back(zadanie);
            time2+=zadanie.pj;
        }
    }

    return std::make_pair(machine1, machine2);
}
std::pair<std::vector<zadanie>, std::vector<zadanie>> problem::sortTwoMachineLPT(std::vector<zadanie>& zad) {
    std::vector<zadanie> sortedZadanie;
    std::sort(zad.begin(), zad.end(), [](const zadanie &a , const zadanie &b)
    {return a.pj > b.pj;});


    std::vector<zadanie> machine1, machine2;
    int time1=0, time2=0;
    for (const auto& zadanie : zad) {
        if (time1 <= time2) {
            machine1.push_back(zadanie);
            time1+=zadanie.pj;
        }
        else {
            machine2.push_back(zadanie);
            time2+=zadanie.pj;
        }
    }

    return std::make_pair(machine1, machine2);
}


std::pair<std::vector<zadanie>, std::vector<zadanie>> problem::sortTwoMachinePD(std::vector<zadanie>& zad) {
    int n = zad.size();

    // Obliczanie sumy wszystkich czasów wykonania
    int sum_pj = 0;
    for (const auto& z : zad) {
        sum_pj += z.pj;
    }

    // Obliczanie rozmiaru K (K = suma_pj/2 + 1)
    int K = (sum_pj / 2) + 1;

    // Tworzenie tablicy T[n+1][K]
    std::vector<std::vector<bool>> T(n + 1, std::vector<bool>(K, false));

    // Inicjalizacja pierwszej kolumny jedynkami
    for (int i = 0; i <= n; i++) {
        T[i][0] = true;
    }

    // Wypełnianie tablicy zgodnie z algorytmem
    for (int j = 1; j <= n; j++) {
        for (int k = 1; k < K; k++) {
            // Sprawdzanie warunków z algorytmu
            if (T[j-1][k] == true) {
                T[j][k] = true;
            } else if (k >= zad[j-1].pj && T[j-1][k-zad[j-1].pj] == true) {
                T[j][k] = true;
            }
        }
    }

    // Backtracking - odtwarzanie rozwiązania
    std::vector<zadanie> machine1, machine2;
    int k = K - 1;

    // Szukamy największego możliwego k
    while (k > 0 && !T[n][k]) {
        k--;
    }

    // Odtwarzanie przydziału zadań
    int j = n;
    while (j > 0 && k >= 0) {
        if (k >= zad[j-1].pj && T[j-1][k-zad[j-1].pj]) {
            machine1.push_back(zad[j-1]);
            k -= zad[j-1].pj;
        } else {
            machine2.push_back(zad[j-1]);
        }
        j--;
    }

    // Dodajemy pozostałe zadania do drugiej maszyny
    while (j > 0) {
        machine2.push_back(zad[j-1]);
        j--;
    }

    // Odwracamy kolejność, bo dodawaliśmy od końca
    std::reverse(machine1.begin(), machine1.end());
    std::reverse(machine2.begin(), machine2.end());

    return std::make_pair(machine1, machine2);
}




std::pair<std::vector<zadanie>, std::vector<zadanie>> problem::sortTwoMachineExhaustive(std::vector<zadanie>& zad) {
    int n = zad.size();
    std::vector<zadanie> best_machine1, best_machine2;
    int best_makespan = INT_MAX;

    // Generujemy wszystkie możliwe kombinacje przydziału zadań do maszyn
    // Używamy maski bitowej: 0 oznacza przydzielenie do maszyny 1, 1 do maszyny 2
    for (int mask = 0; mask < (1 << n); mask++) {
        std::vector<zadanie> current_machine1, current_machine2;

        // Przydzielamy zadania do maszyn na podstawie bitów w masce
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                current_machine2.push_back(zad[i]);
            } else {
                current_machine1.push_back(zad[i]);
            }
        }

        // Obliczamy makespan dla aktualnego przydziału
        int current_makespan = getTimeTwoMachines(current_machine1, current_machine2);

        // Aktualizujemy najlepsze rozwiązanie, jeśli znaleźliśmy lepsze
        if (current_makespan < best_makespan) {
            best_makespan = current_makespan;
            best_machine1 = current_machine1;
            best_machine2 = current_machine2;
        }

        // Jeśli znaleźliśmy idealne zrównoważenie (różnica czasów <= 1), możemy przerwać
        int time1 = 0, time2 = 0;
        for (const auto& z : current_machine1) time1 += z.pj;
        for (const auto& z : current_machine2) time2 += z.pj;
        if (abs(time1 - time2) <= 1) {
            best_machine1 = current_machine1;
            best_machine2 = current_machine2;
            break;
        }
    }
    return std::make_pair(best_machine1, best_machine2);
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

int problem::getTimeTwoMachines(const std::vector<zadanie>& m1, const std::vector<zadanie>& m2) const {
    int time1 =0;
    int time2 =0;

    for (const auto &z: m1) {
        time1 += z.pj;
    }
    for (const auto &z: m2) {
        time2 += z.pj;
    }

    return std::max(time1, time2);
}


void problem::showSequence() const {
    for (const auto &z: zadania) {
        std::cout << "rj: " << z.rj << ", pj: " << z.pj << ", qj: " << z.qj << std::endl;
    }
}
