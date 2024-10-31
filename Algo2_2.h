#ifndef __ALGO2_2_H__
#define __ALGO2_2_H__
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

// Les coefficients de la matrice sont constitués d'arrays de taille k+1
typedef struct _Matrice2
{
    PbResoudre *p ; 
    int ***m ; 
} Mat2 ;

int minimumTab (int* t1, int *t2) ; 
int *valeurDansMatrice2 (int i, int j, Mat2 *mat) ; 
int *calculeCoef2 (int i, int j, Mat2 *mat) ; 
int ***creeMat2 (PbResoudre *prob) ; 
Mat2 *inintialiseMat2 (PbResoudre *prob) ; 
void libereMat2 (Mat2 *mat) ; 
int *Algo2_2 (PbResoudre *p) ; 

#endif