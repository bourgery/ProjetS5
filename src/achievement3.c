#include "achievement3.h"

//Initialise la structure monstre
void init_monstre(struct Monstre *monstre){
  monstre->pos = position_aleatoire();
  monstre->agresse = 0;
  for(int i = 0; i < NB_JOUEURS; i++)
    monstre->tab_joueur_agresse[i] = 0;
}

//Place un monstre dans la grille
void placer_monstre(struct Monstre *monstre, struct Grille *grille){
  grille->tab[position_to_grille(&monstre->pos)].tab[3] = 1;
}

//Cas où le monstre oblitere une ou des cases
int monstre_oblitere(struct Grille *grille, struct Monstre *monstre, struct Joueur *j1, struct Joueur *j2){
  int nb_case_oblitere = 0;
  struct Position pos = monstre->pos;
  for(int i = 1; i <= NB_JOUEURS; i++){//Sous lui
    if((grille->tab[position_to_grille(&pos)].tab[i] == 1) && (grille->tab[position_to_grille(&pos)].tab[0] == 0)){
      nb_case_oblitere ++;
      obliterer_une_case(grille, &pos, j1, j2);
    }
  }
  pos.ligne ++;
  if((monstre->pos.ligne + 1) <= NB_LIGNES){ //En dessous
    for(int i = 1; i <= NB_JOUEURS; i++){//En dessous
      if((grille->tab[position_to_grille(&pos)].tab[i] == 1) && (grille->tab[position_to_grille(&pos)].tab[0] == 0)){
	nb_case_oblitere ++;
	obliterer_une_case(grille, &pos, j1, j2);
      }
    }
  }
  pos.ligne -= 2;
  if((monstre->pos.ligne - 1) >= 0){ //Au dessus
    for(int i = 1; i <= NB_JOUEURS; i++){//Au dessus
      if((grille->tab[position_to_grille(&pos)].tab[i] == 1) && (grille->tab[position_to_grille(&pos)].tab[0] == 0)){
	nb_case_oblitere ++;
	obliterer_une_case(grille, &pos, j1, j2);
      }
    }
  }
  pos.ligne ++;
  pos.colonne ++;
  if((monstre->pos.colonne % NB_COLONNES) != (NB_COLONNES - 1)){//A droite
    for(int i = 1; i <= NB_JOUEURS; i++){
      if((grille->tab[position_to_grille(&pos)].tab[i] == 1) && (grille->tab[position_to_grille(&pos)].tab[0] == 0)){
      nb_case_oblitere ++;
      obliterer_une_case(grille, &pos, j1, j2);
      }
    }
  }
  pos.colonne -= 2;
  if((monstre->pos.colonne % NB_COLONNES) > 0){//A gauche
    for(int i = 1; i <= NB_JOUEURS; i++){
      if((grille->tab[position_to_grille(&pos)].tab[i] == 1) && (grille->tab[position_to_grille(&pos)].tab[0] == 0)){
	nb_case_oblitere ++;
	obliterer_une_case(grille, &pos, j1, j2);
      }
    }
  }
  return(nb_case_oblitere);
}

//Donne les positions les plus proches du monstre
void case_plus_proche_monstre(struct Joueur *j, struct Monstre *monstre, struct Position tab[], int *distance, int *nombre_case){
  for(int i = 0; i < j->taille; i++){
    if((distance_minimale(&monstre->pos, &j->case_en_vie[i]) < *distance)){//Distance inférieur on ajoute la position
      *distance = distance_minimale(&monstre->pos, &j->case_en_vie[i]);
      *nombre_case = 0;//On remet à 0 le nombre de case
      tab[*nombre_case] = j->case_en_vie[i];
      *nombre_case = *nombre_case + 1;
    }
    if(distance_minimale(&monstre->pos, &j->case_en_vie[i]) == *distance){//Si c'est la même distance qu'avant on ajoute la position
      tab[*nombre_case] = j->case_en_vie[i];
      *nombre_case = *nombre_case + 1;//On incremente le nombre de case
    }
  }
}

//Deplace le monstre lorsqu'il n'est pas agresse
void deplacement_monstre_pas_agresse(struct Joueur *j1, struct Joueur *j2, struct Monstre *monstre, struct Grille *grille){
  struct Position pos_direction;
  struct Position tab[j1->taille + j2->taille];
  int nombre = 0;
  int distance = NB_LIGNES * NB_COLONNES;
  case_plus_proche_monstre(j1, monstre, tab, &distance, &nombre);//On cherche les cases du joueur1
  case_plus_proche_monstre(j2, monstre, tab, &distance, &nombre);//On cherche les cases du joueur2
  if(nombre != 0){//Si des cases sont possible
    pos_direction = tab[rand() % nombre];
    grille->tab[position_to_grille(&monstre->pos)].tab[3] = 0;//On enleve le monstre de la grille
    if(abs(pos_direction.ligne - monstre->pos.ligne) - abs(pos_direction.colonne - monstre->pos.colonne) < 0){
      if((pos_direction.colonne - monstre->pos.colonne) > 0)
	monstre->pos.colonne ++;
    else
      monstre->pos.colonne --;
    }
    else{
      if((pos_direction.ligne - monstre->pos.ligne) > 0)
	monstre->pos.ligne ++;
      else
	monstre->pos.ligne --;
    }
  }
}

//Renvoi l'indice du bateau le plus proche du joueur
int bateau_le_plus_proche(struct Monstre *monstre,  struct Joueur *j){
  int nombre = 0;
  int distance = NB_LIGNES * NB_COLONNES;
  struct Position pos;
  struct Position tab[2 * j->taille];
  case_plus_proche_monstre(j, monstre, tab, &distance, &nombre);
  if(nombre == 0)//Si aucun bateau possible
    return(-1);
  pos = tab[rand() % nombre];
  for(int i = 0; i < NB_BATALS; i++){
    if(indice_pos_dans_tab(&pos, j->tab[i].tab, j->tab[i].taille) != -1)
      return(i);
  }
  return(-1);
}

//Si une position est dans un tableau
int position_dans_tab(struct Position tab[], struct Position *pos, int taille){
  for(int i = 0; i < taille; i++){
    if((tab[i].ligne == pos->ligne) && (tab[i].colonne == pos->colonne))
      return(1);
  }
  return(0);
}

//Si une position est dans un tableau et que le monstre peut s'y déplacer
int position_dans_tab_et_possible(struct Position tab[], struct Position *pos, int taille, struct Batal *bat, struct Grille *grille){
  if((pos->ligne < 0) || (pos->ligne >= NB_LIGNES) || (pos->colonne < 0) || (pos->colonne >= NB_COLONNES)){
    return(0);
  }
  if(position_dans_tab(bat->tab, pos, taille) && ((grille->tab[position_to_grille(pos)].tab[bat->joueur] == 1) && (grille->tab[position_to_grille(pos)].tab[0] == 0))){
    return(0);
  }
  return(!position_dans_tab(tab, pos, taille));
}

//Renvoie une position aléatoire parmis toute les cases possible autour d'un bateau
struct Position case_autour_du_batal(struct Batal *bat, struct Grille *grille){
  struct Position tab[bat->taille * 4];
  int nombre = 0;
  struct Position pos;
  for(int i = 0; i < bat->taille; i++){//On parcourt toutes les cases du bateau et on regarde si on peut aller à gauche, droite, dessous, dessus
    pos = bat->tab[i];
    if((grille->tab[position_to_grille(&pos)].tab[0] != -1) && (grille->tab[position_to_grille(&pos)].tab[bat->joueur] != 0)){//Si la case du bateau n'est pas oblitérée
      pos.ligne ++;
      if(position_dans_tab_et_possible(tab, &pos, nombre, bat, grille)){
	tab[nombre] = pos;
	nombre ++;
      }
      pos.ligne -= 2;
      if(position_dans_tab_et_possible(tab, &pos, nombre, bat, grille)){
	tab[nombre] = pos;
	nombre ++;
      }
      pos.ligne ++;
      pos.colonne ++;
      if(position_dans_tab_et_possible(tab, &pos, nombre, bat, grille)){
	tab[nombre] = pos;
	nombre ++;
      }
      pos.colonne -=2;
      if(position_dans_tab_et_possible(tab, &pos, nombre, bat, grille)){
	tab[nombre] = pos;
	nombre ++;
      }
    }
  }
  return(tab[rand() % nombre]);//On en retourne une aléatoirement
}


//Deplace le monstre lorsqu'il est agresse
void deplacement_monstre_agresse(struct Grille *grille, struct Monstre *monstre, struct Joueur *j1, struct Joueur *j2, SDL_Surface *ecran, int affichage){
  int choix_bat;
  int joueur;
  struct Position pos = monstre->pos;
  if((monstre->tab_joueur_agresse[0] == 1) && (monstre->tab_joueur_agresse[1] == 1)){//Si les deux joueurs l'ont agressé on en choisit un aléatoirement
    int a = rand() % 2;
    if(a == 0){
      choix_bat = bateau_le_plus_proche(monstre, j1);
      joueur = 1;
    }
    else{
      choix_bat = bateau_le_plus_proche(monstre, j2);
      joueur = 2;
    }
  }
  else if(monstre->tab_joueur_agresse[0] == 1){
    choix_bat = bateau_le_plus_proche(monstre, j1);
    joueur = 1;
  }
  else{
    choix_bat = bateau_le_plus_proche(monstre, j2);
    joueur = 2;
  }
  if(choix_bat != -1){//Si un choix est possible
    if(joueur == 1){
      grille->tab[position_to_grille(&monstre->pos)].tab[3] = 0;
      monstre->pos = case_autour_du_batal(&j1->tab[choix_bat], grille);
    }
    else{
      grille->tab[position_to_grille(&monstre->pos)].tab[3] = 0;
      monstre->pos = case_autour_du_batal(&j2->tab[choix_bat], grille);
    }
  }
  if(affichage == 1)
    chemin_monstre_SDL(pos, monstre->pos, ecran);
  monstre->agresse = 0;
  monstre->tab_joueur_agresse[0] = 0;
  monstre->tab_joueur_agresse[1] = 0;
}

//affiche le chemin du monstre en SDL
void chemin_monstre_SDL(struct Position pos_depart, struct Position pos_arrive, SDL_Surface *ecran){
  SDL_Surface *monstre = IMG_Load("src/godzilla.gif");
  SDL_Rect pos;
  pos.x = pos_depart.colonne * NB_PIXEL_CASE;
  pos.y = pos_depart.ligne * NB_PIXEL_CASE;
   if(pos_depart.ligne > pos_arrive.ligne){
      while(pos_depart.ligne != pos_arrive.ligne){
	pos_depart.ligne -= 1;
	pos.y -= NB_PIXEL_CASE;
	SDL_BlitSurface(monstre, NULL, ecran, &pos);
	SDL_Flip(ecran);
	SDL_Delay(150);
      }
    }
    if(pos_depart.ligne < pos_arrive.ligne){
      while(pos_depart.ligne != pos_arrive.ligne){
	pos_depart.ligne += 1;
	pos.y +=  NB_PIXEL_CASE;
	SDL_BlitSurface(monstre, NULL, ecran, &pos);
	SDL_Flip(ecran);
	SDL_Delay(150);
      }
    }
    if(pos_depart.colonne > pos_arrive.colonne){
      while(pos_depart.colonne != pos_arrive.colonne){
	pos_depart.colonne -= 1;
	pos.x -= NB_PIXEL_CASE; 
	SDL_BlitSurface(monstre, NULL, ecran, &pos);
	SDL_Flip(ecran);
	SDL_Delay(150);
      } 
    }
    if(pos_depart.colonne < pos_arrive.colonne){
      while(pos_depart.colonne != pos_arrive.colonne){
	pos_depart.colonne += 1;
	pos.x += NB_PIXEL_CASE; 
	SDL_BlitSurface(monstre, NULL, ecran, &pos);
	SDL_Flip(ecran); 
	SDL_Delay(150);
      }
    }
}

//Fonction qui permet de réaliser le tour du monstre
void monstre_qui_joue(struct Monstre *monstre, struct Grille *grille, struct Joueur *joueur1, struct Joueur *joueur2, SDL_Surface *ecran, int affichage){
  if(monstre->agresse)
    deplacement_monstre_agresse(grille, monstre, joueur1, joueur2, ecran, affichage);
  placer_monstre(monstre, grille);//On place le monstre sur la grille
  if(monstre_oblitere(grille, monstre, joueur1, joueur2))//Si aucune case n'est oblitérée on ne rentre pas dans le if car la fonction renvoit 0 donc on fait le else
    ;
  else
    deplacement_monstre_pas_agresse(joueur1, joueur2, monstre, grille);
  placer_monstre(monstre, grille);//On place le monstre sur la grille
}

int achievement3(SDL_Surface *ecran, int affichage){
  init_rand();
  int nb_coup = 0;
  int depart1 = 0;
  int depart2 = 0;
  int distance1 = 0;
  int distance2 = 0;
  struct Grille grille;
  struct Position pos1;
  struct Position pos2;
  init_grille(&grille);
  struct Joueur joueur1;
  struct Joueur joueur2;
  struct Monstre godzilla;
  init_joueur(&joueur1, 1);
  init_joueur(&joueur2, 2);
  placer_batal_joueur(&joueur1, &grille);
  placer_batal_joueur(&joueur2, &grille);
  init_monstre(&godzilla);
  placer_monstre(&godzilla, &grille);
  afficher(&grille, ecran, 1, affichage);
  while((joueur1.taille > 0) && (joueur2.taille > 0) && (nb_coup < NB_COUP_MAX)){
    bouger_bateau(&grille, &joueur1, ecran, affichage); //On bouge le bateau du joueur1
    if(affichage == 1)
      SDL_Delay(500);
    bouger_bateau(&grille, &joueur2, ecran, affichage); //On bouge le bateau du joueur2
    if(affichage == 1)
      SDL_Delay(500);
    depart1 = depart_torpille(&joueur1); //On cherche le premier depart
    distance1 = arrive_torpille(&(joueur1.case_en_vie[depart1]), &joueur2, &pos1); //Et arrive
    depart2 = depart_torpille(&joueur2); //On cherche le deuxieme depart
    distance2 = arrive_torpille(&(joueur2.case_en_vie[depart2]), &joueur1, &pos2); // Et arrive
    if(distance1 >= distance_minimale(&godzilla.pos, &(joueur1.case_en_vie[depart1]))){ // Si le monstre est plus pres
      afficher_chem(ecran, joueur1.case_en_vie[depart1], godzilla.pos, 1, grille, affichage);
      obliterer_une_case(&grille, &godzilla.pos, &joueur1, &joueur2);//On oblitère cette case
      if(affichage == 1)
	afficher_grille_SDL(&grille, ecran, 0);
      godzilla.agresse = 1;
      godzilla.tab_joueur_agresse[0] = 1;
    }
    else
      if((pos1.ligne != NB_LIGNES) && (pos1.colonne != NB_COLONNES)){//Toucher
	afficher_chem(ecran, joueur1.case_en_vie[depart1], pos1, 1, grille, affichage);
	obliterer_une_case(&grille, &pos1, &joueur1, &joueur2);//Enleve la case du bateau touché dans la liste du joueur1 et joueur2
      }
    if(affichage == 1)
      SDL_Delay(750);
    if(distance2 >= distance_minimale(&godzilla.pos, &(joueur2.case_en_vie[depart2]))){// Si le monstre est plus pres
      afficher_chem(ecran, joueur2.case_en_vie[depart2], godzilla.pos, 2, grille, affichage);
      obliterer_une_case(&grille, &godzilla.pos, &joueur1, &joueur2);//On oblitère cette case
      if(affichage == 1)
	afficher_grille_SDL(&grille, ecran, 0);
      godzilla.agresse = 1;
      godzilla.tab_joueur_agresse[1] = 1;
    }
    else
      if((pos2.ligne != NB_LIGNES) && (pos2.colonne != NB_COLONNES)){//Toucher
	afficher_chem(ecran, joueur2.case_en_vie[depart2], pos2, 2, grille, affichage);
	obliterer_une_case(&grille, &pos2, &joueur1, &joueur2);//Enleve la case du bateau touché dans la liste du joueur1 et joueur2
      }
    monstre_qui_joue(&godzilla, &grille, &joueur1, &joueur2, ecran, affichage);//On fait jouer le monstre
    nb_coup ++;
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

