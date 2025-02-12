#include <stdio.h>
#include <stdlib.h>  // Pour malloc et exit
#include <math.h>    // Pour sqrt
#include "image_ppm.h"

int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, SB, SH;

    if (argc != 5) {
        printf("Usage: ImageIn.pgm ImageOut.pgm seuil_bas seuil_haut\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%d", &SB);
    sscanf(argv[4], "%d", &SH);

    OCTET *ImgIn, *ImgOut, *ImgTemp;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    if (nH <= 0 || nW <= 0) {
        printf("Erreur : dimensions invalides de l'image\n");
        exit(1);
    }

    nTaille = nH * nW;

    ImgIn = (OCTET *)malloc(nTaille * sizeof(OCTET));
    ImgOut = (OCTET *)malloc(nTaille * sizeof(OCTET));
    ImgTemp = (OCTET *)malloc(nTaille * sizeof(OCTET));

    if (!ImgIn || !ImgOut || !ImgTemp) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }

    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    memset(ImgTemp, 0, nTaille * sizeof(OCTET));

    for (int i = 1; i < nH - 1; i++) {
        for (int j = 1; j < nW - 1; j++) {
            int index = i * nW + j;
            int verticalGradient = ImgIn[i * nW + j + 1] - ImgIn[index];
            int horizontalGradient = ImgIn[(i + 1) * nW + j] - ImgIn[index];

            double gradient = sqrt((double)(verticalGradient * verticalGradient) + (double)(horizontalGradient * horizontalGradient));

            if (gradient <= SB) gradient = 0;
            else if (gradient >= SH) gradient = 255;

            ImgTemp[index] = (unsigned char)gradient;
        }
    }

    for (int i = 1; i < nH - 1; i++) {
        for (int j = 1; j < nW - 1; j++) {
            int index = i * nW + j;

            if (ImgTemp[index] > SB && ImgTemp[index] < SH) {
                if (ImgTemp[index+nW] == 255 ||
                    ImgTemp[index-nW] == 255 ||
                    ImgTemp[index+1] == 255 ||
                    ImgTemp[index-1] == 255 ||
                    ImgTemp[index+nW+1] == 255 ||
                    ImgTemp[index+nW-1] == 255 ||
                    ImgTemp[index-nW+1] == 255 ||
                    ImgTemp[index-nW-1] == 255) {
                    ImgOut[index] = 255;
                } else {
                    ImgOut[index] = 0;
                }
            } else {
                ImgOut[index] = ImgTemp[index];
            }
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);

    free(ImgIn);
    free(ImgOut);
    free(ImgTemp);

    return 0;
}
