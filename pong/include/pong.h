/*
*	copyright Martin Hundrup
*/

/*
*	pong.h contains the main header for the Pong game.
*/

#ifndef PONG_H
#define PONG_H

#include "../../ascii-engine/include/object.h"

// displays the title screen
// returns the number of players
// 0 = quit, 1 = player vs AI, 2 = player vs player
int title_screen(void);

// starts a game of pong
// num_players: 1 = player vs AI, 2 = player vs player
void play_pong(int num_players);

#endif // PONG_H