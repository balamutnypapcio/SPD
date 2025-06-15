#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <chrono>
#include <iomanip>


using namespace std;
using namespace chrono;

using Matrix = vector<vector<int>>;

// ========== CSV Wczytanie ==========
Matrix loadCSV(const string& filename) {
    ifstream file(filename);
    Matrix processingTimes;
    string line;

    if (!file.is_open()) {
        cerr << "Nie mozna otworzyc pliku: " << filename << endl;
        return {};
    }

    getline(file, line); // pomiń nagłówek

    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        vector<int> row;
        getline(ss, cell, ','); // pomiń nazwę zadania (Job_X)
        while (getline(ss, cell, ',')) {
            row.push_back(stoi(cell));
        }
        processingTimes.push_back(row);
    }
    return processingTimes;
}

// ========== Cmax ==========
int calculateCmax(const vector<int>& perm, const Matrix& processingTimes) {
    int n = perm.size();
    int m = processingTimes[0].size();
    vector<vector<int>> C(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        int job = perm[i];
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0)
                C[i][j] = processingTimes[job][j];
            else if (i == 0)
                C[i][j] = C[i][j - 1] + processingTimes[job][j];
            else if (j == 0)
                C[i][j] = C[i - 1][j] + processingTimes[job][j];
            else
                C[i][j] = max(C[i - 1][j], C[i][j - 1]) + processingTimes[job][j];
        }
    }
    return C[n - 1][m - 1];
}

// ========== Brute Force ==========
int bruteForce(const Matrix& processingTimes, vector<int>& bestPerm) {
    int n = processingTimes.size();
    vector<int> perm(n);
    for (int i = 0; i < n; i++) perm[i] = i;

    int bestCmax = numeric_limits<int>::max();

    do {
        int cmax = calculateCmax(perm, processingTimes);
        if (cmax < bestCmax) {
            bestCmax = cmax;
            bestPerm = perm;
        }
    } while (next_permutation(perm.begin(), perm.end()));

    return bestCmax;
}

// ========== NEH ==========
int NEH(const Matrix& processingTimes, vector<int>& bestPerm) {
    int n = processingTimes.size();
    int m = processingTimes[0].size();
    vector<pair<int, int>> sumJobs(n);

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++)
            sum += processingTimes[i][j];
        sumJobs[i] = {sum, i};
    }

    sort(sumJobs.rbegin(), sumJobs.rend());

    bestPerm.clear();
    bestPerm.push_back(sumJobs[0].second);

    for (int i = 1; i < n; i++) {
        int job = sumJobs[i].second;
        int bestLocalCmax = numeric_limits<int>::max();
        vector<int> tempPerm;

        for (int pos = 0; pos <= i; pos++) {
            vector<int> currentPerm = bestPerm;
            currentPerm.insert(currentPerm.begin() + pos, job);
            int cmax = calculateCmax(currentPerm, processingTimes);
            if (cmax < bestLocalCmax) {
                bestLocalCmax = cmax;
                tempPerm = currentPerm;
            }
        }
        bestPerm = tempPerm;
    }

    return calculateCmax(bestPerm, processingTimes);
}

// ========== Johnson dla m=2 ==========
int johnson(const Matrix& processingTimes, vector<int>& jobOrder) {
    int n = processingTimes.size();
    if (processingTimes[0].size() != 2) {
        cerr << "Johnson: liczba maszyn musi wynosic 2!" << endl;
        return -1;
    }

    vector<pair<int, int>> left, right;

    for (int i = 0; i < n; i++) {
        if (processingTimes[i][0] <= processingTimes[i][1])
            left.push_back({processingTimes[i][0], i});
        else
            right.push_back({processingTimes[i][1], i});
    }

    sort(left.begin(), left.end());
    sort(right.rbegin(), right.rend());

    jobOrder.clear();
    for (auto& p : left) jobOrder.push_back(p.second);
    for (auto& p : right) jobOrder.push_back(p.second);

    return calculateCmax(jobOrder, processingTimes);
}

// ========== MAIN ==========
int main() {
    using namespace chrono;

    string filename = "/home/jakub/SPD/Lab03/instances/flowshop_n10_m2.csv";
    Matrix processingTimes = loadCSV(filename);

    if (processingTimes.empty()) return 1;

    int m = processingTimes[0].size();
    cout << "Wczytano " << processingTimes.size() << " zadan, " << m << " maszyn.\n\n";

    vector<int> bestPerm;

    if (processingTimes.size() <= 10) {
        cout << "--- Brute-force ---\n";
        auto start = high_resolution_clock::now();
        int cmaxBF = bruteForce(processingTimes, bestPerm);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        double time_ms = duration.count() / 1000.0;

        cout << "Cmax: " << cmaxBF << ", Kolejność: ";
        for (int j : bestPerm) cout << "Job_" << j + 1 << " ";
        cout << "\nCzas wykonania: " << fixed << setprecision(5) << time_ms << " ms\n\n";
    }

    cout << "--- NEH ---\n";
    auto startNEH = high_resolution_clock::now();
    int cmaxNEH = NEH(processingTimes, bestPerm);
    auto endNEH = high_resolution_clock::now();
    auto durationNEH = duration_cast<microseconds>(endNEH - startNEH);
    double timeNEH = durationNEH.count() / 1000.0;

    cout << "Cmax: " << cmaxNEH << ", Kolejność: ";
    for (int j : bestPerm) cout << "Job_" << j + 1 << " ";
    cout << "\nCzas wykonania: " << fixed << setprecision(5) << timeNEH << " ms\n\n";

    if (m == 2) {
        cout << "--- Johnson (m=2) ---\n";
        auto startJ = high_resolution_clock::now();
        int cmaxJ = johnson(processingTimes, bestPerm);
        auto endJ = high_resolution_clock::now();
        auto durationJ = duration_cast<microseconds>(endJ - startJ);
        double timeJ = durationJ.count() / 1000.0;

        cout << "Cmax: " << cmaxJ << ", Kolejność: ";
        for (int j : bestPerm) cout << "Job_" << j + 1 << " ";
        cout << "\nCzas wykonania: " << fixed << setprecision(5) << timeJ << " ms\n\n";
    }

    return 0;
}
