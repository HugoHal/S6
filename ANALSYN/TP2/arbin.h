// arbin.h

#ifndef ARBIN_H
#define ARBIN_H

typedef struct Noeud {
    int type;    // 1 pour un nombre, 2 pour une opération (par exemple +)
    int valeur;
    struct Noeud* gauche;
    struct Noeud* droite;
} Noeud;

Noeud* creer_noeud(int type, int valeur);
void afficher_arbre(Noeud* arbre);
int evaluer_arbre(Noeud* arbre);

#endif