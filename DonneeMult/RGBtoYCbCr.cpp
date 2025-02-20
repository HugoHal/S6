#include <stdio.h>
#include <stdlib.h> // Ajouté pour la fonction exit
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgY[250], cNomImgCb[250], cNomImgCm[250];
  int nH, nW, nTaille;

  if (argc != 5) 
  {
    printf("Usage: ImageIn.ppm ImageYOut.pgm ImageCbOut.pgm ImageCmOut.pgm\n"); 
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgY);
  sscanf(argv[3], "%s", cNomImgCb);
  sscanf(argv[4], "%s", cNomImgCm);

  OCTET *ImgIn, *ImgOutY, *ImgOutCb, *ImgOutCm;

  // Lire les dimensions de l'image
  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOutY, OCTET, nTaille);
    allocation_tableau(ImgOutCb, OCTET, nTaille);
    allocation_tableau(ImgOutCm, OCTET, nTaille);
    printf("nh : %d, nw : %d, nTaille : %d, nTaill3 : %d", nH, nW, nTaille, nTaille3);

    for (int i=0; i < nTaille3; i+=3)
    {
        int R = ImgIn[i] ;
        int G = ImgIn[i+1];
        int B = ImgIn[i+2];
        ImgOutY[i/3]= 0.299*R + 0.587*G + 0.114*B;
        ImgOutCb[i/3] = -0.1687*R -0.3313*G + 0.5*B + 128;
        ImgOutCm[i/3] = 0.5*R - 0.4187*G - 0.0813*B + 128;
    }

    ecrire_image_pgm(cNomImgY, ImgOutY,  nH, nW);
    ecrire_image_pgm(cNomImgCb, ImgOutCb,  nH, nW);
    ecrire_image_pgm(cNomImgCm, ImgOutCm,  nH, nW);
    free(ImgIn); free(ImgOutY); free(ImgOutCb); free(ImgOutCm);

    return 1;
}