#include <stdlib.h>
#include <stdio.h>
#include "Algo1.h"
#include "Algo2_1.h"

/*Dans ce cas, on considère que la matrice est de dimention (s + 1) * (k + 1)*/
// Retourne la valeur (i, j) contenue dans la matrice m, INT_MAX le cas écheant 
int valeurDansMatrice (int i, int j, int s, int k, int **m)
{
    if ((i < 0 || j < 0) || (i > s || j > k))
    {
        return INT_MAX ; 
    }
    return m[i][j] ; 
}

/*
Trouve la valeur suivante du coefficient m(i, j), avec : 
- cap : le tableau des capacités de pots 
- m : matrice de dimension (s + 1) * (k + 1)
- i : la quantité restante à stocker 
- j : le pot considéré 
*/
int trouveValeurSuiv (int i, int j, int s, int k, int **m, int *cap)
{
    int sameLineCoef = valeurDansMatrice(i, j - 1, s, k, m) ; 
    int sameColumnCoef = valeurDansMatrice(i - cap[j], j, s, k, m) ; 
    if (sameColumnCoef == INT_MAX)
    {
        sameColumnCoef = INT_MAX - 1 ; 
    }
    return minimum(sameLineCoef, sameColumnCoef + 1) ; 
}

// Renvoie une matrice d'entiers non initialisé de taille (s+1) * (k+1)
int **createMat (int s, int k) 
{
    int **Mat = malloc(sizeof(int*)*(s+1)) ; 

    for (int i = 0 ; i < s + 1 ; i++)
    {
        Mat[i] = malloc(sizeof(int)*(k + 1)) ; 
    }

    return Mat ; 
}

// Initalise la matrice des pots nécessaires, avec les capacités des pots dans cap 
int **initialiseMat (int s, int k, int *cap)
{
    int **res = createMat(s, k) ; 

    for (int i = 0 ; i < s + 1 ; i++)
    {
        res[i][0] = INT_MAX ; 
    }

    for (int j = 1 ; j < k + 1 ; j++)
    {
        res[0][j] = 0 ; 
    }

    for (int j = 1 ; j < k + 1 ; j++)
    {
        for (int i = 1 ; i < s + 1 ; i++)
        {
            res[i][j] = trouveValeurSuiv(i, j, s, k, res, cap) ; 
        }
    }

    return res ; 
}

void afficheMat (int s, int k, int **mat)
{
    for (int i = 0 ; i < s + 1 ; i++) 
    {
        printf("[") ; 
        for (int j = 0 ; j < k + 1 ; j++)
        {
            if (mat[i][j] == INT_MAX)
            {
                printf("+inf ") ; 
            }
            else 
            {
                printf("%d ", mat[i][j]) ; 
            }
        }
        printf("]\n") ; 
    }
}

// Libère la mémoire occupé par une matrice de taille (s+1)*(k+1)
void libereMat (int s, int k, int **mat)
{
    for (int i = 0 ; i < s + 1 ; i++)
    {
        free(mat[i]) ; 
    }
    free(mat) ; 
}

int Algo2_1 (int *T)
{
    int S = T[0] ; 
    int k = T[1] ; 
    int *cap = copieTab(2, T, k+2) ; 
    int **Mat = initialiseMat(S, k, cap) ; 
    int res = Mat[S][k] ; 
    libereMat(S, k, Mat) ; 
    return Mat[S][k] ; 
}