#ifndef _achievement3_H
#define _achievement3_H
#include "achievement2.h"

struct Monstre{
  struct Position pos;
  int agresse; //s'il est agresse ou non
  int tab_joueur_agresse[NB_JOUEURS];//si le joueur i l'a agresse ou non
};
void init_monstre(struct Monstre *monstre);
void placer_monstre(struct Monstre *monstre, struct Grille *grille);
int monstre_oblitere(struct Grille *grille, struct Monstre *monstre, struct Joueur *j1, struct Joueur *j2);
void case_plus_proche_monstre(struct Joueur *j, struct Monstre *monstre, struct Position tab[], int *distance, int *nombre_case);
void deplacement_monstre_pas_agresse(struct Joueur *j1, struct Joueur *j2, struct Monstre *monstre, struct Grille *grille);
int bateau_le_plus_proche(struct Monstre *monstre,  struct Joueur *j);
int position_dans_tab(struct Position tab[], struct Position *pos, int taille);
int position_dans_tab_et_possible(struct Position tab[], struct Position *pos, int taille, struct Batal *bat, struct Grille *grille);
struct Position case_autour_du_batal(struct Batal *bat, struct Grille *grille);
void deplacement_monstre_agresse(struct Grille *grille, struct Monstre *monstre, struct Joueur *j1, struct Joueur *j2, SDL_Surface *ecran, int affichage);
void monstre_qui_joue(struct Monstre *monstre, struct Grille *grille, struct Joueur *joueur1, struct Joueur *joueur2, SDL_Surface *ecran, int affichage);
void chemin_monstre_SDL(struct Position posd, struct Position posa, SDL_Surface *ecran);
int achievement3(SDL_Surface *ecran, int affichage);
#endif
