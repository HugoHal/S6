#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nR, nG, nB, SR, SG, SB;
  
    if (argc != 6)  
    {
        printf("Usage: ImageIn.ppm ImageOut.ppm Seuilrouge Seuilvert Seuilbleu \n"); 
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%d", &SR);
    sscanf(argv[4], "%d", &SG);
    sscanf(argv[5], "%d", &SB);

    OCTET *ImgIn, *ImgOut;
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW); // Pour un fichier PPM, pas PGM
    nTaille = nH * nW;
    int nTaille3 = nTaille * 3;

    allocation_tableau(ImgIn, OCTET, nTaille3); // Allocation pour image RGB
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW); // Lecture de l'image PPM
    allocation_tableau(ImgOut, OCTET, nTaille3);

    for (int i = 0; i < nTaille3; i += 3)
    {
        nR = ImgIn[i];
        nG = ImgIn[i + 1];
        nB = ImgIn[i + 2];
        
        if (nR < SR) ImgOut[i] = 0; else ImgOut[i] = 255;
        if (nG < SG) ImgOut[i + 1] = 0; else ImgOut[i + 1] = 255; 
        if (nB < SB) ImgOut[i + 2] = 0; else ImgOut[i + 2] = 255;
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW); // Écriture de l'image PPM
    free(ImgIn);
    free(ImgOut); // Libération de ImgOut

    return 0;
}
