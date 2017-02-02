#include "../src/achievement3.h"

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

int test_init_monstre(){
  struct Monstre monstre;
  init_monstre(&monstre);
  return(monstre.agresse == 0 && monstre.tab_joueur_agresse[0] == 0 && monstre.tab_joueur_agresse[1] == 0);
}

int test_placer_monstre(){
  struct Position pos = {1, 5};
  struct Grille grille;
  struct Monstre monstre;
  init_monstre(&monstre);
  init_grille(&grille);
  monstre.pos = pos;
  placer_monstre(&monstre, &grille);
  if(grille.tab[15].tab[3] != 1)
    return(0);
  struct Position pos1 = {3, 5};
  monstre.pos = pos1;
  placer_monstre(&monstre, &grille);
  if(grille.tab[35].tab[3] != 1)
    return(0);
  return(1);
}

int test_monstre_oblitere(){
  int n;
  struct Monstre monstre;
  struct Grille grille;
  struct Joueur j;
  struct Position pos1 = {1, 1};
  struct Position pos2 = {2, 1};
  struct Position pos3 = {0, 1};
  struct Position pos4 = {1, 2};
  struct Position pos5 = {1, 0};
  struct Position pos6 = {6, 5};
  struct Position pos = {4, 4};
  init_monstre(&monstre);
  init_grille(&grille);
  init_joueur(&j, 1);
  j.taille  = 6;
  j.case_en_vie[0] = pos1;
  j.case_en_vie[1] = pos2;
  j.case_en_vie[2] = pos3;
  j.case_en_vie[3] = pos4;
  j.case_en_vie[4] = pos5;
  j.case_en_vie[5] = pos6;
  grille.tab[11].tab[1] = 1;
  grille.tab[21].tab[1] = 1;
  grille.tab[1].tab[1] = 1;
  grille.tab[12].tab[1] = 1;
  grille.tab[10].tab[1] = 1;
  grille.tab[65].tab[1] = 1;
  grille.tab[65].tab[0] = -1;
  monstre.pos = pos1;
  n = monstre_oblitere(&grille, &monstre, &j, &j);
  if(n != 5 && grille.tab[11].tab[0] != -1 && grille.tab[21].tab[0] != -1 && grille.tab[1].tab[0] != -1 && grille.tab[12].tab[0] != -1 && grille.tab[10].tab[0] != -1)
    return(0);
  monstre.pos = pos;
  n = monstre_oblitere(&grille, &monstre, &j, &j);
  if(n != 0)
    return(0);
  monstre.pos = pos6;
  n = monstre_oblitere(&grille, &monstre, &j, &j);
  if(n != 0)
    return(0);
  return(1);
}

int test_case_plus_proche_monstre(){
  int distance = 100;
  int nombre = 0;
  struct Position tab[10];
  struct Monstre monstre;
  struct Joueur j;
  struct Position pos1 = {1, 1};
  struct Position pos2 = {2, 1};
  struct Position pos3 = {0, 1};
  struct Position pos4 = {1, 2};
  struct Position pos5 = {1, 0};
  struct Position pos6 = {7, 5};
  struct Position pos = {5, 2};
  struct Position pos7 = {6, 5};
  init_monstre(&monstre);
  init_joueur(&j, 1);
  j.taille  = 6;
  j.case_en_vie[0] = pos1;
  j.case_en_vie[1] = pos2;
  j.case_en_vie[2] = pos3;
  j.case_en_vie[3] = pos4;
  j.case_en_vie[4] = pos5;
  j.case_en_vie[5] = pos6;
  monstre.pos = pos;
  case_plus_proche_monstre(&j, &monstre, tab, &distance, &nombre);
  if(tab[0].ligne != pos2.ligne && tab[0].colonne != pos2.colonne && tab[1].ligne != pos4.ligne && tab[1].colonne != pos4.colonne && distance != 4)
    return(0);
  distance = 100;
  monstre.pos = pos7;
  case_plus_proche_monstre(&j, &monstre, tab, &distance, &nombre);
  if(tab[0].ligne != pos6.ligne && tab[0].colonne != pos6.colonne && distance != 1)
    return(0);
  return(1);
}

int test_deplacement_monstre_pas_agresse(){
  struct Grille grille;
  struct Monstre monstre;
  struct Joueur j1, j2;
  init_grille(&grille);
  struct Position pos = {8, 3};
  struct Position pos1 = {6, 2};
  struct Position pos2 = {2, 3};
  struct Position pos3 = {9, 1};
  struct Position pos4 = {0, 0};
  struct Position pos5 = {8, 6};
  struct Position pos6 = {1, 4};
  struct Position pos7 = {0, 2};
  monstre.pos = pos;
  j1.taille = 3;
  j2.taille = 3;
  j1.case_en_vie[0] = pos1;
  j1.case_en_vie[1] = pos2;
  j1.case_en_vie[2] = pos3;
  j2.case_en_vie[0] = pos4;
  j2.case_en_vie[1] = pos5;
  j2.case_en_vie[2] = pos6;
  deplacement_monstre_pas_agresse(&j1, &j2, &monstre, &grille);
  if((monstre.pos.ligne != 8 && monstre.pos.colonne != 4) && (monstre.pos.ligne != 7 && monstre.pos.colonne != 3))
    return(0);
  monstre.pos = pos7;
  deplacement_monstre_pas_agresse(&j1, &j2, &monstre, &grille);
  if(monstre.pos.ligne != 0 && monstre.pos.colonne != 1)
    return(0);
  return(1);
}

int test_bateau_le_plus_proche(){
  int test;
  struct Joueur joueur;
  struct Monstre monstre;
  struct Position pos0 = {3, 3};
  struct Position pos1 = {4, 3};
  struct Position pos2 = {5, 3};
  struct Position pos3 = {6, 3};
  struct Position pos4 = {7, 3};
  struct Position pos5 = {0, 5};
  struct Position pos6 = {0, 6};
  struct Position pos7 = {0, 7};
  struct Position pos8 = {0, 8};
  struct Position pos9 = {8, 3};
  struct Position pos10 = {8, 4};
  struct Position pos11 = {8, 5};
  struct Position pos12 = {2, 0};
  struct Position pos13 = {3, 0};
  struct Position pos14 = {4, 2};
  joueur.tab[0].taille = 5;
  joueur.tab[1].taille = 4;
  joueur.tab[2].taille = 3;
  joueur.tab[3].taille = 2;
  joueur.tab[4].taille = 1;
  joueur.tab[0].tab[0] = pos0;
  joueur.tab[0].tab[1] = pos1;
  joueur.tab[0].tab[2] = pos2;
  joueur.tab[0].tab[3] = pos3;
  joueur.tab[0].tab[4] = pos4;
  joueur.tab[1].tab[0] = pos5;
  joueur.tab[1].tab[1] = pos6;
  joueur.tab[1].tab[2] = pos7;
  joueur.tab[1].tab[3] = pos8;
  joueur.tab[2].tab[0] = pos9;
  joueur.tab[2].tab[1] = pos10;
  joueur.tab[2].tab[2] = pos11;
  joueur.tab[3].tab[0] = pos12;
  joueur.tab[3].tab[1] = pos13;
  joueur.tab[4].tab[0] = pos14;
  joueur.case_en_vie[0] = pos0;
  joueur.case_en_vie[1] = pos1;
  joueur.case_en_vie[2] = pos2;
  joueur.case_en_vie[3] = pos3;
  joueur.case_en_vie[4] = pos4;
  joueur.case_en_vie[5] = pos5;
  joueur.case_en_vie[6] = pos6;
  joueur.case_en_vie[7] = pos7;
  joueur.case_en_vie[8] = pos8;
  joueur.case_en_vie[9] = pos9;
  joueur.case_en_vie[10] = pos10;
  joueur.case_en_vie[11] = pos11;
  joueur.case_en_vie[12] = pos12;
  joueur.case_en_vie[13] = pos13;
  joueur.case_en_vie[14] = pos14;
  joueur.taille = 15;
  joueur.joueur = 1;
  struct Position pos = {8, 9};
  monstre.pos = pos;
  if(bateau_le_plus_proche(&monstre, &joueur) != 2)
    return(0);
  monstre.pos.ligne = 5;
  monstre.pos.colonne = 6;
  test = bateau_le_plus_proche(&monstre, &joueur);
  if(test != 2 && test != 0)
    return(0);
  monstre.pos.ligne = 2;
  monstre.pos.colonne = 9;
  test = bateau_le_plus_proche(&monstre, &joueur);
  if(test != 1)
    return(0);
  return(1);
}

int test_position_dans_tab(){
  struct Position pos1 = {1, 3};
  struct Position pos2 = {0, 0};
  struct Position pos3 = {2, 6};
  struct Position pos4 = {8, 9};
  struct Position pos5 = {3, 5};
  struct Position pos6 = {2, 2};
  struct Position tab[6];
  tab[0] = pos1;
  tab[1] = pos2;
  tab[2] = pos3;
  tab[3] = pos4;
  tab[4] = pos5;
  tab[5] = pos5;
  if(position_dans_tab(tab, &pos3, 6) != 1)
    return(0);
  if(position_dans_tab(tab, &pos6, 6) != 0)
    return(0);
  if(position_dans_tab(tab, &pos5, 6) != 1)
    return(0);
  return(1);
}

int test_position_dans_tab_et_possible(){
  struct Position pos1 = {1, 3};
  struct Position pos2 = {0, 0};
  struct Position pos3 = {2, 6};
  struct Position pos4 = {8, 9};
  struct Position pos5 = {3, 5};
  struct Position pos7 = {3, 2};
  struct Position pos8 = {4, 2};
  struct Position pos9 = {5, 2};
  struct Position test1 = {10, 8};
  struct Position test2 = {7, 8};
  struct Position tab[6];
  tab[0] = pos1;
  tab[1] = pos2;
  tab[2] = pos3;
  tab[3] = pos4;
  tab[4] = pos5;
  tab[5] = pos5;
  struct Batal bat;
  bat.taille = 3;
  bat.joueur = 1;
  bat.tab[0] = pos7;
  bat.tab[1] = pos8;
  bat.tab[2] = pos9;
  struct Grille grille;
  init_grille(&grille);
  grille.tab[32].tab[1] = 1;
  grille.tab[42].tab[1] = 1;
  grille.tab[52].tab[1] = 1;
  if(position_dans_tab_et_possible(tab, &test1, 6, &bat, &grille) != 0)
    return(0);
  if(position_dans_tab_et_possible(tab, &pos8, 6, &bat, &grille) != 0)
    return(0);
  grille.tab[42].tab[0] = -1;
  if(position_dans_tab_et_possible(tab, &pos8, 6, &bat, &grille) != 1)
    return(0);
  if(position_dans_tab_et_possible(tab, &test2, 6, &bat, &grille) != 1)
    return(0);
  grille.tab[32].tab[1] = 0;
  if(position_dans_tab_et_possible(tab, &pos7, 6, &bat, &grille) != 1)
    return(0);
  return(1);
}

int test_case_autour_du_batal(){
  struct Grille grille;
  init_grille(&grille);
  grille.tab[55].tab[1] = 1;
  grille.tab[56].tab[1] = 1;
  struct Batal bat;
  struct Position pos = {5, 5};
  init_batal(&bat, 2, &pos, 1, 1);
  struct Position pos1 = case_autour_du_batal(&bat, &grille);
  if((pos1.ligne != 4 && pos1.colonne != 5) && (pos1.ligne != 4 && pos1.colonne != 6) && (pos1.ligne != 5 && pos1.colonne != 4) && (pos1.ligne != 5 && pos1.colonne != 7) && (pos1.ligne != 6 && pos1.colonne != 5) && (pos1.ligne != 6 && pos1.colonne != 6))
    return(0);
  grille.tab[55].tab[0] = -1;
  struct Position pos2 = case_autour_du_batal(&bat, &grille);
  if((pos2.ligne != 5 && pos2.colonne != 5) && (pos2.ligne != 4 && pos2.colonne != 6)&& (pos1.ligne != 5 && pos1.colonne != 7) && (pos1.ligne != 6 && pos1.colonne != 6))
    return(0);
  return(1);
}

int test_deplacement_monstre_agresse(){
  struct Monstre monstre;
  struct Joueur j1, j2;
  struct Grille grille;
  struct Position pos = {1, 3};
  struct Position pos1 = {3, 4};
  struct Position pos2 = {6, 4};
  struct Position pos3 = {6, 5};
  struct Position pos4 = {7, 8};
  struct Position pos5 = {0, 0};
  struct Position pos6 = {0, 1};
  init_grille(&grille);
  j1.joueur = 1;
  j2.joueur = 2;
  j1.taille = 0;
  j2.taille = 0;
  monstre.pos = pos;
  deplacement_monstre_agresse(&grille, &monstre, &j1, &j2, NULL, 0);
  if(monstre.pos.ligne != pos.ligne && monstre.pos.colonne != pos.colonne)
    return(0);
  j1.taille = 3;
  j2.taille = 3;
  j1.tab[0].taille = 1;
  j1.tab[1].taille = 2;
  j2.tab[0].taille = 1;
  j2.tab[1].taille = 2;
  j1.case_en_vie[0] = pos1;
  j1.case_en_vie[1] = pos2;
  j1.case_en_vie[2] = pos3;
  j2.case_en_vie[0] = pos4;
  j2.case_en_vie[1] = pos5;
  j2.case_en_vie[2] = pos6;
  j1.tab[0].tab[0] = pos1;
  j1.tab[1].tab[0] = pos2;
  j1.tab[1].tab[1] = pos3;
  j2.tab[0].tab[0] = pos4;
  j2.tab[1].tab[0] = pos5;
  j2.tab[1].tab[1] = pos6;
  j1.tab[0].joueur = 1;
  j1.tab[1].joueur = 1;
  j2.tab[0].joueur = 2;
  j2.tab[1].joueur = 2;
  monstre.tab_joueur_agresse[0] = 1;
  grille.tab[34].tab[1] = 1;
  grille.tab[64].tab[1] = 1;
  grille.tab[65].tab[1] = 1;
  grille.tab[78].tab[2] = 1;
  grille.tab[0].tab[2] = 1;
  grille.tab[1].tab[2] = 1;
  for(int i = 0; i < 20; i++){
    monstre.tab_joueur_agresse[0] = 1;
    monstre.pos = pos;
    deplacement_monstre_agresse(&grille, &monstre, &j1, &j2, NULL, 0);
    if(monstre.pos.ligne != 2 && monstre.pos.colonne != 4 && monstre.pos.ligne != 4 && monstre.pos.colonne != 4 && monstre.pos.ligne != 3 && monstre.pos.colonne != 3 && monstre.pos.ligne != 3 && monstre.pos.colonne != 5)
      return(0);
  }
  for(int i = 0; i < 20; i++){
    monstre.pos = pos;
    monstre.tab_joueur_agresse[0] = 1;
    monstre.tab_joueur_agresse[1] = 1;
    deplacement_monstre_agresse(&grille, &monstre, &j1, &j2, NULL, 0);
    if(monstre.pos.ligne != 2 && monstre.pos.colonne != 4 && monstre.pos.ligne != 4 && monstre.pos.colonne != 4 && monstre.pos.ligne != 3 && monstre.pos.colonne != 3 && monstre.pos.ligne != 3 && monstre.pos.colonne != 5 && monstre.pos.ligne != 1 && monstre.pos.colonne != 0 && monstre.pos.ligne != 1 && monstre.pos.colonne != 1 && monstre.pos.ligne != 0 && monstre.pos.colonne != 2)
    return(0);
  }
  return(1);			      
}

int main(){
  init_rand();
  printf("\n");
  printf("Test achievement 3 :\n");
  printf("\n");
  printf("test_init_monstre : ");
  affiche_resultat_test(test_init_monstre());
  printf("test_placer_monstre : ");
  affiche_resultat_test(test_placer_monstre());
  printf("test_monstre_oblitere : ");
  affiche_resultat_test(test_monstre_oblitere());
  printf("test_case_plus_proche_monstre : ");
  affiche_resultat_test(test_case_plus_proche_monstre());
  printf("test_deplacement_monstre_pas_agresse : ");
  affiche_resultat_test(test_deplacement_monstre_pas_agresse());
  printf("test_bateau_le_plus_proche : ");
  affiche_resultat_test(test_bateau_le_plus_proche());
  printf("test_position_dans_tab : ");
  affiche_resultat_test(test_position_dans_tab());
  printf("test_position_dans_tab_et_possible : ");
  affiche_resultat_test(test_position_dans_tab_et_possible());
  printf("test_case_autour_du_batal : ");
  affiche_resultat_test(test_case_autour_du_batal());
  printf("test_deplacement_monstre_agresse : ");
  affiche_resultat_test(test_deplacement_monstre_agresse());
  return(0);
}
