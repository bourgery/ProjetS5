#ifndef _achievement1_H
#define _achievement1_H
#include "achievement0.h"
#define NB_COUP_MAX 100
#define PORTEE_MAX_TORPILLE 100

int abs(int x);
int distance_minimale(struct Position *position1, struct Position *position2);
int arrive_torpille(struct Position *pos_de_depart, struct Joueur *joueur, struct Position *pos_arrive);
int depart_torpille(struct Joueur *joueur);
void choix_couleur_fleche(char *c, int joueur);
void afficher_chemin(struct Position pos_depart, struct Position pos_arrive, int joueur);
void afficher_chemin_SDL(struct Position pos_depart, struct Position pos_arrive, int joueur, struct Grille grille, SDL_Surface *ecran);
void afficher_chem(SDL_Surface *ecran, struct Position pos_depart, struct Position pos_arrive, int joueur, struct Grille grille, int affichage);
int achievement1(SDL_Surface *ecran, int affichage);
#endif
