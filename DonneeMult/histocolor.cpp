#include <bits/types/FILE.h>
#include <cstdio>
#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    char cNomImgLue[750];
    int nH, nW, nR, nG, nB;

    if (argc != 3)  
    {
        printf("Usage: ImageIn.pgm graphout.dat \n"); 
        exit (1) ;
    }

    sscanf (argv[1],"%s",cNomImgLue) ;

    int tableaurouge[256] = {0};
    int tableaubleu[256] = {0};
    int tableauvert[256] = {0};

    OCTET *ImgIn, *ImgOut;
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);

    int nTaille = nH * nW;
    int nTaille3 = nTaille * 3;

    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    for (int i = 0; i < nTaille3; i += 3)
    {
        nR = ImgIn[i];
        nG = ImgIn[i+1];
        nB = ImgIn[i+2];
        
        tableaurouge[nR]++;
        tableaubleu[nG]++;
        tableauvert[nB]++;
    }
    
    for (int i = 0; i < 256; i++) {
        cout << "tableauRouge[" << i << "] = " << tableaurouge[i] << endl;
        cout << "tableaubleu[" << i << "] = " << tableaubleu[i] << endl;
        cout << "tableauvert[" << i << "] = " << tableauvert[i] << endl;
    }

    FILE* file = fopen(argv[2], "w");

    for (int i = 0; i <256; i++){
        fprintf(file, "%d %d %d %d \n", i, tableaurouge[i], tableaubleu[i], tableauvert[i]);
    }
    
    return 0;
}