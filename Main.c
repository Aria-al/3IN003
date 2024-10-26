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
#include "Algo1.h"

int V [] = {20, 10, 1, 2, 5, 10, 25, 50, 75, 100, 150, 200, 250} ; 


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
    printf("Waspar : %d\n", Algo2_1(V)) ; 
    printf("Fin \n") ; 
    return 0;
}
