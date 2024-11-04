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
        tab[r] = 0 ; 
        for (int i = r ; i < len - 1 ; i++)
        {
            temp = tab[i + 1] ; 
            tab[i + 1] = tempPrec ; 
            tempPrec = temp ; 
        }
    }
    return tab ; 
}

// Détermine l'indice du tableau triée tab[i, j] k tel que tab[k] = v, retourne -1 si c'est impossible 
int auxRechercheDicho (int v, int *tab, int i, int j)
{
    if (i > j)
    {
        return -2 ; 
    }
    /*
    
    */
    else if (i - j == 1)
    {
        return v == tab[i] ; 
    }
    else if (i == j)
    {
        return -1 ; 
    }
    else 
    {
        int c = tab[(i + j) / 2] ; 
        if (v < c)
        {
            return auxRechercheDicho(v, tab, i, (i+j)/2) ; 
        }
        else if (v == c)
        {
            return (i + j) / 2 ; 
        }
        else 
        {
            return auxRechercheDicho(v, tab, (i+j)/2 + 1, j) ; 
        }
    }
}

// Détermine l'indice du tableau triée tab[i, j] k tel que tab[k] = v, retourne -1 si c'est impossible 
int rechercheDicho (int v, int *tab, int len)
{
    return auxRechercheDicho(v, tab, 0, len) ; 
}

// Retourne l'indexe de la valeur v si elle est présente dans le tableau tab, -1 sinon 
int valeurPresente (int *tab, int v, int len)
{
    for (int i = 0 ; i < len ; i++)
    {
        if (tab[i] == v)
        {
            return i ; 
        }
    }
    return -1 ; 
}

// Insère un entier v dans la liste, retourne 1 si réuissi, 0 si la liste est pleine 
// On suppose que les éléments non assignés sont égaux à INT_MAX
// NE VERIFIE PAS SI L'ELEMENT EST DEJA PRESENT DANS LA LISTE 
int insererInt (int v, int *tab, int len)
{
    int p = 0 ; 
    while ((tab[p] < v) && (p < len - 1))
    {
        p += 1 ; 
    }
    if (p >= len)
    {
        return 0 ; 
    }
    tab = bougeValeurs(p + 1, tab, len) ; 
    tab[p] = v ; 
    return 1 ; 
}

int *produitSystemeCapaciteAlea (int len, int pmax)
{
    int *res = malloc(sizeof(int) * len) ; 
    res[0] = 1 ; 
    for (int i = 1 ; i < len ; i++)
    {
        res[i] = INT_MAX ; 
    }
    int nbInsere = 1 ; 
    while (nbInsere < len)
    {
        int val = rand() % pmax ; 
        if (rechercheDicho(val, res, len) == -1)
        {
            
        }
    }

}