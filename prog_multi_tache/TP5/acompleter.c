#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"

struct varPartagees {
    pthread_mutex_t mutex;
    pthread_cond_t cond_embarquement;
    pthread_cond_t cond_debarquement;
    int passagers_embarques;
    int passagers_debarques;
    int nbPassagers_Aller;
    int nbPassagers_Retour;
};

struct paramsAvion {
    char * dest_aller;
    char * dest_retour;
    int nbPassagers_Aller;
    int nbPassagers_Retour;
    struct varPartagees * varP;
};

struct paramsPassager {
    int idPassager;
    char * destination;
    char * couleurTrace;
    struct varPartagees * varP;
};

void * avion (void * p) {
    struct paramsAvion * args = (struct paramsAvion *) p;
    struct varPartagees * varP = args->varP;
    char * couleurTrace = "\x1b[38;5;39m";

    afficher('a', "embarquement immediat !", 0, args->dest_aller, couleurTrace);
    
    pthread_mutex_lock(&varP->mutex);
    while (varP->passagers_embarques < args->nbPassagers_Aller) {
        pthread_cond_wait(&varP->cond_embarquement, &varP->mutex);
    }
    afficher('a', "attente fin embarquement", 0, args->dest_aller, couleurTrace);
    pthread_mutex_unlock(&varP->mutex);
    
    afficher('a', "décollage imminent! Durée du vol estimée à quelques secondes", 0, args->dest_aller, couleurTrace);
    vol(4);
    afficher('a', "arrivé à destination", 0, args->dest_aller, couleurTrace);
    
    pthread_mutex_lock(&varP->mutex);
    while (varP->passagers_debarques < args->nbPassagers_Aller) {
        pthread_cond_wait(&varP->cond_debarquement, &varP->mutex);
    }
    afficher('a', "attente que tout le monde soit descendu", 0, args->dest_aller, couleurTrace);
    pthread_mutex_unlock(&varP->mutex);
    
    afficher('a', "vol aller terminé", 0, args->dest_aller, couleurTrace);
    
    pthread_exit(NULL);
}

void * passager (void * p) {
    struct paramsPassager * args = (struct paramsPassager *) p;
    struct varPartagees * varP = args->varP;
    
    afficher('p', "Yoopi, je vais prendre l'avion !", args->idPassager, args->destination, args->couleurTrace);
    
    pthread_mutex_lock(&varP->mutex);
    afficher('p', "je patiente en salle d'embarquement", args->idPassager, args->destination, args->couleurTrace);
    varP->passagers_embarques++;
    if (varP->passagers_embarques == varP->nbPassagers_Aller) {
        pthread_cond_signal(&varP->cond_embarquement);
    }
    pthread_mutex_unlock(&varP->mutex);
    
    afficher('p', "j'embarque ...", args->idPassager, args->destination, args->couleurTrace);
    action();
    
    pthread_mutex_lock(&varP->mutex);
    afficher('p', "maintenant, je patiente jusqu'à destination", args->idPassager, args->destination, args->couleurTrace);
    varP->passagers_debarques++;
    if (varP->passagers_debarques == varP->nbPassagers_Aller) {
        pthread_cond_signal(&varP->cond_debarquement);
    }
    pthread_mutex_unlock(&varP->mutex);
    
    afficher('p', "je descends de l'avion", args->idPassager, args->destination, args->couleurTrace);
    action();
    
    afficher('p', "je quitte l'aéroport !", args->idPassager, args->destination, args->couleurTrace);
    pthread_exit(NULL);
}

int main(int argc, char * argv[]) {
    if (argc != 5) {
        printf("Usage: %s destination_aller nbPassagers_Aller destination_retour nbPassagers_Retour\n", argv[0]);
        exit(1);
    }

    initDefault(atoi(argv[2]));

    pthread_t threads[1 + atoi(argv[2]) + atoi(argv[4])];
    struct varPartagees varP;
    pthread_mutex_init(&varP.mutex, NULL);
    pthread_cond_init(&varP.cond_embarquement, NULL);
    pthread_cond_init(&varP.cond_debarquement, NULL);
    varP.passagers_embarques = 0;
    varP.passagers_debarques = 0;
    varP.nbPassagers_Aller = atoi(argv[2]);
    varP.nbPassagers_Retour = atoi(argv[4]);

    struct paramsAvion paramAvion = {argv[1], argv[3], atoi(argv[2]), atoi(argv[4]), &varP};
    struct paramsPassager tabParamsAller[atoi(argv[2])];

    char * couleurTraceA = "\x1b[38;5;226m";
    for (int i = 0; i < atoi(argv[2]); i++) {
        tabParamsAller[i].idPassager = i + 1;
        tabParamsAller[i].destination = argv[1];
        tabParamsAller[i].couleurTrace = couleurTraceA;
        tabParamsAller[i].varP = &varP;
        pthread_create(&threads[1 + i], NULL, passager, &(tabParamsAller[i]));
    }
    pthread_create(&threads[0], NULL, avion, &paramAvion);

    for (int i = 0; i < 1 + atoi(argv[2]); i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&varP.mutex);
    pthread_cond_destroy(&varP.cond_embarquement);
    pthread_cond_destroy(&varP.cond_debarquement);

    return 0;
}