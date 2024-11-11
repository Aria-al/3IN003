#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Reader.h"
#include "Algo2_1.h"
#include "Algo2_2.h"
#include "Algo1.h"
#include "Algo3.h"
#include "PerformanceAlgo.h"

int V [] = {100, 11, 1, 2, 5, 10, 25, 50, 75, 100, 150, 200, 250} ; 

int main(int argc, char const *argv[])
{
    int progr = -1 ; 
    if (argc == 0)
    {
        printf("Pas de procedure selectionne\n") ; 
    }
    else
    {
        progr = atoi(argv[0]) ; 

        // Option 1 : calculer les bocaux nécessaire pour faire le système contenu dans le fichier argv[1] par l'algorithme
        /*
        1 - algo1
        2 - algo2
        3 - algoGlouton
        */
        if ((progr == 1) && (argc == 3))
        {
            char *fileName = argv[1] ; 
            int algoChoisi = atoi(argv[2]) ; 
            
            PbResoudre *prob = litProbleme(fileName) ; 
            int *res = NULL ; 

            // On choisit par défaut l'algorithme 2, il est rapide et correct 
            switch (algoChoisi)
            {
            case 1 :
                res = tabBocauxRequisAlgo1(prob) ; 
                break;

            case 2 :
                res = tabBocauxRequisAlgo2(prob) ; 
                break;

            case 3 :
                res = tabBocauxRequisAlgo3(prob) ; 
                break;
            
            default:
                res = tabBocauxRequisAlgo2(prob) ; 
                break;
            }

            printf("Liste des bocaux : ") ; 
            afficheListe(prob->tab, prob->k) ; 
            printf("Bocaux chosis : ") ; 
            afficheListe(res, prob->k) ; 

            int nbBocaux = 0 ; 
            for (int i = 0; i < prob->k; i++)
            {
                nbBocaux += res[i] ; 
            }
            printf("Nombre de bocaux utilisés : %d\n", nbBocaux) ; 

            liberePbResoudre(prob) ; 
            free(res) ; 
        }

        // Permet de tester si le systeme de capacité contenu dans le fichier argv[2] est glouton-compatible 
        else if ((progr == 2) && (argc == 2)) 
        {
            char *fileName = argv[1] ; 
            int algoChoisi = atoi(argv[2]) ; 
            
            PbResoudre *prob = litProbleme(fileName) ;    
            printf("Le systeme : ") ; 
            afficheListe(prob->tab, prob->k) ; 
            if (testGloutonCompatible(prob->k, prob->tab))
            {
                printf("Est glouton-compatible\n") ; 
            }
            else 
            {
                printf("N'est pas glouton-compatible\n") ;
            }
        }

        else 
        {
            printf("Parametre %s incorrect\n", argv[0]) ; 
        }
    }
    // Test de glouton-compatibilité 

    /*
    srand (time(NULL)) ; 
    int nbBocaux = 12 ; 
    int pmax = 500 ; 
    int gCompat = 0 ; 
    int nbSystem = 10 ; 

    for (int i = 0 ; i < nbSystem ; i++)
    {
        int *systCap = produitSystemeCapaciteAlea(nbBocaux, pmax) ; 
        if (testGloutonCompatible(nbBocaux, systCap)) 
        {
            gCompat += 1 ; 
        } 
        free(systCap) ; 
        if (!(i % (nbSystem / 20)))
        {
            printf("Tour : %d\n", i) ; 
        }
    }
    printf ("Nombre totaux de systemes : %d\nNombre de systemes glouton compatible : %d\n", nbSystem, gCompat) ; 
    printf ("Pourcentage de systemes glouton compatible : %f%%", ((float) gCompat) * 100 / ((double) nbSystem) ) ; 
    */
    int valqmals = 0 ; 
    // Tests de performance 
    TabTemps *tempsAlgo1S = perfFonctionDeS(5, 4, 800, 10, Algo1) ; 



    return 0 ; 
    

}
