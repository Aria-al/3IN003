#ifndef __ALGO2_1_H__
#define __ALGO2_1_H__
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Algo1.h"

typedef struct _Matrice1
{
    PbResoudre *p ; 
    int **m ; 
} Mat1;


int valeurDansMatrice1 (int i, int j, Mat1 *mat) ; 
int calculeCoef1 (int i, int j, Mat1 *mat) ; 
int **creeMat1 (PbResoudre *prob) ; 
Mat1 *initialiseMat1 (PbResoudre *prob) ; 
void libereMat1 (Mat1 *mat) ; 
void afficheMat1 (Mat1 *mat) ; 
int Algo2_1 (PbResoudre *p) ; 

int *auxTabBocauxRequis (int i, int j, Mat1 *mat, int *tab); 
int *tabBocauxRequis (PbResoudre *prob) ; 


#endif 