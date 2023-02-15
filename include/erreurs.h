#ifndef H_TSOCK_ERREURS
#define H_TSOCK_ERREURS

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void tsock_erreur(const char* message);

#define TSOCK_ERREUR_USAGE_MSG "Usage: tsock [-u] [-n <messages>] [-l <taille>] -p <port> | -s [dest] <port> "
#define TSOCK_ERREUR_USAGE tsock_erreur(TSOCK_ERREUR_USAGE_MSG)

#define TSOCK_ERREUR_PORT_MSG "Le port doit être supérieur à 5000 "
#define TSOCK_ERREUR_PORT tsock_erreur(TSOCK_ERREUR_PORT_MSG)

#define TSOCK_ERREUR_DEBUT_MSG "Impossible de créer le socket de connexion "
#define TSOCK_ERREUR_DEBUT tsock_erreur(TSOCK_ERREUR_DEBUT_MSG)

#define TSOCK_ERREUR_ENVOI_MSG "Impossible d'envoyer le message "
#define TSOCK_ERREUR_ENVOI tsock_erreur(TSOCK_ERREUR_ENVOI_MSG)

#define TSOCK_ERREUR_RECEPTION_MSG "Impossible de recevoir le prochain message "
#define TSOCK_ERREUR_RECEPTION tsock_erreur(TSOCK_ERREUR_RECEPTION_MSG)

#define TSOCK_ERREUR_FIN_MSG "Impossible de fermer le socket de connexion "
#define TSOCK_ERREUR_FIN tsock_erreur(TSOCK_ERREUR_FIN_MSG)

#endif