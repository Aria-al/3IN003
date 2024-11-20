#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Reader.h"
#include "Algo2_1.h"
#include "Algo2_2.h"
#include "Algo1.h"
#include "Algo3.h"
#include "PerformanceAlgo.h"

void AuxFonctionLibereTripleListe (TabTemps **t)
{
    for (int i = 0 ; i < 3 ; i++)
    {
        libereTabTemps(t[i]) ; 
    }
}

int main(int argc, char const *argv[])
{
    int progr = -1 ; 
    if (argc == 1)
    {
        printf("Pas de procedure selectionne\n") ; 
    }
    else
    {
        progr = atoi(argv[1]) ; 

        /*
        Option 1 : calculer les bocaux nécessaire pour faire le 
        système contenu dans le fichier passé dans le paramètre 
        argv[1] par l'algorithme : 
        1 - algo1
        2 - algo2
        3 - Algo3on
        */
        if ((progr == 1) && (argc == 4))
        {
            const char *fileName = argv[2] ; 
            int algoChoisi = atoi(argv[3]) ; 
            
            PbResoudre *prob = litProbleme(fileName) ; 
            int *res = NULL ; 

            /*
            On choisit par défaut l'algorithme 2, il est rapide et renvoie la bonne 
            valeur de m(S, k)
            */ 
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

        /*
        Option 2 : permet de tester si le systeme de capacité contenu dans le fichier argv[2] est glouton-compatible 
        */ 
        else if ((progr == 2) && (argc == 3)) 
        {
            char *fileName = argv[2] ; 
            
            PbResoudre *prob = litProbleme(fileName) ;    
            printf("Le systeme : ") ; 
            affichePbResoudre(prob) ; 
            if (testGloutonCompatible(prob->k, prob->tab))
            {
                printf("Est glouton-compatible\n") ; 
            }
            else 
            {
                printf("N'est pas glouton-compatible\n") ;
            }
        }

        /*
        Option 3 : permet de tester la proportion de systèmes glouton-compatible avec : 
        argv[2] = nbBocaux : nombre de bocaux maximaux  
        argv[3] = pmax : valeur maximale de V[i]
        argv[4] = nbSysteme : nombre de systèmes 
        */ 
        else if ((progr == 3) && (argc == 5))
        {
            srand (time(NULL)) ; 
            int nbBocaux = atoi(argv[2]) ; 
            if (nbBocaux < 2)
            {
                nbBocaux = 5 ; 
            }
            int pmax = atoi(argv[3]) ; 
            if (pmax < 0)
            {
                pmax = 10 ; 
            }
            int nbSysteme = atoi(argv[4]); 
            if (nbSysteme < 0)
            {
                nbSysteme = 10 ; 
            }
            printf("Parametres en entree :\n nbBocaux : %d\npmax : %d\nnbSysteme : %d\n", nbBocaux, pmax, nbSysteme) ; 

            float gCompat = 0.0 ; 
        
            for (int i = 0 ; i < nbSysteme ; i++)
            {
                int *systCap = produitSystemeCapaciteAlea(nbBocaux, pmax) ; 
                if (testGloutonCompatible(nbBocaux, systCap)) 
                {
                    gCompat = gCompat + 1.0 ; 
                } 
                free(systCap) ; 
            }

            printf ("Nombre total de systemes : %d\nNombre de systemes glouton compatible : %.0f\n", nbSysteme , gCompat) ; 
            printf ("Pourcentage de systemes glouton compatible : %f %%\n", (gCompat * 100 / ((double) nbSysteme ))) ; 
        }

        /*
        Option 4 : donne le temps d'éxécution de la resolution d'un problème en fonction d'un algorithme : 
        argv[2] = nom du fichier contenant le problème 
        argv[3] = algorithme choisi, avec :
            - 1 : Algorithme 1 
            - 2 : Algorithme 2 
            - 3 : Algorihme 3 
        */
        else if ((progr == 4) && (argc == 4))
        {
            PbResoudre *p = litProbleme(argv[2]) ; 
            double temps = 0 ; 
            int algoPris = atoi(argv[3]) ; 
            switch (algoPris)
            {
                case 1 : 
                    temps = mesureTempsExec(p, Algo1) ; 
                    break ; 
                case 2 : 
                    temps = mesureTempsExec(p, Algo2_1) ; 
                    break ; 
                case 3 : 
                    temps = mesureTempsExec(p, Algo3) ;
                    break ; 
                default : 
                    temps = mesureTempsExec(p, Algo2_1) ; 
                    break ; 
            }
            affichePbResoudre(p) ; 
            printf("Temps de resolution : %f\n", temps) ; 
        }

        else 
        {
            printf("Parametre %s incorrect\n", argv[1]) ; 
        }
    }
    // Tests de performances 
    TabTemps **liste = malloc(sizeof(TabTemps*) * 3) ; 
    int valMaxS = 1000 ;
    int it = 1 ;  
    liste[0] = perfFonctionDeS(2, 13, valMaxS, Algo1) ; 
    liste[1] = perfFonctionDeS(3, 9, liste[0]->len, Algo1) ; 
    liste[2] = perfFonctionDeS(4, 7, liste[0]->len, Algo1) ; 
    ecrireListeDoubleSystemeExpo("TempsAlgo1FonctionS.csv", liste) ; 
    AuxFonctionLibereTripleListe(liste) ; 
    printf("%d\n", it) ; 
    it += 1 ; 
    liste[0] = perfFonctionDeS(2, 13, valMaxS, Algo2_1) ; 
    liste[1] = perfFonctionDeS(3, 9, liste[0]->len, Algo2_1) ; 
    liste[2] = perfFonctionDeS(4, 7, liste[0]->len, Algo2_1) ; 
    ecrireListeDoubleSystemeExpo("TempsAlgo2FonctionS.csv", liste) ; 
    AuxFonctionLibereTripleListe(liste) ; 
    printf("%d\n", it) ; 
    it += 1 ; 
    liste[0] = perfFonctionDeS(2, 13, valMaxS, Algo3) ; 
    liste[1] = perfFonctionDeS(3, 9, liste[0]->len, Algo3) ; 
    liste[2] = perfFonctionDeS(4, 7, liste[0]->len, Algo3) ; 
    ecrireListeDoubleSystemeExpo("TempsAlgo3FonctionS.csv", liste) ; 
    AuxFonctionLibereTripleListe(liste) ; 
    printf("%d\n", it) ; 
    it += 1 ; 
    int S = 1000 ; 
    int valMaxK = 40 ; 
    liste[0] = perfFonctionDeK(2, 400, 10, Algo1) ; 
    liste[1] = perfFonctionDeK(3, 400, liste[0]->len, Algo1) ; 
    liste[2] = perfFonctionDeK(4, 400, liste[0]->len, Algo1) ; 
    ecrireListeDoubleSystemeExpo("TempsAlgo1FonctionK.csv", liste) ; 
    AuxFonctionLibereTripleListe(liste) ; 
    printf("%d\n", it) ; 
    it += 1 ; 
    liste[0] = perfFonctionDeK(2, S, valMaxK, Algo2_1) ; 
    liste[1] = perfFonctionDeK(3, S, liste[0]->len, Algo2_1) ; 
    liste[2] = perfFonctionDeK(4, S, liste[0]->len, Algo2_1) ; 
    ecrireListeDoubleSystemeExpo("TempsAlgo2FonctionK.csv", liste) ; 
    AuxFonctionLibereTripleListe(liste) ; 
    printf("%d\n", it) ; 
    it += 1 ; 
    liste[0] = perfFonctionDeK(2, S, valMaxK, Algo3) ; 
    liste[1] = perfFonctionDeK(3, S, liste[0]->len, Algo3) ; 
    liste[2] = perfFonctionDeK(4, S, liste[0]->len, Algo3) ; 
    ecrireListeDoubleSystemeExpo("TempsAlgo3FonctionK.csv", liste) ; 
    AuxFonctionLibereTripleListe(liste) ; 
    printf("%d\n", it) ; 
    it += 1 ; 
    free(liste) ; 
    
    

    return 0 ; 
    

}
