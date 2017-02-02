#include "achievement4.h"

//Fonction permettant de tester l'existence d'une position
int existence_case(struct Position *position){
  if(position->ligne < 0 || position->ligne >= NB_LIGNES || position->colonne < 0 || position->colonne >= NB_COLONNES){
    return(0);
  }
  return(1);
}

//Fonction qui permet de retourner dans quelle direction aller pour utiliser le portal, on suppose l'existence du portal lorsque qu'on cherche son cote
int cote_portal(struct Portal portals[],int indice){
  int compteur=0;
  int cote=0;
  while(compteur<NB_PORTALS && cote==0){
    if(portals[compteur].indpos==indice){
      cote=portals[compteur].cote;
    };
    compteur++;
  }
  return(cote);
}

//Fonction permettant d'initialiser la matrice utilise pour appliquer le theoreme de Floyd Warshall (matrice des poids des chemins possible au debut)    
void init_floyd_warshall(struct Grille *grille, struct Chemin_Minimal tab[],struct Portal portals[]){
  struct Position position, pos1, pos2, pos3, pos4;
  int etatcase, etatcase1, etatcase2, etatcase3, etatcase4, cote, index;
  for(int i=0; i<NB_LIGNES*NB_COLONNES; i++){
    for(int j=0; j<NB_LIGNES*NB_COLONNES; j++){
      if(i==j){
	for(int k=0; k<NB_LIGNES*NB_COLONNES; k++){
	  tab[i*NB_COLONNES*NB_LIGNES+j].tab[k]=-1;
	}
	tab[i*NB_COLONNES*NB_LIGNES+j].taille=0;
      }
      else{
	for(int k=0; k<NB_LIGNES*NB_COLONNES; k++){
	  tab[i*NB_COLONNES*NB_LIGNES+j].tab[k]=-1;
	}
	tab[i*NB_COLONNES*NB_LIGNES+j].taille=-1;
      }
    }
  }
  for(int k=0; k<NB_LIGNES*NB_COLONNES; k++){
    position=grille_to_position(k);
    etatcase=grille->tab[k].tab[0];
    if(etatcase>=-1){
      cote=0;
      if(etatcase>=1){//presence d'un portal
	cote=cote_portal(portals,k);
      }
      pos1.ligne=position.ligne - 1; pos1.colonne=position.colonne;
      etatcase1=grille->tab[position_to_grille(&pos1)].tab[0];
      pos2.ligne=position.ligne; pos2.colonne=position.colonne + 1;
      etatcase2=grille->tab[position_to_grille(&pos2)].tab[0];
      pos3.ligne=position.ligne + 1; pos3.colonne=position.colonne;
      etatcase3=grille->tab[position_to_grille(&pos3)].tab[0];
      pos4.ligne=position.ligne; pos4.colonne=position.colonne - 1;
      etatcase4=grille->tab[position_to_grille(&pos4)].tab[0];
      if((existence_case(&pos1)||cote==1) && etatcase1!=-2){
	if(cote==1){//Uniquement pour un portal
	  tab[k*NB_COLONNES*NB_LIGNES+etatcase-1].taille=1;
	  tab[k*NB_COLONNES*NB_LIGNES+etatcase-1].tab[0]=k;
	  tab[k*NB_COLONNES*NB_LIGNES+etatcase-1].tab[1]=etatcase-1;  
      	}
	else{
	index=position_to_grille(&pos1);
	tab[k*NB_COLONNES*NB_LIGNES+index].taille=1;
	tab[k*NB_COLONNES*NB_LIGNES+index].tab[0]=k;
	tab[k*NB_COLONNES*NB_LIGNES+index].tab[1]=index;
	}
      }
      if((existence_case(&pos2)||cote==2) && etatcase2!=-2){
	if(cote==2){//Uniquement pour un portal
       	  tab[k*NB_COLONNES*NB_LIGNES+etatcase-1].taille=1;
	  tab[k*NB_COLONNES*NB_LIGNES+etatcase-1].tab[0]=k;
	  tab[k*NB_COLONNES*NB_LIGNES+etatcase-1].tab[1]=etatcase-1; 
	}
	else{
	  index=position_to_grille(&pos2);
	  tab[k*NB_COLONNES*NB_LIGNES+index].taille=1;
	  tab[k*NB_COLONNES*NB_LIGNES+index].tab[0]=k;
	  tab[k*NB_COLONNES*NB_LIGNES+index].tab[1]=index;
	}
      }
      if((existence_case(&pos3)||cote==3) && etatcase3!=-2){
	if(cote==3){//Uniquement pour un portal
	  tab[k*NB_COLONNES*NB_LIGNES+etatcase-1].taille=1;
	  tab[k*NB_COLONNES*NB_LIGNES+etatcase-1].tab[0]=k;
	  tab[k*NB_COLONNES*NB_LIGNES+etatcase-1].tab[1]=etatcase-1; 
	}
	else{
	  index=position_to_grille(&pos3);
	  tab[k*NB_COLONNES*NB_LIGNES+index].taille=1;
	  tab[k*NB_COLONNES*NB_LIGNES+index].tab[0]=k;
	  tab[k*NB_COLONNES*NB_LIGNES+index].tab[1]=index;
	}
      }
      if((existence_case(&pos4)||cote==4) && etatcase4!=-2){
	if(cote==4){//Uniquement pour un portal
	  tab[k*NB_COLONNES*NB_LIGNES+etatcase-1].taille=1;
	  tab[k*NB_COLONNES*NB_LIGNES+etatcase-1].tab[0]=k;
	  tab[k*NB_COLONNES*NB_LIGNES+etatcase-1].tab[1]=etatcase-1; 
	}
	else{
	  index=position_to_grille(&pos4);
	  tab[k*NB_COLONNES*NB_LIGNES+index].taille=1;
	  tab[k*NB_COLONNES*NB_LIGNES+index].tab[0]=k;
	  tab[k*NB_COLONNES*NB_LIGNES+index].tab[1]=index;
	}
      }
    }
  }
}

//Permettant de modifier en place la matrice initialise avant, il n'est pas necessaire d'avoir une autre matrice car les calcul n'utilisent pas les valeurs deja modifie
void floyd_warshall(struct Chemin_Minimal tab[]){
  int n=NB_COLONNES*NB_LIGNES;
  for(int k=0; k<n; k++){
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
	if(tab[i*n+j].taille==-1 && tab[i*n+k].taille!=-1 && tab[k*n+j].taille!=-1){
	  for(int m=0; m<=(tab[i*n+k].taille); m++){
	    tab[i*n+j].tab[m] = tab[i*n+k].tab[m];
	  }
	  for(int m=0; m<=tab[k*n+j].taille; m++){
	    tab[i*n+j].tab[m+tab[i*n+k].taille] = tab[k*n+j].tab[m];
	  } 
	  tab[i*n+j].taille = tab[i*n+k].taille + tab[k*n+j].taille;
	}
	if(tab[i*n+k].taille!=-1 && tab[k*n+j].taille!=-1 && tab[i*n+j].taille>(tab[i*n+k].taille+tab[k*n+j].taille)){
	  for(int m=0; m<=(tab[i*n+k].taille); m++){
	    tab[i*n+j].tab[m] = tab[i*n+k].tab[m];
	  }
	  for(int m=0; m<=tab[k*n+j].taille; m++){
	    tab[i*n+j].tab[m+tab[i*n+k].taille] = tab[k*n+j].tab[m];
	  } 
	  tab[i*n+j].taille = tab[i*n+k].taille + tab[k*n+j].taille;
	}
      }
    }
  }
} 

//Calcule la distance minimale entre deux positions en considérant les archipels et les portals (pour aller de pos1 à pos2)
int distminimale(struct Position *pos1, struct Position *pos2, struct Chemin_Minimal tab[]){
  int index1=position_to_grille(pos1);
  int index2=position_to_grille(pos2);
  int res=tab[index1*NB_COLONNES*NB_LIGNES+index2].taille;
  return(res);
}

//Calcul l'arrive de la torpille avec pour distance minimale la case correspondante dans la matrice de Floyd Warshall
int arrive_torpille2(struct Position *pos_de_depart, struct Joueur *joueur, struct Position *pos_arrive,struct Chemin_Minimal tab[]){
  int distance = NB_LIGNES * NB_COLONNES;
  int a;
  pos_arrive->ligne = NB_LIGNES; //Si on a rien touché
  pos_arrive->colonne = NB_COLONNES; // Si on a rien touché
  for(int k = 0; k < joueur->taille; k++){ //On parcourt toutes les positions de la liste des positions des bateaux de l'autre joueur pour trouver la plus petite distance
    a = distminimale(pos_de_depart, &(joueur->case_en_vie[k]), tab);
    if((a <= PORTEE_MAX_TORPILLE) && (a <= distance)){
      pos_arrive->ligne = joueur->case_en_vie[k].ligne;
      pos_arrive->colonne = joueur->case_en_vie[k].colonne;
      distance = a;
    }
  }
  return(distance);
}

//Permet de retourner un cote aleatoire pour un portal
int cote_aleatoire(){
  return((rand() % 4)+1);
}

//Permet d'initialise les portals dans la grille et dans le tableau de portal
void init_portals(struct Grille *grille, struct Portal portals[]){
  for(int i=0; i<NB_PORTALS; i++){
    struct Position pos1,pos2;
    int index1,index2;
    do{
      pos1=position_aleatoire();
      pos2=position_aleatoire();
      index1=position_to_grille(&pos1);
      index2=position_to_grille(&pos2);
	}
    while(grille->tab[index1].tab[0]>=1 || grille->tab[index1].tab[0]==-2 || index1==index2 || grille->tab[index2].tab[0]>=1 || grille->tab[index2].tab[0]==-2);
    portals[i].indpos=index1;
    portals[i].arrive = index2;
    portals[i].cote = cote_aleatoire();
    grille->tab[index1].tab[0] = index2+1;
  }
}

//Permet d'initialise les archipals dans la grille    
void init_archipals(struct Grille *grille){
  for(int i=0; i<NB_ARCHIPALS; i++){
    struct Position pos;
    int index;
    do{
      pos=position_aleatoire();
      index=position_to_grille(&pos);
    }
    while(grille->tab[index].tab[0]>=1 || grille->tab[index].tab[0]==-2);
    grille->tab[index].tab[0] = -2;
  }
}

//BOUGER BATEAU
int direction_portal(struct Position pos, struct Portal tab[]){
  for(int i = 0; i < NB_PORTALS; i++){
    if(position_to_grille(&pos) == tab[i].indpos)
      return(tab[i].cote);
  }
  return(-1);
}

int portal_ou_non(struct Position pos, struct Grille grille, struct Portal tab[], int direction){
  if(grille.tab[position_to_grille(&pos)].tab[0] > 0){
    if(direction_portal(pos, tab) == direction)
      return(grille.tab[position_to_grille(&pos)].tab[0] - 1);
  }
  return(-1);
}
    
void bouge_pos_bat(struct Batal *bat, int direction, struct Portal tab[], struct Grille grille){
  int indice;
  switch(direction){
  case(10):
    for(int i = 0; i < bat->taille; i++){
      indice = portal_ou_non(bat->tab[i], grille, tab, 3);
      if(indice >= 0)
	bat->tab[i] = grille_to_position(indice);
	else
      bat->tab[i].ligne ++;
    }
    break;
  case(-10):
    for(int i = 0; i < bat->taille; i++){
      indice = portal_ou_non(bat->tab[i], grille, tab, 1);
      if(indice >= 0)
	bat->tab[i] = grille_to_position(indice);
	else
	bat->tab[i].ligne --;
    }
    break;
  case(1):
    for(int i = 0; i < bat->taille; i++){
      indice = portal_ou_non(bat->tab[i], grille, tab, 2);
      if(indice >= 0)
	bat->tab[i] = grille_to_position(indice);
      else
	  bat->tab[i].colonne ++;
    }
    break;
  case(-1):
    for(int i = 0; i < bat->taille; i++){
      indice = portal_ou_non(bat->tab[i], grille, tab, 4);
      if(indice >= 0)
	bat->tab[i] = grille_to_position(indice);
      else
	bat->tab[i].colonne --;
    }
    break;
  }
}

void copie_bat(struct Batal *bat1, struct Batal bat2){
  bat1->taille = bat2.taille;
  bat1->joueur = bat2.joueur;
  bat1->alignement = bat2.alignement;
  for(int i = 0; i < bat2.taille; i++){
    bat1->tab[i].ligne = bat2.tab[i].ligne;
    bat1->tab[i].colonne = bat2.tab[i].colonne;
  }
}

void liste_case_possible2(struct Grille grille, struct Batal bat, struct Portal tab_portal[], struct Batal tab[], int liste_indice_oblitere[]){
    for(int i = 0; i < bat.taille; i++){
      if((grille.tab[position_to_grille(&bat.tab[i])].tab[0] == -1) || (grille.tab[position_to_grille(&bat.tab[i])].tab[bat.joueur] == 0))
	liste_indice_oblitere[i] = 0;
      else
	liste_indice_oblitere[i] = 1;
      grille.tab[position_to_grille(&bat.tab[i])].tab[bat.joueur] = 0;
    }
    if(bat.tab[0].ligne + 1 < NB_LIGNES)
      liste_case_possiblerec2(grille, bat, tab_portal, tab, liste_indice_oblitere, 1);
    if(bat.tab[0].ligne - 1 >= 0)
      liste_case_possiblerec2(grille, bat, tab_portal, tab, liste_indice_oblitere, -1);
    if(bat.tab[0].colonne + 1 < NB_COLONNES)
      liste_case_possiblerec2(grille, bat, tab_portal, tab, liste_indice_oblitere, 10);
    if(bat.tab[0].colonne - 1 >= 0)
      liste_case_possiblerec2(grille, bat, tab_portal, tab, liste_indice_oblitere, -10);
}

void liste_case_possiblerec2(struct Grille grille, struct Batal bata, struct Portal tab_portal[], struct Batal tab[], int liste_indice_oblitere[], int direction){
  bouge_pos_bat(&bata, direction, tab_portal, grille);
  if(bata.tab[0].ligne >= 0 && bata.tab[0].colonne >= 0 && tab[position_to_grille(&bata.tab[0])].taille != bata.taille){
    if(verif_arrive_bateau(grille, bata, liste_indice_oblitere) == 0){
      tab[position_to_grille(&bata.tab[0])].taille = -1;
      }
    else{
      copie_bat(&tab[position_to_grille(&bata.tab[0])], bata);
      if(bata.tab[0].colonne + 1 < NB_COLONNES)
	liste_case_possiblerec2(grille, bata, tab_portal, tab, liste_indice_oblitere, 1);
      if(bata.tab[0].colonne - 1 >= 0)
	liste_case_possiblerec2(grille, bata, tab_portal, tab, liste_indice_oblitere, -1);
      if(bata.tab[0].ligne + 1 < NB_LIGNES){
	liste_case_possiblerec2(grille, bata, tab_portal, tab, liste_indice_oblitere, 10);
      }
      if(bata.tab[0].ligne - 1 >= 0)
	liste_case_possiblerec2(grille, bata, tab_portal, tab, liste_indice_oblitere, -10);
    }
  }
}

void mise_a_jour_liste2(struct Batal bat, struct Joueur *joueur, int liste_indice_oblitere[], struct Batal *nouveau){
  int tab[bat.taille];
  for(int i = 0; i < bat.taille; i++){
      tab[i] = indice_pos_dans_tab(&bat.tab[i], joueur->case_en_vie, joueur->taille);
  }
  for(int i = 0; i < bat.taille; i++){
    if(tab[i] >= 0)
      joueur->case_en_vie[tab[i]] = nouveau->tab[i];
  }
}

void mise_a_jour_structure2(struct Grille *grille, struct Batal *bat, int liste_indice_oblitere[], struct Batal *nouveau){
  for(int i = 0; i < bat->taille; i++){
    grille->tab[position_to_grille(&bat->tab[i])].tab[bat->joueur] = 0;
  }
  for(int i = 0; i < bat->taille; i++){
    if(liste_indice_oblitere[i]) 
      grille->tab[position_to_grille(&nouveau->tab[i])].tab[bat->joueur] = 1;
  }
}

void bouger_bateau2(struct Grille *grille, struct Joueur *joueur, struct Portal portals[]){
  int nombre = 0;
  int choix_bateau;
  int liste_indice_oblitere[TAILLE_MAX_BAT];
  struct Batal tab_tous[NB_LIGNES * NB_COLONNES];
  struct Batal tab_possible[NB_LIGNES * NB_COLONNES];
  struct Batal nouveau_bat;
  for(int i = 0; i < NB_LIGNES * NB_COLONNES; i++)
    tab_tous[i].taille = 0;
  choix_bateau = choix_du_bateau(grille, joueur);
  liste_case_possible2(*grille, joueur->tab[choix_bateau], portals, tab_tous, liste_indice_oblitere);
  for(int i = 0; i < NB_LIGNES * NB_COLONNES; i++)
    if(tab_tous[i].taille == joueur->tab[choix_bateau].taille){
      copie_bat(&tab_possible[nombre], tab_tous[i]);
      nombre ++;
    }
  if(nombre){
    copie_bat(&nouveau_bat, tab_possible[rand() % nombre]);
    for(int i = 0; i < nouveau_bat.taille; i++){
      mise_a_jour_liste2(joueur->tab[choix_bateau], joueur, liste_indice_oblitere, &nouveau_bat);
      mise_a_jour_structure2(grille, &joueur->tab[choix_bateau], liste_indice_oblitere, &nouveau_bat);
      copie_bat(&joueur->tab[choix_bateau], nouveau_bat);
    }
  }
}
  
int achievement4(){
  init_rand();
  struct Chemin_Minimal matrice[NB_COLONNES*NB_LIGNES*NB_LIGNES*NB_COLONNES];
  struct Portal portals[NB_PORTALS];
  int nb_coup = 0;
  int depart1 = 0;
  int depart2 = 0;
  struct Grille grille;
  struct Position pos1;
  struct Position pos2;
  init_grille(&grille);
  init_portals(&grille,portals);
  init_archipals(&grille);
  init_floyd_warshall(&grille,matrice,portals);
  floyd_warshall(matrice);
  struct Joueur joueur1;
  struct Joueur joueur2;
  init_joueur(&joueur1, 1);
  init_joueur(&joueur2, 2);
  placer_batal_joueur(&joueur1, &grille);
  placer_batal_joueur(&joueur2, &grille);
  afficher_grille(&grille);
  while((joueur1.taille > 0) && (joueur2.taille > 0) && (nb_coup < NB_COUP_MAX)){
    //Fonction mise en commentaire car problème pour bouger les bateaux non résolus
    //bouger_bateau2(&grille, &joueur1, portals);
    //bouger_bateau2(&grille, &joueur2, portals);
    depart1 = depart_torpille(&joueur1); //On cherche le premier depart
    arrive_torpille2(&(joueur1.case_en_vie[depart1]), &joueur2, &pos1, matrice); //Et arrive
    depart2 = depart_torpille(&joueur2); //On cherche le deuxieme depart
    arrive_torpille2(&(joueur2.case_en_vie[depart2]), &joueur1, &pos2, matrice); // Et arrive
    if((pos1.ligne != NB_LIGNES) && (pos1.colonne != NB_COLONNES)){//Toucher
      obliterer_une_case(&grille, &pos1, &joueur1, &joueur2); //Enleve la case du bateau touché dans la liste du joueur1 et joueur2
    }
    if((pos2.ligne != NB_LIGNES) && (pos2.colonne != NB_COLONNES)){//Toucher;
      obliterer_une_case(&grille, &pos2, &joueur1, &joueur2);
    }
    nb_coup ++;
    afficher_grille(&grille);
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

  
 
  

      
	  
  
  
