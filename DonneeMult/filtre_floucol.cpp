#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nR, nG, nB, SR, SG, SB;
  
    if (argc != 3)  // Vous attendez 6 arguments : l'image d'entrée, l'image de sortie et 3 valeurs de couleur
    {
        printf("Usage: ImageIn.ppm ImageOut.ppm\n"); 
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW); // Pour un fichier PPM, pas PGM
    nTaille = nH * nW;
    int nTaille3 = nTaille * 3;

    allocation_tableau(ImgIn, OCTET, nTaille3); // Allocation pour image RGB
    lire_image_ppm(cNomImgLue, ImgIn, nTaille); // Lecture de l'image PPM
    allocation_tableau(ImgOut, OCTET, nTaille3);

    for (int i = 0; i < nTaille3; i += 3)
    {
        int row = i / 3 / nW;  // Calcul de la ligne actuelle
        int col = (i / 3) % nW;  // Calcul de la colonne actuelle

        // Initialisation des couleurs
        int sumR = 0, sumG = 0, sumB = 0, count = 0;

        // Boucle sur les voisins (y compris le pixel actuel)
        for (int di = -1; di <= 1; di++)
        {
            for (int dj = -1; dj <= 1; dj++)
            {
                int newRow = row + di;
                int newCol = col + dj;

                // Vérifier que le voisin est dans les limites de l'image
                if (newRow >= 0 && newRow < nH && newCol >= 0 && newCol < nW)
                {
                    int idx = (newRow * nW + newCol) * 3;
                    sumR += ImgIn[idx];
                    sumG += ImgIn[idx + 1];
                    sumB += ImgIn[idx + 2];
                    count++;
                }
            }
        }

        // Calculer la moyenne pour chaque couleur
        ImgOut[i] = sumR / count;
        ImgOut[i + 1] = sumG / count;
        ImgOut[i + 2] = sumB / count;
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW); // Écriture de l'image PPM
    free(ImgIn);
    free(ImgOut); // Libération de ImgOut

    return 0;
}
