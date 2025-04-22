#include <stdlib.h>
#include <sys/types.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct message {
    long type;
    char text[100];
    pid_t pid;
};

int main() {
    key_t key = ftok("pourCle.txt", 122);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("Erreur lors de la récupération de la file de messages");
        exit(EXIT_FAILURE);
    }

    struct message msgenv;
    msgenv.type = 1;
    msgenv.pid = getpid();
    strcpy(msgenv.text, "J'aimerais accéder à la ressource");

    msgsnd(msgid, &msgenv, sizeof(msgenv.text), 0);
    printf("Pi : Demande d'accès envoyée\n");

    struct message ressource;
    msgrcv(msgid, &ressource, sizeof(ressource.text), (long)msgenv.pid, 0);
    printf("Pi : Ressource reçue - %s\n", ressource.text);

    sleep(2); 

    struct message fin;
    fin.type = (long)msgenv.pid; 
    strcpy(fin.text, "Je rends la ressource");
    msgsnd(msgid, &fin, sizeof(fin.text), 0);
    printf("Pi : Ressource libérée\n");

    return 0;
}
