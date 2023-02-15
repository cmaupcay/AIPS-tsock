#ifndef H_TSOCK_RESEAU
#define H_TSOCK_RESEAU

#include "affichage.h"

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void tsock_construire_message(char* message, char motif, const int lg);

struct sockaddr_in* tsock_adresser(const tsock_config* const config);

int tsock_debut(const tsock_config* const config, const struct sockaddr_in* const adresse);

unsigned int tsock_envoyer(const char* const message, const int sock, const tsock_config* const config, const struct sockaddr_in* const adresse);

unsigned int tsock_recevoir(char* const message, const int sock, const tsock_config* const config);

void tsock_fin(const int sock, const tsock_config* const config);

#endif