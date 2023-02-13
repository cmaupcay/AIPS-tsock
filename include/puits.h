#ifndef H_TSOCK_PUITS
#define H_TSOCK_PUITS

#include "affichage.h"
#include "reseau.h"

#define TSOCK_PUITS_CONNEXIONS_MAX 10

void tsock_puits_reception(const tsock_config* const config, const int socket, const char* const message, int* const n);

void tsock_puits(const tsock_config* const config, const int socket);

#endif