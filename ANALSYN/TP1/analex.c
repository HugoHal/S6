#include <stdio.h>
#include <string.h>
#include "afd.h"    /* Définition de l'AFD et des JETONS */
#include "analex.h" /* Définition de la fonction : int analex() */

int main() {
  int j;  /* jeton retourné par analex() */
  creerAfd();  /* Construction de l'AFD à jeton */

  // Test de la fonction classe() et des transitions
  printf("Transition de EINIT vers EA pour les caractères 'a' à 'z':\n");
  for (int i = 'a'; i <= 'z'; i++) {
    if (TRANS[EINIT][i] == EA) {
      printf("Transition OK pour '%c'\n", i);
    } else {
      printf("Erreur de transition pour '%c'\n", i);
    }
  }

  // Test de l'analyseur lexical
  while ((j = analex())) {  /* Analyse jusqu'à EOF */
    printf("Jeton = %d ; Lexème = %s\n", j, lexeme);
  }

  return 0;
}

