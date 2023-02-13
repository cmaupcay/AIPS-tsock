#include <stdlib.h>

#include "../include/affichage.h"

int main(const int argc, char** argv)
{
	tsock_config* config = tsock_creer_config();
	tsock_configurer(config, argc, argv);
	tsock_afficher_config(config);
	return EXIT_SUCCESS;
}