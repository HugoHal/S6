#include <iostream>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include "calcul.h"

using namespace std;

// Structure qui regroupe les variables partagées entre les threads.
struct varPartagees {
    int nbZones;
    int *di; // Tableau contenant l'état de progression des traitements
    pthread_mutex_t lock;  // Mutex pour synchronisation
    pthread_cond_t cond; // Tableau de conditions pour la synchronisation
};

// Structure qui regroupe les paramètres d'un thread
struct params {
    int idThread; // Numéro de traitement associé à un thread
    struct varPartagees *vPartage;
};

// Fonction associée à chaque thread secondaire
void *traitement(void *p) {
    struct params *args = (struct params *)p;
    struct varPartagees *vPartage = args->vPartage;

    printf(" ⛏  Lancement du participant %d  ⛏ \n", args->idThread);

    for (int i = 1; i <= vPartage->nbZones; i++) {
        // Attente de la fin du traitement précédent (sauf pour le premier thread)
        if (args->idThread != 1) {
            pthread_mutex_lock(&vPartage->lock);
            while (vPartage->di[args->idThread - 2] < i) {
                pthread_cond_wait(&vPartage->cond, &vPartage->lock);
            }
            pthread_mutex_unlock(&vPartage->lock);
        }
        printf(" 🍌 Le participant %d fait la partie de l'image N° %d 🍌 \n", args->idThread, i);

        // Simulation d'un long calcul
        calcul(rand() % 2 + 1);

        printf(" 🍯  Le participant %d a finit la partie de l'image N° %d 🍯 \n", args->idThread, i);

        // Mise à jour de l'état et signalisation
        pthread_mutex_lock(&vPartage->lock);
        vPartage->di[args->idThread - 1] = i;
        pthread_cond_broadcast(&vPartage->cond);
        pthread_mutex_unlock(&vPartage->lock);
    }

    printf(" 🦍  Fermeture du participant %d  🦍\n", args->idThread);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Argument requis : ./prog nombre_Traitements nombre_Zones" << endl;
        exit(1);
    }

    int nbThreads = atoi(argv[1]);
    int nbZones = atoi(argv[2]);

    pthread_t threads[nbThreads];
    struct params tabParams[nbThreads];
    struct varPartagees vPartage;

    vPartage.nbZones = nbZones;
    vPartage.di = new int[nbThreads]();
    pthread_mutex_init(&vPartage.lock, NULL);
    pthread_cond_init(&vPartage.cond, NULL);

    srand(time(NULL));  // Initialisation de rand pour la simulation de longs calculs

    // Création des threads
    for (int i = 0; i < nbThreads; i++) {
        tabParams[i].idThread = i + 1;
        tabParams[i].vPartage = &vPartage;
        if (pthread_create(&threads[i], NULL, traitement, &tabParams[i]) != 0) {
            perror("Erreur création thread");
            exit(1);
        }
    }

    // Attente de la fin des threads
    for (int i = 0; i < nbThreads; i++) {
        pthread_join(threads[i], NULL);
    }
    cout << "Thread principal : fin de tous les threads secondaires" << endl;

    // Libération des ressources
    delete[] vPartage.di;
    pthread_cond_destroy(&vPartage.cond);
    pthread_mutex_destroy(&vPartage.lock);

    return 0;
}
