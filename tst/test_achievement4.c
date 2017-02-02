#include "../src/achievement4.h"

void affiche_resultat_test(int valeur){
  if(valeur){
    couleur("32");
    printf("OK\n");
  }
  else{
    couleur("31");
    printf("KO\n");
  }
  couleur("0");
}
int test_existence_case(){
  struct Position pos1={0,0};
  if (existence_case(&pos1) != 1){
    return(0);
  }
  struct Position pos2={100,100};
  if (existence_case(&pos2)){
    return(0);
  }
  struct Position pos3={5,11};
  if (existence_case(&pos3)){
    return(0);
  }
  return(1);
}

int test_cote_portal(){
  struct Portal portals[2];
  portals[0].indpos=5;
  portals[0].arrive=15;
  portals[0].cote=3;
  portals[1].indpos=10;
  portals[1].arrive=98;
  portals[1].cote=2;
  int cote1=cote_portal(portals,5);
  int cote2=cote_portal(portals,10);
  return(cote1==3 && cote2==2);
}

int test_init_floyd_warshall(){
  int N=NB_COLONNES*NB_LIGNES;
  struct Grille grille;
  struct Chemin_Minimal tab[N*N];
  struct Portal portals[0];
  init_grille(&grille); 
  init_floyd_warshall(&grille,tab,portals);
  for(int i=0; i<NB_LIGNES*NB_COLONNES; i++){
    for(int j=0; j<NB_LIGNES*NB_COLONNES; j++){
      if (tab[i*N+j].taille!=0 && tab[i*N+j].taille!=1 && tab[i*N+j].taille!=-1){
	printf("%d\n", tab[i*N+j].taille);
	printf("%d\n", i*N+j);
	return(0);
      }
    }
  }
  return(1);
}   

int test_floyd_warshall(){
  int N=NB_COLONNES*NB_LIGNES;
  struct Chemin_Minimal tab[N*N];
  for(int i=0; i<NB_LIGNES*NB_COLONNES; i++){
    for(int j=0; j<NB_LIGNES*NB_COLONNES; j++){
      for(int k=0; k<NB_LIGNES*NB_COLONNES; k++){
	tab[i*NB_COLONNES*NB_LIGNES+j].tab[k]=-1;
      }
      if (i==j){
	tab[i*N+j].taille=0;
      }
      else{ 
      tab[i*N+j].taille=1;
      tab[i*N+j].tab[0]=i;
      tab[i*N+j].tab[1]=j;
      }
    }
  }
  floyd_warshall(tab);
  for(int i=0; i<NB_LIGNES*NB_COLONNES; i++){
    for(int j=0; j<NB_LIGNES*NB_COLONNES; j++){
      if (i!=j && tab[i*N+j].taille!=1){
	return(0);
      }
      if (i==j && tab[i*N+j].taille!=0){
	return(0);
      }
    }
  }
  return(1);
}
	 
int test_distminimale(){
  //Test sans portal ni archipal
  int N=NB_LIGNES*NB_COLONNES;
  struct Grille grille;
  struct Chemin_Minimal matrice[N*N];
  init_grille(&grille);
  struct Portal portal1[0];
  init_floyd_warshall(&grille, matrice, portal1);
  floyd_warshall(matrice);
  struct Position pos1, pos2;
  int min,distmin;
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      pos1=grille_to_position(i);
      pos2=grille_to_position(j);
      min=distminimale(&pos1,&pos2,matrice);
      distmin=abs(pos1.ligne - pos2.ligne) + abs(pos1.colonne - pos2.colonne);
      if(min!=distmin){
	return(0);
      }
    }
  }
  if(NB_PORTALS==0){
    return(1);
  }
  struct Portal portal2[1];
  portal2[0].indpos=73;
  portal2[0].arrive=18;
  portal2[0].cote=2;
  init_grille(&grille);
  grille.tab[73].tab[0]=19;
  init_floyd_warshall(&grille, matrice, portal2);
  floyd_warshall(matrice);
  pos1=grille_to_position(72);
  pos2=grille_to_position(28);
  min=distminimale(&pos1,&pos2,matrice);
  if(min!=3){
    return(0);
  }
  pos1=grille_to_position(90);
  pos2=grille_to_position(9);
  min=distminimale(&pos1,&pos2,matrice);
  if(min!=8){
    return(0);
  }
  if(NB_PORTALS==1){
    return(1);
  }
  struct Portal portal3[2];
  portal3[0].indpos=73;
  portal3[0].arrive=18;
  portal3[0].cote=2;
  portal3[1].indpos=38;
  portal3[1].arrive=0;
  portal3[1].cote=3;
  init_grille(&grille);
  grille.tab[73].tab[0]=19;
  grille.tab[38].tab[0]=1;
  init_floyd_warshall(&grille, matrice, portal3);
  floyd_warshall(matrice);
  pos1=grille_to_position(82);
  pos2=grille_to_position(10);
  min=distminimale(&pos1,&pos2,matrice);
  if(min!=7){
    return(0);
  }
  init_grille(&grille);
  grille.tab[23].tab[0]=-2;
  init_floyd_warshall(&grille, matrice, portal1);
  floyd_warshall(matrice);
  pos1=grille_to_position(21);
  pos2=grille_to_position(27);
  min=distminimale(&pos1, &pos2, matrice);
  if(min!=8){
    return(0);
  }
  return(1); 
}

int test_direction_portal(){
  struct Portal portals[2];
  portals[0].indpos = 78;
  portals[0].cote = 3;
  portals[1].indpos = 54;
  portals[1].cote = 1;
  struct Position pos1 = {7, 8};
  struct Position pos2 = {5, 4};
  struct Position pos3 = {2, 5};
  if(direction_portal(pos1, portals) != 3)
    return(0); 
  if(direction_portal(pos2, portals) != 1)
    return(0);
  if(direction_portal(pos3, portals) != -1)
    return(0);
  return(1);
}

int test_portal_ou_non(){
  struct Portal portals[2];
  struct Grille grille;
  init_grille(&grille);
  portals[0].indpos = 78;
  portals[0].cote = 3;
  portals[0].arrive = 27;
  portals[1].indpos = 54;
  portals[1].cote = 1;
  portals[1].arrive = 63;
  struct Position pos1 = {7, 8};
  struct Position pos2 = {5, 4};
  struct Position pos3 = {2, 5};
  grille.tab[78].tab[0] = 28;
  grille.tab[54].tab[0] = 64;
  if(portal_ou_non(pos1, grille, portals, 3) != 27)
    return(0);
  if(portal_ou_non(pos2, grille, portals, 3) != -1)
    return(0);
  if(portal_ou_non(pos3, grille, portals, 3) != -1)
    return(0);
  return(1);
}

int test_bouge_pos_bat(){
  struct Portal portals[2];
  struct Grille grille;
  init_grille(&grille);
  portals[0].indpos = 78;
  portals[0].cote = 3;
  portals[0].arrive = 27;
  portals[1].indpos = 54;
  portals[1].cote = 1;
  portals[1].arrive = 10;
  struct Position pos1 = {7, 7};
  struct Position pos2 = {7, 6};
  struct Position pos3 = {2, 5};
  struct Position pos4 = {3, 5};
  struct Position pos5 = {6, 4};
  struct Position pos6 = {6, 5};
  grille.tab[78].tab[0] = 28;
  grille.tab[54].tab[0] = 11;
  struct Batal bat;
  bat.taille = 2;
  bat.joueur = 2;
  bat.alignement = 10;
  bat.tab[0] = pos3;
  bat.tab[1] = pos4;
  bouge_pos_bat(&bat, 10, portals, grille);
  if(bat.tab[0].ligne != 3 && bat.tab[0].colonne != 5 && bat.tab[1].ligne != 4 && bat.tab[1].colonne != 5)
    return(0);
  bat.alignement = 1;
  bat.tab[0] = pos2;
  bat.tab[1] = pos1;
  bouge_pos_bat(&bat, 1, portals, grille);
  if(bat.tab[0].ligne != 7 && bat.tab[0].colonne != 7 && bat.tab[1].ligne != 7 && bat.tab[1].colonne != 8)
    return(0);
  bat.tab[0] = pos5;
  bat.tab[1] = pos6;
  bouge_pos_bat(&bat, -10, portals, grille);
  if(bat.tab[0].ligne != 1 && bat.tab[0].colonne != 0 && bat.tab[1].ligne != 5 && bat.tab[1].colonne != 5)
    return(0);
  return(1);
}

int test_copie_bat(){
  struct Batal bat1;
  struct Batal bat2;
  struct Position pos1 = {1, 3};
  struct Position pos2 = {1, 4};
  bat1.taille = 2;
  bat1.alignement = 1;
  bat1.joueur = 1;
  bat1.tab[0] = pos1;
  bat1.tab[1] = pos2;
  copie_bat(&bat2, bat1);
  if(bat2.taille != 2 && bat2.joueur != 1 && bat2.alignement != 1 && bat2.tab[0].ligne != 1 && bat2.tab[0].colonne != 3 && bat2.tab[1].ligne != 1 && bat2.tab[1].colonne != 4)
    return(0);
  return(1);
}

int test_liste_case_possible2(){
  int liste_indice[3];
  int tab_test[100];
  struct Grille grille;
  init_grille(&grille);
  struct Batal tab[100];
  for(int i = 0; i < 100; i++)
    tab[i].taille = 0;
  struct Portal portals[2];
  portals[0].indpos = 49;
  portals[0].cote = 2;
  portals[0].arrive = 71;
  portals[1].indpos = 49;
  portals[1].cote = 2;
  portals[1].arrive = 71;
  grille.tab[49].tab[0] = 72;
  struct Position pos1 = {4, 1};
  struct Position pos2 = {4, 2};
  struct Position pos3 = {4, 3};
  struct Batal bat;
  bat.taille = 3;
  bat.joueur = 1;
  bat.alignement = 1;
  bat.tab[0] = pos1;
  bat.tab[1] = pos2;
  bat.tab[2] = pos3;
  grille.tab[41].tab[1] = 1;
  grille.tab[42].tab[1] = 1;
  grille.tab[43].tab[1] = 1;
  liste_case_possible2(grille, bat, portals, tab, liste_indice);
  for(int i = 0; i < 100; i ++)
    tab_test[i] = 3;
  tab_test[78] = -1;
  tab_test[79] = -1;
  tab_test[88] = -1;
  tab_test[89] = 0;
  tab_test[98] = -1;
  tab_test[99] = 0;
  for(int i = 0; i < 100; i ++)
    if(tab_test[i] != tab[i].taille)
      return(0);
  init_grille(&grille);
  grille.tab[41].tab[1] = 1;
  grille.tab[42].tab[1] = 1;
  grille.tab[43].tab[1] = 1;
  grille.tab[23].tab[0] = -1;
  grille.tab[33].tab[0] = 54;
  portals[0].indpos = 33;
  portals[0].cote = 1;
  portals[0].arrive = 55;
  portals[1].indpos = 33;
  portals[1].cote = 1;
  portals[1].arrive = 55;
  for(int i = 0; i < 100; i++)
    tab[i].taille = 0;
  liste_case_possible2(grille, bat, portals, tab, liste_indice);
  for(int i = 0; i < 100; i ++)
    tab_test[i] = 3;
  for(int i = 0; i < 10; i++){
    tab_test[i * 10 + 8] = -1;
    tab_test[i * 10 + 9] = 0;
  }
  tab_test[23] = -1;
  for(int i = 0; i < 100; i ++)
    if(tab_test[i] != tab[i].taille)
      return(0);
  return(1);  
}

int main(){
  printf("\n");
  printf("Test achievement 4 :\n");
  printf("\n");
  printf("test_distminimale : ");
  affiche_resultat_test(test_distminimale());
  printf("test_direction_portal : ");
  affiche_resultat_test(test_direction_portal());
  printf("test_portal_ou_non : ");
  affiche_resultat_test(test_portal_ou_non());
  printf("test_bouge_pos_bat : ");
  affiche_resultat_test(test_bouge_pos_bat());
  printf("test_copie_bat : ");
  affiche_resultat_test(test_copie_bat());
  printf("test_liste_case_possible2 : ");
  affiche_resultat_test(test_liste_case_possible2());
  printf("test_existence_case : ");
  affiche_resultat_test(test_existence_case());
  printf("test_cote_portal : ");
  affiche_resultat_test(test_cote_portal());
  printf("test_init_floyd_warshall : ");
  affiche_resultat_test(test_init_floyd_warshall());
  printf("test_floyd_warshall : ");
  affiche_resultat_test(test_floyd_warshall());
  return(0);
}
