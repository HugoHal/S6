/**
 * @file afd.h
 * @brief Définition d'un AFD du langage C
 * @author Michel Meynard
 */
#define EINIT 0
#define EA 1
#define EAB 2
#define EABC 3
#define EB 4
#define EBD 5
#define NBETAT 6

int TRANS[NBETAT][256]; /* table de transition : état suivant */
int JETON[NBETAT];      /* jeton (1-32000) ou non Final (0) ? */

void classe(int ed, int cd, int cf, int ef) {
  // Parcours de l'intervalle de caractères de cd à cf
  for (int i = cd; i <= cf; i++) {
    TRANS[ed][i] = ef;  // Crée une transition de ed vers ef pour le caractère i
  }
}

void creerAfd() {
  int i, j;  // Variables locales
  for (i = 0; i < NBETAT; i++) {
    for (j = 0; j < 256; j++)
      TRANS[i][j] = -1;  // Initialisation de la table de transition
    JETON[i] = 0;  // Initialisation des états non finaux
  }

  // Transitions de l'AFD
  TRANS[EINIT]['a'] = EA;  // Transition de EINIT vers EA avec 'a'
  TRANS[EA]['b'] = EAB;    // Transition de EA vers EAB avec 'b'
  TRANS[EAB]['b'] = EAB;   // Transition de EAB vers EAB avec 'b'
  TRANS[EAB]['c'] = EABC;  // Transition de EAB vers EABC avec 'c'
  TRANS[EINIT]['b'] = EB;  // Transition de EINIT vers EB avec 'b'
  TRANS[EB]['d'] = EBD;    // Transition de EB vers EBD avec 'd'
  
  // Utilisation de la fonction classe pour ajouter des transitions pour les caractères minuscules et les chiffres
  classe(EINIT, 'a', 'z', EA);  // Transition de EINIT vers EA pour les minuscules
  classe(EAB, '0', '9', EAB);   // Transition de EAB vers EAB pour les chiffres
  
  // Définition des jetons (états finaux)
  JETON[EA] = 300;
  JETON[EABC] = 301;
  JETON[EAB] = 302;
  JETON[EBD] = -302;  // Jetons des états finaux
}