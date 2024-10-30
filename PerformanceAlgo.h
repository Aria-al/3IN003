#ifndef __PERFORMANCEALGO_H__
#define __PERFORMANCEALGO_H__
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
TabTemps *perfFonctionDeS (int d, int k, int valMaxS, int (*f) (PbResoudre*)) ; 
void ecrireListeDouble (char *filename, TabTemps *tab) ; 
#endif