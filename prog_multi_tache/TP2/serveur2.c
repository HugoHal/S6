#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/* Programme serveur */

int main(int argc, char *argv[]) {

  /* Je passe en paramètre le numéro de port qui sera donné à la socket créée
   * plus loin.*/

  if (argc != 2) {
    printf("utilisation : %s port_serveur\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */
  int ds = socket(PF_INET, SOCK_STREAM, 0);
  if (ds == -1) {
    perror("Serveur : pb creation socket :");
    exit(1); // Arrêter le programme si la création de la socket échoue
  }

  printf("Serveur : creation de la socket réussie \n");

  /* Etape 2 : Nommer la socket du serveur */
  struct sockaddr_in ad;
  ad.sin_family = AF_INET;
  ad.sin_addr.s_addr = INADDR_ANY;
  ad.sin_port = htons(atoi(argv[1]));

  if (bind(ds, (struct sockaddr *)&ad, sizeof(ad)) < 0) {
    perror("Serveur : erreur bind");
    close(ds);
    exit(1);
  }

  if (listen(ds, 10) < 0) {
    perror("Serveur : erreur listen");
    close(ds);
    exit(1);
  }

  printf("Serveur : écoute en attente de connexion...\n");

  struct sockaddr_in adClient;
  socklen_t lga = sizeof(struct sockaddr_in);
  int dsClient = accept(ds, (struct sockaddr *)&adClient, &lga);

  if (dsClient < 0) {
    perror("Serveur : erreur accept");
    close(ds);
    exit(1);
  }

  printf("Serveur : connexion établie avec le client\n");

  int taille;
  if (recv(dsClient, &taille, sizeof(int), 0) < 0) {
    perror("Serveur : problème reception taille de message");
    close(dsClient);
    close(ds);
    exit(1);
  }

  // Allocation dynamique de mémoire pour le message
  char *message = malloc(taille);
  if (message == NULL) {
    perror("Serveur : erreur d'allocation mémoire");
    close(dsClient);
    close(ds);
    exit(1);
  }

  if (recv(dsClient, message, taille, 0) < 0) {
    perror("Serveur : problème réception message");
    free(message);
    close(dsClient);
    close(ds);
    exit(1);
  }

  printf("Serveur : message reçu : %s\n", message);

  // Réponse du serveur
  char reponse[] = "Message reçu avec succès";
  if (send(dsClient, reponse, strlen(reponse) + 1, 0) < 0) {
    perror("Serveur : problème envoi message");
    free(message);
    close(dsClient);
    close(ds);
    exit(1);
  }

  free(message);
  close(dsClient);
  close(ds);
  printf("Serveur : je termine\n");
  return 0;
}
