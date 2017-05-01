/**
 * @brief Implementacion de las reglas del juego
 *
 * @file game_rules.c
 * @author Laura Bernal 
 * @author Sandra Benitez
 * @version 1.0
 * @date 28-04-2017
 */

#include "types.h"
#include "game.h"
#include "dialogue.h"

/**
 * @cond
 */
#define N_RULES 7

typedef STATUS(*game_rule)(Game* game);

STATUS game_rules_no_rule(Game* game);
STATUS game_rules_switch_light_object(Game* game);
STATUS game_rules_switch_light_space(Game* game);
STATUS game_rules_hide_object(Game* game);
STATUS game_rules_lose_object (Game* game);
STATUS game_rules_switch_opening_link(Game* game);
STATUS game_rules_change_last_link(Game* game);

static game_rule game_rules_functions[N_RULES] = {
    game_rules_no_rule,
    game_rules_switch_light_object,
    game_rules_switch_light_space,
    game_rules_hide_object,
    game_rules_lose_object,
    game_rules_change_last_link,
    game_rules_switch_opening_link
};

int last_rule = 0;
/* 
 * @brief Ejecuta una regla aleatoria que está en la lista de reglas
 * @author Laura Bernal
 * @param game Un puntero a la estructura del juego
 * @return OK si todo ha ido bien o ERROR en caso contrario
 */
STATUS game_rules_run_random_rule(Game* game){
    int random_number = 0;
    Die * main_die = NULL;
    if(!game)
        return ERROR;
    
    main_die = game_get_die(game);
    die_set_faces(main_die, N_RULES);
    while((random_number = (die_roll(main_die) - 1)) == last_rule){
        random_number = (die_roll(main_die) - 1);    
    }
    last_rule = random_number;
    (*game_rules_functions[random_number])(game);
    
    return OK;
}

STATUS game_rules_no_rule(Game* game){
    return OK;
}

/*
 * @brief Enciende y apaga objetos
 * @author Sandra Benitez
 * @author Laura Bernal
 * @param game
 * @return Devuelve OK en caso de que se realice de forma correcta
 */
STATUS game_rules_switch_light_object(Game* game){
    int i, tam;
    Object* objects_illum[20] = {NULL};
    Object* aux = NULL;
    Die* die = NULL;
    int random_number = 0;
    die = game_get_die(game);
    if (!game)
        return ERROR;
    
    for (i=0, tam = 0; (aux = game_get_object_at(game, i)) != NULL; i++){
        
        if(object_Get_Illuminates(aux) == TRUE){
            objects_illum[tam] = aux;
            tam++;
        }
    }
    
    if(tam < 1){
        return ERROR;
    }
    die_set_faces(die, tam);
    random_number = (die_roll(die) - 1); /* el dado genera numeros de 1 a n */
    /* se necesitan numeros de o a n-1 */
    /* !object_Get_Light(objects_illum[random_number]));*/
    /* si está apagado lo niega entonces se enciende*/
    /* si está encendido lo niega entonces se apaga */
    object_Set_Light(objects_illum[random_number], !object_Get_Light(objects_illum[random_number]));
    dialogue_game_rule(game_get_dialogue(game), LIGHT_OBJECT);
    
    return OK; 
}

/*
 * @brief Enciende y apaga espacios
 * @author Sandra Benitez
 * @author Laura Bernal
 * @param game
 * @return Devuelve OK en caso de que se realice de forma correcta
 */
STATUS game_rules_switch_light_space(Game* game){
    int i;   
    int random_number = 0;
    Space* aux = NULL;
    Die* die = NULL;
    
    die = game_get_die(game);
    if (!game)
        return ERROR;
    
    for (i=0; (aux = game_get_space_at(game, i)) != NULL; i++);
    if(i < 1){
        return ERROR;
    }    
    die_set_faces(die, i);
    random_number = (die_roll(die) - 1);   
    space_set_iluminated(game_get_space(game, random_number), !space_get_iluminated(game_get_space(game, random_number)));
    dialogue_game_rule(game_get_dialogue(game), LIGHT_SPACE);
    return OK;
}

/*
 * @brief Esconde un objeto
 * @author Sandra Benitez
 * @author Laura Bernal
 * @param game
 * @return Devuelve OK en caso de que se realice de forma correcta
 */
 STATUS game_rules_hide_object(Game* game){
    int i, tam;
    Object* objects_hide[20] = {NULL};
    Object* aux = NULL;
    Die* die = NULL;
    int random_number = 0;
    
    die = game_get_die(game);
    if (!game)
        return ERROR;
    
    for (i=0, tam = 0; (aux = game_get_object_at(game, i)) != NULL; i++){
        
        if(object_Get_Hidden(aux) == FALSE){
            objects_hide[tam] = aux;
            tam++;
        }
    }
    if(tam < 1){
        return ERROR;
    }
    die_set_faces(die, tam);
    random_number = (die_roll(die) - 1); 

    object_Set_Hidden(objects_hide[random_number], !object_Get_Hidden(objects_hide[random_number]));
    dialogue_game_rule(game_get_dialogue(game), HIDE_OBJECT);
    return OK;
}


STATUS game_rules_lose_object (Game* game){
    int i, tam;
    Object* objects[20] = {NULL};
    Object* aux = NULL;
    Space* space = NULL;
    Player* player = NULL;
    Die* die = NULL;
    int random_number = 0;
    
    if (!game)
        return ERROR;
    die = game_get_die(game);
    player = game_get_player(game);
    space = game_get_space(game, player_Get_Location(player));
    /* Buscar los objetos que tiene el jugador*/
    for (i=0, tam = 0; (aux = game_get_object_at(game, i)) != NULL; i++){
        if (player_Has_Object(player, object_Get_Id(aux)) == TRUE && object_Get_Id(aux) != 16){
            objects[tam] = aux; 
            tam++;
        }
    }
    
    if(tam < 1)/* si no tiene ninguno, que no haga nada */
        return ERROR;
    
    die_set_faces(die, tam);
    random_number = (die_roll(die) - 1); 
    aux = objects[random_number];
    player_Remove_Object(player, object_Get_Id(aux)); /* Se lo quita al jugador */
    space_add_object(space, object_Get_Id(aux)); /* Lo deja en la casilla */
    object_Set_Hidden(aux, TRUE); /* Y lo oculta */
    dialogue_game_rule(game_get_dialogue(game), LOSE_OBJECT);
    return OK;
}

/*
 * @brief Abre y cierra links
 * @author Sandra Benitez
 * @author Laura Bernal
 * @param game
 * @return Devuelve OK en caso de que se realice de forma correcta
 */

 
 STATUS game_rules_switch_opening_link(Game* game){
    long ids[5] = {1, 4, 6, 11, 12};
    Die* die = NULL;
    Link* link = NULL;
    int random_number = 0;
    die = game_get_die(game);
    if (!game)
        return ERROR;
    die_set_faces(die, 5);
    random_number = (die_roll(die) - 1); 
    link = game_get_link(game,ids[random_number]);
    if(link_get_state(link) == OPENED){
        link_set_state(link, CLOSED);
    }else{
        link_set_state(link, OPENED);
    }
    dialogue_game_rule(game_get_dialogue(game), CLOSE_LINK);
    return OK;
}


/* Cambia de sitio la entrada a la ultima sala de la casilla 4 a la casilla 6*/
STATUS game_rules_change_last_link(Game* game){
    Space* space = NULL;
    Object* object = NULL;
    int i;
    
    Id link_id = NO_ID;
    if(!game)
        return ERROR;
    space = game_get_space(game, 4);
    for(i = 0; (object =  game_get_object_at(game,i)) != NULL; i++){
        if(object_Get_Id(object) == 13){
            break;
        }
    }
    if(!space)
        return ERROR;
    link_id = space_get_down(space);
    if(link_id != NO_ID && link_id != -2){
        space_set_down(space, -2);
        space = game_get_space(game, 6);
        space_set_down(space, 12);
        object_Set_Open(object, 12);
    }else if(link_id == -2){
        space_set_down(space, 6);
        space = game_get_space(game, 6);
        space_set_down(space, -2);
        object_Set_Open(object, 6);
    }
    dialogue_game_rule(game_get_dialogue(game), CHANGE_LAST_LINK);
    return OK;
}

/**
 * @endcond
 */