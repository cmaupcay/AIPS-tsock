#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>

#define USAGE_ERR "Usage: tsock [-p|-s] [-u] [-n ##]\n"
#define ARGS_ERR  "Pas assez d'arguments...\n"
#define SOCKET_ERR "Impossible de créer le socket.\n"
#define CONNECT_ERR "Impossible de se connecter au puits.\n"
#define SEND_ERR "Impossible d'envoyer le message.\n"
#define RECIEVE_ERR "Impossible de recevoir le message.\n"

#define SOURCE_PRE 	"SOURCE : "
#define PUITS_PRE	"PUITS : "

#define SOURCE_MSG_PAR_DEFAUT 10

#define LG_MSG_PAR_DEFAUT 30

unsigned int getOptsFromArgs(int argc, char** argv, int* nb_message, int* source, int* protocole)
{
	unsigned int opts = 0;
	int c;
	extern char *optarg;
	extern int optind;
	while ((c = getopt(argc, argv, "pn:su")) != -1) {
		switch (c) {
		case 'p':
			if (*source == 1) {
				printf(USAGE_ERR);
				exit(1);
			}
			*source = 0;
			opts++;
			break;

		case 's':
			if (*source == 0) {
				printf(USAGE_ERR);
				exit(1) ;
			}
			*source = 1;
			opts++;
			break;

		case 'n':
			*nb_message = atoi(optarg);
			opts += 2;
			break;

		case 'u':
			*protocole = 1;
			opts++;
			break;

		default:
			printf(USAGE_ERR);
			opts++;
			break;
		}
	}
	if (*source == 1 && *nb_message == -1) *nb_message = SOURCE_MSG_PAR_DEFAUT;
	return opts;
}

void getConfigFromArgs(int argc, char** argv, const unsigned int* opts, const int* source, int* port, char** host)
{
	if (*source == 1) // Source
	{
		if (*opts + 2 >= argc)
		{
			printf(ARGS_ERR);
			printf(USAGE_ERR);
			exit(EXIT_FAILURE);
		}
		*host = argv[*opts + 1];
		*port = atoi(argv[*opts + 2]);
	}
	else // Puit
	{
		if (*opts + 1 >= argc)
		{
			printf(ARGS_ERR);
			printf(USAGE_ERR);
			exit(EXIT_FAILURE);
		}
		*port = atoi(argv[*opts + 1]);
	}
	// *port = htons(*port);
}

void printSessionConfig(const int* source, const int* lg_message, const int* nb_message, const int* protocole, const int* port, const char* host)
{
	const char* tp = *protocole == 1 ? "UDP" : "TCP";
	if (*source == 1)
	{
		printf(SOURCE_PRE);
		printf("lg_mesg_emis=%d, port=%d, nb_envois=%d, TP=%s, dest=%s", *lg_message, *port, *nb_message, tp, host);
	}
	else
	{
		printf(PUITS_PRE);
		printf("lg_mesg-lu=%d, port=%d, nb_receptions=", *lg_message, *port);
		if (*nb_message < 0) printf("infini");
		else printf("%d", *nb_message);
		printf(", TP=%s", tp);
	}
	printf("\n");
}

int createSocket(const int* protocole)
{
	int sock = socket(AF_INET, *protocole == 0 ? SOCK_STREAM : SOCK_DGRAM, 0);
	if (sock == -1)
	{
		printf(SOCKET_ERR);
		exit(EXIT_FAILURE);
	}
	return sock;
}

void construire_message(char *message, char motif, int lg)
{
	int i;
	for (i=0;i<lg;i++) message[i] = motif;
}

void source_send(const int* sock, const struct sockaddr_in* host, const int* protocole, const char* message, const int* lg_message)
{
	if (*protocole == 0)
	{

	}
	else
	{
		if (sendto(*sock, message, *lg_message, 0, (const struct sockaddr*)host, sizeof(host)) == -1)
		{
			printf(SEND_ERR);
			exit(EXIT_FAILURE);
		}
	}
}

void source_start(const int* sock, const int* protocole, const int* nb_message, const int* lg_message, const int* port, const char* host)
{
	// Construction de l'adresse du puit cible.
	struct sockaddr_in hostAdress;
	memset((char*)&hostAdress, 0, sizeof(hostAdress));
	hostAdress.sin_family = AF_INET;
	hostAdress.sin_port = *port;
	struct hostent* hostInfos = gethostbyname(host);
	if (hostInfos == NULL)
	{
		printf(CONNECT_ERR);
		exit(EXIT_FAILURE);
	}
	memcpy((char*)&(hostAdress.sin_addr.s_addr), hostInfos->h_addr_list, hostInfos->h_length);
	// Génération et envoi des messages.
	int n = 0;
	char* message = (char*)malloc(*lg_message * sizeof(char));
	char motif = 'a';
	for (n = 0; n < *nb_message; n++)
	{
		construire_message(message, motif, *lg_message);
		printf(SOURCE_PRE);
		printf("Envoi n°%d (%d) [----%d%s]\n", n + 1, *lg_message, n + 1, message);
		source_send(sock, &hostAdress, protocole, message, lg_message);
		motif++;
		if (motif > 'z') motif = 'a';
	}
	printf(SOURCE_PRE);
	printf("fin\n");
}

void afficher_message(char *message, int lg)
{
	int i;
	for (i=0;i<lg;i++) printf("%c", message[i]);
}

void puits_recieve(const int* sock, const int* protocole, char* message, const int* lg_message)
{
	if (*protocole == 0)
	{

	}
	else
	{
		if (recvfrom(*sock, message, *lg_message, 0, NULL, 0) == -1)
		{
			printf(RECIEVE_ERR);
			exit(EXIT_FAILURE);
		}
	}
}

void puits_start(const int* sock, const int* protocole, const int* nb_message, const int* lg_message, const int* port)
{
	struct sockaddr_in adresse;
	memset((char*)&adresse, 0, sizeof(adresse));
	adresse.sin_family = AF_INET;
	adresse.sin_port = *port;
	adresse.sin_addr.s_addr = INADDR_ANY;
	if (bind(*sock, (struct sockaddr*)&adresse, sizeof(adresse)) == -1)
	{
		printf(SOCKET_ERR);
		exit(EXIT_FAILURE);
	}
	// Réception des messages.
	int n = 0;
	char* message = (char*)malloc(*lg_message * sizeof(char));
	for (n = 0; n < *nb_message; n++)
	{
		printf(PUITS_PRE);
		printf("Réception n°%d (%d) [----%d", n + 1, *lg_message, n + 1);
		puits_recieve(sock, protocole, message, lg_message);
		afficher_message(message, *lg_message);
		printf("]\n");
	}
}

int main(int argc, char **argv)
{
	int source = -1 ; /* 0=puits, 1=source */
	int protocole = 0; /* 0 = TCP, 1 = UDP */
	int nb_message = -1; /* Nb de messages à envoyer ou à recevoir, par défaut : 10 en émission, infini en réception */
	int lg_message = LG_MSG_PAR_DEFAUT;

	const unsigned int opts = getOptsFromArgs(argc, argv, &nb_message, &source, &protocole);

	if (source == -1) {
		printf(USAGE_ERR);
		exit(1) ;
	}

	int port = -1;
	char* host = NULL;
	getConfigFromArgs(argc, argv, &opts, &source, &port, &host);

	printSessionConfig(&source, &lg_message, &nb_message, &protocole, &port, host);

	int sock = createSocket(&protocole);
	if (source == 1) source_start(&sock, &protocole, &nb_message, &lg_message, &port, host);
	else puits_start(&sock, &protocole, &nb_message, &lg_message, &port);

	close(sock);

	return EXIT_SUCCESS;
}