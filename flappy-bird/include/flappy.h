/*
*	copyright Martin Hundrup
*/

/*
*	flappy.h contains the main header for the Flappy Bird game.
*/

#ifndef FLAPPY_H
#define FLAPPY_H

#define TITLE_FLAPPY { \
  "#####  #       ###   ####   ####   #   #", \ 
  "#      #      #   #  #   #  #   #   # # ", \
  "###    #      #####  ####   ####     #  ", \
  "#      #      #   #  #      #        #  ", \
  "#      #####  #   #  #      #        #  ", \
};

#define TITLE_BIRD { \
  "####   #####  ####   #### ", \ 
  "#   #    #    #   #  #   #", \
  "####     #    ####   #   #", \
  "#   #    #    #   #  #   #", \
  "####   #####  #   #  #### ", \
};

#include "../../ascii-engine/include/object.h"

#endif // FLAPPY_H