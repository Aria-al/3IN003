#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "Algo2_1.h"
#include "Algo1.h"
#include "Algo3.h"
#include "PerformanceAlgo.h"
#define TEMPSMAX 60

double mesureTempsExec (PbResoudre *prob, int (*f) (PbResoudre*))
{
    double time1, timediff ;   
    time1 = (double) clock() ;            
    time1 = time1 / CLOCKS_PER_SEC ;
    int t = f(prob) ; 
    timediff = ( ((double) clock()) / CLOCKS_PER_SEC) - time1 ;
    return timediff ; 
}

// renvoie un tableau qui est une copie de tab, sachant que len(tab) <= oldlen
double *copieTabDouble (int newLen, double *tab)
{
    double *res = malloc(sizeof(double) * (newLen)) ; 
    for (int i = 0 ; i < newLen ; i++)
    {
        res[i] = tab[i] ; 
    }
    return res ; 
}

TabTemps *perfFonctionDeS (int d, int k, int valMaxS, int (*f) (PbResoudre*))
{
    TabTemps *res = malloc(sizeof(TabTemps)) ; 
    res->len = valMaxS ; 
    res->listeTemps = malloc(sizeof(double) * valMaxS) ; 

    PbResoudre *prob = genereSystemExpo (k, d) ; 
    prob->S = 1 ; 

    double mesure = 0 ; 
    int i = 0 ; 
    while ((i < res->len) && (mesure < TEMPSMAX))
    {
        mesure = mesureTempsExec(prob, f) ; 
        prob->S += 1 ; 
        res->listeTemps[i] = mesure ; 
        i += 1 ;  
    }
    double *temp = copieTabDouble(i, res->listeTemps) ; 
    free(res->listeTemps) ; 
    res->listeTemps = temp ; 
    res->len = i ; 
    return res ; 
}


TabTemps *perfFonctionDeK (int d, int s, int valMaxK, int (*f) (PbResoudre*))
{
    TabTemps *res = malloc(sizeof(TabTemps)) ; 
    res->len = valMaxK ; 
    res->listeTemps = malloc(sizeof(double) * res->len) ;

    PbResoudre *prob = NULL ; 

    double mesure = 0 ; 
    double *dup = NULL ; 
    int v = d ; 
    int i = 0 ; 
    // Quand on multiplie un grand nombre par d, il retourne à 0 
    while ((i < valMaxK) && (v != 0))
    {
        prob = genereSystemExpo(i + 1, d) ; 
        prob->S = s ; 
        mesure = mesureTempsExec(prob, f) ; 
        res->listeTemps[i] = mesure ; 
        i += 1 ; 
        liberePbResoudre(prob) ; 
        v = v * d ; 
    }
    double *temp = copieTabDouble(i, res->listeTemps) ; 
    free(res->listeTemps) ; 
    res->listeTemps = temp ;
    res->len = i ; 
    return res ; 
}

// Renvoie  
int* ecartRelatif (int pmax, int nbBocaux, int f, int nbTirages)
{
    PbResoudre *p = malloc(sizeof(PbResoudre)) ; 
    p->S = pmax ; 
    p->k = nbBocaux ; 
    int *res = malloc(sizeof(int) * 3) ; 
    for (int i = 0; i < 3; i++)
    {
        res[i] = 0 ; 
    }
    int ecart = 0 ; 
    for (int i = 0 ; i < nbTirages ; i++)
    {
        p->S = pmax ; 
        p->tab = produitSystemeCapaciteAlea(nbBocaux, pmax) ; 
        if (!testGloutonCompatible(p->k, p->tab)) 
        {
            res[2] += 1 ; 
            while (p->S <= f*pmax)
            {
                ecart = Algo2_1(p) - Algo3(p) ; 
                if (ecart < 0)
                {
                    ecart = -ecart ; 
                }
                res[0] = (res[0] < ecart) ? ecart : res[0] ; 
                res[1] += ecart ; 
                p->S += 1 ; 
            }
        }
    }
    res[1] = res[1] / nbTirages ; 
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
    for (int i = 0 ; i < d2->len ; i++)
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
    for (int i = 0 ; i < tab->len ; i++)
    {
        fprintf(f, "%d, %f,\n", i, tab->listeTemps[i]) ; 
    }
    fclose(f) ; 
}