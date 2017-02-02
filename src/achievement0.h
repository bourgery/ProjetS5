#ifndef _achievement0_H
#define _achievement0_H
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define couleur(param) printf("\033[%sm",param)
#define NB_PIXEL_CASE 60
#define NB_MONSTRES 1
#define NB_JOUEURS 2
#define NB_BATALS 5
#define NB_LIGNES 10
#define NB_COLONNES 10
#define TAILLE_MAX_BAT 10
#define TAB_TAILLE 5,4,3,2,1

struct Position{
  int ligne;
  int colonne;
};

struct Case{
  int tab[NB_JOUEURS + NB_MONSTRES + 1]; //Case 0 : intact ou oblitere, case i : présence du joueur ou d'un monstre
};

struct Grille{
  struct Case tab[NB_LIGNES * NB_COLONNES];
};

enum Alignement{
  VERTICAL = 10, HORIZONTAL = 1, INCONNUE = 0, ROND = 20, H1=31, H2=32, L1=41, L2=42, L3=43, L4=44, L5=45, L6=46, L7=47, L8=48
};
 
struct Batal{
  int taille;
  struct Position tab[TAILLE_MAX_BAT];
  enum Alignement alignement;
  int joueur;
};

struct Joueur{
  int joueur;
  struct Batal tab[NB_BATALS];
  struct Position case_en_vie[NB_BATALS * TAILLE_MAX_BAT];
  int taille;
};

void pause();
void init_rand();
void init_tab();
void echange_element_tab(int indice1, int indice2);
void melange_tab();
void init_grille(struct Grille *grille);
void init_batal(struct Batal *joueur, int taille, struct Position *positon, int alignement, int nbjoueur);
void init_rond(struct Batal *bateau, struct Position *posinit);
void init_H(struct Batal *bateau, struct Position *posinit,int alignement);
void init_L(struct Batal *bateau, struct Position *posinit,int alignement);
void init_joueur(struct Joueur *joueur, int nbjoueur);
void choix_couleur(int n);
int valeur_a_afficher(struct Case *cases);
void afficher_grille(struct Grille *grille);
int position_to_grille(struct Position *position);
struct Position grille_to_position(int index);
struct Position position_aleatoire();
int alignement_aleatoire(int taille);
int batal_en_jeu(struct Batal *bateau, struct Grille *grille);
int max_colonne_batal(struct Batal *bateau);
int verif_pour_mettre_bateau(struct Grille *grille, struct Batal *bateau);
void placer_batal(struct Grille *grille, struct Batal *bateau);
void obliterer_une_case(struct Grille *grille, struct Position *position, struct Joueur *joueur1, struct Joueur *joueur2);
int un_bateau_toujours_en_vie(struct Grille *grille, struct Joueur *joueur);
void placer_batal_joueur(struct Joueur *joueur, struct Grille *grille);
void afficher_grille_SDL(struct Grille *grille, SDL_Surface *ecran, int continuer);
void afficher(struct Grille *grille, SDL_Surface *ecran, int n, int affichage);
int achievement0();

#endif
