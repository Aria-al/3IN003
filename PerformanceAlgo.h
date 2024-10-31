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
double *copieTabDouble (int oldLen, int newLen, double *tab) ; 
TabTemps *perfFonctionDeS (int d, int k, int valMaxS, int nbMesure, int (*f) (PbResoudre*)) ; 
void ecrireListeDouble (char *filename, TabTemps *tab) ; 
#endif