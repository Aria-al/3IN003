#ifndef __PERFORMANCEALGO_H__
#define __PERFORMANCEALGO_H__
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "Algo2_1.h"
#include "Algo1.h"
#include "Algo3.h"


typedef struct _tableTemps
{
    int len ; 
    double *listeTemps ;
} TabTemps ;

double mesureTempsExec (PbResoudre *prob, int (*f) (PbResoudre*) ) ; 
double *copieTabDouble (int newLen, double *tab) ; 
TabTemps *perfFonctionDeS (int d, int k, int valMaxS, int (*f) (PbResoudre*)) ; 
TabTemps *perfFonctionDeK (int d, int s, int valMaxK, int (*f) (PbResoudre*)) ; 
int* ecartRelatif (int pmax, int nbBocaux, int f, int nbTirages) ; 
void ecrireListeDouble (char *filename, TabTemps *tab) ; 
void ecrireListeDoubleSystemeExpo (char *filename, TabTemps **liste) ; 
void libereTabTemps (TabTemps *t) ; 

#endif