#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/* Programme client */

int main(int argc, char *argv[]) {

  if (argc != 5) {
    printf("utilisation : %s ip_serveur port_serveur port_client nb_itération\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */
  int ds = socket(PF_INET, SOCK_STREAM, 0);
  if (ds == -1) {
    perror("Client : pb creation socket :");
    exit(1);
  }

  printf("Client : creation de la socket réussie \n");

  struct sockaddr_in sockServ;
  sockServ.sin_family = AF_INET;
  sockServ.sin_addr.s_addr = inet_addr(argv[1]);
  sockServ.sin_port = htons(atoi(argv[2]));

  if (connect(ds, (struct sockaddr *)&sockServ, sizeof(sockServ)) < 0) {
    perror("Client : problème à connect");
    close(ds);
    exit(1);
  }else {
  printf("connecté");}

  /* Etape 4 : envoyer un message au serveur */
  char m[1500] = "caca feur \n";
  int limi = atoi(argv[4]);
  printf("limi : %d ", limi);
  int nboct = 0;
  for (int i = 0; i < limi; i++) {
    int a = send(ds, m, strlen(m), 0);
    if (a <= 0) {
      perror("Client : problème à send message");
      close(ds);
      exit(1);
    }
    printf("client : %d eme message envoyé", i);
    nboct += a;
  }
  printf("nb d'octet envoyé : %d", nboct);


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
