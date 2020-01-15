// Apricots finish game routine
// Author: M.D.Snellgrove
// Date: 26/3/2002
// History:

// Changes by M Harman for Windows version, June 2003:
//   Changes for graphics and font related stuff.

// Changes by M Snellgrove 15/7/2003
//   SDLfont used for fonts

#include "apricots.h"

// Draw a winnerbox
extern SDL_Surface *ScreenSurface;
void winnerbox(gamedata &g, int winner, int player, int y, int control){

  int boxcolour = 4; // red for losers
  if (player == control){
    boxcolour = 13; // green if winner
  }
/*
  SDL_Rect rect;
    rect.x = 200;
    rect.y = 64+y;
    rect.w = 240;
    rect.h = 80;
  SDL_FillRect(g.virtualscreen,&rect,1);
    rect.x = 201;
    rect.y = 65+y;
    rect.w = 238;
    rect.h = 78;
  SDL_FillRect(g.virtualscreen,&rect,boxcolour);
*/

  SDL_Rect rect;
    rect.x = 50;
    rect.y = 64+y;
    rect.w = 220;
    rect.h = 80;
  SDL_FillRect(g.virtualscreen,&rect,1);
    rect.x = 51;
    rect.y = 65+y;
    rect.w = 218;
    rect.h = 78;
  SDL_FillRect(g.virtualscreen,&rect,boxcolour);

  if (player == control){
    char winstring[] = "You win!";
    //g.whitefont.writemask(g.virtualscreen, 288, 72+y, winstring);
    //char congrats[] = "Congratulations";
    //g.whitefont.writemask(g.virtualscreen, 260, 122+y, congrats);
    g.whitefont.writemask(g.virtualscreen, 130, 72+y, winstring);
    char congrats[] = "Congratulations";
    g.whitefont.writemask(g.virtualscreen, 100, 122+y, congrats);
  }else{
    char losestring[] = "You lose";
    //g.whitefont.writemask(g.virtualscreen, 288, 72+y, losestring);
    g.whitefont.writemask(g.virtualscreen, 130, 72+y, losestring);
    if (control > 0){
      char winstring[] = "Player x wins";
      winstring[7] = '0' + control;
      //g.whitefont.writemask(g.virtualscreen, 268, 112+y, winstring);
      g.whitefont.writemask(g.virtualscreen, 110, 112+y, winstring);
    }else{
      char winstring[] = "Computer (Plane x) wins";
      winstring[16] = '0' + winner;
      //g.whitefont.writemask(g.virtualscreen, 228, 112+y, winstring);
      g.whitefont.writemask(g.virtualscreen, 70, 112+y, winstring);
    }
  }

}

// Main finish game routine

void finish_game(gamedata &g){

// Stop enginenoise
  g.sound.stop(0);
  g.sound.stop(1);
// Display winnerbox
  if (g.winner > 0 && !demo){
    winnerbox(g, g.winner, 1, 0, g.planeinfo[g.winner].control);
    if (g.players == 2){
      winnerbox(g, g.winner, 2, 240, g.planeinfo[g.winner].control);
    }
// Update display
    SDL_Rect rect;
      rect.x = 0;
      rect.y = 0;
      rect.w = 320;
      rect.h = 240;
    // SDL_BlitSurface(g.virtualscreen, &rect, g.physicalscreen, NULL);
    //SDL_Flip(g.physicalscreen);
	if(SDL_MUSTLOCK(ScreenSurface)) SDL_LockSurface(ScreenSurface);
    // SDL_Surface *p = SDL_ConvertSurface(g.physicalscreen, ScreenSurface->format, 0);
		SDL_Surface *p = SDL_ConvertSurface(g.virtualscreen, ScreenSurface->format, 0);

    // SDL_BlitSurface(p, NULL, ScreenSurface, NULL);
    SDL_BlitSurface(p, &rect, ScreenSurface, NULL);
		// SDL_SoftStretch(p, NULL, ScreenSurface, NULL);
	if(SDL_MUSTLOCK(ScreenSurface)) SDL_UnlockSurface(ScreenSurface);
		SDL_Flip(ScreenSurface);
		SDL_FreeSurface(p);


    //SDL_UpdateRect(g.physicalscreen, 0, 0, 0, 0);
    g.sound.play(SOUND_FINISH);
// Wait 4 Seconds
   int then = time(0);
   while (time(0) - then < 4){ if(demo) break;}
  }
// Clean up linkedlists
  g.radar.clearlist();
  g.gun.clearlist();
  g.p.clearlist();
  g.dp.clearlist();
  g.explosion.clearlist();
  g.flame.clearlist();
  g.smoke.clearlist();
  g.fall.clearlist();
  g.shot.clearlist();
  g.drakgun.clearlist();
  g.laser.clearlist();

}
