#ifndef H_TSOCK_AFFICHAGE
#define H_TSOCK_AFFICHAGE

#include "config.h"

#define TSOCK_PREFIX_PUITS  "PUITS : "
#define TSOCK_PREFIX_SOURCE "SOURCE : "

void tsock_afficher(const char* message, const tsock_config* const config);

void tsock_afficher_config(const tsock_config* const config);

#endif