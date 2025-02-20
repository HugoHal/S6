#include <string.h>
#include <stdio.h> // perror
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "calcul.h"

struct paramsFonctionThread {
  int idThread;
  int *a;
};

// Fonction exécutée par chaque thread
void *fonctionThread(void *params) {
  struct paramsFonctionThread *args = (struct paramsFonctionThread *)params;
  printf("Thread %d en cours d'exécution\n", args->idThread);
  calcul(1);
  *(args->a)++;
  printf("a = %d\n", *args->a);
  printf("Thread %d 1ere etape\n", args->idThread);
  calcul(1);
  printf("Thread %d 2eme etape\n", args->idThread);
  calcul(1);
  printf("Thread %d terminé\n", args->idThread);

  // 🚀 NE PAS FAIRE DE `free(args);` car la mémoire est sur la pile (stack)
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Utilisation: %s nombre_threads\n", argv[0]);
    return 1;
  }

  int nb_threads = atoi(argv[1]);
  pthread_t threads[nb_threads];
  struct paramsFonctionThread params[nb_threads]; // Allocation sur la pile
  int a = 12;
  // Création des threads
  for (int i = 0; i < nb_threads; i++) {
    params[i].idThread = i;
    params[i].a = &a;
    if (pthread_create(&threads[i], NULL, fonctionThread, &params[i]) != 0) {
      perror("Erreur création thread");
      exit(1);
    }
  }

  // Attente de la saisie utilisateur
  printf("Saisir un caractère pour continuer...\n");
  fgetc(stdin);

  // Attente de la fin des threads
  for (int i = 0; i < nb_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
