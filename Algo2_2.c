#include <stdlib.h>
#include <stdio.h>
#include "Algo1.h"
#include "Algo2_2.h"

/*Dans ce cas, on considère que la matrice est de dimention (s + 1) * (k + 1) 
Et que chaque coefficient (i, j) est un array de taille k+1, et M[i][j][1 : ] 
est la liste des nombres de pots employés pour obtenir M(i, j), avec 
M[i][j][0] = somme des M[i][j][1 : ]*/

// Retourne 1 si t1[0] < t2[0] + 1 ou t2 == NULL, 0 si t1[0] >= t2[0] + 1 ou t1 == NULL 
int minimumTab (int* t1, int *t2) 
{
    if (!t1)
    {
        return 0 ; 
    }
    else if (!t2)
    {
        return 1 ; 
    }
    else 
    {
        return t1[0] < t2[0] + 1 ; 
    }
}

// Retourne l'array à la coordonné (i, j), NULL si c'est impossible
int *valeurDansMatrice2 (int i , int j, Mat2 *mat)
{
    if ((i >= 0) && (j >= 0) && (i <= mat->p->S + 1) && (j <= mat->p->k +1))
    {
        return mat->m[i][j] ; 
    }
    return NULL ; 
}

// Calcule le coefficient (i, j)
int *calculeCoef2 (int i, int j, Mat2 *mat) 
{
    int *memeLigneCoef = valeurDansMatrice2(i, j - 1, mat) ; 
    int *memeColonneCoef = valeurDansMatrice2(i - mat->p->tab[j - 1], j, mat) ; 
    int d = minimumTab(memeLigneCoef, memeColonneCoef) ; 
    // memeColonneCoef est nul alors que devrait être non nul  
    if (d)
    {
        return copieTab(0, memeLigneCoef, mat->p->k + 1) ; 
    }
    else
    {
        int *res = copieTab(0, memeColonneCoef, mat->p->k + 1) ; 
        res[0] += 1 ; 
        res[j + 1] += 1 ; 
        return res ; 
    }
}

int ***creeMat2(PbResoudre *prob) 
{
    int ***res = malloc(sizeof(int**) * (prob->S + 1)) ; 
    for (int i = 0 ; i < prob->S + 1; i++)
    {
        res[i] = malloc(sizeof(int*) * (prob->k + 1)) ; 
    }
    return res ; 
}

Mat2 *inintialiseMat2(PbResoudre *prob)
{
    Mat2 *res = malloc(sizeof(Mat2)) ; 
    res->m = creeMat2(prob) ; 
    res->p = copiePbResoudre(prob) ;  

    for (int i = 0 ; i < prob->S + 1 ; i++)
    {
        res->m[i][0] = NULL ; 
    }

    for (int j = 1 ; j < prob->k + 1 ; j++)
    {
        res->m[0][j] = malloc(sizeof(int) * (prob->k+1)) ; 
        for (int k = 0 ; k < prob->k + 1 ; k++)
        {
            res->m[0][j][k] = 0 ; 
        }
    }
    
    for (int j = 1 ; j < prob->k + 1 ; j++)
    {
        for (int i = 1 ; i < prob->S + 1 ; i++)
        {
            res->m[i][j] = calculeCoef2(i, j, res) ; 
        }
    }
    
    return res ; 
}

void libereMat2 (Mat2 *mat)
{
    for (int i = 0 ; i < mat->p->S + 1 ; i++)
    {
        for (int j = 0 ; j < mat->p->k + 1 ; j++)
        {
            if (mat->m[i][j])
            {
                free(mat->m[i][j]) ; 
            }
        }
    }
    liberePbResoudre(mat->p) ; 
    free(mat->m) ; 
    free(mat) ; 
}

int *Algo2_2(PbResoudre *prob)
{
    Mat2 *m = inintialiseMat2(prob) ; 
    int *res = copieTab(0, m->m[prob->S][prob->k], prob->k + 1) ; 
    libereMat2(m) ; 
    return res ; 
}