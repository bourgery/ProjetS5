#include "achievement0.h"

//Tableau des tailles des différents bateaux
int TAB_TAILLES1[NB_BATALS]={TAB_TAILLE};


//Création d'un tableau de position pour obtenir des positions aléatoires plus tard
struct Position TAB_POSITION[NB_LIGNES * NB_COLONNES];

//Fonction mettant en pause la SDL
void pause(){
  SDL_Event event;
  int continuer = 1;
  while(continuer){
    SDL_WaitEvent(&event);
    switch(event.type){
    case(SDL_QUIT):
      continuer = 0;
      break;
    case(SDL_KEYDOWN):
      switch(event.key.keysym.sym){
      case(SDLK_ESCAPE):
	continuer = 0;
	break;
      default:
	break;
      }
      break;
    }
  }
}

//Fonction permettant d'initialiser le rand pour éviter d'avoir toujours la même suite de valeur
void init_rand(){
  srand(time(NULL));
}

//Fonction permettant d'initialiser notre tableau de position créer précédemment
void init_tab(){
  for(int i = 0; i < NB_LIGNES; i++){
    for(int j = 0; j < NB_COLONNES; j++){
      struct Position pos = {i, j};
      TAB_POSITION[i * NB_COLONNES + j] = pos;
    }
  }
}

//Fonction permettant d'échanger deux éléments d'un tableau utile pour notre tableau de position
void echange_element_tab(int indice1, int indice2){
  struct Position pos = TAB_POSITION[indice1];
  TAB_POSITION[indice1] = TAB_POSITION[indice2];
  TAB_POSITION[indice2] = pos;
}

//Fonction permettant de mélanger les cases du tableau de position
void melange_tab(){
  for(int i = 0; i < NB_LIGNES * NB_COLONNES; i++){
    echange_element_tab(rand() % (NB_LIGNES * NB_COLONNES), rand() % (NB_LIGNES * NB_COLONNES));
  }
}
  
//Fonction  permettant de passer d'un index du tableau à une position
struct Position grille_to_position(int index){
  struct Position position = { index / NB_COLONNES, index % NB_COLONNES};
  return position;
}

//Fonction permettant d'initialiser notre grille avec des 0 partout signifiant qu'aucun bateau n'est placé
void init_grille(struct Grille *grille){
  for(int i = 0; i < NB_LIGNES * NB_COLONNES; i++){
    for(int j = 0; j <= NB_JOUEURS + NB_MONSTRES; j++){
      grille->tab[i].tab[j] = 0;
    }
  }
}

//Pour l'alignement en rond, la position initiale est celle du coin haut gauche
//On initialise le tableau dans le sens horaire
//On utilise la fonction suivante:
void init_rond(struct Batal *bateau, struct Position *posinit){
  int ligne= posinit->ligne;
  int colonne= posinit->colonne;
  bateau->tab[0] = *posinit;
  struct Position pos1 = {ligne,colonne + 1};
  bateau->tab[1] = pos1;
  struct Position pos2 = {ligne,colonne + 2};
  bateau->tab[2] = pos2;
  struct Position pos3 = {ligne + 1,colonne + 2};
  bateau->tab[3] = pos3;
  struct Position pos4 = {ligne + 2,colonne + 2};
  bateau->tab[4] = pos4;
  struct Position pos5 = {ligne + 2, colonne + 1};
  bateau->tab[5] = pos5;
  struct Position pos6 = {ligne + 2, colonne};
  bateau->tab[6] = pos6;
  struct Position pos7 = {ligne + 1, colonne};
  bateau->tab[7] = pos7;
}

//Pour l'alignement en H, la position du coin haut gauche du H est la position initiale
//Puis les cases du tableau sont initialisées de haut en bas puis de gauche à droite
void init_H(struct Batal *bateau, struct Position *posinit, int alignement){
  int ligne= posinit->ligne;
  int colonne= posinit->colonne;
  bateau->tab[0]= *posinit;
  if(alignement == 31){
   struct Position pos1 = {ligne + 1,colonne};
   bateau->tab[1] = pos1;
   struct Position pos2 = {ligne + 2,colonne};
   bateau->tab[2] = pos2;
   struct Position pos3 = {ligne + 1,colonne + 1};
   bateau->tab[3] = pos3;
   struct Position pos4 = {ligne,colonne + 2};
   bateau->tab[4] = pos4;
   struct Position pos5 = {ligne + 1, colonne + 2};
   bateau->tab[5] = pos5;
   struct Position pos6 = {ligne + 2, colonne + 2};
   bateau->tab[6] = pos6;
  }
  if(alignement == 32){
    struct Position pos1 = {ligne - 2,colonne};
    bateau->tab[1] = pos1;
    struct Position pos2 = {ligne,colonne + 1};
    bateau->tab[2] = pos2;
    struct Position pos3 = {ligne - 1,colonne + 1};
    bateau->tab[3] = pos3;
    struct Position pos4 = {ligne - 2,colonne + 1};
    bateau->tab[4] = pos4;
    struct Position pos5 = {ligne, colonne + 2};
    bateau->tab[5] = pos5;
    struct Position pos6 = {ligne - 2, colonne + 2};
    bateau->tab[6] = pos6;
  }
}

//La case initiale est toujours la petite case seule
//Puis on initialise le tableau en partant de cette case initiale vers la case contingente suivante
void init_L(struct Batal *bateau, struct Position *posinit, int alignement){
  int ligne= posinit->ligne;
  int colonne= posinit->colonne;
  bateau->tab[0]= *posinit;
  if(alignement == 41){
    struct Position pos1 = {ligne,colonne - 1};
    bateau->tab[1] = pos1;
    struct Position pos2 = {ligne - 1,colonne - 1};
    bateau->tab[2] = pos2;
    struct Position pos3 = {ligne - 2,colonne - 1};
    bateau->tab[3] = pos3;
  }
  if(alignement == 42){
    struct Position pos1 = {ligne,colonne + 1};
    bateau->tab[1] = pos1;
    struct Position pos2 = {ligne - 1,colonne + 1};
    bateau->tab[2] = pos2;
    struct Position pos3 = {ligne - 2,colonne + 1};
    bateau->tab[3] = pos3;
  }
  if(alignement == 43){
    struct Position pos1 = {ligne,colonne - 1};
    bateau->tab[1] = pos1;
    struct Position pos2 = {ligne + 1,colonne - 1};
    bateau->tab[2] = pos2;
    struct Position pos3 = {ligne + 2,colonne - 1};
    bateau->tab[3] = pos3;
  }
  if(alignement == 44){
    struct Position pos1 = {ligne,colonne + 1};
    bateau->tab[1] = pos1;
    struct Position pos2 = {ligne + 1,colonne + 1};
    bateau->tab[2] = pos2;
    struct Position pos3 = {ligne + 2,colonne + 1};
    bateau->tab[3] = pos3;
  }
  if(alignement == 45){
    struct Position pos1 = {ligne + 1,colonne};
    bateau->tab[1] = pos1;
    struct Position pos2 = {ligne + 1,colonne - 1};
    bateau->tab[2] = pos2;
    struct Position pos3 = {ligne + 1,colonne - 2};
    bateau->tab[3] = pos3;
  }
  if(alignement == 46){
    struct Position pos1 = {ligne - 1,colonne};
    bateau->tab[1] = pos1;
    struct Position pos2 = {ligne - 1,colonne - 1};
    bateau->tab[2] = pos2;
    struct Position pos3 = {ligne - 1,colonne -2};
    bateau->tab[3] = pos3;
  }
  if(alignement == 47){
    struct Position pos1 = {ligne + 1,colonne};
    bateau->tab[1] = pos1;
    struct Position pos2 = {ligne + 1,colonne + 1};
    bateau->tab[2] = pos2;
    struct Position pos3 = {ligne + 1,colonne + 2};
    bateau->tab[3] = pos3;
  }
  if(alignement == 48){
    struct Position pos1 = {ligne - 1,colonne};
    bateau->tab[1] = pos1;
    struct Position pos2 = {ligne - 1,colonne + 1};
    bateau->tab[2] = pos2;
    struct Position pos3 = {ligne - 1,colonne + 2};
    bateau->tab[3] = pos3;
  }
}
  
//Fonction permettant d'initisaliser un batal de la structure batal
void init_batal(struct Batal *bateau, int taille, struct Position *position, int alignement, int nbjoueur){
  bateau->taille = taille;
  if(alignement == 1){
    bateau->tab[0]= *position;
    for(int i = 0; i < taille; i++){ 
      bateau->tab[i].ligne=position->ligne ;
      bateau->tab[i].colonne=position->colonne + i;
    }
  }
  else if(alignement == 10){
    bateau->tab[0]= *position;
    for(int i = 0; i < taille; i++){ 
      bateau->tab[i].ligne=position->ligne + i ;
      bateau->tab[i].colonne=position->colonne;
    }
  }
  else if(alignement == 20){
    init_rond(bateau, position);
  }
  else if(alignement == 31 || alignement == 32){
    init_H(bateau, position, alignement);
  }
  else if(alignement > 40){
    init_L(bateau, position, alignement);    
  }
  else{
    bateau->tab[0] = *position;
  }
  bateau->alignement = alignement;
  bateau->joueur = nbjoueur;
}

//Fonction permettant d'initialiser un joueur avec des batals
void init_joueur(struct Joueur *joueur, int nbjoueur){
  joueur->joueur = nbjoueur;
  struct Position pos = {0, 0};
  joueur->taille = 0;
  for(int i = 0; i < NB_BATALS; i++){
    init_batal(&joueur->tab[i],TAB_TAILLES1[i], &pos, 0, nbjoueur);
    joueur->taille += TAB_TAILLES1[i];
  }
}

//Fonction permettant de donner des couleurs à la grille
void choix_couleur(int n){
  if(n == 1)//1 correspond à une occupation de la case par un batal du joueur 1
    couleur("34");
  else if(n == 2)//2 correspond à une occupation de la case par un batal du joueur 2
    couleur("33");
  else if(n == 3)//3 correspond à une occupation de la case par un batal du joueur 1 et un batal du joueur 2
    couleur("32");
 else if(n == -1)//-1 correspond à une case oblitérée
   couleur("31");
 else if(n == -2)//-2 correspond à un archipal
   couleur("35");
 else//0 correspond à une case ni oblitérée ni occupée
   couleur("0");
}

int valeur_a_afficher(struct Case *cases){
  int valeur = 0;
  if(cases->tab[0] == -2)
    return(-2);
  if(cases->tab[0] == -1)
    return(-1);
  valeur += cases->tab[1] + 2*cases->tab[2];
  return(valeur);
}

//Fonction permettant d'afficher la grille avec des couleurs
void afficher_grille(struct Grille *grille){
  int valeur;
  for (int i = 0; i < NB_COLONNES; i++){
    printf("\t%d",i);
  }
  printf("\n");
  for (int i = 0; i < NB_LIGNES; i++){
    printf("%d", i);
    for (int j = 0; j < NB_COLONNES; j++){
      valeur = valeur_a_afficher(&grille->tab[i * NB_COLONNES + j]);
      choix_couleur(valeur);
      if(grille->tab[i * NB_COLONNES + j].tab[0] > 0)//Si on a un portal
	printf("\t%d'", valeur);
      else if(grille->tab[i * NB_COLONNES + j].tab[3] == 1)//S'il y a godzilla
	printf("\t%d*", valeur);
      else if(grille->tab[i * NB_COLONNES + j].tab[0] > 0 && grille->tab[i * NB_COLONNES + j].tab[3] == 1)//Si on a un portal et godzilla
	printf("\t'%d*", valeur);
      else
	printf("\t%d", valeur);
      couleur("0");
    }
    printf("\n");
  }
  printf("\n");
} 

//Fonction permettant de passer d'une position de la structure position à un index du tableau de la grille
int position_to_grille(struct Position *position){
  return (NB_COLONNES * position->ligne + position->colonne);
}

//Fonction permettant d'avoir une position aléatoire 
struct Position position_aleatoire(){ 
  struct Position position = {rand() % NB_LIGNES, rand() % NB_COLONNES};
  return position;
}

//Fonction permettant d'obtenir un alignement aléatoire entre horizontal ou vertical
int alignement_aleatoire(int taille){
  if(taille == 4){
    int tab[10]={1,10,41,42,43,44,45,46,47,48};
    int nombre_aleatoire = rand() % 10;
    return(tab[nombre_aleatoire]);
  }
  else if(taille == 8){
    int tab[3]={1,10,20};
    int nombre_aleatoire = rand() % 3;
    return(tab[nombre_aleatoire]);
  }
  else if(taille == 7){
    int tab[4]={1,10,31,32};
    int nombre_aleatoire = rand() % 4;
    return(tab[nombre_aleatoire]);
  }
  else{
    int tab[2]={1,10};
    int nombre_aleatoire = rand() % 2;
    return(tab[nombre_aleatoire]);
  }
}
 
//Fonction permettant de savoir si un bateau est toujours en jeu ou non
int batal_en_jeu(struct Batal *bateau, struct Grille *grille){
  int s = 0;
  for(int i = 0; i < bateau->taille; i++){
    if((grille->tab[position_to_grille(&bateau->tab[i])].tab[0] != -1) && (grille->tab[position_to_grille(&bateau->tab[i])].tab[bateau->joueur] != 0)){
      s++;
    }
  }
  return(s);
}

//Fonction qui permet de connaitre la colonne la plus grande qu'utilise le bateau
int max_colonne_batal(struct Batal *bateau){
  int max = 0;
  for(int i = 0; i < bateau->taille; i++){
    if(max < bateau->tab[i].colonne){
      max=bateau->tab[i].colonne;
    }
  }
  return(max);
}
  
//Fonction permettant de vérifier qu'il y la place disponible pour mettre le batal sur la grille    
int verif_pour_mettre_bateau(struct Grille *grille, struct Batal *bateau){
  int index;
  if(max_colonne_batal(bateau) >= NB_COLONNES)
    return(0);
  for(int i = 0; i < bateau->taille; i++){
    if(bateau->tab[i].colonne < 0 || bateau->tab[i].colonne >= NB_COLONNES)
      return(0);
    index = position_to_grille(&bateau->tab[i]);
    if(index >= NB_LIGNES * NB_COLONNES || index < 0 || grille->tab[index].tab[bateau->joueur] == 1 || grille->tab[index].tab[0]==-2)
      return(0);
  }
  return(1);
}

//Fonction permettant de placer un batal sur la grille de jeu
void placer_batal(struct Grille *grille, struct Batal *bateau){
  int index;
  int alignement;
  struct Position posinit;
  do{
    posinit= position_aleatoire();
    alignement=alignement_aleatoire(bateau->taille);
    init_batal(bateau,bateau->taille,&posinit,alignement,bateau->joueur);
  } while(verif_pour_mettre_bateau(grille, bateau) == 0);
  for(int i = 0; i < bateau->taille; i ++){//On place le bateau dans la grille
    index = position_to_grille(&bateau->tab[i]);
    grille->tab[index].tab[bateau->joueur] = 1;
    
  }
}

//Fonction permettant d'oblitérer une case de la grille (mettre -1)
void obliterer_une_case(struct Grille *grille, struct Position *position,struct Joueur *joueur1, struct Joueur *joueur2){
  grille->tab[position_to_grille(position)].tab[0] = -1;//On oblitère la case
  for(int i = 0; i < joueur1->taille; i++){//On enleve la position dans case en vie du joueur 1 si elle s'y trouve
    if(joueur1->case_en_vie[i].ligne == position->ligne && joueur1->case_en_vie[i].colonne == position->colonne){
      joueur1->case_en_vie[i].ligne = joueur1->case_en_vie[(joueur1->taille)-1].ligne;
      joueur1->case_en_vie[i].colonne = joueur1->case_en_vie[(joueur1->taille)-1].colonne;
      joueur1->taille --;
    }
  }
 for(int i = 0; i < joueur2->taille; i++){//On enleve la position dans case en vie du joueur 2 si elle s'y trouve
    if(joueur2->case_en_vie[i].ligne == position->ligne && joueur2->case_en_vie[i].colonne == position->colonne){
      joueur2->case_en_vie[i].ligne = joueur2->case_en_vie[(joueur2->taille)-1].ligne;
      joueur2->case_en_vie[i].colonne = joueur2->case_en_vie[(joueur2->taille)-1].colonne;
      joueur2->taille --;
    }
  } 
}

//Fonction permettant de savoir si le joueur donner en argument à toujours un bateau en jeu ou non
int un_bateau_toujours_en_vie(struct Grille *grille, struct Joueur *joueur){
  return ((batal_en_jeu(&joueur->tab[0], grille)) || (batal_en_jeu(&joueur->tab[1], grille)) || (batal_en_jeu(&joueur->tab[2], grille))|| (batal_en_jeu(&joueur->tab[3], grille)) || (batal_en_jeu(&joueur->tab[4], grille)));
}

//Fonction permettant de placer les batals d'un joueur donné sur la grille à partir de la fonction placer_batal
void placer_batal_joueur(struct Joueur *joueur, struct Grille *grille){
  for(int i = 0; i < NB_BATALS; i++){
    placer_batal(grille, &joueur->tab[i]);
  }
  int cpt = 0;
  for(int i = 0; i < NB_BATALS; i++){
    for(int j = 0; j < TAB_TAILLES1[i]; j++){
      joueur->case_en_vie[cpt].ligne = joueur->tab[i].tab[j].ligne;
      joueur->case_en_vie[cpt].colonne = joueur->tab[i].tab[j].colonne;
      cpt ++;
    }
  }
}

void afficher_grille_SDL(struct Grille *grille, SDL_Surface *ecran, int continuer){
  SDL_Event event;
  int valeur;
  SDL_Surface *cases = NULL, *epaisseur_ligne = NULL, *epaisseur_colonne = NULL, *godzilla = NULL, *archipal = NULL;
  godzilla = IMG_Load("doc/godzilla.gif");
  archipal = IMG_Load("doc/archipal.png");
  SDL_Rect pos;
  cases = SDL_CreateRGBSurface(SDL_HWSURFACE, NB_PIXEL_CASE, NB_PIXEL_CASE,32, 0, 0, 0, 0);
  epaisseur_ligne = SDL_CreateRGBSurface(SDL_HWSURFACE, NB_PIXEL_CASE * NB_COLONNES, 1, 32, 0, 0, 0, 0);
  epaisseur_colonne = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, NB_PIXEL_CASE * NB_LIGNES, 32, 0, 0, 0, 0);
  for(int i = 0; i < NB_LIGNES; i++){
    for(int j = 0; j < NB_COLONNES; j++){
      pos.x = j * NB_PIXEL_CASE;
      pos.y = i * NB_PIXEL_CASE;
      valeur = valeur_a_afficher(&grille->tab[i * NB_COLONNES + j]);
      switch(valeur){
      case(0):
	SDL_FillRect(cases, NULL, SDL_MapRGB(ecran->format, 116, 208, 241));
	SDL_BlitSurface(cases, NULL, ecran, &pos);
	break;
      case(1):
	SDL_FillRect(cases, NULL, SDL_MapRGB(ecran->format, 58, 137, 35));
	SDL_BlitSurface(cases, NULL, ecran, &pos);
	break;
      case(2):
	SDL_FillRect(cases, NULL, SDL_MapRGB(ecran->format, 189, 51, 164));
	SDL_BlitSurface(cases, NULL, ecran, &pos);
	break;
      case(-1):
	SDL_FillRect(cases, NULL, SDL_MapRGB(ecran->format, 204, 14, 0));
	SDL_BlitSurface(cases, NULL, ecran, &pos);
	break;
      case(3):
	SDL_FillRect(cases, NULL, SDL_MapRGB(ecran->format, 190, 159, 121));
	SDL_BlitSurface(cases, NULL, ecran, &pos);
	break;
      case(-2):
	SDL_BlitSurface(archipal, NULL, ecran, &pos);
	break;
      }
      if(grille->tab[i * NB_COLONNES + j].tab[3] == 1)
	SDL_BlitSurface(godzilla, NULL, ecran, &pos);
    }
  }
  pos.x = 0;
  for(int i = 1; i < NB_LIGNES; i++){//On trace la grille
    pos.y = i * NB_PIXEL_CASE;
    SDL_FillRect(epaisseur_ligne, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(epaisseur_ligne, NULL, ecran, &pos);
  }
  pos.y = 0;
  for(int i = 1; i < NB_COLONNES; i++){
    pos.x = i * NB_PIXEL_CASE;
    SDL_FillRect(epaisseur_colonne, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(epaisseur_colonne, NULL, ecran, &pos);
  }
  SDL_Flip(ecran);
  while(continuer){
    SDL_WaitEvent(&event);
    switch(event.type){
    case(SDL_KEYDOWN):
      switch(event.key.keysym.sym){
      case(SDLK_SPACE):
	continuer = 0;
	break;
      default:
	break;
      }
      break;
    }
  }
  SDL_FreeSurface(archipal);/* On libère l'espace */
  SDL_FreeSurface(godzilla);
  SDL_FreeSurface(cases);
  SDL_FreeSurface(epaisseur_ligne);
  SDL_FreeSurface(epaisseur_colonne);
}

void afficher(struct Grille *grille, SDL_Surface *ecran, int n,  int affichage){
  if(affichage == 0)
    afficher_grille(grille);
  else
    afficher_grille_SDL(grille, ecran, n);
}

//Fonction permettant de simuler une partie de batal naval entre deux joueurs
int achievement0(SDL_Surface *ecran, int affichage){
  init_rand();
  int indice = 0;
  struct Position pos;
  struct Grille grille;
  init_grille(&grille);
  struct Joueur joueur1;
  struct Joueur joueur2;
  init_joueur(&joueur1, 1);
  init_joueur(&joueur2, 2);
  init_tab();
  melange_tab();
  placer_batal_joueur(&joueur1, &grille);
  placer_batal_joueur(&joueur2, &grille);
  afficher(&grille, ecran, 1, affichage);
  while(un_bateau_toujours_en_vie(&grille, &joueur1) && un_bateau_toujours_en_vie(&grille, &joueur2)){
    pos = TAB_POSITION[indice];
    obliterer_une_case(&grille, &pos, &joueur1, &joueur2);
    indice ++;
    pos = TAB_POSITION[indice];
    obliterer_une_case(&grille, &pos, &joueur1, &joueur2);
    indice ++;
    afficher(&grille, ecran, 1, affichage);
  }
  if(un_bateau_toujours_en_vie(&grille, &joueur1)){
    return(1);
    }
  if(un_bateau_toujours_en_vie(&grille, &joueur2)){
    return(2);
  }
  return(0);
}




  
     

