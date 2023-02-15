#include "../include/source.h"

void tsock_source(const tsock_config* const config, const int socket, const struct sockaddr_in* const adresse)
{
	tsock_afficher("Nouvelle connexion établie avec le puit (", config);
	printf("%d).\n", socket);
	char* message = (char*)malloc(config->lg_messages * sizeof(char));
    int n = 0;
	char motif = 'a';
	for (n = 0; n < config->nb_messages; n++)
	{
		tsock_construire_message(message, motif, config->lg_messages);
		tsock_afficher("Envoi n°", config);
        printf("%03d (%03d) [----%03d", n + 1, config->lg_messages, n + 1);
		tsock_afficher_message(message, config->lg_messages);
        printf("]\n");
        tsock_envoyer(message, socket, config, adresse);
		motif++;
		if (motif > 'z') motif = 'a';
	}
	tsock_fin(socket, config);
}