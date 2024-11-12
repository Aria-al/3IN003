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
    while ((res->nbVal < valMaxS) && (temps < 60))
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

// Permet de calculer l'écart relatif l'algorithme 2 et 3 
int ecartRelatif (int pmax, int nbBocaux, int f, int nbTirages)
{
    PbResoudre *p = malloc(sizeof(PbResoudre)) ; 
    p->S = pmax ; 
    p->k = nbBocaux ; 
    int res = 0 ; 
    int ecart = 0 ; 
    for (int i = 0 ; i < nbTirages ; i++)
    {
        p->S = pmax ; 
        p->tab = produitSystemeCapaciteAlea(nbBocaux, pmax) ; 
        if (!testGloutonCompatible(p->k, p->tab)) 
        {
            while (p->S <= f*pmax)
            {
                ecart = Algo2_1(p) - AlgoGlout(p) ; 
                if (ecart < 0)
                {
                    ecart = -ecart ; 
                }
                res += ecart ; 
                p->S += 1 ; 
            }
        }
    }
    liberePbResoudre(p) ; 
    return res ; 
}   

/*
Permet d'écrire les temps du système exponetiel avec liste de taille 3 : 
liste[0] = temps pour d = 2 
liste[1] = temps pour d = 3 
liste[2] = temps pour d = 4 
*/ 
void ecrireListeDoubleSystemeExpo (char *filename, TabTemps **liste)
{
    TabTemps *d2 = liste[0] ; 
    TabTemps *d3 = liste[1] ; 
    TabTemps *d4 = liste[2] ; 
    FILE *f = fopen(filename, "w") ; 
    int m = (d2->nbVal < d3->nbVal) ? d2->nbVal : d3->nbVal ; 
    m = (m < d4->nbVal) ? m : d4->nbVal ; 
    for (int i = 0 ; i < m ; i++)
    {
        fprintf(f, "%d, %f, %f, %f,\n", i, d2->listeTemps[i], d3->listeTemps[i], d4->listeTemps[i]) ; 
    }
    fclose(f) ; 
}

void libereTabTemps (TabTemps *t) 
{
    free(t->listeTemps) ; 
    free(t) ; 
}

void ecrireListeDouble (char *filename, TabTemps *tab)
{
    FILE *f = fopen(filename, "w") ; 
    printf("Longueur Tableau : %d\n", tab->len) ; 
    for (int i = 0 ; i < tab->nbVal ; i++)
    {
        fprintf(f, "%d, %f,\n", i, tab->listeTemps[i]) ; 
    }
    fclose(f) ; 
}