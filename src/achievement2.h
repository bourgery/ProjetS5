#ifndef _achievement2_H
#define _achievement2_H
#include "achievement1.h"

void init_tab_entier(int tab[], int taille);
int choix_du_bateau(struct Grille *grille, struct Joueur *joueur);
int verif_arrive_bateau(struct Grille grille, struct Batal bat, int liste_indice_oblitere[]);
void liste_case_possibles(struct Grille grille, struct Batal bateau, int *tab, int *liste_case_possibles, int tab_prec[]);
void liste_case_possiblesrec(struct Grille grille, struct Batal bateau, int *tab, int indice, int *liste_case_possibles, int tab_prec[]);
int deplacement_possible_uniquement(int tab_pas_tous[], int tab_tous[]);
int indice_pos_dans_tab(struct Position *pos, struct Position tab[], int taille);
void mise_a_jour_batal(struct Batal *bat, struct Position *nouvelle);
void mise_a_jour_liste(struct Batal bat, struct Joueur *joueur, struct Position *nouvelle);
void mise_a_jour_structure(struct Grille *grille, struct Batal *bat, int *liste_indice_oblitere, struct Position *nouvelle);
void bouger_bateau(struct Grille *grille, struct Joueur *joueur, SDL_Surface *ecran, int affichage);
void afficher_mvt_bateau_SDL(int tab_prec[], SDL_Surface *ecran, struct Batal bat, struct Position pos_arrive, struct Grille grille, int liste_indice_oblitere[]);
int achievement2(SDL_Surface *ecran, int affichage);
#endif
