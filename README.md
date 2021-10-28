Projet de création d'une version de pong sur PC, codé en C

pour compiler le programme, il faut avoir préalablement télécharger le package de la librairie SDL2, en effectuant la commande suivante sur bash :

sudo apt-get install libsdl2-dev

ensuite, il suffit de se déplacer dans le dossier dans lequel se trouve pong.c et d'effectuer la commande suivante :

gcc pong.c -o pong -lm -lSDL2

finalement, pour executer le code, ecrivez ./pong.
