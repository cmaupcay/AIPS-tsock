#include "../include/puits.h"

static int TSOCK_RECEPTIONS;

void tsock_puits_reception(const tsock_config* const config, const int socket, char* const message)
{
    while (tsock_recevoir(message, socket, config) > 0)
    {
        TSOCK_RECEPTIONS++;
        if (config->nb_messages > 0 && TSOCK_RECEPTIONS > config->nb_messages) break;
        tsock_afficher("Réception n°", config);
        printf("%03d (%03d) [----%03d", TSOCK_RECEPTIONS, config->lg_messages, TSOCK_RECEPTIONS);
        tsock_afficher_message(message, config->lg_messages);
        printf("]\n");
    }
    tsock_fin(socket, config);
}

void tsock_puits(const tsock_config* const config, const int socket)
{
    char* message = (char*)malloc(config->lg_messages * sizeof(char));
    TSOCK_RECEPTIONS = 0;

    if (config->protocole == TSOCK_TCP)
    {
        if (listen(socket, TSOCK_PUITS_CONNEXIONS_MAX) == -1)
            TSOCK_ERREUR_DEBUT;
        int sourceSocket = -1;
        while ((sourceSocket = accept(socket, NULL, 0)) != -1)
        {
            tsock_afficher("Nouvelle connexion établie avec la source (", config);
            printf("%d).\n", sourceSocket);
            if (config->async == 0)
                tsock_puits_reception(config, sourceSocket, message);
            else switch (fork())
            {
            case -1:
                TSOCK_ERREUR_DEBUT;
                break;
            case 0:
                close(socket);
                tsock_puits_reception(config, sourceSocket, message);
                exit(0);
                break;
            default:
                close(sourceSocket);
                break;
            }
        }
        tsock_fin(socket, config);

    }
    else tsock_puits_reception(config, socket, message);
}