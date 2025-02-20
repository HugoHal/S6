#include <stdio.h>
#include <stdlib.h> // Ajouté pour la fonction exit
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgOut[250], cNomImgY[250], cNomImgCb[250], cNomImgCm[250];
  int nH, nW, nTaille;

  if (argc != 5) 
  {
    printf("Usage: ImageYIn.pgm ImageCbIn.pgm ImageCmIn.pgm ImageOut.ppm \n"); 
    exit(1);
  }

    sscanf(argv[4], "%s", cNomImgOut);
    sscanf(argv[1], "%s", cNomImgY);
    sscanf(argv[2], "%s", cNomImgCb);
    sscanf(argv[3], "%s", cNomImgCm);

    OCTET *ImgOut, *ImgInY, *ImgInCb, *ImgInCm;

  // Lire les dimensions de l'image
    lire_nb_lignes_colonnes_image_pgm(cNomImgY, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgInY, OCTET, nTaille);
    allocation_tableau(ImgInCb, OCTET, nTaille);
    allocation_tableau(ImgInCm, OCTET, nTaille);
    lire_image_pgm(cNomImgY, ImgInY, nH * nW);
    lire_image_pgm(cNomImgCb, ImgInCb, nH * nW);
    lire_image_pgm(cNomImgCm, ImgInCm, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);
    printf("nh : %d, nw : %d, nTaille : %d, nTaill3 : %d", nH, nW, nTaille, nTaille3);

    for (int i=0; i < nTaille3; i+=3)
    {
        int Y = ImgInY[i/3] ;
        int Cb = ImgInCb[i/3];
        int Cr = ImgInCm[i/3];
        ImgOut[i]= Y + 1.402 * (Cr - 128);
        ImgOut[i+1] =  Y - 0.34414 * (Cb - 128) - 0.714414 * (Cr - 128);
        ImgOut[i+2] = Y + 1.772 * (Cb - 128);
    }


    ecrire_image_ppm(cNomImgOut, ImgOut,  nH, nW);
    free(ImgInY); free(ImgOut); free(ImgInCb); free(ImgInCm);

    return 1;
}