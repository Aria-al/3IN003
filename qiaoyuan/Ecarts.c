#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

#define INF 1000000

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
    }
}

int AlgoDynamic(int S, int k, int *V) {
    int *dp = (int *)malloc((S + 1) * sizeof(int));
    for (int i = 0; i <= S; i++) dp[i] = INF;
    dp[0] = 0;

    for (int i = 0; i < k; i++) {
        for (int j = V[i]; j <= S; j++) {
            if (dp[j - V[i]] + 1 < dp[j]) {
                dp[j] = dp[j - V[i]] + 1;
            }
        }
    }

    int result = dp[S];
    free(dp);
    if (result == INF) {
        return -1;
    }
    else {
        return result;
    }
}


bool TestGloutonCompatible(int k, int *V) {
    if (k < 3) {
        return true;
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
    V[0] = 1;
    for (int i = 1; i < k; i++) {
        V[i] = (rand() % (pmax - 1)) + 2;
    }

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
    int f = 5;
    int totalSystems = 100;
    int incompatibleCount = 0;
    int *V = (int *)malloc(k * sizeof(int));

    srand(time(0));

    double totalGap = 0;
    double worstGap = 0;
    int comparisons = 0;

    for (int i = 0; i < totalSystems; i++) {
        generateRandomSystem(k, pmax, V);

        if (!TestGloutonCompatible(k, V)) {
            incompatibleCount++;

            for (int S = pmax; S <= f * pmax; S++) {
                int resultDP = AlgoDynamic(S, k, V);
                int resultGreedy = AlgoGlouton(S, k, V);

                if (resultDP > 0 && resultGreedy > 0 && resultGreedy >= resultDP) {
                    double gap = (double)(resultGreedy - resultDP) / resultDP;
                    totalGap += gap;
                    if (gap > worstGap) {
                        worstGap = gap;
                    }
                    comparisons++;
                }
            }
        }
    }

    printf("incompatible number:%d\n", incompatibleCount);
    if (comparisons > 0) {
        printf("l'ecart moyen:%.2f%%\n", (totalGap / comparisons) * 100);
        printf("pire ecart:%.2f%%\n", worstGap * 100);
    } else {
        printf("Tous sont compatibles\n");
    }

    free(V);
    return 0;
}
