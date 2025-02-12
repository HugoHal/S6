#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"

int main(int argc, char* argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;
    
    if (argc != 3) {
        printf("Usage: %s ImageIn.pgm ImageOut.pgm\n", argv[0]);
        return 1;
    }
    
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    
    OCTET *ImgIn, *ImgOut;
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);
    
    for (int i = 1; i < nH - 1; i++) {
        for (int j = 1; j < nW - 1; j++) {
            ImgOut[i * nW + j] = (ImgIn[i * nW + j]+ImgIn[(i-1) * nW + j]+ImgIn[(i+1) * nW + j]+ImgIn[i * nW + (j - 1)]+ImgIn[i * nW + (j + 1)])/5;
        }
    }
    
    // Gérer les bords en copiant les pixels d'origine
    for (int i = 0; i < nW; i++) {
        ImgOut[i] = ImgIn[i];
        ImgOut[(nH - 1) * nW + i] = ImgIn[(nH - 1) * nW + i];
    }
    for (int i = 0; i < nH; i++) {
        ImgOut[i * nW] = ImgIn[i * nW];
        ImgOut[i * nW + (nW - 1)] = ImgIn[i * nW + (nW - 1)];
    }
    
    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);
    
    return 0;}