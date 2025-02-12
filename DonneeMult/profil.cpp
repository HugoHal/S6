#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Pour malloc et free
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250], lc[3];
    int nH, nW, indice, taillecl;

    if (argc != 4)  
    {
        printf("Usage: ImageIn.pgm lin/col indice \n"); 
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[3], "%d", &indice);
    sscanf(argv[2], "%s", lc);

    OCTET *ImgIn;
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);

    int nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille); // Appel sans capturer la valeur de retour

    // Déterminer la taille en fonction de l'argument "lin" ou "col"
    if (strcmp(lc, "col") == 0)
        taillecl = nH;
    else if (strcmp(lc, "lin") == 0)
        taillecl = nW;
    else
    {
        printf("Erreur : Le deuxième argument (%s) doit être 'lin' ou 'col'.\n", lc);
        exit(1);
    }

    // Allocation dynamique pour le tableau des fréquences
    int* res = (int*)malloc(256 * sizeof(int)); // Allocation pour 256 niveaux de gris
    if (res == NULL) {
        printf("Erreur d'allocation mémoire pour 'res'.\n");
        free(ImgIn);
        exit(1);
    }
    memset(res, 0, 256 * sizeof(int));  // Initialisation à 0

    // Calcul des fréquences
    if (strcmp(lc, "col") == 0) {
        for (int i = 0; i < nH; i++) {
            int pixelValue = ImgIn[i * nW + indice];
            res[pixelValue]++;
        }
    } else {
        for (int i = 0; i < nW; i++) {
            int pixelValue = ImgIn[indice * nW + i];
            res[pixelValue]++;
        }
    }

    // Écriture des résultats dans le fichier
    FILE* file = fopen("fich.dat", "w");
    if (file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier fich.dat.\n");
        free(res);
        free(ImgIn);
        exit(1);
    }

    for (int i = 0; i < 256; i++) {
        fprintf(file, "%d %d\n", i, res[i]);
    }

    fclose(file); // Fermeture du fichier
    printf("Résultats écrits dans fich.dat\n");

    // Libération de la mémoire
    free(res);
    free(ImgIn);

    return 0;
}
