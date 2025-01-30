#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char cNomImgLue[250], cNomImgTemp[250], cNomImgEcrite[250];
    
    if (argc != 3) {
        printf("Usage: %s ImageIn.pgm ImageOut.pgm\n", argv[0]);
        return 1;
    }
    
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    
    // Nom du fichier temporaire pour la dilatation
    sprintf(cNomImgTemp, "temp_dilatation.pgm");

    // Étape 2 : Érosion
    char cmdErosion[300];
    sprintf(cmdErosion, "./erosion %s %s",cNomImgLue, cNomImgTemp);
    system(cmdErosion);
    
    // Étape 1 : Dilatation
    char cmdDilatation[300];
    sprintf(cmdDilatation, "./dilatation %s %s", cNomImgTemp, cNomImgEcrite);
    system(cmdDilatation);
    
    
    // Supprimer le fichier temporaire
    remove(cNomImgTemp);
    
    return 0;
}