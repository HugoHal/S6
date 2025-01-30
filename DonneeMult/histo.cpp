#include <bits/types/FILE.h>
#include <cstdio>
#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    char cNomImgLue[250];
    int nH, nW;

    if (argc != 3)  
    {
        printf("Usage: ImageIn.pgm graphout.dat \n"); 
        exit (1) ;
    }

    sscanf (argv[1],"%s",cNomImgLue) ;

    int tableau[256] = {0};

    OCTET *ImgIn, *ImgOut;
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);

    int nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    for (int i = 0; i < nH; i++) {
    for (int j = 0; j < nW; j++) {
        int pixelValue = ImgIn[i * nW + j]; // Valeur du pixel
        tableau[pixelValue]++; // Incrémente le niveau de gris correspondant
    }
}
    
    for (int i = 0; i < 256; i++) {
        cout << "tableau[" << i << "] = " << tableau[i] << endl;
    }

    FILE* file = fopen(argv[2], "w");

    for (int i = 0; i <256; i++){
        fprintf(file, "%d %d \n", i, tableau[i]);
    }
    
    return 0;
}