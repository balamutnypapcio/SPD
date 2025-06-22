#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int main() {
    const int numJobs = 25;
    const int numMachines = 2;
    const int minTime = 1;
    const int maxTime = 99;

    ofstream file("flowshop_n25_m2.csv");
    if (!file.is_open()) {
        cerr << "Nie można utworzyć pliku!" << endl;
        return 1;
    }

    srand(time(nullptr)); 

    // Nagłówek
    file << ",";
    for (int m = 1; m <= numMachines; ++m) {
        file << "Machine_" << m;
        if (m < numMachines) file << ",";
    }
    file << "\n";

    // Zadania
    for (int j = 1; j <= numJobs; ++j) {
        file << "Job_" << j;
        for (int m = 0; m < numMachines; ++m) {
            int time = rand() % (maxTime - minTime + 1) + minTime;
            file << "," << time;
        }
        file << "\n";
    }

    file.close();
    cout << "stworzono plik\n" << endl;
    return 0;
}