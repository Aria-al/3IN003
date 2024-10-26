#ifndef __ALGO2_1_H__
#define __ALGO2_1_H__
#include <stdlib.h>
#include <stdio.h>
#include "Algo1.h"

int valeurDansMatrice (int i, int j, int s, int k, int **m) ; 
int trouveValeurSuiv (int i, int j, int s, int k, int **m, int *cap) ; 
int **createMat (int s, int k) ;
int **initialiseMat (int s, int k, int *cap) ; 
void afficheMat (int s, int k, int **mat) ; 
int Algo2_1 (int *T) ; 



#endif