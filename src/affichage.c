#include "../include/affichage.h"

#include <stdio.h>

void tsock_afficher(const char* message, const tsock_config* const config)
{
    printf("%s%s\n", config->mode == TSOCK_PUITS ? TSOCK_PREFIX_PUITS : TSOCK_PREFIX_SOURCE, message);
}

void tsock_afficher_config(const tsock_config* const config)
{
	const char* tp = config->protocole == TSOCK_UDP ? "UDP" : "TCP";
	if (config->mode == TSOCK_SOURCE)
	{
		printf(TSOCK_PREFIX_SOURCE);
		printf(
            "lg_mesg_emis=%d, port=%d, nb_envois=%d, TP=%s, dest=%s",
            config->lg_messages, config->port, config->nb_messages, tp, config->destinataire
        );
	}
	else
	{
		printf(TSOCK_PREFIX_PUITS);
		printf("lg_mesg-lu=%d, port=%d, nb_receptions=", config->lg_messages, config->port);
		if (config->nb_messages == 0) printf("infini");
		else printf("%d", config->nb_messages);
		printf(", TP=%s", tp);
	}
	printf("\n");
}