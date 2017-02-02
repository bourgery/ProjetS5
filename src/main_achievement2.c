#include "achievement2.h"

int main(int argc, char *argv[]){
  int gagnant;
  char *s = "";
  if(atoi(argv[1]) == 0){
    gagnant = achievement2(NULL, atoi(argv[1]));
    switch(gagnant){
    case(0):
      s = "Egalite";
      break;
    case(1):
      s = "Joueur 1";
      break;
    case(2):
      s = "Joueur 2";
      break;
    }
    printf("%s\n", s);
    return(0);
  }
  SDL_Surface *ecran = NULL, *texte = NULL;
  TTF_Font *police = NULL;
  SDL_Color noir = {255, 255, 255};
  SDL_Rect pos;
  pos.x = NB_PIXEL_CASE * NB_COLONNES / 2 - NB_PIXEL_CASE;
  pos.y = NB_PIXEL_CASE * NB_LIGNES / 2 - NB_PIXEL_CASE;
  TTF_WasInit();
  TTF_Init();
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Achievement2", NULL);
  ecran = SDL_SetVideoMode(NB_PIXEL_CASE * NB_COLONNES, NB_PIXEL_CASE * NB_LIGNES, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  police = TTF_OpenFont("doc/angelina.TTF", NB_PIXEL_CASE);
  gagnant = achievement2(ecran, atoi(argv[1]));
  switch(gagnant){
  case(0):
    s = "Egalite";
    break;
  case(1):
    s = "Joueur 1";
    break;
  case(2):
    s = "Joueur 2";
    break;
  }
  texte = TTF_RenderText_Blended(police, s, noir);
  SDL_BlitSurface(texte, NULL, ecran, &pos);
  SDL_Flip(ecran);
  pause();
  TTF_CloseFont(police);
  TTF_Quit();
  SDL_FreeSurface(texte);
  SDL_Quit();
}

