#include "../include/erreurs.h"

#include <stdlib.h>
#include <stdio.h>

void tsock_erreur(const char* message)
{
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}