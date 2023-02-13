#ifndef H_TSOCK_CONFIG
#define H_TSOCK_CONFIG

#include "erreurs.h"

#include <unistd.h>

#define TSOCK_OPTIONS                       "pn:su"
#define TSOCK_PROTOCOLE_PAR_DEFAUT          0
#define TSOCK_NB_MESSAGES_PAR_DEFAUT_PUITS  0
#define TSOCK_NB_MESSAGES_PAR_DEFAUT_SOURCE 10
#define TSOCK_LG_MESSAGES_PAR_DEFAUT        30

typedef enum
{
    TSOCK_NON_CONFIGURE = -1,
    TSOCK_PUITS = 0,
    TSOCK_SOURCE = 1
} tsock_mode;

typedef enum
{
    TSOCK_TCP = 0,
    TSOCK_UDP = 1
} tsock_protocole;

typedef struct
{
    tsock_mode mode;
    tsock_protocole protocole;
    unsigned int nb_messages;
    unsigned int lg_messages;
    unsigned short port;
    const char* destinataire;
} tsock_config;

tsock_config* tsock_creer_config();

void tsock_configurer(tsock_config* const config, const int argc, char* const* argv);

#endif