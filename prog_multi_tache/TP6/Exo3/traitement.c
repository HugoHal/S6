#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <time.h>

void P(int semid, int semnum) {
    struct sembuf op = {semnum, -1, 0};
    semop(semid, &op, 1);
}

void V(int semid, int semnum) {
    struct sembuf op = {semnum, 1, 0};
    semop(semid, &op, 1);
}

void traitement(int numero_traitement, int *zone, int id_zone) {
    int temps = 1 + rand() % 3; // entre 1 et 3 secondes
    printf("T%d commence sur zone %d (valeur = %d)\n", numero_traitement, id_zone, *zone);
    sleep(temps);
    *zone += numero_traitement;
    printf("T%d termine sur zone %d (valeur = %d)\n", numero_traitement, id_zone, *zone);
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Usage : %s numero_traitement nb_traitements nb_zones fichier-cle-ipc entier-cle\n", argv[0]);
        exit(1);
    }

    int numero_traitement = atoi(argv[1]);   // Ex: 1 ou 2
    int nb_traitements    = atoi(argv[2]);   // Ex: 2
    int nb_zones          = atoi(argv[3]);   // Ex: 4
    char *fichier_cle     = argv[4];
    int entier_cle        = atoi(argv[5]);

    srand(getpid()); // pour les temps aléatoires

    key_t cle = ftok(fichier_cle, entier_cle);
    if (cle == -1) {
        perror("ftok");
        exit(1);
    }

    int idSem = semget(cle, nb_traitements - 1, 0600);
    if (idSem == -1) {
        perror("semget");
        exit(1);
    }

    int idMem = shmget(cle, nb_zones * sizeof(int), 0600);
    if (idMem == -1) {
        perror("shmget");
        exit(1);
    }

    int *image = shmat(idMem, NULL, 0);
    if (image == (void *) -1) {
        perror("shmat");
        exit(1);
    }

    for (int zone = 0; zone < nb_zones; zone++) {
        if (numero_traitement == 1) {
            // Premier traitement : pas de synchronisation nécessaire avant
            traitement(1, &image[zone], zone);
            // Réveil du traitement 2 sur cette zone
            V(idSem, zone);
        } else if (numero_traitement == 2) {
            // Attente que le traitement 1 ait fini cette zone
            P(idSem, zone);
            traitement(2, &image[zone], zone);
        }
    }

    shmdt(image);
    return 0;
}
