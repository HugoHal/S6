// test_couleur.cpp : Seuille une image en niveau de gris

#include "image_ppm.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  char cNomImgLue[250];
  int nH, nW, nTaille, indice;
  bool loc;    // true = ligne, false = colonne
  int tempLoc; // Variable temporaire pour lire la valeur de loc

  if (argc != 4) {
    printf("Usage: %s ImageIn.pgm colOrLine(0:col, 1:line) indice\n", argv[0]);
    exit(1);
  }

  // Lecture des arguments
  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%d", &tempLoc); 
  loc = (tempLoc != 0);            
  sscanf(argv[3], "%d", &indice);

  // Validation de la valeur de loc
  if (tempLoc != 0 && tempLoc != 1) {
    printf("Erreur: colOrLine doit être 0 (colonne) ou 1 (ligne).\n");
    exit(1);
  }

  printf("Image: %s\n", cNomImgLue);
  printf("Mode: %s\n", loc ? "Ligne" : "Colonne");
  printf("Indice: %d\n", indice);

  OCTET *ImgIn, *ImgOut;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille);

  if (loc) { // C'est une ligne
    int t[nH] = {0};
    for (int j = 0; j < nW; j++) {
      t[j] = ImgIn[indice * nW + j];
    }

    FILE *file = fopen("resultat/profil.dat", "w");
  if (file == nullptr) {
    perror("Erreur lors de l'ouverture du fichier");
    return 1;
  }

  for (int i = 0; i < 256; i++) {
    fprintf(file, "%d %d\n", i, t[i]); // Écrit chaque valeur avec son index
  }

  fclose(file);
  free(ImgIn);
  } else {
          int t[nW] = {0};
    for (int i = 0; i < nH; i++) {
      t[i] = ImgIn[i * nW + indice];
    }


    FILE *file = fopen("resultat/profil.dat", "w");
  if (file == nullptr) {
    perror("Erreur lors de l'ouverture du fichier");
    return 1;
  }

  for (int i = 0; i < 256; i++) {
    fprintf(file, "%d %d\n", i, t[i]); // Écrit chaque valeur avec son index
  }

  fclose(file);
  free(ImgIn);
  }

  

  return 1;
}