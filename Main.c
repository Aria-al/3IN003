#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Algo2_1.h"
#include "Algo2_2.h"
#include "Algo1.h"
#include "PerformanceAlgo.h"

int V [] = {20, 11, 1, 2, 5, 10, 25, 50, 75, 100, 150, 200, 250} ; 

int main(int argc, char const *argv[])
{
    /*
    for (int i = 2 ; i < V[k] * 4 ; i++)
    {
        if (Algo1(i, k) != AlgoGlout(i, k))
        {
            printf("Erreur, systeme non-glouton-optimal pour la valeur : s = %d, A1 = %d, AG = %d\n", i, Algo1(i, k), AlgoGlout(i, k)) ; 
        }
    }
    */
    PbResoudre *prob = malloc(sizeof(PbResoudre)) ; 
    prob->S = V[0] ; 
    prob->k = V[1] ; 
    prob->tab = copieTab(2, V, V[1] + 2) ; 
    printf ("Algorithme 2 : \n") ; 
    int res = Algo2_1(prob) ; 
    printf("%d\n", res) ; 

    printf("Algorithme 2 : variante 1\n") ; 
    int *res2 = Algo2_2(prob) ; 
    for (int i = 0 ; i < prob->k + 1; i++)
    {
        printf("%d ",res2[i]) ; 
    }

    printf("Algorithme 2 : variante 2\n") ; 
    int *res3 = tabBocauxRequis(prob) ; 
    for (int i = 0 ; i < prob->k ; i++)
    {
        printf("%d ",res3[i]) ; 
    }
    remove("Temps.txt") ; 
    printf("Mesure de temps\n") ; 
    fclose(fopen("Temps.txt", "w")); 
    TabTemps *valeur = perfFonctionDeS(2, 5, 900000, AlgoGlout) ; 
    ecrireListeDouble("Temps.txt", valeur) ; 
    prob->S = 527 ; 
    double temps = mesureTempsExec(prob, AlgoGlout) ; 
    printf("%f\n", temps) ; 
    printf("%d\n", Algo1(prob) == AlgoGlout(prob)) ; 
    printf("\nFin\n") ; 

    return 0;
}
