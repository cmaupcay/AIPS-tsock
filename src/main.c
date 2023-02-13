#include <stdlib.h>

#include "../include/puits.h"
#include "../include/source.h"

int main(const int argc, char** argv)
{
	tsock_config* config = tsock_creer_config();
	tsock_configurer(config, argc, argv);
	tsock_afficher_config(config);

	struct sockaddr_in* adresse = tsock_adresser(config);
	const int sock = tsock_socket(config, adresse);
	if (config->mode == TSOCK_PUITS) tsock_puits(config, sock);
	else tsock_source(config, sock, adresse);
	
	free(config);
	free(adresse);
	return EXIT_SUCCESS;
}