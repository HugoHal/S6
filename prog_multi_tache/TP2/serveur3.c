#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("utilisation : %s port_serveur\n", argv[0]);
    exit(1);
  }

  int ds = socket(PF_INET, SOCK_STREAM, 0);
  if (ds == -1) {
    perror("Serveur : pb creation socket :");
    exit(1);
  }
  printf("Serveur : creation de la socket réussie \n");

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

  char buffer[1500];
  int nbappel = 0;
  int nboctet = 0;

  // Reception de plusieurs messages jusqu'à ce que le client ferme la connexion
  while (1) {
    int received = recv(dsClient, buffer, sizeof(buffer), 0);
    if (received <= 0) {
      // Si aucune donnée n'est reçue ou une erreur se produit, on termine
      if (received < 0) {
        perror("Serveur : problème réception message");
      }
      break;
    }

    nbappel++;
    nboctet += received;
    printf("Serveur : nombre de messages recu : %d, nombre d'octets recu : %d\n", nbappel, nboctet);
  }

  // Réponse du serveur
  char reponse[] = "Message reçu avec succès";
  if (send(dsClient, reponse, strlen(reponse) + 1, 0) < 0) {
    perror("Serveur : problème envoi message");
    close(dsClient);
    close(ds);
    exit(1);
  }

  close(dsClient);
  close(ds);
  printf("Serveur : je termine\n");
  return 0;
}
