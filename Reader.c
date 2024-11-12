#include <stdlib.h>
#include <stdio.h>
#include "Algo1.h"

/*
Renvoie un problème en lisant filename qui contient : 
*/ 
PbResoudre *litProbleme (char *filename) 
{
    FILE *f = fopen (filename, "r") ; 
    if (!f)
    {
        printf("Fichier non trouve : %s\n", filename) ; 
        return NULL ; 
    }

    int S = -1 ; 
    int k = -1 ; 
    if (!fscanf(f, "%d\n", &S) || S < 0)
    {
        printf("Erreur de formattage du fichier %s pour la valeur S\n", filename) ; 
        fclose (f) ; 
        return NULL ; 
    }
    if (!fscanf(f, "%d\n", &k) || k <= 0)
    {
        printf("Erreur de formattage du fichier %s pour la valeur k\n", filename) ; 
        fclose (f) ; 
        return NULL ; 
    }
    PbResoudre *res = malloc(sizeof(PbResoudre)) ;
    res->k = k ; 
    res->S = S ; 
    res->tab = malloc(sizeof (int) * k) ; 
    int c = 0 ; 
    int i = 0 ; 
    while (i < k)
    {
        fscanf(f, "%d\n", &c) ; 
        res->tab[i] = c ;
        i += 1 ; 
    }

    fclose (f) ; 
    return res ; 
}

