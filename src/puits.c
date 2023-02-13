#include "../include/puits.h"

void tsock_puits(const tsock_config* const config, const int socket)
{
    char* message = (char*)malloc(config->lg_messages * sizeof(char));
    int n = 1;
    while (tsock_recevoir(message, socket, config) > 0)
    {
        tsock_afficher("Réception n°", config);
        printf("%d (%d) [----%d", n, config->lg_messages, n);
        tsock_afficher_message(message, config->lg_messages);
        printf("]\n");
        n++;
    }
}