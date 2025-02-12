%{
#include <stdio.h>

FILE *output_file;
%}

%%

^[ \t]*$                   { /* Ignorer les lignes blanches */ }
^[ \t]+                     { /* Supprimer les espaces en début de ligne */ }
[ \t]+$                     { /* Ignorer les espaces en fin de ligne */ }
[ \t]+                      { fprintf(output_file, " "); fflush(output_file); }  // Remplacer les espaces multiples par un seul espace
.                            { fprintf(output_file, "%c", yytext[0]); fflush(output_file); }  // Imprimer les autres caractères

%%

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fichier_entrée>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");  // Ouvrir le fichier d'entrée en lecture
    if (input_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier d'entrée");
        return 1;
    }

    output_file = fopen("output.txt", "w");  // Ouvrir le fichier en mode écriture ("w")
    if (output_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        fclose(input_file);  // N'oublie pas de fermer le fichier d'entrée si l'ouverture du fichier de sortie échoue
        return 1;
    }

    yyin = input_file;  // Rediriger l'entrée vers le fichier
    printf("Début de l'analyse...\n");

    yylex();  // Lancer l'analyseur lexical

    printf("Analyse terminée.\n");

    fclose(output_file);  // Fermer le fichier de sortie
    fclose(input_file);   // Fermer le fichier d'entrée après utilisation

    return 0;
}
