#ifndef ACHIEVEMENT4_H
#define ACHIEVEMENT4_H
#include "achievement3.h"
#define NB_PORTALS 2
#define NB_ARCHIPALS 5

enum Cote_case{
  HAUT=1, DROITE, BAS, GAUCHE
};

struct Portal{
  int indpos;
  int arrive;
  enum Cote_case cote;
};

struct Chemin_Minimal{
  int tab[NB_COLONNES*NB_LIGNES];
  int taille;
};

int existence_case(struct Position *position);
int cote_portal(struct Portal portals[],int indice);
void init_floyd_warshall(struct Grille *grille, struct Chemin_Minimal tab[],struct Portal portals[]);
void floyd_warshall(struct Chemin_Minimal tab[]);
int distminimale(struct Position *pos1, struct Position *pos2, struct Chemin_Minimal tab[]);
int arrive_torpille2(struct Position *pos_de_depart, struct Joueur *joueur, struct Position *pos_arrive, struct Chemin_Minimal tab[]);
int cote_aleatoire();
void init_portals(struct Grille *grille, struct Portal portals[]);
void init_archipals(struct Grille *grille);
int direction_portal(struct Position pos, struct Portal tab[]);
int portal_ou_non(struct Position pos, struct Grille grille, struct Portal tab[], int direction);
void bouge_pos_bat(struct Batal *bat, int direction, struct Portal tab[], struct Grille grille);
void copie_bat(struct Batal *bat1, struct Batal bat2);
void liste_case_possible2(struct Grille grille, struct Batal bat, struct Portal tab_portal[], struct Batal tab[], int liste_indice_oblitere[]);
void liste_case_possiblerec2(struct Grille grille, struct Batal bata, struct Portal tab_portal[], struct Batal tab[], int liste_indice_oblitere[], int direction);
int achievement4();





#endif
