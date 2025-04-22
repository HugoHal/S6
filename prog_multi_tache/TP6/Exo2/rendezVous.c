#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
};

void afficherValeur(int semid) {
  int val = semctl(semid, 0, GETVAL);
  if (val == -1) {
    perror("semctl GETVAL");
    exit(1);
  }
  printf("[PID %d] Valeur du sémaphore : %d\n", getpid(), val);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Nbre d'args invalide, utilisation :\n");
    printf("%s fichier-pour-cle-ipc entier-pour-cl�-ipc\n", argv[0]);
    exit(0);
  }

  int clesem = ftok(argv[1], atoi(argv[2]));

  if (clesem == -1) {
    perror("erreur ftok : ");
    exit(2);
  }

  int semid = semget(clesem, 1, 0);
  if (semid == -1) {
    perror("Erreur semget");
    exit(EXIT_FAILURE);
  }

  struct sembuf op[] = {{(unsigned short)0, (short)-1, 0}, {(unsigned short)0, (short)0, 0}};

  if (semop(semid, op, 1) == -1) {
    perror("Erreur semop (P)");
    exit(EXIT_FAILURE);
  }

  printf("[PID %d] Arrivé au point de rendez-vous.\n", getpid());
  afficherValeur(semid);

  if(semop(semid, op, 1) == -1){
    perror("Erreur semop (P)");
    exit(EXIT_FAILURE);
  }

  printf("c'est gagné !!! 🥃🥃\n");
}