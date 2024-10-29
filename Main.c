/*

#include <stdio.h>

int main() {
  printf("Hello World!");
  return 0;
} 
*/
#include <stdlib.h>
#include <stdio.h>
#include "Algo2_1.h"
#include "Algo2_2.h"
#include "Algo1.h"

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
    int res = Algo2_1(prob) ; 
    printf("%d\n", res) ; 
    int *res2 = Algo2_2(prob) ; 
    for (int i = 0 ; i < prob->k + 1; i++)
    {
        printf("%d ",res2[i]) ; 
    }

    printf("\nFin\n") ; 
    return 0;
}
