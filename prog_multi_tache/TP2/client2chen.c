#include <netinet/in.h>
#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

/* Programme client */

int main(int argc, char *argv[]) {

  if (argc != 4){
    printf("utilisation : %s ip_serveur port_serveur port_client\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */
  int ds = socket(PF_INET, SOCK_STREAM, 0);
  if (ds == -1){
    perror("Client : pb creation socket :");
    exit(1);
  }

  printf("Client : creation de la socket réussie \n");

  struct sockaddr_in sockServ;
  sockServ.sin_family = AF_INET;
  sockServ.sin_addr.s_addr = inet_addr(argv[1]);
  sockServ.sin_port = htons(atoi(argv[2]));

  if (connect(ds, (struct sockaddr *) &sockServ, sizeof(struct sockaddr_in)) < 0) {
    perror("Client : problème à connect");
    close(ds);
    exit(1);
  }

  /* Etape 4 : envoyer un message au serveur */
  char m[1500] = "caca feur \n";
  int lm = strlen(m);
  
  if (send(ds, &lm, sizeof(int), 0) < 0) {
    perror("Client : problème à send taille");
    close(ds);
    exit(1);
  }

  if (send(ds, m, lm, 0) < 0) {
    perror("Client : problème à send message");
    close(ds);
    exit(1);
  }

  /* Etape 5 : recevoir un message du serveur */
  char recep[100];
  if (recv(ds, recep, sizeof(recep), 0) < 0) {
    perror("Client : problème au recv");
    close(ds);
    exit(1);
  }

  printf("Réponse du serveur : %s\n", recep);

  /* Etape 6 : fermer la socket */
  close(ds);

  printf("Client : je termine\n");
  return 0;
}
