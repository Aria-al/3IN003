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

int* tabBocauxRequisAlgo3 (PbResoudre *prob)
{
    int *res = malloc(sizeof(int) * prob->k) ; 
    for (int i = 0 ; i < prob->k ; i++)
    {
        res[i] = 0 ; 
    }
    int i = prob->k - 1 ; 
    int q = prob->S ; 
    int d = q - prob->tab[i] ; 
    while (q > 0)
    {
        while (d < 0 && i > 0)
        {
            i = i - 1 ; 
            d = q - prob->tab[i] ; 
        }
        q = q - prob->tab[i] ; 
        d = q - prob->tab[i] ; 
        res[i] += 1 ;
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
        int valeurSuivante = 0 ; 
        int valeurPrecedente = tab[r] ;  
        tab[r] = 0 ; 
        for (int i = r ; i < len - 1 ; i++)
        {
            valeurSuivante = tab[i + 1] ; 
            tab[i + 1] = valeurPrecedente ; 
            valeurPrecedente = valeurSuivante ; 
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
// Si la valeur est déja présente dans la liste, elle ne l'ajoute pas 
void insererInt (int v, int *tab, int len)
{
    int p = rechercheDicho(v, tab, len) ; 
    if (p != -1)
    {
        return ; 
    }
    p = 0 ; 
    while (tab[p] < v)
    {
        p += 1 ; 
    }
    bougeValeurs(p, tab, len) ; 
    tab[p] = v ; 
}

// Produit un système de capacité aléatoire, on suppose aussi 
// que pmax > len, sinon il manque des valeurs 
////////////////////////////////////
////////////////////////////// ALERTE : CE CODE NE MARCHE PAS, NE BOUGE PAS LES VALEURS CORRECTEMENT 
///// ET GENERE SOIT UN 0 OU UN 1 POUR LA PREMIERER VALEUR
int *produitSystemeCapaciteAlea (int len, int pmax)
{
    int *res = malloc(sizeof(int) * len) ; 
    // Si pmax <= len ; on peut mettre chacun des nombres entres 1 et pmax dans la liste  
    if (pmax <= len)
    {
        printf("pmax : %d <= len : %d\nLe système de capacité ne peux pas etre construit\n", pmax, len) ; 
        return NULL ; 
    }
    else 
    {
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
                insererInt(val, res, len) ; 
                nbInsere += 1 ; 
            }
        }
    }

    // BAND-AID FIX, REPARER L'ERREUR
    if (res[0] != 1)
    {
        int d = 0 ; 
        if (res[0] < 1)
        {
            d = res[0] + 1 ; 
        }
        else 
        {
            d = -res[0] + 1 ; 
        }
        for (int i = 0 ; i < len ; i++)
        {
            res[i] += d ; 
        }
    }
    return res ; 
}

void afficheListe (int *tab, int len)
{
    for (int i = 0 ; i < len ; i++)
    {
        printf("%d ", tab[i]) ; 
    }
    printf("\n") ; 
}