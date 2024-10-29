#include <stdlib.h>
#include <stdio.h>
#include "Algo1.h"

// Minimum entre a et b des relatifs 
int minimumInt (int a, int b)
{
    if (a < b)
    {
        return a ; 
    }
    return b ; 
}

// Renvoie la copie des tableau T[k:] de longueur len
int *copieTab (int k, int *T, int len) 
{
    int *res = malloc(sizeof(int) * (len - k)) ; 
    for (int i = k ; i < len ; i++)
    {
        res[i - k] = T[i] ; 
    }
    return res ; 
}

// ALGORITHME I 

int Aux1(int s, int i,int *cap) 
{
    if (s == 0) 
    {
        return 0 ; 
    }
    else if ((s < 0) || (i == 0))
    {
        return INT_MAX ; 
    }
    
    int V1 = Aux1(s, i - 1, cap) ; 
    int V2 = Aux1(s - cap[i], i, cap) ; 
    if (V2 == INT_MAX)
    {
        V2 -= 1 ; 
    }
    return minimumInt(V1, V2+1) ; 
}

/* Renvoie la valeur de M(S, k), en prenant en paramètre un tableau qui est dans le format suivant : 
T[0] = S ;  T[1] = k ; T[i] = V[i-2] pour tout i < k*/ 
int Algo1 (PbResoudre *p)
{
    int res = Aux1(p->S, p->k, p->tab) ; 
    return res ; 
}

PbResoudre *copiePbResoudre(PbResoudre *p)
{
    PbResoudre *res = malloc(sizeof(PbResoudre)) ; 
    res->k = p->k ; 
    res->S = p->S ; 
    res->tab = copieTab(0, p->tab, p->k) ; 
    return res ; 
}

void liberePbResoudre (PbResoudre *p)
{
    free(p->tab) ; 
    free(p) ; 
}