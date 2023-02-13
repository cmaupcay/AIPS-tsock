# TP AIPS - __tsock__

> __Étudiant n°1 :__ Clément MAUPERON

- [Compilation](#compilation)
  - [Exécutable seulement](#exécutable-seulement)
  - [Tests rapides](#tests-rapides)
  - [Nettoyage](#nettoyage)
- [Utilisation](#utilisation)
  - [Mode puits](#mode-puits)
  - [Mode source](#mode-source)
  - [Autres options](#autres-options)

## Compilation

L'ensemble des cibles disponibles sont détaillées dans le fichier `Makefile`. Vous pouvez compiler les cibles principales avec `make` ou `make all`.

### Exécutable seulement

Pour compiler l'exécutable _`tsock`_ seulement, utiliser la commande `make tsock`.

### Tests rapides

Pour tester rapidement les fonctionnalités de ___tsock___, utiliser la commande `make test`.

### Nettoyage

Vous pouvez nettoyer facilement le dossier de travail avec les commandes `make clean` et `make erase`.

## Utilisation

### Mode puits

Pour utiliser le __mode puits__, utiliser l'option `-p` et indiquer le port à ouvrir. Voici un exemple d'utilisation :

```bash
$ ./bin/tsock -p 7000

PUITS : lg_mesg-lu=30, port=7000, nb_receptions=infini, TP=TCP
```

### Mode source

Pour utiliser le __mode source__, utiliser l'option `-s` et indiquer le nom d'hôte et le port de destination. Voici un exemple d'utilisation :

```bash
$ ./bin/tsock -s localhost 7000

SOURCE : lg_mesg_emis=30, port=7000, nb_envois=10, TP=TCP, dest=localhost
```

### Autres options

Les options suivantes sont aussi disponibles :

- __-u :__ utilisation du protocole _UDP_ plutôt que _TCP_ ;
- __-l \<_taille_\> :__ surcharge de la taille des messages échangés ;
- __-n \<_messages_\> :__ surcharge du nombre de messages envoyés pour la [source](#mode-source) et de messages reçus pour le [puits](#mode-puits) ;
- __-a :__ gestion asynchrone des requêtes (_en mode [puits](#mode-puits) seulement_).

> __Dépôt :__ [github.com/tensaiji/AIPS-tsock](https://github.com/tensaiji/AIPS-tsock/)