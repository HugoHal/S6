#include <stdio.h>
#include <math.h>  // Inclure math.h pour sqrt
#include "image_ppm.h"

int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, S, Seuille;

    if (argc != 4)
    {
        printf("Usage: ImageIn.pgm ImageOut.pgm\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%d", &Seuille);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    for (int i = 1; i < nH - 1; i++)
    {
        for (int j = 1; j < nW - 1; j++)
        {
            int index = i * nW + j;     
            int verticalGradient = ImgIn[i * nW + j + 1] - ImgIn[index];
            int horizontalGradient = ImgIn[(i + 1) * nW + j] - ImgIn[index];

            // Convertir en double avant de passer à sqrt()
            double gradient = sqrt((double)(verticalGradient * verticalGradient) + (double)(horizontalGradient * horizontalGradient));

            // Si la valeur du gradient est trop grande, la contraindre entre 0 et 255
            if (gradient > Seuille)
                gradient = 255;
            else gradient = 0;

            ImgOut[index] = (unsigned char)gradient;
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);
    return 0;
}
