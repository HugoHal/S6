// arbin1.c
#include "arbin.h"
#include <stdio.h>
#include <stdlib.h>

// Définition des fonctions qui utilisent Noeud, sans redéfinir la structure

Noeud* creer_noeud(int type, int valeur) {
    Noeud* n = (Noeud*)malloc(sizeof(Noeud));
    if (n == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }
    n->type = type;
    n->valeur = valeur;
    n->gauche = NULL;
    n->droite = NULL;
    return n;
}

void afficher_arbre(Noeud* arbre) {
    if (arbre != NULL) {
        if (arbre->type == 1) {  // type 1 : nombre
            printf("%d", arbre->valeur);
        } else {  // type 2 : opération
            printf("(");
            afficher_arbre(arbre->gauche);
            printf(" %d ", arbre->valeur);
            afficher_arbre(arbre->droite);
            printf(")");
        }
    }
}

int evaluer_arbre(Noeud* arbre) {
    if (arbre == NULL) {
        return 0;
    }
    if (arbre->type == 1) {
        return arbre->valeur;
    }
    // Opérations : ici, on gère seulement l'addition pour l'exemple
    if (arbre->valeur == '+') {
        return evaluer_arbre(arbre->gauche) + evaluer_arbre(arbre->droite);
    }
    return 0;
}
