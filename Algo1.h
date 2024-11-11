#ifndef __ALGO1_1_H__
#define __ALGO1_1_H__
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct _problemeResoudre 
{
    int S ; 
    int k ; 
    int *tab ; 
} PbResoudre ;


int minimumInt (int a, int b) ; 
int *copieTab (int k, int *T, int len) ; 
int Aux1(int s, int i,int *cap) ; 
int Algo1 (PbResoudre *T) ;
PbResoudre *copiePbResoudre (PbResoudre *p) ; 
void liberePbResoudre (PbResoudre *p) ; 
PbResoudre *genereSystemExpo (int k, int d) ; 
void affichePbResoudre (PbResoudre *p) ; 
int auxTabBocauxRequisAlgo1 (int s, int i,int *cap, int **tab) ; 
int *tabBocauxRequisAlgo1 (PbResoudre *p) ; 

#endif