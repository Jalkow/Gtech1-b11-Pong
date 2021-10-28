Projet de création d'une version de pong sur PC, codé en C

pour compiler le programme, il faut avoir préalablement télécharger le package des librairies SDL2 et SDL2_ttf, en effectuant la commande suivante sur bash :

sudo apt-get install libsdl2-dev libsdl2-ttf-dev

ensuite, il suffit de se déplacer dans le dossier dans lequel se trouve pong.c et d'effectuer la commande suivante :

gcc pong.c -o pong -lm -lSDL2 -lSDL2_ttf

finalement, pour executer le code, ecrivez ./pong.
