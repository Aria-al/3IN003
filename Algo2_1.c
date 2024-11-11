#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Algo1.h"
#include "Algo2_1.h"

/*Dans ce cas, on considère que la matrice est de dimention (s + 1) * (k + 1)*/
// Retourne la valeur (i, j) contenue dans la matrice mat->m, INT_MAX le cas écheant 
int valeurDansMatrice1 (int i, int j, Mat1 *mat)
{
    if ((i >= 0) && (j >= 0) && (i <= mat->p->S) && (j <= mat->p->k))
    {
        return mat->m[i][j] ; 
    }
    return INT_MAX ; 
}

/*
Trouve la valeur suivante du coefficient m(i, j), avec : 
- cap : le tableau des capacités de pots 
- m : matrice de dimension (s + 1) * (k + 1)
- i : la quantité restante à stocker 
- j : le pot considéré 
*/
int calculeCoef1 (int i, int j, Mat1 *mat)
{
    int memeLigneCoef = valeurDansMatrice1 (i, j - 1, mat) ; 
    int memeColonneCoef = valeurDansMatrice1 (i - mat->p->tab[j - 1], j, mat) ; 
    if (memeColonneCoef == INT_MAX)
    {
        memeColonneCoef = INT_MAX - 1 ; 
    }

    return minimumInt(memeLigneCoef, memeColonneCoef + 1) ; 
}

// Renvoie une matrice d'entiers non initialisé de taille (s+1) * (k+1)
int **creeMat1 (PbResoudre *prob) 
{
    int **Mat = malloc(sizeof(int*)*(prob->S+1)) ; 

    for (int i = 0 ; i < prob->S + 1 ; i++)
    {
        Mat[i] = malloc(sizeof(int)*(prob->k + 1)) ; 
    }

    return Mat ; 
}

// Initalise la matrice des pots nécessaires, avec les capacités des pots dans cap 
Mat1 *initialiseMat1 (PbResoudre *prob)
{
    Mat1 *res = malloc(sizeof(Mat1)) ; 

    res->m = creeMat1(prob) ; 
    res->p = copiePbResoudre(prob) ; 

    for (int i = 0 ; i < prob->S + 1 ; i++)
    {
        res->m[i][0] = INT_MAX ; 
    }

    for (int j = 1 ; j < prob->k + 1 ; j++)
    {
        res->m[0][j] = 0 ; 
    }

    for (int i = 1 ; i < prob->S + 1 ; i++)
    {
        for (int j = 1 ; j < prob->k + 1 ; j++)
        {
            res->m[i][j] = calculeCoef1(i, j, res) ; 
        }
    }

    return res ; 
}

void afficheMat1 (Mat1 *mat)
{
    for (int i = 0 ; i < mat->p->S + 1 ; i++) 
    {
        printf("[") ; 
        for (int j = 0 ; j < mat->p->k + 1 ; j++)
        {
            if (mat->m[i][j] == INT_MAX)
            {
                printf("+inf ") ; 
            }
            else 
            {
                printf("%d ", mat->m[i][j]) ; 
            }
        }
        printf("]\n") ; 
    }
}

// Libère la mémoire occupé par une matrice de taille (s+1)*(k+1)
void libereMat1 (Mat1 *mat)
{
    for (int i = 0 ; i < mat->p->S + 1 ; i++)
    {
        free(mat->m[i]) ; 
    }
    liberePbResoudre(mat->p) ; 
    free(mat->m) ; 
    free(mat) ; 
}

int Algo2_1 (PbResoudre *p)
{
    Mat1 *mat = initialiseMat1(p) ; 
    int res = mat->m[mat->p->S][mat->p->k] ; 
    //afficheMat1(mat) ; 
    libereMat1(mat) ; 
    return res ; 
}

int *auxTabBocauxRequisAlgo2 (int i, int j, Mat1 *mat, int *tab)
{
    if ((i <= 0) || (j <= 0))
    {
        int *res = malloc(sizeof(int) * (mat->p->k)) ; 
        for (int i = 0 ; i < mat->p->k ; i++)
        {
            res[i] = 0 ; 
        }
        return res ; 
    }

    if(valeurDansMatrice1(i, j, mat) == valeurDansMatrice1(i, j - 1, mat))
    {
        return auxTabBocauxRequisAlgo2(i, j - 1, mat, tab) ; 
    }
    else if (valeurDansMatrice1(i, j, mat) == (valeurDansMatrice1(i - mat->p->tab[j - 1], j, mat) + 1))
    {
        int *res = auxTabBocauxRequisAlgo2(i - mat->p->tab[j - 1], j, mat, tab) ; 
        res[j - 1] += 1 ; 
        return res ; 
    }

}

// Retourne les bocaux requis pour achever la bonne capacité 
int *tabBocauxRequisAlgo2 (PbResoudre *prob)
{
    Mat1 *mat = initialiseMat1(prob) ; 
    int *res = auxTabBocauxRequisAlgo2(mat->p->S, mat->p->k, mat, NULL) ; 
    return res ; 
}