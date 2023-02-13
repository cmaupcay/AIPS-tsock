#ifndef H_TSOCK_ERREURS
#define H_TSOCK_ERREURS

void tsock_erreur(const char* message);

#define TSOCK_ERREUR_USAGE_MSG "Usage: tsock [-u] [-n <messages>] -p <port> | -s <dest> <port>"
#define TSOCK_ERREUR_USAGE tsock_erreur(TSOCK_ERREUR_USAGE_MSG)

#endif