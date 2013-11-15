#include <iostream>

unsigned long int amount;
unsigned long int array[30][19];

unsigned long int getCurrentVal(int power2, int power3) {
    unsigned long int currentVal = amount;
    for (int i = 0; i < power2; i++)
        currentVal /= 2;
    for (int j = 0; j < power3; j++)
        currentVal /= 3;
    return currentVal;
}

unsigned long int findMaxCost(int power2, int power3) {
    unsigned long int currentVal = getCurrentVal(power2, power3);
    if (currentVal < 12) {
        return currentVal;
    } else {
        if (array[power2][power3] == 0)
            array[power2][power3] = findMaxCost(power2 + 1, power3) + findMaxCost(power2, power3 + 1) + findMaxCost(power2 + 2, power3);
        return array[power2][power3];
    }
}

int main(int argc, char** argv) {

    while (scanf("%lu", &amount) != EOF) {
        for (int i = 0; i < 30; i++)
            for (int j = 0; j < 19; j++)
                array[i][j] = 0;
        printf("%lu\n", findMaxCost(0, 0));
    }
    return 0;
}
