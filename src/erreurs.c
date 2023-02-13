#include "../include/erreurs.h"

void tsock_erreur(const char* message)
{
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}