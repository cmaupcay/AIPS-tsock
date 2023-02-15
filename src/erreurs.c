#include "../include/erreurs.h"

void tsock_erreur(const char* message)
{
    if (errno == 0) errno = EPERM;
    perror(message);
    exit(errno);
}