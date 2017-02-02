#include "../src/achievement2.h"

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

int test_init_tab_entier(){
  int n = NB_LIGNES * NB_COLONNES;
  int tab[n];
  init_tab_entier(tab, n);
  int somme = 0;
  for(int i = 0; i < n; i++){
    if(tab[i] != 0){
      return(0);
    }
    somme += tab[i];
  }
  return(somme == 0);
}

int test_choix_du_bateau(){
  int test;
  struct Joueur joueur;
  struct Grille grille;
  init_grille(&grille);
  init_joueur(&joueur, 1);
  placer_batal_joueur(&joueur, &grille);
  for(int i = 0; i < 20; i++){
    test = choix_du_bateau(&grille, &joueur);
    if((test >= NB_BATALS) || (test < 0))
      return(0);
  }
  for(int i = 0; i < joueur.tab[4].taille; i++){
     grille.tab[position_to_grille(&joueur.tab[4].tab[i])].tab[0] = -1;
  }
  for(int i = 0; i < 40; i++){
    test = choix_du_bateau(&grille, &joueur);
    if((test >= NB_BATALS - 1 ) || (test < 0))
      return(0);
  }
  return(1);
}

int test_verif_arrive_bateau(){
  struct Batal bat;
  struct Grille grille;
  init_grille(&grille);
  int liste_indice[2] = {1, 1};
  bat.taille = 2;
  bat.joueur = 2;
  grille.tab[41].tab[0] = -1;
  struct Position pos1 = {4, 1};
  struct Position pos2 = {4, 3};
  bat.tab[0] = pos1;
  bat.tab[1] = pos2;
  if(verif_arrive_bateau(grille, bat, liste_indice) != 0)
    return(0);
  liste_indice[0] = 0;
  if(verif_arrive_bateau(grille, bat, liste_indice) != 1)
    return(0);
  bat.tab[0].ligne = 10;
  if(verif_arrive_bateau(grille, bat, liste_indice) != 0)
    return(0);
  liste_indice[0] = 1;
  struct Position pos3 = {5, 4};
  bat.tab[0] = pos3;
  grille.tab[54].tab[0] = -2;
  if(verif_arrive_bateau(grille, bat, liste_indice) != 0)
    return(0); 
  return(1);
}

int test_liste_case_possibles(){
  int tab[100];
  int tab_test[100];
  int tab_obli[TAILLE_MAX_BAT];
  int tab_prec[100];
  struct Grille grille;
  struct Batal bat;
  struct Position pos = {8, 4};
  init_grille(&grille);
  init_tab_entier(tab, 100);
  init_tab_entier(tab_test, 100);
  init_tab_entier(tab_obli, TAILLE_MAX_BAT);
  init_batal(&bat, 2, &pos, 10, 1);
  liste_case_possibles(grille, bat, tab, tab_obli, tab_prec);
  for(int i = 0; i < 90; i ++){ //rien dans la grille
    if(tab[i] != 1)
      return(0);
  }
  for(int i = 90; i < 100; i ++){
    if(tab[i] != -1){
      return(0);
    }
  }
  init_grille(&grille);
  grille.tab[1].tab[2] = 1;
  grille.tab[10].tab[2] = 1;
  grille.tab[11].tab[2] = 1;
  init_tab_entier(tab, 100);
  init_tab_entier(tab_obli, TAILLE_MAX_BAT);
  init_batal(&bat, 1, &pos, 10, 2);
  grille.tab[84].tab[2] = 1;
  liste_case_possibles(grille, bat, tab, tab_obli, tab_prec);
  for(int i = 0; i < 100; i++) //Case en haut à gauche inaccessible 
    tab_test[i] = 1;
  tab_test[0] = 0;
  tab_test[1] = -1;
  tab_test[10] = -1;
  tab_test[11] = -1;
  for(int i = 0; i < 100; i++){
    if(tab[i] != tab_test[i])
      return(0);
  }
  grille.tab[84].tab[1] = 0;
  grille.tab[15].tab[1] = 1;
  grille.tab[25].tab[1] = 1;
  pos.ligne = 1;
  pos.colonne = 5;
  grille.tab[8].tab[2] = 1;
  grille.tab[18].tab[2] = 1;
  grille.tab[28].tab[2] = 1;
  init_batal(&bat, 2, &pos, 10, 1);
  init_tab_entier(tab, 100);
  init_tab_entier(tab_obli, TAILLE_MAX_BAT);
  liste_case_possibles(grille, bat, tab, tab_obli, tab_prec);
  for(int i = 90; i < 100; i++)
    tab_test[i] = -1;
  tab_test[8] = -1;
  tab_test[18] = -1;
  tab_test[28] = -1;
  tab_test[74] = -1;
  tab_test[84] = -1;
  tab_test[94] = 0;
  for(int i = 0; i < 100; i++){ //Contournement d'un mur de bateau
    if(tab[i] != tab_test[i])
      return(0);
  }
  init_grille(&grille);
  init_tab_entier(tab, 100);
  grille.tab[89].tab[0] = -1;
  grille.tab[15].tab[1] = 1;
  grille.tab[25].tab[1] = 0;
  grille.tab[35].tab[1] = 1;
  for(int i = 0; i < 80; i++)
    tab_test[i] = 1;
  for(int i = 80; i < 90; i++)
    tab_test[i] = -1;
  for(int i = 90; i < 100; i++)
    tab_test[i] = 0;
  tab_test[69] = -1;
  init_batal(&bat, 3, &pos, 10, 1);
  liste_case_possibles(grille, bat, tab, tab_obli, tab_prec);
  for(int i = 0; i < 100; i++){ //Bateau coupe en deux
    if(tab[i] != tab_test[i])
      return(0);
  }
  init_grille(&grille);
  init_batal(&bat, 4, &pos, 43, 2);
  grille.tab[15].tab[2] = 1;
  grille.tab[14].tab[2] = 1;
  grille.tab[24].tab[2] = 1;
  grille.tab[34].tab[2] = 1;
  init_tab_entier(tab, 100);
  init_tab_entier(tab_test, 100);
  init_tab_entier(tab_obli, TAILLE_MAX_BAT);
  liste_case_possibles(grille, bat, tab, tab_obli, tab_prec);
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 10; j++){
      tab_test[i * 10 + j] = 1;
    }
  }
  for(int i = 0; i < 8; i ++)
    tab_test[i * 10] = -1;
  for(int i = 1; i < 10; i++){
    tab_test[80 + i] = -1;
  }
  for(int i = 0; i < 100; i++){ //Bateau en L sans rien
    if(tab[i] != tab_test[i])
      return(0);
  }
  init_grille(&grille);
  init_batal(&bat, 5, &pos, 1, 2);
  grille.tab[15].tab[1] = 1;
  grille.tab[25].tab[1] = 1;
  grille.tab[5].tab[1] = 1;
  grille.tab[15].tab[2] = 1;
  grille.tab[16].tab[2] = 1;
  grille.tab[17].tab[2] = 1;
  grille.tab[18].tab[2] = 1;
  grille.tab[19].tab[2] = 1;
  init_tab_entier(tab, 100);
  init_tab_entier(tab_test, 100);
  tab_test[5] = -1;
  tab_test[14] = -1;
  tab_test[16] = -1;
  tab_test[25] = -1;
  liste_case_possibles(grille, bat, tab, tab_obli, tab_prec);
  for(int i = 0; i < 100; i++){
    if(tab[i] != tab_test[i])
      return(0);
  }	
  return(1);
}

int test_deplacement_possible_uniquement(){
  int n;
  int tab_tous[100];
  for(int i = 0; i < 100; i++)
    tab_tous[i] =0;
  tab_tous[1] = 1;
  tab_tous[4] = 1;
  tab_tous[7] = 1;
  tab_tous[8] = 1;
  tab_tous[9] = 1;
  int tab_pas_tous[100];
  n = deplacement_possible_uniquement(tab_tous, tab_pas_tous);
  if((n != 5) || (tab_pas_tous[0] != 1) || (tab_pas_tous[1] != 4) || (tab_pas_tous[2] != 7) || (tab_pas_tous[3] != 8) || (tab_pas_tous[4] != 9))
    return(0);
  return(1);
}

int test_indice_pos_dans_tab(){
  struct Position posi = {0, 1};
  struct Position test;
  struct Position pos = {4, 4};
  struct Position tab[10];
  for(int i = 0; i < 10; i++){
    test.ligne = i;
    test.colonne = i;
    tab[i] = test;
  }
  if(indice_pos_dans_tab(&pos, tab, 10) != 4)
    return(0);
  if(indice_pos_dans_tab(&posi, tab, 10) != -1)
    return(0);
  return(1);
}

int test_mise_a_jour_liste(){
  struct Joueur joueur;
  joueur.taille = 5;
  struct Batal bat;
  struct Position pos1 = {1, 2};
  struct Position pos2 = {1, 3};
  struct Position pos3 = {5, 6};
  struct Position pos4 = {7, 9};
  struct Position pos5 = {4, 5};
  struct Position pos6 = {3, 4};
  struct Position pos7 = {3, 5};
  struct Position pos8 = {9, 9};
  bat.taille = 2;
  bat.joueur = 1;
  bat.alignement = 1;
  bat.tab[0] = pos1;
  bat.tab[1] = pos2;
  joueur.case_en_vie[0] = pos1;
  joueur.case_en_vie[1] = pos2;
  joueur.case_en_vie[2] = pos3;
  joueur.case_en_vie[3] = pos4;
  joueur.case_en_vie[4] = pos5;
  mise_a_jour_liste(bat, &joueur, &pos6);
  if(indice_pos_dans_tab(&pos1, joueur.case_en_vie, 5) != -1 && indice_pos_dans_tab(&pos2, joueur.case_en_vie, 5) != -1)
    return(0);
  if(indice_pos_dans_tab(&pos6, joueur.case_en_vie, 5) == -1 && indice_pos_dans_tab(&pos7, joueur.case_en_vie, 5) == -1)
    return(0);
  joueur.case_en_vie[0] = pos1;
  joueur.case_en_vie[1] = pos8;
  joueur.case_en_vie[2] = pos3;
  joueur.case_en_vie[3] = pos4;
  joueur.case_en_vie[4] = pos5;
  mise_a_jour_liste(bat, &joueur, &pos6);
  if(indice_pos_dans_tab(&pos1, joueur.case_en_vie, 5) != -1)
    return(0);
  if(indice_pos_dans_tab(&pos6, joueur.case_en_vie, 5) == -1 && indice_pos_dans_tab(&pos7, joueur.case_en_vie, 5) != -1)
    return(0);
  return(1);
}

int test_mise_a_jour_structure(){
  struct Batal bat;
  struct Grille grille;
  init_grille(&grille);
  int liste_indice[2] = {1, 1};
  struct Position pos1 = {3, 4};
  struct Position pos2 = {4, 4};
  struct Position pos3 = {7, 7};
  bat.taille = 2;
  bat.alignement = 10;
  bat.joueur = 2;
  bat.tab[0] = pos1;
  bat.tab[1] = pos2;
  grille.tab[34].tab[2] = 1;
  grille.tab[44].tab[2] = 1;
  mise_a_jour_structure(&grille, &bat, liste_indice, &pos3);
  if(bat.tab[0].ligne != 7 || bat.tab[0].colonne != 7 || bat.tab[1].ligne != 8 || bat.tab[1].colonne != 7)
    return(0);
  if(grille.tab[34].tab[2] != 0 || grille.tab[44].tab[2] != 0 || grille.tab[77].tab[2] != 1 || grille.tab[87].tab[2] != 1)
    return(0);
  init_grille(&grille);
  liste_indice[1] = 0;
  bat.taille = 2;
  bat.alignement = 10;
  bat.joueur = 2;
  bat.tab[0] = pos1;
  bat.tab[1] = pos2;
  grille.tab[34].tab[2] = 1;
  grille.tab[44].tab[2] = 1;
  mise_a_jour_structure(&grille, &bat, liste_indice, &pos3);
  if(bat.tab[0].ligne != 7 || bat.tab[0].colonne != 7 || bat.tab[1].ligne != 8 || bat.tab[1].colonne != 7)
    return(0);
  if(grille.tab[34].tab[2] != 0 || grille.tab[44].tab[2] != 0 || grille.tab[77].tab[2] != 1 || grille.tab[87].tab[2] != 0)
    return(0);
  return(1);
}
    

int main(){
  init_rand();
  printf("\n");
  printf("Test achievement 2 :\n");
  printf("\n");
  printf("test_init_tab_entier : ");
  affiche_resultat_test(test_init_tab_entier());
  printf("test_choix_du_bateau : ");
  affiche_resultat_test(test_choix_du_bateau());
  printf("test_verif_arrive_bateau : ");
  affiche_resultat_test(test_verif_arrive_bateau());
  printf("test_liste_case_possibles : ");
  affiche_resultat_test(test_liste_case_possibles());
  printf("test_deplacement_possible_uniquement : ");
  affiche_resultat_test(test_deplacement_possible_uniquement());
  printf("test_indice_pos_dans_tab : ");
  affiche_resultat_test(test_indice_pos_dans_tab());
  printf("test_mise_a_jour_liste : ");
  affiche_resultat_test(test_mise_a_jour_liste());
  printf("test_mise_a_jour_structure : ");
  affiche_resultat_test(test_mise_a_jour_structure());
  return(0);
}

