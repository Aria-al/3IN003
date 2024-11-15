#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define INF 1000000

// Algo glouton
int AlgoGlouton(int S, int k, int *V) {
    int count = 0;
    for (int i = k - 1; i >= 0; i--) {
        count += S / V[i];
        S %= V[i];
    }
    if (S == 0) {
        return count;
    }
    else {
        return INF;
    } // si pas compatible, retourner INF
}


bool TestGloutonCompatible(int k, int *V) {
    if (k < 3) {
        return true; // si k<3, compatible
    }

    for (int S = V[2] + 2; S < V[k - 2] + V[k - 1]; S++) {
        for (int j = 0; j < k; j++) {
            if (V[j] < S) {
                if (AlgoGlouton(S, k, V) > 1 + AlgoGlouton(S - V[j], k, V)) {
                    return false;
                }
            }
        }
    }
    return true;
}


void generateRandomSystem(int k, int pmax, int *V) {
    V[0] = 1;  // contenir la capacite 1
    for (int i = 1; i < k; i++) {
        V[i] = (rand() % (pmax - 1)) + 2; //des autres entre 2 et pmax
    }

    //tirer par l'ordre croissant
    for (int i = 0; i < k - 1; i++) {
        for (int j = 0; j < k - i - 1; j++) {
            if (V[j] > V[j + 1]) {
                int temp = V[j];
                V[j] = V[j + 1];
                V[j + 1] = temp;
            }
        }
    }
}

int main() {
    int k = 5;           
    int pmax = 10;       
    int totalSystems = 100; 
    int compatibleCount = 0; 
    int *V = (int *)malloc(k * sizeof(int)); 

    srand(time(0));

    // generer aleatoirement 100
    for (int i = 0; i < totalSystems; i++) {
        generateRandomSystem(k, pmax, V);

        if (TestGloutonCompatible(k, V)) {
            compatibleCount++;
        }
    }

    // calcul le pourcentage
    double compatibleRatio = (double)compatibleCount / totalSystems * 100;
    printf("A partir de %d exemples, il y a %d compatibles.\n", totalSystems, compatibleCount);
    printf("La pourcentage de compatible est: %.2f%%\n", compatibleRatio);

    free(V);
    return 0;
}

