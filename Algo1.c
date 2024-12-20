#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Algo1.h"

// Renvoie la copie du tableau T[k:] passé en paramètre de longueur len
int *copieTab (int k, int *T, int len) 
{
    int *res = malloc(sizeof(int) * (len - k)) ; 
    for (int i = k ; i < len ; i++)
    {
        res[i - k] = T[i] ; 
    }
    return res ; 
}

// Fonction auxiliaire pour l'algorithme 1
int Aux1(int s, int i,int *cap) 
{
    if (s == 0)
    {
        return 0 ; 
    }
    else if (((s >= 1) && (i <= -1)) || ((s < 0) && (i >= 0)))
    {
        return INT_MAX ; 
    }
    
    int V1 = Aux1(s, i - 1, cap) ; 
    int V2 = Aux1(s - cap[i], i, cap) ; 
    if (V2 == INT_MAX)
    {
        return V1 ; 
    }
    return (V1 < V2 + 1) ? V1 : V2 + 1 ; 
}
// Algorithme 1
int Algo1 (PbResoudre *p)
{
    int res = Aux1(p->S, p->k - 1, p->tab) ; 
    return res ; 
}

// Copie le système de capacité passé en paramètre
PbResoudre *copiePbResoudre(PbResoudre *p)
{
    PbResoudre *res = malloc(sizeof(PbResoudre)) ; 
    res->k = p->k ; 
    res->S = p->S ; 
    res->tab = copieTab(0, p->tab, p->k) ; 
    return res ; 
}

// Libère le problème 
void liberePbResoudre (PbResoudre *p)
{
    free(p->tab) ; 
    free(p) ; 
}

// Affiche le problème 
void affichePbResoudre (PbResoudre *p)
{
    printf("k : %d\nS : %d\n", p->k, p->S) ; 
    for (int i = 0 ; i < p->k ; i++)
    {
        printf("%d ", p->tab[i]) ; 
    }
    printf("\n") ; 
}

// Génère un système de capacité exponentiel : V[0] = 1, V[1] = d, etc...
PbResoudre *genereSystemExpo (int k, int d)
{
    PbResoudre *res = malloc(sizeof(PbResoudre)) ; 
    res->k = k ; 
    res->S = 0 ; 
    res->tab = malloc(sizeof(int) * (k)) ; 
    int c = 1 ; 
    for (int i = 0 ; i < k ; i++)
    {
        res->tab[i] = c ; 
        c = c * d ; 
    }
    return res ; 
}


int auxTabBocauxRequisAlgo1 (int s, int i,int *cap, int **tab)
{
    if (s == 0)
    {
        return 0 ; 
    }
    else if (((s >= 1) && (i <= -1)) || ((s < 0) && (i >= 0)))
    {
        return INT_MAX ; 
    }
    
    int V1 = auxTabBocauxRequisAlgo1(s, i - 1, cap, tab) ; 
    int V2 = auxTabBocauxRequisAlgo1(s - cap[i], i, cap, tab) ; 
    if ((V2 == INT_MAX) || (V1 < V2 + 1))
    {
        return V1 ; 
    }
    else 
    {
        (*tab)[i] += 1 ; 
        return V2 + 1 ; 
    }
}
// Renvoie le tableau de bocaux nécessaire pour résoudre le problème passé en paramètre 
int *tabBocauxRequisAlgo1 (PbResoudre *p)
{
    int *tabRes = malloc(sizeof(int) * p->k) ; 
    for (int i = 0 ; i < p->k ; i++)
    {
        tabRes[i] = 0 ; 
    }
    auxTabBocauxRequisAlgo1(p->S, p->k - 1, p->tab, &tabRes) ; 
    return tabRes ; 
}