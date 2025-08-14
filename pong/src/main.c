/*
*	copyright Martin Hundrup
*/

/*
*	main.c contains the entry point for the Pong game.
*/

#include "../include/pong.h"


int main(void) {
   
  srand(time(NULL)); // Seed the random number generator

  // int num_players = title_screen(); // Show title screen and get number of players
  // if (num_players == 0) {
  //   return 0; // Exit if user chose to quit
  // }

  //play_pong(num_players); // Start the game
  
  play_pong(0);

  return 0;
}