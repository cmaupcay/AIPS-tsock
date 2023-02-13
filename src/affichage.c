#include "../include/affichage.h"

void tsock_afficher(const char* const message, const tsock_config* const config)
{
    printf("%s%s", config->mode == TSOCK_PUITS ? TSOCK_PREFIX_PUITS : TSOCK_PREFIX_SOURCE, message);
}

void tsock_afficher_config(const tsock_config* const config)
{
	const char* tp = config->protocole == TSOCK_UDP ? "UDP" : "TCP";
	if (config->mode == TSOCK_SOURCE)
	{
		printf(TSOCK_PREFIX_SOURCE);
		printf(
            "lg_mesg_emis=%u, port=%hu, nb_envois=%u, TP=%s, dest=%s",
            config->lg_messages, config->port, config->nb_messages, tp, config->destinataire
        );
	}
	else
	{
		printf(TSOCK_PREFIX_PUITS);
		printf("lg_mesg-lu=%u, port=%hu, nb_receptions=", config->lg_messages, config->port);
		if (config->nb_messages == 0) printf("infini");
		else printf("%u", config->nb_messages);
		printf(", TP=%s", tp);
	}
	printf("\n");
}

void tsock_afficher_message(const char* const message, const int lg)
{
	int i;
	for (i = 0;i < lg; i++)
        printf("%c", message[i]);
}