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

    while (1) {
        struct message msgdemande;
        msgrcv(msgid, &msgdemande, sizeof(msgdemande.text), 1, 0);
        printf("Pctrl : Demande reçue - %s\n", msgdemande.text);

        pid_t clientPid = msgdemande.pid;

        sleep(2);

        struct message msglibre;
        msglibre.type = (long)clientPid;
        strcpy(msglibre.text, "Ressource attribuée");
        msgsnd(msgid, &msglibre, sizeof(msglibre.text), 0);
        printf("Pctrl : Ressource accordée\n");

        struct message msgrecu;
        msgrcv(msgid, &msgrecu, sizeof(msgrecu.text), (long)clientPid, 0);
        printf("Pctrl : Libération reçue - %s\n", msgrecu.text);
    }

    return 0;
}
