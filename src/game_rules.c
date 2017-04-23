#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "types.h"
#include "game.h"
#define N_RULES 1

typedef STATUS(*game_rule)(Game* game);

STATUS game_rules_no_rule(Game* game);

static game_rule game_rules_functions[N_RULES] = {
    game_rules_no_rule
};

STATUS game_run_random_rule(Game* game){
    int random_number;
    /* Usar dado, esto es solo una prueba*/
    random_number = 1;
    /*****************/
    (*game_rules_functions[random_number])(game);
    
    return OK;
}

STATUS game_rules_no_rule(Game* game){
    return OK;
}


#endif