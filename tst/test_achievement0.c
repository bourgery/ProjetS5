#include "../src/achievement0.h"


int TAB_TAILLES2[NB_BATALS]={TAB_TAILLE};
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

int test_position_to_grille(){
  struct Position pos1 = {5, 5};
  struct Position pos2 = {2, 5};
  struct Position pos3 = {8, 1};
  struct Position pos4 = {4, 9};
  if(position_to_grille(&pos1) != (5 * NB_COLONNES + 5))
    return(0);
  if(position_to_grille(&pos2) != (2 * NB_COLONNES + 5))
    return(0);
  if(position_to_grille(&pos3) != (8 * NB_COLONNES + 1))
    return(0);
  if(position_to_grille(&pos4) != (4 * NB_COLONNES + 9))
    return(0);
  return(1);
}
  
int test_init_grille(){
  struct Grille grille;
  init_grille(&grille);
  for(int i = 0; i < NB_LIGNES * NB_COLONNES; i++){
    for(int j = 0; j <= NB_JOUEURS; j++){
      if(grille.tab[i].tab[j] != 0){
	return(0);
      }
    }
  }
  return(1);
}

int test_placer_batal(int joueur){
  int index;
  struct Grille grille;
  struct Position position ={NB_LIGNES, NB_COLONNES};
  init_grille(&grille);
  for(int i = 1; i < 6; i++){
    struct Batal bateau;
    init_batal(&bateau, i, &position, 0, joueur);
    placer_batal(&grille, &bateau);
    for(int j = 0; j < bateau.taille; j++){ //Test pour savoir si le bateau est bien placer
      index = position_to_grille(&bateau.tab[j]);
      if(grille.tab[index].tab[joueur] != 1)
	return(0);
    }
    init_grille(&grille);
  }
  return(1);
  }

int test_verif_pour_mettre_bateau(){
  int bool;
  struct Grille grille;
  init_grille(&grille);
  grille.tab[11].tab[1] = 1;
  grille.tab[12].tab[1] = 1;
  grille.tab[13].tab[1] = 1;
  grille.tab[21].tab[1] = 1;
  grille.tab[31].tab[1] = 1;
  grille.tab[32].tab[1] = 1;
  grille.tab[33].tab[1] = 1;
  grille.tab[53].tab[1] = 1;
  grille.tab[53].tab[2] = 1;
  grille.tab[54].tab[1] = 1;
  grille.tab[54].tab[2] = 1;
  grille.tab[55].tab[1] = 1;
  grille.tab[55].tab[2] = 1;
  grille.tab[74].tab[1] = 1;
  grille.tab[75].tab[1] = 1;
  grille.tab[76].tab[1] = 1;
  struct Batal bat1;
  struct Position pos1 = {2, 2}; //Pas de bateau
  init_batal(&bat1, 4, &pos1, 1, 1);
  bool = verif_pour_mettre_bateau(&grille, &bat1);
  if(bool != 1){ 
    return(0);
  }
  struct Batal bat2;
  struct Position pos2 = {1, 1}; //Bateau mais pas du même joueur
  init_batal(&bat2, 5, &pos2, 10, 2);
  bool = verif_pour_mettre_bateau(&grille, &bat2);
  if(bool != 1){
    return(0);
  }
  struct Batal bat3;
  struct Position pos3 = {7, 1}; //Bateau du même joueur
  init_batal(&bat3, 4, &pos3, 1, 1);
  bool = verif_pour_mettre_bateau(&grille, &bat3);
  if(bool != 0){
    return(0);
  }
  struct Batal bat4;
  struct Position pos4 = {5, 3}; //Bateau des 2 joueurs
  init_batal(&bat4, 3, &pos4, 1, 2);
  bool = verif_pour_mettre_bateau(&grille, &bat4);
  if(bool != 0){
    return(0);
  }

  struct Batal bat5;
  struct Position pos5 = {7, 0}; //Bateau qui depasse de la grille verticalement
  init_batal(&bat5, 5, &pos5, 10, 1);
  bool = verif_pour_mettre_bateau(&grille, &bat5);
  if(bool != 0){
    return(0);
  }
  struct Batal bat6;
  struct Position pos6 = {0, 8}; //Bateau qui depasse de la grille horizontalement
  init_batal(&bat6, 3, &pos6, 1, 2);
  bool = verif_pour_mettre_bateau(&grille, &bat6);
  if(bool != 0){
    return(0);
  }
  return(1);
}

int compare_position(struct Position pos1, struct Position pos2){
  return((pos1.ligne == pos2.ligne) && (pos1.colonne == pos2.colonne));
}

int compare_tab_position(struct Position tab1[], struct Position tab2[],int taille){
  for(int i = 0; i < taille; i++){
    if(compare_position(tab1[i], tab2[i]) == 0)
      return(0);
  }
  return 1;
}

int test_batal_en_jeu(){
  struct Grille grille;
  init_grille(&grille);
  grille.tab[12].tab[1]=1;
  grille.tab[13].tab[1]=1;
  grille.tab[14].tab[1]=1;
  grille.tab[15].tab[1]=1;
  grille.tab[16].tab[1]=1;
  struct Batal bateau1;
  struct Position position1={1,2};
  init_batal(&bateau1,5,&position1,1,1);
  for(int i = 1; i < 5; i++){
    struct Position pos={1, i + 2};
    bateau1.tab[i]=pos;
  }
  if(batal_en_jeu(&bateau1,&grille)==0)
    return(0);
  grille.tab[44].tab[0]=-1;
  grille.tab[54].tab[0]=-1;
  grille.tab[64].tab[0]=-1;
  grille.tab[74].tab[2]=1;
  struct Batal bateau2;
  struct Position position2={4,4};
  init_batal(&bateau2,4,&position2,10,2);
  for(int i = 1; i < 4; i++){
    struct Position pos={i + 4, 4};
    bateau2.tab[i]=pos;
  }
  if(batal_en_jeu(&bateau2,&grille)==0)
    return(0);
  grille.tab[29].tab[0]=-1;
  grille.tab[39].tab[0]=-1;
  grille.tab[49].tab[0]=-1;
  struct Batal bateau3;
  struct Position position3={2,9};
  init_batal(&bateau3,3,&position3,10,1);
  for(int i = 1; i < 3; i++){
    struct Position pos={i + 2, 9};
    bateau3.tab[i]=pos;
  }
  if(batal_en_jeu(&bateau3,&grille))
     return(0);
  grille.tab[93].tab[2]=1;
  grille.tab[94].tab[0]=-1;
  struct Batal bateau4;
  struct Position position4={9,3};
  init_batal(&bateau4,2,&position4,1,2);
  for(int i = 1; i < 2; i++){
    struct Position pos={9, i + 3};
    bateau4.tab[i]=pos;
  }
  if(batal_en_jeu(&bateau4,&grille)==0)
    return(0);
  return(1);
}

int test_grille_to_position(){
  int i1 = 3 * NB_COLONNES + 5;
  struct Position pos1 = {3, 5};
  int i2 = 1 * NB_COLONNES + 9;
  struct Position pos2 = {1, 9};
  int i3 = NB_LIGNES * NB_COLONNES - 1;
  struct Position pos3 = {NB_LIGNES - 1, NB_COLONNES - 1};
  if(compare_position(pos1, grille_to_position(i1)) && compare_position(pos2, grille_to_position(i2)) && compare_position(pos3, grille_to_position(i3)))
    return(1);
  return(0);
}

int test_init_batal(){
  struct Batal battest1;
  struct Position pos1={5,2};
  init_batal(&battest1,4,&pos1,10,2);
  int test1=(battest1.taille==4 && compare_position(pos1,battest1.tab[0]) && battest1.alignement==10 && battest1.joueur==2);
  struct Batal battest2;
  struct Position pos2={9,9};
  init_batal(&battest2,3,&pos2,1,1);
  int test2=(battest2.taille==3 && compare_position(pos2,battest2.tab[0]) && battest2.alignement==1 && battest2.joueur==1);
  struct Batal battest3;
  struct Position pos3={1,0};
  init_batal(&battest3,1,&pos3,1,2);
  int test3=(battest3.taille==1 && compare_position(pos3,battest3.tab[0]) && battest3.alignement==1 && battest3.joueur==2);
  return(test1 && test2 & test3);
}

int test_init_joueur(){
  struct Joueur joueur1;
  init_joueur(&joueur1,1);
  struct Position pos={0, 0};
  int testtaille1=1; int testjoueur1=1; int testalignement1=1; int testpos1=1;
  for(int i=0; i < NB_BATALS; i++){
    testtaille1= testtaille1 && joueur1.tab[i].taille == TAB_TAILLES2[i];
    testalignement1= testalignement1 && joueur1.tab[i].alignement==0;
    testpos1=testpos1 && compare_position(pos, joueur1.tab[i].tab[0]);
  }
  return(testpos1 && testtaille1 && testjoueur1 && testalignement1);
}

int test_obliterer_une_case(){
  struct Grille grille;
  struct Joueur j1;
  struct Joueur j2;
  init_joueur(&j1, 1);
  init_joueur(&j2, 2);
  init_grille(&grille);
  struct Position postest1 = {9, 9};
  struct Position postest2 = {5, 2};
  struct Position postest3 = {2, 3};
  struct Position postest4 = {1, 0};
  struct Position postest5 = {0, 1};
  struct Position pos6 = {3, 3};
  j1.taille = 5;
  j2.taille = 5;
  j1.case_en_vie[0] = postest5;
  j2.case_en_vie[0] = postest5;
  j1.case_en_vie[1] = postest4;
  j1.case_en_vie[2] = pos6;
  j1.case_en_vie[3] = pos6;
  j1.case_en_vie[4] = pos6;
  j2.case_en_vie[1] = pos6;
  j2.case_en_vie[2] = pos6;
  j2.case_en_vie[3] = pos6;
  j2.case_en_vie[4] = pos6; 
  obliterer_une_case(&grille,&postest1, &j1, &j2);
  obliterer_une_case(&grille,&postest2, &j1, &j2);
  obliterer_une_case(&grille,&postest3, &j1, &j2);
  obliterer_une_case(&grille,&postest4, &j1, &j2);
  obliterer_une_case(&grille,&postest5, &j1, &j2);
  if(j1.taille != 3 && j2.taille != 4){
    return(0);
  }
  for(int i = 0; i < j1.taille; i++)
    if(((j1.case_en_vie[i].ligne == postest5.ligne) && (j1.case_en_vie[i].colonne == postest5.colonne)) || ((j1.case_en_vie[i].ligne == postest4.ligne) && (j1.case_en_vie[i].colonne == postest4.colonne))){
      return(0);
    }
  for(int i = 0; i < j2.taille; i++)
    if(((j2.case_en_vie[i].ligne == postest5.ligne) && (j2.case_en_vie[i].colonne == postest5.colonne))){
      return(0);
    }
  return(grille.tab[99].tab[0] == -1 && grille.tab[52].tab[0] == -1 && grille.tab[10].tab[0] == -1 && grille.tab[10].tab[0] == -1 && grille.tab[1].tab[0] == -1);
}

int test_un_bateau_toujours_en_vie(){
  struct Grille grille;
  for(int i = 0; i < NB_LIGNES * NB_COLONNES; i++){
  grille.tab[i].tab[0] = -1;
  }
  struct Joueur joueurtest1;
  init_joueur(&joueurtest1,1);
  struct Position pos1={0,0};
  joueurtest1.tab[0].tab[0]=pos1;
  joueurtest1.tab[0].alignement=1;
  for(int i = 1; i < 5; i++){
    struct Position pos={0, i};
    joueurtest1.tab[0].tab[i]=pos;
  }
  struct Position pos2={1,0};
  joueurtest1.tab[1].tab[0]=pos2;
  joueurtest1.tab[1].alignement=1;
  for(int i = 1; i < 4; i++){
    struct Position pos={1, i};
    joueurtest1.tab[1].tab[i]=pos;
  }
  struct Position pos3={2,0};
  joueurtest1.tab[2].tab[0]=pos3;
  joueurtest1.tab[2].alignement=1;
  for(int i = 1; i < 3; i++){
    struct Position pos={2, i};
    joueurtest1.tab[2].tab[i]=pos;
  }
  struct Position pos4={3,0};
  joueurtest1.tab[3].tab[0]=pos4;
  joueurtest1.tab[3].alignement=1;
  for(int i = 1; i < 2; i++){
    struct Position pos={3, i};
    joueurtest1.tab[3].tab[i]=pos;
  }
  struct Position pos5={4,0};
  joueurtest1.tab[4].tab[0]=pos5;
  joueurtest1.tab[4].alignement=1;
  int test1=(un_bateau_toujours_en_vie(&grille,&joueurtest1)==0);
  grille.tab[0].tab[0]=0;
  grille.tab[0].tab[1]=1;
  grille.tab[0].tab[2]=1;
  int test2=(un_bateau_toujours_en_vie(&grille,&joueurtest1)!=0);
  grille.tab[0].tab[0]=-1;
  grille.tab[4].tab[0]=0;
  grille.tab[4].tab[1]=1;
  int test3=(un_bateau_toujours_en_vie(&grille,&joueurtest1)!=0);
  return(test1 && test2 && test3);
  } 

int test_placer_batal_joueur(){
  struct Joueur joueur;
  struct Grille grille;
  init_grille(&grille);
  init_joueur(&joueur,1);
  placer_batal_joueur(&joueur,&grille);
  int indice1=position_to_grille(&(joueur.tab[0].tab[0]));
  int test1=(0 <= indice1) && (indice1 < NB_LIGNES * NB_COLONNES);
  int indice2=position_to_grille(&(joueur.tab[1].tab[0]));
  int test2=(0 <= indice2) && (indice2 < NB_LIGNES * NB_COLONNES);
  int indice3=position_to_grille(&(joueur.tab[2].tab[0]));
  int test3=(0 <= indice3) && (indice3 < NB_LIGNES * NB_COLONNES);
  int indice4=position_to_grille(&(joueur.tab[3].tab[0]));
  int test4=(0 <= indice4) && (indice4 < NB_LIGNES * NB_COLONNES);
  int indice5=position_to_grille(&(joueur.tab[4].tab[0]));
  int test5=(0 <= indice5) && (indice5 < NB_LIGNES * NB_COLONNES);
  return(test1 && test2 & test3 && test4 && test5);
}

int test_bateau_rond(struct Batal bateau){
  int l = bateau.tab[0].ligne;
  int c = bateau.tab[0].colonne;
  int test1 =(bateau.tab[1].ligne == l && bateau.tab[1].colonne == (c+1));
  int test2 =(bateau.tab[2].ligne == l && bateau.tab[2].colonne == (c+2));
  int test3 =(bateau.tab[3].ligne == (l+1) && bateau.tab[3].colonne == (c+2));
  int test4 =(bateau.tab[4].ligne == (l+2) && bateau.tab[4].colonne == (c+2));
  int test5 =(bateau.tab[5].ligne == (l+2) && bateau.tab[5].colonne == (c+1));
  int test6 =(bateau.tab[6].ligne == (l+2) && bateau.tab[6].colonne == c);
  int test7 =(bateau.tab[7].ligne == (l+1) && bateau.tab[7].colonne == c);
  return(test1 && test2 && test3 && test4 && test5 && test6 && test7);
}

int test_init_rond(){
  struct Batal bateau;
  struct Position pos={5,5};
  init_rond(&bateau,&pos);
  return(test_bateau_rond(bateau));
}

int test_bateau_H(struct Batal bateau,int alignement){
  int l = bateau.tab[0].ligne;
  int c = bateau.tab[0].colonne;
  int test1; int test2; int test3; int test4; int test5; int test6;
  if(alignement == 31){
    test1 =(bateau.tab[1].ligne == (l+1) && bateau.tab[1].colonne == c);
    test2 =(bateau.tab[2].ligne == (l+2) && bateau.tab[2].colonne == c);
    test3 =(bateau.tab[3].ligne == (l+1) && bateau.tab[3].colonne == (c+1));
    test4 =(bateau.tab[4].ligne == l && bateau.tab[4].colonne == (c+2));
    test5 =(bateau.tab[5].ligne == (l+1) && bateau.tab[5].colonne == (c+2));
    test6 =(bateau.tab[6].ligne == (l+2) && bateau.tab[6].colonne == (c+2));
  }
  else if(alignement == 32){
    test1 =(bateau.tab[1].ligne == (l-2) && bateau.tab[1].colonne == c);
    test2 =(bateau.tab[2].ligne == l && bateau.tab[2].colonne == (c+1));
    test3 =(bateau.tab[3].ligne == (l-1) && bateau.tab[3].colonne == (c+1));
    test4 =(bateau.tab[4].ligne == (l-2) && bateau.tab[4].colonne == (c+1));
    test5 =(bateau.tab[5].ligne == l && bateau.tab[5].colonne == (c+2));
    test6 =(bateau.tab[6].ligne == (l-2) && bateau.tab[6].colonne == (c+2));
  }
  else{
    return(0);
  }
  return(test1 && test2 && test3 && test4 && test5 && test6);
}

int test_init_H(){
  struct Batal bateau1;
  struct Batal bateau2;
  struct Position pos1={0,0};
  struct Position pos2={5,5};
  init_H(&bateau1,&pos1,31);
  init_H(&bateau2,&pos2,32);
  return(test_bateau_H(bateau1,31) && test_bateau_H(bateau2,32));
}

int test_bateau_L(struct Batal bateau,int alignement){
  int l = bateau.tab[0].ligne;
  int c = bateau.tab[0].colonne;
  int test1; int test2; int test3;
  if(alignement == 41){
    test1 =(bateau.tab[1].ligne == l && bateau.tab[1].colonne == (c-1));
    test2 =(bateau.tab[2].ligne == (l-1) && bateau.tab[2].colonne == (c-1));
    test3 =(bateau.tab[3].ligne == (l-2) && bateau.tab[3].colonne == (c-1));
  }
  else if(alignement == 42){
    test1 =(bateau.tab[1].ligne == l && bateau.tab[1].colonne == (c+1));
    test2 =(bateau.tab[2].ligne == (l-1) && bateau.tab[2].colonne == (c+1));
    test3 =(bateau.tab[3].ligne == (l-2) && bateau.tab[3].colonne == (c+1));
  }
  else if(alignement == 43){
    test1 =(bateau.tab[1].ligne == l && bateau.tab[1].colonne == (c-1));
    test2 =(bateau.tab[2].ligne == (l+1) && bateau.tab[2].colonne == (c-1));
    test3 =(bateau.tab[3].ligne == (l+2) && bateau.tab[3].colonne == (c-1));
  }
  else if(alignement == 44){
    test1 =(bateau.tab[1].ligne == l && bateau.tab[1].colonne == (c+1));
    test2 =(bateau.tab[2].ligne == (l+1) && bateau.tab[2].colonne == (c+1));
    test3 =(bateau.tab[3].ligne == (l+2) && bateau.tab[3].colonne == (c+1));
  }
  else if(alignement == 45){
    test1 =(bateau.tab[1].ligne == (l+1) && bateau.tab[1].colonne == c);
    test2 =(bateau.tab[2].ligne == (l+1) && bateau.tab[2].colonne == (c-1));
    test3 =(bateau.tab[3].ligne == (l+1) && bateau.tab[3].colonne == (c-2));
  }
  else if(alignement == 46){
    test1 =(bateau.tab[1].ligne == (l-1) && bateau.tab[1].colonne == c);
    test2 =(bateau.tab[2].ligne == (l-1) && bateau.tab[2].colonne == (c-1));
    test3 =(bateau.tab[3].ligne == (l-1) && bateau.tab[3].colonne == (c-2));
  }
  else if(alignement == 47){
    test1 =(bateau.tab[1].ligne == (l+1) && bateau.tab[1].colonne == c);
    test2 =(bateau.tab[2].ligne == (l+1) && bateau.tab[2].colonne == (c+1));
    test3 =(bateau.tab[3].ligne == (l+1) && bateau.tab[3].colonne == (c+2));
  }
  else if(alignement == 48){
    test1 =(bateau.tab[1].ligne == (l-1) && bateau.tab[1].colonne == c);
    test2 =(bateau.tab[2].ligne == (l-1) && bateau.tab[2].colonne == (c+1));
    test3 =(bateau.tab[3].ligne == (l-1) && bateau.tab[3].colonne == (c+2));
  }
  else{
    return(0);
  }
  return(test1 && test2 && test3);
}

int test_init_L(){
  struct Batal bateau1;
  struct Batal bateau2;
  struct Batal bateau3;
  struct Batal bateau4;
  struct Batal bateau5;
  struct Batal bateau6;
  struct Batal bateau7;
  struct Batal bateau8;
  struct Position pos={5,5};
  init_L(&bateau1,&pos,41);
  init_L(&bateau2,&pos,42);
  init_L(&bateau3,&pos,43);
  init_L(&bateau4,&pos,44);
  init_L(&bateau5,&pos,45);
  init_L(&bateau6,&pos,46);
  init_L(&bateau7,&pos,47);
  init_L(&bateau8,&pos,48);
  return(test_bateau_L(bateau1,41) && test_bateau_L(bateau2,42) && test_bateau_L(bateau3,43) && test_bateau_L(bateau4,44) && test_bateau_L(bateau5,45) && test_bateau_L(bateau6,46) && test_bateau_L(bateau7,47) && test_bateau_L(bateau8,48));
}

int test_alignement_aleatoire(){
  int taille=4;
  int res;
  for(int i = 0; i < 20; i++){
    res=alignement_aleatoire(taille);
    int test1= (res==1 || res==10 || res==41 || res==42 || res==43 || res==44 || res==45 || res==46 || res==47 || res==48);
    taille=8;
    res=alignement_aleatoire(taille);
    int test2= (res==1 || res==10 || res==20);
    taille=7;
    res=alignement_aleatoire(taille);
    int test3= (res==1 || res==10 || res==31 || res==32);
    taille=42;
    res=alignement_aleatoire(taille);
    int test4= (res==1 || res==10);
    if((test1 && test2 && test3 && test4) == 0)
      return(0);
  }
  return(1);
}


int main(){
  init_rand();
  printf("\n");
  printf("Test achievement 0 :\n");
  printf("\n");
  printf("test_grille_to_position : ");
  affiche_resultat_test(test_grille_to_position());	 
  printf("test_position_to_grille : ");
  affiche_resultat_test(test_position_to_grille());
  printf("test_verif_pour_mettre_bateau : ");
  affiche_resultat_test(test_verif_pour_mettre_bateau());
  printf("test_placer_batal : ");
  affiche_resultat_test(test_placer_batal(1) && test_placer_batal(2));
  printf("test_init_grille : ");
  affiche_resultat_test(test_init_grille());
  printf("test_batal_en_jeu : ");
  affiche_resultat_test(test_batal_en_jeu());
  printf("test_init_batal : ");
  affiche_resultat_test(test_init_batal());
  printf("test_init_joueur : ");
  affiche_resultat_test(test_init_joueur());
  printf("test_obliterer_une_case : ");
  affiche_resultat_test(test_obliterer_une_case());
  printf("test_un_bateau_toujours_en_vie : ");
  affiche_resultat_test(test_un_bateau_toujours_en_vie());
  printf("test_placer_batal_joueur : ");
  affiche_resultat_test(test_placer_batal_joueur());
  printf("test_init_rond : ");
  affiche_resultat_test(test_init_rond());
  printf("test_init_H : ");
  affiche_resultat_test(test_init_H());
  printf("test_init_L : ");
  affiche_resultat_test(test_init_L());
  printf("test_alignement_aleatoire : ");
  affiche_resultat_test(test_alignement_aleatoire());
    return(0);
}




