#ifndef H_TSOCK_ERREURS
#define H_TSOCK_ERREURS

#include <stdlib.h>
#include <stdio.h>

void tsock_erreur(const char* message);

#define TSOCK_ERREUR_USAGE_MSG "Usage: tsock [-u] [-n <messages>] -p <port> | -s <dest> <port> "
#define TSOCK_ERREUR_USAGE tsock_erreur(TSOCK_ERREUR_USAGE_MSG)

#define TSOCK_ERREUR_SOCKET_MSG "Impossible de créer le socket de connexion "
#define TSOCK_ERREUR_SOCKET tsock_erreur(TSOCK_ERREUR_SOCKET_MSG)

#define TSOCK_ERREUR_ENVOI_MSG "Impossible d'envoyer le message "
#define TSOCK_ERREUR_ENVOI tsock_erreur(TSOCK_ERREUR_ENVOI_MSG)

#define TSOCK_ERREUR_RECEPTION_MSG "Impossible de recevoir le prochain message "
#define TSOCK_ERREUR_RECEPTION tsock_erreur(TSOCK_ERREUR_RECEPTION_MSG)

#endif