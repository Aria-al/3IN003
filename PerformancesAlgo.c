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
    res->nbVal = 0 ; 

    PbResoudre *prob = genereSystemExpo (k, d) ; 
    prob->S = 0 ; 

    double mesure = 0 ; 
    double *dup = NULL ; 
    double temps = 0 ; 
    while ((res->nbVal < valMaxS) && (temps <= 60))
    {
        mesure = 0 ; 
        for (int i = 0 ; i < nbMesure ; i++)
        {
            temps = mesureTempsExec(prob, f) ; 
            if (temps > 60)
            {
                break ;
            }
            mesure += temps ; 
        }
        prob->S += 1 ; 
        if (res->nbVal >= res->len)
        {
            dup = copieTabDouble(res->len, 2*res->len, res->listeTemps) ; 
            res->len = res->len * 2 ; 
            free(res->listeTemps) ; 
            res->listeTemps = dup ; 
        }
        res->listeTemps[res->nbVal] = mesure / nbMesure; 
        res->nbVal += 1 ; 
    }
    if (temps < 60)
    {
        for (int i = res->nbVal ; i < res->len ; i++)
        {
            res->listeTemps[i] = res->listeTemps[res->nbVal - 1] ; 
        }
    }
    return res ; 
}

TabTemps *perfFonctionDeK (int d, int s, int valMaxK, int nbMesure, int (*f) (PbResoudre*))
{
    TabTemps *res = malloc(sizeof(TabTemps)) ; 
    res->len = 50 ; 
    res->listeTemps = malloc(sizeof(double) * res->len) ; 
    res->nbVal = 0 ; 

    PbResoudre *prob = NULL ; 

    double mesure = 0 ; 
    double *dup = NULL ; 
    int v = d ; 
    double temps = 0 ; 
    while ((res->nbVal < valMaxK) && (v < INT_MAX) && (temps < 60))
    {
        prob = genereSystemExpo(res->nbVal + 1, d) ; 
        prob->S = s ; 
        mesure = 0 ; 
        for (int i = 0 ; i < nbMesure ; i++)
        {
            temps = mesureTempsExec(prob, f) ; 
            if (temps > 60)
            {
                break ; 
            }
            mesure += temps ; 
        }
        if (res->nbVal >= res->len)
        {
            dup = copieTabDouble(res->len, 2*res->len, res->listeTemps) ; 
            res->len = res->len * 2 ; 
            free(res->listeTemps) ; 
            res->listeTemps = dup ; 
        }
        res->listeTemps[res->nbVal] = mesure / nbMesure; 
        res->nbVal += 1 ; 
        liberePbResoudre(prob) ; 
        v = v * d ; 
    }
    if (mesure < 60)
    {
        for (int i = res->nbVal ; i < res->len ; i++)
        {
            res->listeTemps[i] = res->listeTemps[res->nbVal - 1] ; 
        }
    }
    return res ; 
}

void ecrireListeDouble (char *filename, TabTemps *tab)
{
    FILE *f = fopen(filename, "w") ; 
    printf("Longueur Tableau : %d\n", tab->len) ; 
    for (int i = 0 ; i < tab->nbVal ; i++)
    {
        fprintf(f, "%d, %.4f,\n", i, tab->listeTemps[i]) ; 
    }
    fclose(f) ; 
}