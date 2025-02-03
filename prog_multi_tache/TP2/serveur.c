#include <netinet/in.h>
#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>

/* Programme serveur */

int main(int argc, char *argv[]) {

  /* Je passe en paramètre le numéro de port qui sera donné à la socket créée plus loin.*/

  /* Je teste le passage de parametres. Le nombre et la nature des
     paramètres sont à adapter en fonction des besoins. Sans ces
     paramètres, l'exécution doit être arrétée, autrement, elle
     aboutira à des erreurs.*/
  if (argc != 2){
    printf("utilisation : %s port_serveur\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_STREAM, 0);

  /* /!\ : Il est indispensable de tester les valeurs de retour de
     toutes les fonctions et agir en fonction des valeurs
     possibles. Voici un exemple */
  if (ds == -1){
    perror("Serveur : pb creation socket :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }
  
  /* J'ajoute des traces pour comprendre l'exécution et savoir
     localiser des éventuelles erreurs */
  printf("Serveur : creation de la socket réussie \n");
  
  // Je peux tester l'exécution de cette étape avant de passer à la
  // suite. Faire de même pour la suite : n'attendez pas de tout faire
  // avant de tester.
  
  /* Etape 2 : Nommer la socket du seveur */

   struct sockaddr_in ad;
   ad.sin_family = AF_INET;
   ad.sin_addr.s_addr = INADDR_ANY;
   ad.sin_port = htons(atoi(argv[1]));

   bind(ds, (struct sockaddr*)&ad, sizeof(ad));

   int res = listen(ds, 10);

   struct sockaddr_in adClient;
   socklen_t lga = sizeof(struct sockaddr_in);

   printf("écrivez un caractrère");
   char c = getchar();

   int dsClient = accept(ds, (struct sockaddr *) &adClient, &lga);
  /* Etape 4 : recevoir un message du client (voir sujet pour plus de détails)*/
  
   int message[500]; 
   recv(dsClient, message, sizeof(message), 0);
   printf("recu : %s", message);

  /* Etape 5 : envoyer un message au serveur (voir sujet pour plus de détails)*/
   
   send(dsClient, message, sizeof(message), 0);

  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  
   close( dsClient); close(ds);
  printf("Serveur : je termine\n");
  return 0;
}
