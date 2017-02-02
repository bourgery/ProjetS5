#include "achievement2.h"

//Initialise un tableau d'entier à 0
void init_tab_entier(int tab[], int taille){
  for(int i = 0; i < taille; i ++)
    tab[i] = 0;
}

//Permet de choisir le bateau qui va se deplacer
int choix_du_bateau(struct Grille *grille, struct Joueur *joueur){
  int n;
  do{
    n = rand() % NB_BATALS;
  }while(batal_en_jeu(&joueur->tab[n], grille) == 0);//Tant qu'on a pas un bateau qui n'est pas en vie
  return(n);
}

//Verifie si le bateau peut être la ou sont ses positions changer en tenant compte des cases obliterees du bateau ou non
int verif_arrive_bateau(struct Grille grille, struct Batal bat, int liste_indice_oblitere[]){
  for(int i = 0; i < bat.taille; i++){
    if(bat.tab[i].ligne < 0 || bat.tab[i].colonne < 0 || bat.tab[i].ligne >= NB_LIGNES || bat.tab[i].colonne >= NB_COLONNES)
      return(0);
    if(liste_indice_oblitere[i]){
      if((grille.tab[position_to_grille(&bat.tab[i])].tab[0] == -1) || (grille.tab[position_to_grille(&bat.tab[i])].tab[0] == -2) || (grille.tab[position_to_grille(&bat.tab[i])].tab[1] == 1) || (grille.tab[position_to_grille(&bat.tab[i])].tab[2] == 1)){
	return(0);
      }
    }
  }
  return(1);
}

//Fonction non récursive qui va appeler la fonction récursive pour déplacer le bateau 
void liste_case_possibles(struct Grille grille, struct Batal bat, int tab[], int liste_indice_oblitere[], int tab_prec[]){
  int indice;
  for(int i = 0; i < bat.taille; i++){ // On regarde s'il y a des positions oblitere
    if((grille.tab[position_to_grille(&bat.tab[i])].tab[0] == -1) || (grille.tab[position_to_grille(&bat.tab[i])].tab[bat.joueur] == 0))
      liste_indice_oblitere[i] = 0;
    else
      liste_indice_oblitere[i] = 1;
    grille.tab[position_to_grille(&bat.tab[i])].tab[bat.joueur] = 0; //On enleve le bateau de la grille
  }
  indice = position_to_grille(&bat.tab[0]);
  if((indice % NB_COLONNES) < (NB_COLONNES - 1)){//On verifie qu'on ne passe pas à la ligne du dessous
    if(indice + 1 < 100)//On verifie qu'on ne sort pas de la grille
      tab_prec[indice + 1] = indice;
    liste_case_possiblesrec(grille, bat, tab, indice + 1, liste_indice_oblitere, tab_prec);
  }
  if((indice % NB_COLONNES) > 0){//On verifie qu'on ne passe pas à la ligne du dessus
    if(indice - 1 >= 0)//On verifie qu'on ne sort pas de la grille
    tab_prec[indice - 1] = indice;
    liste_case_possiblesrec(grille, bat, tab, indice - 1, liste_indice_oblitere, tab_prec);
  }
  if(indice + NB_COLONNES < 100)//On verifie qu'on ne sort pas de la grille
    tab_prec[indice + NB_COLONNES] = indice;
  liste_case_possiblesrec(grille, bat, tab, indice + NB_COLONNES, liste_indice_oblitere, tab_prec);
  if(indice - NB_COLONNES >= 0)//On verifie qu'on ne sort pas de la grille
    tab_prec[indice - NB_COLONNES] = indice;
  liste_case_possiblesrec(grille, bat, tab, indice - NB_COLONNES, liste_indice_oblitere, tab_prec);
}

//Fonction recursive pour chercher les positions possibles d'un bateau
void liste_case_possiblesrec(struct Grille grille, struct Batal bateau, int tab[], int indice, int liste_indice_oblitere[], int tab_prec[]){
  struct Position pos;
  if((indice < NB_LIGNES * NB_COLONNES) && (indice >= 0) && (tab[indice] == 0)){ //Si on a pas deja explore la case et que la case ne depasse pas de la grille
    pos = grille_to_position(indice);
    init_batal(&bateau, bateau.taille, &pos, bateau.alignement, bateau.joueur);
    if(verif_arrive_bateau(grille, bateau, liste_indice_oblitere) == 0){
      tab[indice] = -1;
    }
    else{
      tab[indice] = 1;
      if((indice % NB_COLONNES) < (NB_COLONNES - 1)){//On verifie qu'on ne passe pas à la ligne du dessous
	if(indice + 1 < 100 && tab_prec[indice + 1] == -1)//On verifie qu'on ne sort pas de la grille et qu'on a pas déjà une façon d'y arriver
	  tab_prec[indice + 1] = indice;
	liste_case_possiblesrec(grille, bateau, tab, indice + 1, liste_indice_oblitere, tab_prec); //droite
      }
      if((indice % NB_COLONNES) > 0){//On verifie qu'on ne passe pas à la ligne du dessus
	if(indice - 1 >=0 && tab_prec[indice - 1] == -1)//On verifie qu'on ne sort pas de la grille et qu'on a pas déjà une façon d'y arriver
	  tab_prec[indice - 1] = indice;
	liste_case_possiblesrec(grille, bateau, tab, indice - 1, liste_indice_oblitere, tab_prec); //gauche
      }
      if(indice + NB_COLONNES < 100 && tab_prec[indice + NB_COLONNES] == -1)//On verifie qu'on ne sort pas de la grille et qu'on a pas déjà une façon d'y arriver
	tab_prec[indice + NB_COLONNES] = indice;
      liste_case_possiblesrec(grille, bateau, tab, indice + NB_COLONNES, liste_indice_oblitere, tab_prec);//bas
      if((indice - NB_COLONNES >=0) && tab_prec[indice - NB_COLONNES] == -1)//On verifie qu'on ne sort pas de la grille et qu'on a pas déjà une façon d'y arriver
	tab_prec[indice - NB_COLONNES] = indice;
      liste_case_possiblesrec(grille, bateau, tab, indice - NB_COLONNES, liste_indice_oblitere, tab_prec);//haut
    }
  }
}

//On garde que les positions possibles
int deplacement_possible_uniquement(int tab_pas_tous[], int tab_tous[]){
  int nombre = 0;
  for(int i = 0; i < NB_LIGNES * NB_COLONNES; i++){
    if(tab_pas_tous[i] == 1){
      tab_tous[nombre] = i;
      nombre ++;
    }
  }
  return(nombre);
}

//Fonction qui renvoit l'indice d'une position dans un tableau
int indice_pos_dans_tab(struct Position *pos, struct Position tab[], int taille){
  for(int i = 0; i < taille; i ++){
    if((tab[i].ligne == pos->ligne) && (tab[i].colonne == pos->colonne))
      return(i);
  }
  return(-1);
}

//Met à jour le bateau
void mise_a_jour_batal(struct Batal *bat, struct Position *nouvelle){
  init_batal(bat, bat->taille, nouvelle, bat->alignement, bat->joueur);
}

//Met à jour la structure joueur, c'est à dire ses cases en vie
void mise_a_jour_liste(struct Batal bat, struct Joueur *joueur, struct Position *nouvelle){
  int tab[bat.taille];
  for(int i = 0; i < bat.taille; i++){
      tab[i] = indice_pos_dans_tab(&bat.tab[i], joueur->case_en_vie, joueur->taille);
  }
  mise_a_jour_batal(&bat, nouvelle);//On met à jour le bateau pour pouvoir changer les cases en vie
  for(int i = 0; i < bat.taille; i++){
    if(tab[i] >= 0)
      joueur->case_en_vie[tab[i]] = bat.tab[i];
  }
}

//Met à jour la grille ainsi que le bateau
void mise_a_jour_structure(struct Grille *grille, struct Batal *bat, int liste_indice_oblitere[], struct Position *nouvelle){
  for(int i = 0; i < bat->taille; i++){
    grille->tab[position_to_grille(&bat->tab[i])].tab[bat->joueur] = 0;
  }
  mise_a_jour_batal(bat, nouvelle);//On met à jour le bateau pour pouvoir remettre les positions dans la grille et pour que le bateau soit pour de bon mis à jour
  for(int i = 0; i < bat->taille; i++){
    if(liste_indice_oblitere[i]) 
      grille->tab[position_to_grille(&bat->tab[i])].tab[bat->joueur] = 1;
  }
}

//Fonction permettant de bouger le bateau
void bouger_bateau(struct Grille *grille, struct Joueur *joueur, SDL_Surface *ecran, int affichage){
  int tab_deplacement_possible_ou_non[NB_LIGNES * NB_COLONNES]; //tableau contenant la possibilité pour un bateau d'aller à une case ou non
  int tab_deplacement_possible[NB_LIGNES * NB_COLONNES]; //tableau permettant de récuperer tout les deplacements
  int choix_bateau;
  int nombre_case_possible;
  int liste_indice_oblitere[TAILLE_MAX_BAT];
  int tab_prec[NB_LIGNES * NB_COLONNES];//Tableau pour le chemin
  struct Position nouvelle_pos;
  init_tab_entier(tab_deplacement_possible_ou_non, NB_LIGNES * NB_COLONNES);
  init_tab_entier(tab_deplacement_possible, NB_LIGNES * NB_COLONNES);
  init_tab_entier(tab_prec, NB_LIGNES * NB_COLONNES);
  for(int i = 0; i < 100; i++)//On initialise le tableau pour le chemin
    tab_prec[i] = -1;
  choix_bateau = choix_du_bateau(grille, joueur);
  liste_case_possibles(*grille, joueur->tab[choix_bateau], tab_deplacement_possible_ou_non, liste_indice_oblitere, tab_prec);
  nombre_case_possible = deplacement_possible_uniquement(tab_deplacement_possible_ou_non, tab_deplacement_possible);
  if(nombre_case_possible){//S'il y a une case pour que le bateau puisse bouger
    nouvelle_pos = grille_to_position(tab_deplacement_possible[rand() % nombre_case_possible]);
    if(affichage == 1)
      afficher_mvt_bateau_SDL(tab_prec, ecran, joueur->tab[choix_bateau], nouvelle_pos, *grille, liste_indice_oblitere); 
    mise_a_jour_liste(joueur->tab[choix_bateau], joueur, &nouvelle_pos);
    mise_a_jour_structure(grille, &joueur->tab[choix_bateau], liste_indice_oblitere, &nouvelle_pos); 
  }
}

//Inverse les éléments d'un tableau
void inverser_tabpos(struct Position tab[], int taille){
  int n = taille / 2;
  struct Position pos;
  for(int i = 0; i < n; i++){
    pos = tab[i];
    tab[i] = tab[taille - i];
    tab[taille - i] = pos;
  }
}

//Affiche le mouvement d'un bateau en SDL
void afficher_mvt_bateau_SDL(int tab_prec[], SDL_Surface *ecran, struct Batal bat, struct Position pos_arrive, struct Grille grille, int liste_indice_oblitere[]){
  struct Position tab[100];
  int nombre = 1;
  tab[0] = pos_arrive;
  while(tab[nombre - 1].ligne != bat.tab[0].ligne && tab[nombre - 1].colonne != bat.tab[0].colonne){
    tab[nombre] = grille_to_position(tab_prec[position_to_grille(&tab[nombre - 1])]);
    nombre ++;
  }
  inverser_tabpos(tab, nombre);
  for(int i = 1; i < nombre; i++){
    mise_a_jour_structure(&grille, &bat, liste_indice_oblitere, &tab[i]);
    afficher_grille_SDL(&grille, ecran, 0);
    SDL_Delay(150);
  }
  afficher_grille_SDL(&grille, ecran, 0);
}

int achievement2(SDL_Surface *ecran, int affichage){
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
    bouger_bateau(&grille, &joueur1, ecran, affichage); //On bouge le bateau du joueur1
    if(affichage == 1)
      SDL_Delay(500);
    bouger_bateau(&grille, &joueur2, ecran, affichage); //On bouge le bateau du joueur2
    if(affichage == 1)
      SDL_Delay(500);
    depart1 = depart_torpille(&joueur1); //On cherche le premier depart
    arrive_torpille(&(joueur1.case_en_vie[depart1]), &joueur2, &pos1); //Et arrive
    depart2 = depart_torpille(&joueur2); //On cherche le deuxieme depart
    arrive_torpille(&(joueur2.case_en_vie[depart2]), &joueur1, &pos2); // Et arrive
    if((pos1.ligne != NB_LIGNES) && (pos1.colonne != NB_COLONNES)){//Toucher
      afficher_chem(ecran, joueur1.case_en_vie[depart1], pos1, 1, grille, affichage);
      obliterer_une_case(&grille, &pos1, &joueur1, &joueur2); //Enleve la case du bateau touché dans la liste du joueur1 et joueur2
    }
    if(affichage == 1)
      SDL_Delay(750);
    if((pos2.ligne != NB_LIGNES) && (pos2.colonne != NB_COLONNES)){ //Toucher
      afficher_chem(ecran, joueur2.case_en_vie[depart2], pos2, 2, grille, affichage);
      obliterer_une_case(&grille, &pos2, &joueur2, &joueur1);//Enleve la case du bateau touché dans la liste du joueur1 et joueur2
    }
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
