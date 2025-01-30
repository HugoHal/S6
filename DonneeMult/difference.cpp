#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"

int main(int argc, char* argv[]) {
    char cNomImgLue[250],cNomImgLue2[250] , cNomImgEcrite[250];
    int nH, nW, nTaille;
    
    if (argc != 4) {
        printf("Usage: %s ImageIn1.pgm ImageIn2.pgm ImageOut.pgm\n", argv[0]);
        return 1;
    }
    
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgLue2);
    sscanf(argv[3], "%s", cNomImgEcrite);
    
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    
    OCTET *ImgIn1, *ImgIn2, *ImgOut;
    allocation_tableau(ImgIn1, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn1, nTaille);
    allocation_tableau(ImgIn2, OCTET, nTaille);
    lire_image_pgm(cNomImgLue2, ImgIn2, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);
    
    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            if (ImgIn1[i * nW + j] == ImgIn2[i * nW + j]) {
                ImgOut[i * nW + j] = 255;
            } else {
                ImgOut[i * nW + j] = 0;
            }
        }
    }
    
    // Gérer les bords en copiant les pixels d'origine
    
    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn1);
    free(ImgIn2);
    free(ImgOut);
    
    return 0;
}