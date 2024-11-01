#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Algo1.h" 

int AlgoGlout (PbResoudre *prob)
{
    int i = prob->k - 1 ; 
    int q = prob->S ; 
    int d = q - prob->tab[i] ; 
    int res = 0 ; 
    while (q > 0)
    {
        while (d < 0 && i > 0)
        {
            i = i - 1 ; 
            d = q - prob->tab[i] ; 
        }
        q = q - prob->tab[i] ; 
        d = q - prob->tab[i] ; 
        res += 1 ;
    }
    return res ; 
}

int testGloutonCompatible (int k, int *tab)
{
    if (k >= 3)
    {
        PbResoudre *prob = malloc(sizeof(PbResoudre)) ; 
        prob->k = k ; 
        prob->tab = copieTab(0, tab, k) ; 
        prob->S = prob->tab[2] + 2 ; 
        PbResoudre *probC = copiePbResoudre(prob) ; 

        while (prob->S < prob->tab[k-2] + prob->tab[k-1] - 1)
        {
            for (int j = 0 ; j < k ; j++)
            {
                probC->S = prob->S - prob->tab[j] ; 
                if ((prob->tab[j] < prob->S) && (AlgoGlout(prob) > 1 + AlgoGlout(probC)))
                {
                    liberePbResoudre(prob) ; 
                    liberePbResoudre(probC) ; 
                    return 0 ; 
                }
            }
            prob->S += 1 ; 
        }
        liberePbResoudre(prob) ; 
        liberePbResoudre(probC) ; 
    }
    return 1 ; 
}

// Décale tout les nombres à partir du rang r de 1 emplacement vers la droite 
int *bougeValeurs (int r, int *tab, int len)
{
    if (r < len - 1)
    {
        int temp = 0 ; 
        int tempPrec = tab[r] ;  
        for (int i = r ; i < len - 1 ; i++)
        {
            temp = tab[i + 1] ; 
            tab[i + 1] = tempPrec ; 
            tempPrec = temp ; 
        }
    }
    return tab ; 
}

int valeurPresente (int *tab, int v, int len)
{
    
}

int *insererInt (int v, int *tab, int len)
{
    int p = 0 ; 
    while (tab[p] < v)
    {
        p += 1 ; 
    }
}

int *produitSystemeCapaciteAlea (int len, int pmax)
{
    int *res = malloc(sizeof(int) * len) ; 
    res[0] = 1 ; 

}