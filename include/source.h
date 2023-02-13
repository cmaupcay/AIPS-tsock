#ifndef H_TSOCK_SOURCE
#define H_TSOCK_SOURCE

#include "affichage.h"
#include "reseau.h"

void tsock_source(const tsock_config* const config, const int socket, const struct sockaddr_in* const adresse);

#endif