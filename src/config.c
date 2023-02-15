#include "../include/config.h"

tsock_config* tsock_creer_config()
{
    tsock_config* config = (tsock_config*)malloc(sizeof(tsock_config));
    config->mode = TSOCK_NON_CONFIGURE;
    config->protocole = (tsock_mode)TSOCK_PROTOCOLE_PAR_DEFAUT;
    config->nb_messages = 0;
    config->lg_messages = TSOCK_LG_MESSAGES_PAR_DEFAUT;
    config->destinataire = NULL;
    config->async = 0;
    return config;
}

void tsock_configurer(tsock_config* const config, const int argc, char* const* argv)
{
    if (argc < 2) TSOCK_ERREUR_USAGE;
    int opt;
    extern char* optarg;
    extern int optind;
    while ((opt = getopt(argc, argv, TSOCK_OPTIONS)) != -1)
    {
        switch (opt)
        {
        case 'p':
            if (config->mode != TSOCK_NON_CONFIGURE)
                TSOCK_ERREUR_USAGE;
            config->mode = TSOCK_PUITS;
            config->nb_messages = TSOCK_NB_MESSAGES_PAR_DEFAUT_PUITS;
            break;

        case 's':
            if (config->mode != TSOCK_NON_CONFIGURE)
                TSOCK_ERREUR_USAGE;
            config->mode = TSOCK_SOURCE;
            config->nb_messages = TSOCK_NB_MESSAGES_PAR_DEFAUT_SOURCE;
            break;

        case 'n':
            config->nb_messages = atoi(optarg);
            break;

        case 'u':
            config->protocole = TSOCK_UDP;
            break;

        case 'l':
            config->lg_messages = atoi(optarg);
            break;

        case 'a':
            config->async = 1;
            break;

        default:
            break;
        }
    }
    if (config->mode == TSOCK_NON_CONFIGURE) TSOCK_ERREUR_USAGE;
    if (config->mode == TSOCK_PUITS)
    {
        if (optind < argc) config->port = atoi(argv[optind]);
        else TSOCK_ERREUR_USAGE;
    }
    else
    {
        if (optind + 1 < argc)
        {
            config->destinataire = argv[optind];
            config->port = atoi(argv[optind + 1]);
        }
        else if (optind < argc)
        {
            config->destinataire = TSOCK_DESTINATAIRE_PAR_DEFAUT;
            config->port = atoi(argv[optind]);
        }
        else TSOCK_ERREUR_USAGE;
    }
    if (config->port < TSOCK_PORT_MIN) TSOCK_ERREUR_PORT;
}