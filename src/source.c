#include "../include/source.h"

void tsock_source(const tsock_config* const config, const int socket, const struct sockaddr_in* const adresse)
{
	char* message = (char*)malloc(config->lg_messages * sizeof(char));
    int n = 0;
	char motif = 'a';
	for (n = 0; n < config->nb_messages; n++)
	{
		tsock_construire_message(message, motif, config->lg_messages);
		tsock_afficher("Envoi n°", config);
        printf("%d (%d) [----%d%s]\n", n + 1, config->lg_messages, n + 1, message);
        tsock_envoyer(message, socket, config, adresse);
		motif++;
		if (motif > 'z') motif = 'a';
	}
	tsock_afficher("fin\n", config);
	close(socket);
}