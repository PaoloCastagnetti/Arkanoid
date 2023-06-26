#include "Functions.h";

int RandomNumForBlock(int first, int last) {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Crea una distribuzione uniforme tra 1 e 5
    std::uniform_int_distribution<int> dis(first, last);

    // Genera un numero casuale tra 1 e 5
    int randomNum = dis(gen);
    return randomNum;
}