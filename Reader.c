#include <stdlib.h>
#include <stdio.h>
#include "Algo1.h"

/*
Renvoie un problème en lisant filename qui contient : 
*/ 
PbResoudre *lit_probleme (char *filename) 
{
    FILE *f = fopen (filename, "r") ; 
    if (!f)
    {
        printf("File not found : %s\n", filename) ; 
        return NULL ; 
    }

    int S = -1 ; 
    int k = -1 ; 
    if (!fscanf(f, "%d", &S) || S < 0)
    {
        fclose (f) ; 
        return NULL ; 
    }
    if (!fscanf(f, "%d", &k) || k <= 0)
    {
        fclose (f) ; 
        return NULL ; 
    }
    PbResoudre *res = malloc(sizeof(PbResoudre)) ;
    res->k = k ; 
    res->S = S ; 
    int c = 0 ; 
    int i = 0 ; 
    while (i < k )
    {
        fscanf(f, "%d", &c) ; 
        printf("Hi : %d\n",c) ; 
        res->tab[i] = c ;
        i += 1 ; 
    }

    fclose (f) ; 
    return res ; 
}

