#include <bits/types/FILE.h>
#include <cstdio>
#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;

  if (argc != 3) 
  {
    printf("Usage: ImageIn.ppm ImageOut.pgm \n"); 
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgEcrite);

  OCTET *ImgIn, *ImgOut;

  // Lire les dimensions de l'image
  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);
    printf("nh : %d, nw : %d, nTaille : %d, nTaill3 : %d", nH, nW, nTaille, nTaille3);

    for (int i=0; i < nTaille3; i+=3)
    {
        ImgOut[i/3]=((0.3*ImgIn[i])+(0.59*ImgIn[i+1])+(0.11*ImgIn[i+2]));
    }

    std::string path = "resultat/" + std::string(cNomImgEcrite);  // Concaténation correcte
    ecrire_image_pgm((char*)path.c_str(), ImgOut, nH, nW);
    free(ImgIn); free(ImgOut);

    return 0;
}