#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define INF 1000000  // grand nombre pour representer le cas pas possible

// Lire les données d'entrée du fichier
int readInput(const char *filename, int *S, int *k, int **V) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("on ne peut pas ouvrir le fichier");
        return -1;
    }

    fscanf(file, "%d", S);
    fscanf(file, "%d", k);

    *V = (int *)malloc(*k * sizeof(int));
    if (*V == NULL) {
        perror("erreur");
        fclose(file);
        return -1;
    }

    for (int i = 0; i < *k; i++) {
        fscanf(file, "%d", &(*V)[i]);
    }

    fclose(file);
    return 0;
}

// Algo glouton (numero 3)
void greedyAlgorithm(int S, int k, int *V, int *result) {
    for (int i = k - 1; i >= 0; i--) {
        result[i] = S / V[i];  // nombre max de bocaux de capacite V[i] qu'on peut utiliser 
        S %= V[i];             // Renouveler les confitures restes
    }
}

// Algo dynamique (numero 2)
void dynamicProgrammingAlgorithm(int S, int k, int *V, int *result) {
    int *dp = (int *)malloc((S + 1) * sizeof(int));
    int *track = (int *)malloc((S + 1) * sizeof(int));
    
    for (int i = 0; i <= S; i++) dp[i] = INF;  // Initialiser dp comme infinie
    dp[0] = 0;  

    // fill the tableau dp
    for (int i = 0; i < k; i++) {
        for (int j = V[i]; j <= S; j++) {
            if (dp[j - V[i]] + 1 < dp[j]) {
                dp[j] = dp[j - V[i]] + 1;
                track[j] = i;  // 
            }
        }
    }

    // faire le backward
    int remaining = S;
    while (remaining > 0 && dp[remaining] < INF) {
        int type = track[remaining];
        result[type]++;
        remaining -= V[type];
    }

    free(dp);
    free(track);
}

// Algo recurssive (numero 1)

int min(int a, int b){
    if (a <= b) return a;
    return b;
}


int recursiveAlgorithm(int S, int k, int *V) {
    if (S == 0) return 0;
    if (k == 0) return INF;

    int avec_k;
    int sans_k;
    if (S >= V[k-1]){
        avec_k = 1+recursiveAlgorithm(S-V[k-1], k, V);
    }
    else{
        avec_k = INF;
    }

    sans_k = recursiveAlgorithm(S, k-1, V);
    return min(avec_k, sans_k);
}




// afficher le resultat
void displayResult(int k, int *result, int *V) {
    printf("le nombre minimun de bocaux prises:\n");
    int res=0;
    for (int i = 0; i < k; i++) {
        printf("nombre de bocaux de volume %d est: %d\n", V[i], result[i]);
        res+=result[i];
    }
    printf("le nombre total de bocaus prises: %d\n", res);
}


double getCPUTime(void) {
    return (double)clock();
}

void experiment(int S, int k, int choice){
    int d=4;    //on peut changer le d comme 2,3 ou 4
    int V[k];         // tableau de capacité
    int *result;    
    for (int i = 0; i < k; i++) {
        V[i] = (int)pow(d, i);  // V[i] = d^i
    }

    result = (int *)calloc(k, sizeof(int));

   
    double startTime = getCPUTime();
    // choisir l'algo
    switch (choice) {
        case 1:
            printf("recursive algorithm result:\n");
            int a=recursiveAlgorithm(S, k, V);
            printf("le nombre total de bocaus prises: %d\n", a);
            break;
        case 2:
            printf("dynamic programming algorithm result:\n");
            dynamicProgrammingAlgorithm(S, k, V, result);
            displayResult(k, result, V);
            break;
        case 3:
            printf("greedy algorithm result:\n");
            greedyAlgorithm(S, k, V, result);
            displayResult(k, result, V);
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }

    double endTime = getCPUTime();
    printf("running time: %.5f sec\n", (endTime - startTime)/CLOCKS_PER_SEC);


    FILE *outputFile = fopen("complexity_data.txt", "a");
    fprintf(outputFile, "%d %d %.5f\n", S, k, (endTime - startTime)/CLOCKS_PER_SEC);
    fclose(outputFile);

    free(V);
    free(result);
}

int main() {
    //on peut changer les variables ici
    int choice=3;

    int S = 1000000000;
    int k=16;
    experiment(S, k, choice);

    return 0;
}





