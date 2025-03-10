#include <iostream>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include "calcul.h"

using namespace std;

struct predicatRdv {
    int count;  
    int total;  
    pthread_mutex_t lock;  
    pthread_cond_t cond;   
};

struct params {
    int idThread;  
    struct predicatRdv * varPartagee;  
};

void * participant(void * p) { 
    struct params * args = (struct params *) p;
    struct predicatRdv * predicat = args->varPartagee;

    printf(" ⛏  Lancement du participant %d  ⛏ \n", args->idThread);

    // Calcul avant la synchronisation
    calcul(rand()%2+1);

    // Synchronisation des threads
    pthread_mutex_lock(&predicat->lock);
    predicat->count++;
    if (predicat->count == predicat->total) {
        pthread_cond_broadcast(&predicat->cond);
    } else {
        while (predicat->count < predicat->total) {
            pthread_cond_wait(&predicat->cond, &predicat->lock);
        }
    }
    pthread_mutex_unlock(&predicat->lock);

    // Calcul après la synchronisation
    calcul(rand()%2+1);

    printf(" 🦍  Fermeture du participant %d  🦍\n", args->idThread);

    pthread_exit(NULL);  
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        cout << "./prog number_of_threads" << endl;
        exit(1);
    }

    int numThreads = atoi(argv[1]);
    
    pthread_t threads[numThreads];
    struct params tabParams[numThreads];
    struct predicatRdv predicat;
    predicat.count = 0;
    predicat.total = numThreads;
    pthread_mutex_init(&predicat.lock, NULL);
    pthread_cond_init(&predicat.cond, NULL);
    
    srand(time(NULL));  // Initialisation de la graine avec le temps actuel

    // Créer les threads
    for (int i = 0; i < numThreads; i++) {
        tabParams[i].idThread = i + 1;  
        tabParams[i].varPartagee = &predicat;

        if (pthread_create(&threads[i], NULL, participant, &tabParams[i]) != 0) {
            perror("Error creating thread");
            exit(1);
        }
    }

    // Attendre la fin de tous les threads
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Afficher le message de fin après la fin de tous les threads
    cout << "Le thread principal finit après tous les autres threads secondaires." << endl;

    pthread_mutex_destroy(&predicat.lock);
    pthread_cond_destroy(&predicat.cond);

    return 0;
}
