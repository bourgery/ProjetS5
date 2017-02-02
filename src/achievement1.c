#include "achievement1.h"

//Tableau des tailles des différents bateaux
int TAB_TAILLES3[NB_BATALS]={TAB_TAILLE};

int abs(int x){
  if(x < 0)
    return(-x);
  return(x);
}

//Calcule la distance minimal entre deux cases
int distance_minimale(struct Position *position1, struct Position *position2){
  return(abs(position1->ligne - position2->ligne) + abs(position1->colonne - position2->colonne));
}

//Calcul l'arrive de la torpille
int arrive_torpille(struct Position *pos_de_depart, struct Joueur *joueur, struct Position *pos_arrive){
  int distance = NB_LIGNES * NB_COLONNES;
  int a;
  pos_arrive->ligne = NB_LIGNES; //Si on a rien touché
  pos_arrive->colonne = NB_COLONNES; // Si on a rien touché
  for(int i = 0; i < joueur->taille; i ++){ //On parcourt toutes les positions de la liste des positions des bateaux de l'autre joueur pour trouver la plus petite distance
    a = distance_minimale(pos_de_depart, &(joueur->case_en_vie[i]));
    if((a <= PORTEE_MAX_TORPILLE) && (a <= distance)){
      pos_arrive->ligne = joueur->case_en_vie[i].ligne;
      pos_arrive->colonne = joueur->case_en_vie[i].colonne;
      distance = a;
    }
  }
  return(distance);
}

//On renvoie un indice aléatoire parmis les cases en vie ce qui nous donnera la position de départ de la torpille 
int depart_torpille(struct Joueur *joueur){
  return(rand() % (joueur->taille));
}

//Pour savoir la couleur pour l'affichage de la trajectoire de la torpille
void choix_couleur_fleche(char *c, int joueur){
  if((joueur ==1) && strcmp(c, "."))
    couleur("34");
  else if((joueur == 2) && strcmp(c, "."))
    couleur("33");
  else
    couleur("0");
}

//Affiche chemin en console
void afficher_chemin(struct Position pos_depart, struct Position pos_arrive, int joueur){
  struct Position pos1 = {pos_depart.ligne, pos_depart.colonne};
  char *tab[100];
  if((pos_arrive.ligne != NB_LIGNES) && (pos_arrive.colonne != NB_COLONNES)){
    for(int i = 0; i < 100; i ++){
      tab[i] = ".";
    }
    if(pos_depart.ligne > pos_arrive.ligne){
      while(pos_depart.ligne != pos_arrive.ligne){
        pos_depart.ligne -= 1;
        tab[position_to_grille(&pos_depart)] = "↑";

      }
    }
    if(pos_depart.ligne < pos_arrive.ligne){
      while(pos_depart.ligne != pos_arrive.ligne){
        pos_depart.ligne += 1;
        tab[position_to_grille(&pos_depart)] = "↓";
      }
    }
    if(pos_depart.colonne > pos_arrive.colonne ){
      while(pos_depart.colonne != pos_arrive.colonne){
        tab[position_to_grille(&pos_depart)] = "←";
        pos_depart.colonne -= 1;
      }
    }
    if(pos_depart.colonne < pos_arrive.colonne){
      while(pos_depart.colonne != pos_arrive.colonne){
        tab[position_to_grille(&pos_depart)] = "→";
        pos_depart.colonne += 1;
      }
    }
    tab[position_to_grille(&pos1)] = "x";
    tab[position_to_grille(&pos_arrive)] = "☠";
 
  for(int i = 0; i < 10; i++){
    printf("\t%d", i);
  }
  printf("\n");
  for(int i = 0; i < 10; i ++){
    printf("%d", i);
    for(int j = 0; j < 10; j++){
      choix_couleur_fleche(tab[(i * 10) + j], joueur);
      printf("\t%s", tab[(i * 10) + j]);
      couleur("0");
    }
    printf("\n");
  }
  }
  else
    printf("Le joueur %d n'a rien touché\n", joueur);
}

//Affiche chemin en SDL
void afficher_chemin_SDL(struct Position pos_depart, struct Position pos_arrive, int joueur, struct Grille grille, SDL_Surface *ecran){
  SDL_Surface *cases = NULL;
  SDL_Rect pos;
  cases = SDL_CreateRGBSurface(SDL_HWSURFACE, NB_PIXEL_CASE, NB_PIXEL_CASE, 32, 0, 0, 0, 0);
  Uint32 couleurj;
  pos.x = pos_depart.colonne * NB_PIXEL_CASE;
  pos.y = pos_depart.ligne * NB_PIXEL_CASE;
  if(joueur == 1)
    couleurj = SDL_MapRGB(ecran->format, 27, 79, 8);
  else
    couleurj = SDL_MapRGB(ecran->format, 112, 41, 99);
    if(pos_depart.ligne > pos_arrive.ligne){
      while(pos_depart.ligne != pos_arrive.ligne){
	pos_depart.ligne -= 1;
	pos.y -= NB_PIXEL_CASE;
	SDL_FillRect(cases, NULL, couleurj);
	SDL_BlitSurface(cases, NULL, ecran, &pos);
	SDL_Flip(ecran);
	SDL_Delay(150);
	afficher_grille_SDL(&grille, ecran, 0);
      }
    }
    if(pos_depart.ligne < pos_arrive.ligne){
      while(pos_depart.ligne != pos_arrive.ligne){
	pos_depart.ligne += 1;
	pos.y +=  NB_PIXEL_CASE;
	SDL_FillRect(cases, NULL, couleurj);
	SDL_BlitSurface(cases, NULL, ecran, &pos);
	SDL_Flip(ecran);
	SDL_Delay(150);
	afficher_grille_SDL(&grille, ecran, 0);
      }
    }
    if(pos_depart.colonne > pos_arrive.colonne){
      while(pos_depart.colonne != pos_arrive.colonne){
	pos_depart.colonne -= 1;
	pos.x -= NB_PIXEL_CASE; 
	SDL_FillRect(cases, NULL, couleurj);
	SDL_BlitSurface(cases, NULL, ecran, &pos);
	SDL_Flip(ecran);
	SDL_Delay(150);
	afficher_grille_SDL(&grille, ecran, 0);
      } 
    }
    if(pos_depart.colonne < pos_arrive.colonne){
      while(pos_depart.colonne != pos_arrive.colonne){
	pos_depart.colonne += 1;
	pos.x += NB_PIXEL_CASE; 
	SDL_FillRect(cases, NULL, couleurj);
	SDL_BlitSurface(cases, NULL, ecran, &pos);
	SDL_Flip(ecran); 
	SDL_Delay(150);
	afficher_grille_SDL(&grille, ecran, 0);
      }
    }
    grille.tab[position_to_grille(&pos_arrive)].tab[0] = -1;
    afficher_grille_SDL(&grille, ecran, 0);
    SDL_FreeSurface(cases);
}

void afficher_chem(SDL_Surface *ecran, struct Position pos_depart, struct Position pos_arrive, int joueur, struct Grille grille, int affichage){
  if(affichage == 0)
    afficher_chemin(pos_depart, pos_arrive, joueur);
  else
    afficher_chemin_SDL(pos_depart, pos_arrive, joueur, grille, ecran);
}

int achievement1(SDL_Surface *ecran, int affichage){
  init_rand();
  int nb_coup = 0;
  int depart1 = 0;
  int depart2 = 0;
  struct Grille grille;
  struct Position pos1;
  struct Position pos2;
  init_grille(&grille);
  struct Joueur joueur1;
  struct Joueur joueur2;
  init_joueur(&joueur1, 1);
  init_joueur(&joueur2, 2);
  placer_batal_joueur(&joueur1, &grille);
  placer_batal_joueur(&joueur2, &grille);
  afficher(&grille, ecran, 1, affichage);
  while((joueur1.taille > 0) && (joueur2.taille > 0) && (nb_coup < NB_COUP_MAX)){
    depart1 = depart_torpille(&joueur1); //On cherche le premier depart
    arrive_torpille(&(joueur1.case_en_vie[depart1]), &joueur2, &pos1); //Et arrive
    depart2 = depart_torpille(&joueur2); //On cherche le deuxieme depart
    arrive_torpille(&(joueur2.case_en_vie[depart2]), &joueur1, &pos2); // Et arrive
    if((pos1.ligne != NB_LIGNES) && (pos1.colonne != NB_COLONNES)){//Toucher
      afficher_chem(ecran, joueur1.case_en_vie[depart1], pos1, 1, grille, affichage);
      obliterer_une_case(&grille, &pos1, &joueur1, &joueur2); //Enleve la case du bateau touché dans la liste du joueur1 et joueur2
    }
    if(affichage == 1){
      afficher_grille_SDL(&grille, ecran, 0);
      SDL_Delay(750);
    }
    if((pos2.ligne != NB_LIGNES) && (pos2.colonne != NB_COLONNES)){//Toucher
      afficher_chem(ecran, joueur2.case_en_vie[depart2], pos2, 2, grille, affichage);
       obliterer_une_case(&grille, &pos2, &joueur1, &joueur2);//Enleve la case du bateau touché dans la liste du joueur1 et joueur2
    }
    nb_coup ++;//On incremente le nombre de tour
    afficher(&grille, ecran, 1, affichage);
  }
  if((un_bateau_toujours_en_vie(&grille, &joueur1)) && (un_bateau_toujours_en_vie(&grille, &joueur2))){
    return(0);
  }
  if(un_bateau_toujours_en_vie(&grille, &joueur1)){
    return(1);
  }
  if(un_bateau_toujours_en_vie(&grille, &joueur2)){
    return(2);
  }
  return(0);
}
