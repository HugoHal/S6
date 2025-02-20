#include <stdio.h>
#include <stdlib.h> // Ajouté pour la fonction exit
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgOut[250], cNomImgY[250], cNomImgCb[250], cNomImgCm[250];
  int nH, nW, nTaille, k;

  if (argc != 4) 
  {
    printf("Usage: ImageYIn.pgm ImageOut.pgm k(int entre -128 et 128)\n"); 
    exit(1);
  }

    sscanf(argv[2], "%s", cNomImgOut);
    sscanf(argv[1], "%s", cNomImgY);
    sscanf(argv[3], "%d", &k);

    OCTET *ImgOut, *ImgInY;

    lire_nb_lignes_colonnes_image_pgm(cNomImgY, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;

    allocation_tableau(ImgInY, OCTET, nTaille);

    lire_image_pgm(cNomImgY, ImgInY, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille3);

    printf("nh : %d, nw : %d, nTaille : %d, nTaill3 : %d", nH, nW, nTaille, nTaille3);

    for (int i=0; i < nTaille; i++)
    {
        int a = ImgInY[i] + k;
        if (a < 0) {
            ImgOut[i] = 0;
        } else {
            if (a > 255) {
                ImgOut[i] = 255;
            } else {
                ImgOut[i] = a;
            }
        }
    }

    ecrire_image_pgm(cNomImgOut, ImgOut,  nH, nW);
    free(ImgInY); free(ImgOut);

    return 1;
}