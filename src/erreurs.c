#include "../include/erreurs.h"

void tsock_erreur(const char* message)
{
    perror(message);
    exit(EXIT_FAILURE);
}