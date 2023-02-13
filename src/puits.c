#include "../include/puits.h"

void tsock_puits_reception(const tsock_config* const config, const int socket, char* const message, int* const n)
{
    while (tsock_recevoir(message, socket, config) > 0)
    {
        tsock_afficher("Réception n°", config);
        printf("%d (%d) [----%d", *n, config->lg_messages, *n);
        tsock_afficher_message(message, config->lg_messages);
        printf("]\n");
        (*n)++;
        if (config->nb_messages > 0 && *n > config->nb_messages) break;
    }
    close(socket);
}

void tsock_puits(const tsock_config* const config, const int socket)
{
    char* message = (char*)malloc(config->lg_messages * sizeof(char));
    int n = 1;

    if (config->protocole == TSOCK_TCP)
    {
        if (listen(socket, TSOCK_PUITS_CONNEXIONS_MAX) == -1)
            TSOCK_ERREUR_SOCKET;
        int sourceSocket = -1;
        while ((sourceSocket = accept(socket, NULL, 0)) != -1)
        {
            if (config->async == 0)
                tsock_puits_reception(config, sourceSocket, message, &n);
            else switch (fork())
            {
            case -1:
                TSOCK_ERREUR_SOCKET;
            case 0:
                close(socket);
                tsock_puits_reception(config, sourceSocket, message, &n);
                exit(0);
            default:
                close(sourceSocket);
            }
        }

    }
    else tsock_puits_reception(config, socket, message, &n);
}