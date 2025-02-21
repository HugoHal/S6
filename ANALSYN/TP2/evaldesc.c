// evaldesc.c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "arbin.h"


char jeton;
int position = 0;

void avancer() {
    jeton = getchar();
    position++;
}

void erreur() {
    printf("Erreur de syntaxe à la position %d\n", position);
    exit(1);
}

void test_avance(char attendu) {
    if (jeton == attendu) {
        avancer();
    } else {
        erreur();
    }
}

Noeud* expr();

Noeud* facteur() {
    Noeud* arbre;

    if (isdigit(jeton)) {
        int valeur = jeton - '0';  // Conversion du caractère en entier
        avancer();
        arbre = creer_noeud(1, valeur);  // Noeud de type nombre
    } else if (jeton == '(') {
        avancer();
        arbre = expr();  // On analyse une sous-expression
        test_avance(')');
    } else {
        erreur();  // Si c'est un autre caractère, erreur
    }

    return arbre;
}

Noeud* terme() {
    Noeud* gauche = facteur();

    while (jeton == '*' || jeton == '/') {
        char op = jeton;
        avancer();
        Noeud* droite = facteur();

        Noeud* noeud = creer_noeud(2, op);
        noeud->gauche = gauche;
        noeud->droite = droite;

        gauche = noeud;
    }

    return gauche;
}

Noeud* expr() {
    Noeud* gauche = terme();

    while (jeton == '+' || jeton == '-') {
        char op = jeton;
        avancer();
        Noeud* droite = terme();

        Noeud* noeud = creer_noeud(2, op);
        noeud->gauche = gauche;
        noeud->droite = droite;

        gauche = noeud;
    }

    return gauche;
}

int main() {
    avancer();  // Lire le premier caractère
    Noeud* arbre = expr();
    
    if (jeton != EOF) {
        erreur();  // Si le fichier n'est pas complètement analysé, erreur
    }

    printf("Expression correcte.\n");
    afficher_arbre(arbre);
    printf("\n");
    
    int resultat = evaluer_arbre(arbre);
    printf("Résultat : %d\n", resultat);

    return 0;
}
