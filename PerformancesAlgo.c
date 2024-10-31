#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "Algo2_1.h"
#include "Algo1.h"
#include "Algo3.h"
#include "PerformanceAlgo.h"

double mesureTempsExec (PbResoudre *prob, int (*f) (PbResoudre*))
{
    double time1, timediff ;   
    time1 = (double) clock() ;            
    time1 = time1 / CLOCKS_PER_SEC ;
    int t = f(prob) ; 
    timediff = ( ((double) clock()) / CLOCKS_PER_SEC) - time1 ;
    return timediff ; 
}

double *copieTabDouble (int oldLen, int newLen, double *tab)
{
    double *res = malloc(sizeof(double) * (newLen)) ; 
    for (int i = 0 ; i < oldLen ; i++)
    {
        res[i] = tab[i] ; 
    }
    for (int i = oldLen - 1 ; i < newLen ; i++)
    {
        res[i] = tab[oldLen - 2] ; 
    }
    return res ; 
}

TabTemps *perfFonctionDeS (int d, int k, int valMaxS, int nbMesure, int (*f) (PbResoudre*))
{
    TabTemps *res = malloc(sizeof(TabTemps)) ; 
    res->len = 50 ; 
    res->listeTemps = malloc(sizeof(double) * res->len) ; 

    PbResoudre *prob = genereSystemExpo (k, d) ; 
    prob->S = 0 ; 

    double mesure = 0 ; 
    int nbVal = 0 ; 
    double *dup = NULL ; 
    while ((mesure < 60) && (nbVal < valMaxS))
    {
        mesure = 0 ; 
        for (int i = 0 ; i < nbMesure ; i++)
        {
            mesure += mesureTempsExec(prob, f) ; 
        }
        prob->S += 1 ; 
        if (nbVal >= res->len)
        {
            dup = copieTabDouble(res->len, 2*res->len, res->listeTemps) ; 
            res->len = res->len * 2 ; 
            free(res->listeTemps) ; 
            res->listeTemps = dup ; 
        }
        res->listeTemps[nbVal] = mesure ; 
        nbVal += 1 ; 
    }
    return res ; 
}

void ecrireListeDouble (char *filename, TabTemps *tab)
{
    FILE *f = fopen(filename, "w") ; 
    printf("Longueur Tableau : %d\n", tab->len) ; 
    for (int i = 0 ; i < tab->len ; i++)
    {
        fprintf(f, "%d, %.4f\n", i, tab->listeTemps[i]) ; 
    }
    fclose(f) ; 
}