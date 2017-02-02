Ceci est le projet du semestre 5 de l’enseirb qui consistait à réaliser une bataille navale avec différents objectifs.
Il faut installer la police angelina.TTF qui se trouve dans le dossier doc.
Pour lancer la compilation de tous les fichiers il faut exécuter la commande make.
Pour exécuter l'achievement "i" il faut exécuter la commande make execute"i" pour avoir l'affichage dans le terminal et la commande make executeSDL"i" pour avoir l'affichage en SDL.
Lors de l’execution en SDL pour avancer dans les étapes il faut appuyer sur “espace”
Avant de lancer les tests il faut mettre les constantes aux bonnes valeurs c'est à dire :
NB_MONSTRES 1
NB_JOUEURS 2
NB_BATALS 5
NB_LIGNES 10
NB_COLONNES 10
TAILLE_MAX_BAT 10
TAB_TAILLE 5,4,3,2,1
PORTEE_MAX_TORPILLE 100
NB_PORTALS 2
NB_ARCHIPALS 5

Pour lancer tous les tests il faut la commande make test où si on veut exécuter les tests achievement par achievement il faut lancer la commande make test"i" où i correspond au numéro de l'achievement.
Avant de relancer le même test il faut utiliser la commande make clean.
