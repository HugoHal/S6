// test_couleur.cpp : Inverse une image en niveau de gris

#include <stdio.h>
#include <stdlib.h> // Ajouté pour la fonction exit
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;

  if (argc != 3) 
  {
    printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgEcrite);

  OCTET *ImgIn, *ImgOut;

  // Lire les dimensions de l'image
  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  // Allocation des tableaux d'images
  ImgIn = (OCTET *)malloc(nTaille * sizeof(OCTET)); // Utilisation de malloc
  ImgOut = (OCTET *)malloc(nTaille * sizeof(OCTET));

  if (ImgIn == NULL || ImgOut == NULL) {
    printf("Erreur d'allocation de mémoire\n");
    exit(1);
  }

  // Lire l'image en niveau de gris
  lire_image_pgm(cNomImgLue, ImgIn, nTaille);

  // Inverser les pixels
  for (int i = 0; i < nTaille; i++) {
    ImgOut[i] = 255 - ImgIn[i]; // Inverse la valeur du pixel
  }

  // Écrire l'image modifiée
  ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);

  // Libérer la mémoire allouée
  free(ImgIn);
  free(ImgOut);

  return 0;
}
