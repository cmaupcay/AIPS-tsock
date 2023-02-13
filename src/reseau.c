#include "../include/reseau.h"
#include <errno.h>
void tsock_construire_message(char* message, char motif, const int lg)
{
	int i;
	for (i = 0; i < lg; i++)
		message[i] = motif;
}

struct sockaddr_in* tsock_adresser(const tsock_config* const config)
{
	struct sockaddr_in* adresse = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	memset((char*)adresse, 0, sizeof(adresse));
	adresse->sin_family = AF_INET;
	adresse->sin_port = htons(config->port);
	if (config->mode == TSOCK_SOURCE)
	{
		const struct hostent* infos = gethostbyname(config->destinataire);
		if (infos == NULL) TSOCK_ERREUR_SOCKET;
		memcpy((char*)&(adresse->sin_addr.s_addr), infos->h_addr_list[0], infos->h_length);
	}
	else adresse->sin_addr.s_addr = htonl(INADDR_ANY);
	return adresse;
}

int tsock_socket(const tsock_config* const config, const struct sockaddr_in* const adresse)
{
	const int sock = socket(
		AF_INET,
		config->protocole == TSOCK_TCP ? SOCK_STREAM : SOCK_DGRAM,
		0
	);
	if (sock == -1) TSOCK_ERREUR_SOCKET;
	if (config->mode == TSOCK_PUITS)
	{
		if (bind(sock, (const struct sockaddr*)adresse, sizeof(*adresse)) == -1)
			TSOCK_ERREUR_SOCKET;
	}
	else if (config->protocole == TSOCK_TCP)
	{
		if (connect(sock, (const struct sockaddr*)adresse, sizeof(*adresse)) == -1)
			TSOCK_ERREUR_SOCKET;
	}
	return sock;
}

unsigned int tsock_envoyer(const char* const message, const int sock, const tsock_config* const config, const struct sockaddr_in* const adresse)
{
	int envoyes = -1;
	if (config->protocole == TSOCK_TCP)
		envoyes = write(sock, message, config->lg_messages);
	else
	    envoyes = sendto(
			sock, message, config->lg_messages, 0,
			(const struct sockaddr*)adresse, sizeof(*adresse)
		);
	if (envoyes == -1) TSOCK_ERREUR_ENVOI;
	return envoyes;
}

unsigned int tsock_recevoir(char* const message, const int sock, const tsock_config* const config)
{
	int recus = -1;
	if (config->protocole == TSOCK_TCP)
		recus = read(sock, message, config->lg_messages);
	else
		recus = recvfrom(sock, message, config->lg_messages, 0, NULL, 0);
	if (recus == -1) TSOCK_ERREUR_RECEPTION;
	return recus;
}