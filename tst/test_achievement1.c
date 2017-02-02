#include "../src/achievement1.h"

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
int test_abs(){
  if(abs(-8) != 8)
    return(0);
  if(abs(0) != 0)
    return(0);
  if(abs(1) != 1)
    return(0);
  return(1);
}

int test_distance_minimale(){
  struct Grille grille;
  init_grille(&grille);
  struct Position pos1 = {0, 0};
  struct Position pos2 = {9, 9};
  struct Position pos3 = {1, 4};
  struct Position pos4 = {4, 1};
  struct Position pos5 = {4, 7};
  struct Position pos6 = {6, 8};
  struct Position pos7 = {0, 9};
  struct Position pos8 = {0, 1};
  if(distance_minimale(&pos1, &pos2) != 18)
    return(0);
  if(distance_minimale(&pos2, &pos3) != 13)
    return(0);
  if(distance_minimale(&pos3, &pos4) != 6)
    return(0);
  if(distance_minimale(&pos5, &pos6) != 3)
    return(0);
  if(distance_minimale(&pos6, &pos7) != 7)
    return(0);
  if(distance_minimale(&pos8, &pos1) != 1)
    return(0);
  return(1);
}

int test_arrive_torpille(){
  struct Joueur joueur;
  joueur.taille = 5;
  struct Position test = {0, 0};
  struct Position pos1 = {1, 5};
  struct Position pos2 = {1, 6};
  struct Position pos3 = {1, 7};
  struct Position pos4 = {3, 2};
  struct Position pos5 = {4, 2};
  joueur.case_en_vie[0] = pos1; 
  joueur.case_en_vie[1] = pos2; 
  joueur.case_en_vie[2] = pos3; 
  joueur.case_en_vie[3] = pos4; 
  joueur.case_en_vie[4] = pos5;
  struct Position pos6 = {3, 4};
  arrive_torpille(&pos6, &joueur, &test);
  if((test.ligne != 3) || (test.colonne != 2))
    return(0);
  struct Position pos7 = {4, 7};
  arrive_torpille(&pos7, &joueur, &test);
  if((test.ligne != 1) || (test.colonne != 7))
    return(0);
  struct Position pos8 = {0, 0};
  arrive_torpille(&pos8, &joueur, &test);
  if((test.ligne != 3) || (test.colonne != 2))
    return(0);
  return(1);
}
  
int main(){
  init_rand();
  printf("\n");
  printf("Test achievement 1 :\n");
  printf("\n");
  printf("test_abs : ");
  affiche_resultat_test(test_abs());
  printf("test_distance_minimale : ");
  affiche_resultat_test(test_distance_minimale());
  printf("test_arrive_torpille : ");
  affiche_resultat_test(test_arrive_torpille());
  return(0);
}
