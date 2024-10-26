#include <stdlib.h>
#include <stdio.h>

/*
Renvoie un tableau contenant : 
T[0] := S
T[1] := k
T[i+2] := capacité du i-ème pot 
*/ 
int *read_capacity (char *filename) 
{
    FILE *f = fopen (filename, "r") ; 
    if (!f)
    {
        printf("File not found : %s\n", filename) ; 
        return NULL ; 
    }

    int *res = NULL ;
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
    res = malloc(sizeof(int) * (k + 2)) ; 

    int c = 0 ; 
    res[0] = S ; 
    res[1] = k ; 
    int i = 2 ; 
    while (i < k + 2)
    {
        fscanf(f, "%d", &c) ; 
        printf("Hi : %d\n",c) ; 
        res[i] = c ;
        i += 1 ; 
    }

    fclose (f) ; 
    return res ; 
}

void affiche_valeurs (int *T)
{
    printf("V = %d\nK=%d\n", T[0], T[1]) ; 
    for (int i = 2 ; i < T[1] + 2 ; i++)
    {
        printf("T[%d] = %d\n", i+2, T[i]) ; 
    }
}

int main(int argc, char const *argv[])
{
    int *k = read_capacity("Valeurs.txt") ; 
    affiche_valeurs(k) ; 
    free(k) ; 
    return 0 ;
}
