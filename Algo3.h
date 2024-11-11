#ifndef __ALGO3_H__
#define __ALGO3_H__
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Algo1.h" 

int AlgoGlout (PbResoudre *prob) ; 
int testGloutonCompatible (int k, int *tab) ; 
int *bougeValeurs (int r, int *tab, int len) ; 
int valeurPresente (int *tab, int v, int len) ; 
int insererInt (int v, int *tab, int len) ; 
int *produitSystemeCapaciteAlea (int len, int pmax) ; 
int auxRechercheDicho (int v, int *tab, int i, int j) ; 
void afficheListe (int *tab, int len) ; 
int* tabBocauxRequisAlgo3 (PbResoudre *prob) ; 

#endif