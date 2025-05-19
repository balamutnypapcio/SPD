#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Użycie: " << argv[0] << " nazwa_pliku ile_wierszy min max\n";
        return 1;
    }

    std::string nazwa_pliku = argv[1];
    int ile_wierszy = std::atoi(argv[2]);
    int min = std::atoi(argv[3]);
    int max = std::atoi(argv[4]);

    if (min > max || ile_wierszy <= 0) {
        std::cerr << "Błędne wartości parametrów.\n";
        return 1;
    }

    std::ofstream plik(nazwa_pliku);
    if (!plik) {
        std::cerr << "Nie można otworzyć pliku do zapisu: " << nazwa_pliku << "\n";
        return 1;
    }

    std::srand(std::time(nullptr));

    plik << ile_wierszy << "\n";
    for (int i = 0; i < ile_wierszy; ++i) {
        int wartosc = min + std::rand() % (max - min + 1);
        plik << "0 " << wartosc << " 0\n";
    }

    plik.close();
    std::cout << "Plik " << nazwa_pliku << " został wygenerowany.\n";
    return 0;
}
