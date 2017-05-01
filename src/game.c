/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * @file game.c
 * @author Profesores PPROG
 * @author Javier Bernardo
 * @author Mihai Blidaru
 * @author Laura Bernal
 * @author Sandra Benitez
 * @version 2.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

/*
 * Cabeceras libc
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*
 * Cabeceras propias
 */
#include "die.h"
#include "game.h"
#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "dialogue.h"
#include "game_management.h"

/**
 * @cond HIDDEN_SYMBOLS
 * Número de funciones callbacks
 *
 */
#define N_CALLBACK 15

/**
 * @brief Define the function type for the callbacks
 */
typedef STATUS(*callback_fn)(Game* game, Command* cmd);

/**
 * Ancho de una casilla
 */
#define SPACE_DRAW_WIDTH 34

/*
 *
 * @brief Estructura de game
 *
 */
struct _Game {
    Player* player;                  /*!< Puntero a la estructura player */
    Object* objects[MAX_OBJECTS];    /*!< Puntero a la estructura object */
    Space* spaces[MAX_SPACES];       /*!< Puntero a la estructura space */
    Link* links[MAX_LINK];           /*!< Puntero a la estructura link */
    Die* die;                        /*!< Puntero a la estructura die */
    Space* last_space;               /*!< Puntero al ultimo space */
    Object* last_object;             /*!< Puntero al ultimo objeto */
    Dialogue* dialogue;
};

/**
 * @endcond
 */
/*
 * Lista de los callbaks de cada comando del juego.
 */
STATUS game_callback_unknown(Game* game, Command* cmd); /*!< UNKNOWN @private */
STATUS game_callback_quit(Game* game, Command* cmd); /*!< QUIT @private */
STATUS game_callback_take(Game* game, Command* cmd); /*!< TAKE @private */
STATUS game_callback_leave(Game* game, Command* cmd); /*!< LEAVE @private */
STATUS game_callback_roll(Game* game, Command* cmd); /*!< ROLL @private */
STATUS game_callback_go(Game* game, Command* cmd); /*!< GO @private */
STATUS game_callback_inspect(Game* game, Command* cmd); /*!< INSPECT @private */
STATUS game_callback_turn_on(Game* game, Command* cmd); /*!< TURNON @private */
STATUS game_callback_turn_off(Game* game, Command* cmd); /*!< TURNOFF @private */
STATUS game_callback_open(Game* game, Command* cmd);/*!< OPEN @private */
STATUS game_callback_save(Game* game, Command* cmd);/*!< SAVE @private */
STATUS game_callback_load(Game* game, Command* cmd);/*!< LOAD @private */
STATUS game_callback_dir(Game* game, Command* cmd);/*!< DIR @private */
STATUS game_callback_help(Game* game, Command* cmd);/*!< HELP @private */
STATUS game_callback_attack(Game* game, Command* cmd);/*!< ATTACK @private */

void game_clear_inspect (Game *game); /*!< @private */
Object* game_get_Object_byName(Game* game, char* name); /*!< @private */
STATUS game_set_player_location(Game* game, Id player_location); /*!< @private */

static callback_fn game_callback_fn_list[N_CALLBACK] = {
    game_callback_unknown,
    game_callback_quit,
    game_callback_take,
    game_callback_leave,
    game_callback_roll,
    game_callback_go,
    game_callback_inspect,
    game_callback_turn_on,
    game_callback_turn_off,
    game_callback_open,
    game_callback_save,
    game_callback_load,
    game_callback_dir,
    game_callback_help,
    game_callback_attack
};

/*
 * @brief Inicializa los datos del juego
 *      Esta función inicializa los espacios, crea e inicializa
 *      el jugador, los objetos y el dado
 * @author Profesores PPROG
 * @author Mihai Blidaru
 *
 * @return OK si todo ha ido bien. En caso contrario ERROR
 */
Game* game_create() {
    int i;
    Game* game = NULL;
    if(!(game = calloc(1, sizeof(Game)))){
        return NULL;
    }

    for (i = 0; i < MAX_SPACES; i++) {
        game->spaces[i] = NULL;
    }

    if (!(game->die = die_create(DIE_ID))){
        game_destroy(game);
        return NULL;
    }
    die_set_faces(game->die, 6);
    game->last_object = NULL;
    game->last_space = NULL;

    for (i = 0; i < MAX_OBJECTS; i++)
        game->objects[i] = NULL;

    /* Inicializar la estructura del jugador */
    game->dialogue = dialogue_ini();
    player_Set_Name(game->player, "Player 1");
    player_Set_Id(game->player, GENERIC_ID);
    return game;

}

/*
 * @brief Destruye la estructura game.
 *      Se encarga de liberar la memoria reservada por los elementos del juego
 *      spaces, player, objects y die.
 *
 * @author Profesores PPROG
 * @author Mihai Blidaru
 *
 * @param game Puntero a la estructura del juego.
 * @return OK si se ha podido hacer todo correctamente. ERROR en caso contrario.
 */
STATUS game_destroy(Game* game) {
    int i = 0;

    if (!game)
        return ERROR;

    /* libera memoria de los espacios */
    for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
        space_destroy(game->spaces[i]);
    }

    /* lo mismo para los objetos*/
    for (i = 0; i < MAX_OBJECTS; i++) {
        object_destroy(game->objects[i]);
    }

    for (i = 0; i < MAX_LINK; i++) {
        link_destroy(game->links[i]);
    }

    /* y se libera la memoria usada por el dado y el jugador */
    die_destroy(game->die);
    player_destroy(game->player);
    dialogue_destroy(game->dialogue);
    free(game);

    return OK;
}

/*
 * @brief Añade un espacio al juego
 *
 * @author Profesores PPROG
 *
 * @param game El puntero al juego
 * @param space Un puntero al espacio
 * @return OK si se ha añadido correctamente, sino ERROR
 */
STATUS game_add_space(Game* game, Space* space) {
    int i = 0;

    if (!game || !space) {
        return ERROR;
    }

    while ((i < MAX_SPACES) && (game->spaces[i] != NULL)) {
        i++;
    }

    if (i >= MAX_SPACES) {
        return ERROR;
    }

    game->spaces[i] = space;

    return OK;
}


/*
 * @brief Añade un objeto al juego
 *
 * @author Javier Bernardo
 *
 * @param game El puntero al juego
 * @param object Un puntero al objeto
 * @return OK si se ha añadido correctamente, sino ERROR
 */
STATUS game_add_object(Game* game, Object* object) {
    int i = 0;

    if (!game || !object) {
        return ERROR;
    }

    while ((i < MAX_OBJECTS) && (game->objects[i] != NULL)) {
        i++;
    }

    if (i >= MAX_OBJECTS) {
        return ERROR;
    }

    game->objects[i] = object;

    return OK;
}

/*
 * @brief Añade un objeto al juego
 *
 * @author Mihai Blidaru
 *
 * @param game El puntero al juego
 * @param link Un puntero al objeto
 * @return OK si se ha añaido correctamente, sino ERROR
 */
STATUS game_add_link(Game* game, Link* link) {
    int i = 0;

    if (!game || !link) {
        return ERROR;
    }

    while ((i < MAX_LINK) && (game->links[i] != NULL)) {
        i++;
    }

    if (i >= MAX_LINK) {
        return ERROR;
    }

    game->links[i] = link;

    return OK;
}

/*
 * @brief Añade un jugador al juego. Si el jugador ya está inicializado, lo sustituye por otro.
 *
 * @author Mihai Blidaru
 *
 * @param game El puntero al juego
 * @param link Un puntero al jugador
 * @return OK si se ha añaido correctamente, sino ERROR
 */
STATUS game_add_player(Game* game, Player* player) {
    if (!game || !player) {
        return ERROR;
    }

    if(game->player != NULL)
        player_destroy(game->player);

    game->player = player;

    return OK;
}


/*
 * @brief Devuelve un puntero al space que tiene el Id igual al Id pasado como parametro.
 *
 * @author Profesores PPROG
 * @param game Puntero a la estructura del juego
 * @param space_id Id del espacio
 * @return Puntero al espacio que tiene el Id igual al Id pasado como parametro. NULL si no existe.
 */
Space* game_get_space(Game* game, Id space_id) {
    int i = 0;

    if (!game || space_id == NO_ID) {
        return NULL;
    }

    /* Se recorre el array de espacios, comparado el Id de cada espacio con el id dado*/
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        if (space_id == space_get_id(game->spaces[i])) {
            return game->spaces[i];
        }
    }

    return NULL;
}

/*
 * @brief Develve el espacop una posición dada.
 *
 * @author Mihai Blidaru
 *
 * @param game Puntero a la estructura del juego
 * @param index La posición de la cual se quiere encontrar el espacio
 *
 * @return El espacio en la posición dada.Null si la posición es invalida.
 */
Space* game_get_space_at(Game* game, int index) {

    if (!game || index < 0 || index >= MAX_SPACES) {
        return NULL;
    }

    return game->spaces[index];
}

/**
 * @brief Devuelve el objeto que tiene el id igual al pasado como parametro
 * @author Javier Bernardo
 * @param game Un puntero a la estructura del juego
 * @param id Id del objeto a buscar
 * @private
 * @return El objeto que ha encontrado o NULL en caso contrario
 */
Object* game_get_object(Game* game, Id id) {
    int i = 0;

    if (!game || id == NO_ID)
        return NULL;

    for (i = 0; i < MAX_OBJECTS; i++) {
        if (game->objects[i] != NULL && object_Get_Id(game->objects[i]) == id) {
            return game->objects[i];
        }
    }

    return NULL;
}

/**
 * @brief Devuelve el objeto que tiene el nombre igual al pasado como parametro
 * @author Javier Bernardo
 * @param game Un puntero a la estructura del juego
 * @param name Nombre del objeto a buscar
 * @private
 * @return El objeto que ha encontrado o NULL en caso contrario
 */
Object* game_get_Object_byName(Game* game, char* name) {
    int i = 0, j = 0;
    char find_copy[30] = "\0";
    char copy[20];


    if (!game || !name)
        return NULL;
    strcpy(find_copy, name);
    for (i = 0; find_copy[i]; i++) {
            find_copy[i] = toupper(find_copy[i]);
    }

    for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) {
        strcpy(copy, object_Get_Name(game->objects[i]));

        for (j = 0; copy[j]; j++) {
            copy[j] = toupper(copy[j]);
        }

        if (strcmp(copy, find_copy) == 0) {
            return game->objects[i];
        }
    }

    return NULL;
}

/**
 * @brief Devuelve el link que tiene el nombre igual al pasado como parametro
 * @author Javier Bernardo
 * @param game Un puntero a la estructura del juego
 * @param name Nombre del link a buscar
 * @private
 * @return El link que ha encontrado o NULL en caso contrario
 */
Link* game_get_link_byName(Game* game, char* name) {
    int i = 0, j = 0;
    char copy[20];/* Copia para no modificar el nombre del link */


    if (!game || !name)
        return NULL;

    for (i = 0; name[i]; i++) {
            name[i] = toupper(name[i]);
    }

    for (i = 0; i < MAX_LINK && game->links[i] != NULL; i++) {
        strcpy(copy, link_get_name(game->links[i]));

        for (j = 0; copy[j]; j++) {
            copy[j] = toupper(copy[j]);
        }

        if (strcmp(copy, name) == 0) {
            return game->links[i];
        }
    }

    return NULL;
}


/*
 * @brief Develve el objeto una posición dada.
 *
 * @author Mihai Blidaru
 *
 * @param game Puntero a la estructura del juego
 * @param index La posición de la cual se quiere encontrar el objeto
 *
 * @return El objeto en la posición dada.Null si la posición es invalida.
 */
Object* game_get_object_at(Game* game, int index) {

    if (!game || index < 0 || index >= MAX_OBJECTS) {
        return NULL;
    }

    return game->objects[index];
}



/*
 * @brief Devuelve un puntero al space que tiene el Id igual al Id pasado como parametro.
 *
 * @author Profesores PPROG
 * @param game Puntero a la estructura del juego
 * @param link_id Id del espacio
 * @return Puntero al espacio que tiene el Id igual al Id pasado como parametro. NULL si no existe.
 */
Link* game_get_link(Game* game, Id link_id) {
    int i = 0;

    if (!game || link_id == NO_ID) {
        return NULL;
    }

    /* Se recorre el array de espacios, comparado el Id de cada espacio con el id dado*/
    for (i = 0; i < MAX_LINK && game->links[i] != NULL; i++) {
        if (link_id == link_get_id(game->links[i])) {
            return game->links[i];
        }
    }

    return NULL;
}

/*
 * @brief Develve el link en una posición dada.
 *
 * @author Mihai Blidaru
 *
 * @param game Puntero a la estructura del juego
 * @param index La posición de la cual se quiere encontrar el link
 *
 * @return El espacio en la posición dada.Null si la posición es invalida.
 */
Link* game_get_link_at(Game* game, int index) {

    if (!game || index < 0 || index >= MAX_LINK) {
        return NULL;
    }

    return game->links[index];
}


/*
 * @brief Devuelve el dado del juego
 *
 * @author Mihai Blidaru
 * @param game Puntero a la estructura del juego
 * @return Dado del juego.
 */
Die* game_get_die(Game* game){
    if(!game)
        return NULL;

    return game->die;
}

/**
 * @brief Cambia la localización del jugador a un espacio con el id dado.
 *
 * @author Mihai Blidaru
 *
 * @param game Puntero a la estructura de l juego.
 * @param player_location La posición donde se quiere colocar al jugador.
 * @private
 * @return OK si se ha cambiado la posición correctamente. ERROR en caso contrario.
 */
STATUS game_set_player_location(Game* game, Id player_location) {

    if (!game || player_location == NO_ID) {
        return ERROR;
    }

    if (!(player_Set_Location(game->player, player_location))) {
        return ERROR;
    }

    return OK;
}

/*
 * @brief Devuelve la localización del jugador.
 *
 * @author Mihai Blidaru
 *
 * @param game Puntero a la estructura de l juego.
 * @return La localización del jugador. NO_ID si hay algun error.
 */
Id game_get_player_location(Game* game) {
    if (!game)
        return NO_ID;

    return player_Get_Location(game->player);
}

/*
 * @brief Devuelve el jugador del juego
 *
 * @author Mihai Blidaru
 * @param game Puntero a la estructura del juego
 * @return Jugador del juego.
 */
Player* game_get_player(Game* game){
    if(!game)
        return NULL;

    return game->player;
}

/*
 * @brief  Devuelve un puntero al modulo dialogo del juego
 * 
 * @author Mihai Blidaru
 * @param game Puntero a la estructura del juego.
 * @return Un puntero al modulo dialogo del juego o NULL si hay algun error
 */
Dialogue* game_get_dialogue(Game* game){
    if(!game)
        return NULL;

    return game->dialogue;
}


/*
 * @brief Obtiene la localización  de un objeto.
 *
 * @author Javier Bernardo
 *
 * @param game Puntero a la estructura de el juego.
 * @param object El objeto del que quieres obtener la posicion.
 * @return La posicion del objeto o NO_ID en caso de error
 */
Id game_get_object_location(Game* game, Object* object) {
    int i;
    Id objId = NO_ID;
    if (!game || !object)
        return NO_ID;

    if ((objId = object_Get_Id(object)) == NO_ID)
        return NO_ID;

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        if (space_contains_object(game->spaces[i], objId)) {
            return space_get_id(game->spaces[i]);
        }
    }

    if(player_Has_Object(game->player, objId))
        return PLAYER_INV_LOCATION;

    return NO_ID;
}

/*
 * @brief Devuelve la lista de objetos de una casilla como cadena
 * @author Mihai Blidaru
 * @param game Un puntero a la estructura game
 * @param space Un puntero a la casilla desde la cual leer los objetos
 * @return Una cadena con la lista de los objetos. Quien use esta funciónse tiene
 *         que encargar de liberar la memoria usada.
 */
char* game_get_obj_list_as_str(Game* game, Space* space) {
    int i;
    char *string;

    if (!game || !space)
        return NULL;

    if (!(string = calloc(100, sizeof (char))))
        return NULL;

    strcat(string, " ");
    for (i = 0; i < MAX_OBJECTS && game->objects[i]; i++) {
        if(object_Get_Hidden(game->objects[i]) == FALSE){
            if (space_contains_object(space, object_Get_Id(game->objects[i]))) {
                sprintf(string, "%sO%ld ", string, object_Get_Id(game->objects[i]));
            }
        }
    }

    /* Añadir los espacios necesarios para completar la casilla*/
    for (i = strlen(string); i < SPACE_DRAW_WIDTH; i++) {
        strcat(string, " ");
    }
    return string;
}

/*
 * @brief Devuelve el último espacio inspeccionado
 * @author Laura Bernal y Sandra Benitez
 * @param game Un puntero a la estructura game
 *
 * @return El ultimo espacio inspeccionado
 */
Space* game_get_last_inspected_space(Game* game){
    if(!game)
        return NULL;
    return game->last_space;
}

/*
 * @brief Devuelve el ultimo objeto inspeccionado
 * @author Laura Bernal y Sandra Benitez
 * @param game Un puntero a la estructura game
 *
 * @return El ultimo objeto inspeccionado
 */
Object* game_get_last_inspected_object(Game* game){
    if(!game)
        return NULL;
    return game->last_object;
}

/*
 * @brief Imprime la información del juego
 *
 * @author Profesores PPROG
 * @author Javier Bernardo
 *
 * @param game Puntero a la estructura del juego.
 * @return Nada
 */
void game_print_data(Game* game) {
    int i = 0;
    Id objLoc = NO_ID;
    if (!game)
        return;

    printf("\n\n-------------\n\n");

    printf("=> Spaces: \n");
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        space_print(game->spaces[i]);
    }

    printf("=> Objects: \n");
    for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) {
        object_print(game->objects[i]);
    }

    printf("=> Object location:\n    ");
    for (i = 0; i < MAX_OBJECTS; i++) {
        objLoc = game_get_object_location(game, game->objects[i]);
        if (objLoc != NO_ID) {
            printf("%s:%ld ", object_Get_Name(game->objects[i]), objLoc);
        }
    }

    printf("=> Player location: %d\n", (int) game_get_player_location(game));
    printf("=>Last die value: %d", die_get_number(game->die));

    printf("prompt:> ");
}

/*
 * @brief Devuelve si el juego a acabado o no.
 *
 *      En esta iteración la función devuelve siempre FALSE ya que no hay
 *      suficiente funcionalidad en el juego como para poder decidir si el juego
 *      ha acabado o no.
 *
 * @author Profesores PPROG
 * @param game Puntero a la estructura del juego.
 * @return FALSE
 */
BOOL game_is_over(Game* game) {
    if(!game)
        return TRUE;
    if(game_get_player_location(game) == 1){
        if(player_Has_Object(game->player, 14) == TRUE){
            return TRUE;
        }
    }
    return FALSE;
}

/*
 * Implementación de cada funcion callback para cada acción
 */


/*
 *  @brief Elimina los ultimos objetos y los ultimos espacios del juego
 *  @author Laura Bernal y Sandra Benitez
 *  @param game Un puntero a la estructura game
 *
 *  @return
 *
 */
void game_clear_inspect (Game *game){
    if(game){
        game->last_object = NULL;
        game->last_space = NULL;
    }
}

/*
 * @brief Ejecuta una de las funciones callback en funcion del comando recibido
 *
 * @author Profesores PPROG
 *
 * @param game Puntero a la estructura del juego
 * @param command Comando que se tiene que ejecutar
 * @return
 */
STATUS game_update(Game* game, Command* command) {
    STATUS status = UNDEFINED;
    if (!game || !command)
        return ERROR;

    game_clear_inspect(game);
    status = (*game_callback_fn_list[Command_get_cmd(command)])(game, command);

    return status;
}

/* @brief No hace nada. Se ejecuta cuando el comando introducido es desconocido.
 *
 * @author Profesores PPROG
 *
 * @param game Puntero a la estructura del Juego.
 * @param cmd Una estructura tipo Command para leer los parametros de un comando cuando sea necesario
 * @return ERROR siempre.
 */
STATUS game_callback_unknown(Game* game, Command* cmd) {
    dialogue_unknown(game->dialogue);
    return ERROR;

}

/* @brief No hace nada. Se ejecuta cuando el comando introducido es QUIT.
 *         La salida del juego no se maneja en esta funciónsino en
 *         game_loop.
 *
 * @author Profesores PPROG
 *
 * @param game Puntero a la estructura del Juego.
 * @param cmd Una estructura tipo Command para leer los parametros de un comando cuando sea necesario
 * @return OK
 */
STATUS game_callback_quit(Game* game, Command* cmd) {
    return OK;
}

/* @brief No hace nada. Se ejecuta cuando el comando introducido es GO.
 *         La salida del juego no se maneja en esta funciónsino en
 *         game_loop.
 *
 * @author Profesores PPROG
 *
 * @param game Puntero a la estructura del Juego.
 * @param cmd Una estructura tipo Command para leer los parametros de un comando cuando sea necesario
 * @return OK
 */
STATUS game_callback_go(Game* game, Command* cmd) {
    char* dir = NULL;
    Link* link = NULL;
    Space* space = NULL;
    Id player_location = NO_ID, dest_id = NO_ID;
    DIRECTION direction = UNKNOWN_DIRECTION;

    if(!game || !cmd)
        return ERROR;

    dir = Command_get_cmd_arg(cmd, 0);
    player_location = game_get_player_location(game);

    space = game_get_space(game, player_location);

    if(!space)
        return ERROR;
    if(!strcmp(dir,"north") || !strcmp(dir,"n")){
        link = game_get_link(game, space_get_north(space));
        direction = NORTH;
    }else if(!strcmp(dir,"south") || !strcmp(dir,"s")){
        link = game_get_link(game, space_get_south(space));
        direction = SOUTH;
    }else if(!strcmp(dir,"east") || !strcmp(dir,"e")){
       link = game_get_link(game, space_get_east(space));
       direction = EAST;
    }else if(!strcmp(dir,"west") || !strcmp(dir,"w")){
        link = game_get_link(game, space_get_west(space));
        direction = WEST;
    }else if(!strcmp(dir,"up") || !strcmp(dir,"u")){
        link = game_get_link(game, space_get_up(space));
        direction = UP;
    }else if(!strcmp(dir,"down") || !strcmp(dir,"d")){
        link = game_get_link(game, space_get_down(space));
        direction = DOWN;
    }

    if(!link){
        dialogue_go(game->dialogue, direction, space, ERROR, dir, NULL);
        return ERROR;
    }

    if(link_get_state(link) == CLOSED){
        dialogue_go(game->dialogue, direction, space, ERROR, dir, link);
        return ERROR;
    }

    dest_id = link_get_dest_from(link, player_location);
    if(dest_id == NO_ID){
        dialogue_go(game->dialogue, direction, space, ERROR, dir, NULL);
        return ERROR;
    }
    game_set_player_location(game,dest_id);
    dialogue_go(game->dialogue, direction, game_get_space(game, dest_id), OK, dir, link);
    return OK;
}

/* @brief No hace nada. Se ejecuta cuando el comando introducido es INSPECT.
 *         La salida del juego no se maneja en esta función sino en
 *         game_loop.
 *
 * @author Profesores PPROG
 *
 * @param game Puntero a la estructura del Juego.
 * @param cmd Una estructura tipo Command para leer los parametros de un comando cuando sea necesario
 * @return OK
 */
STATUS game_callback_inspect(Game* game, Command* cmd) {
    char* dir = NULL;
    Space* space = NULL;
    Object* object = NULL;
    BOOL player_lights = FALSE;
    Id player_location = NO_ID, object_id = NO_ID;
    int i = 0;
    if(!game || !cmd)
        return ERROR;

    dir = Command_get_cmd_arg(cmd, 0);
    player_location = game_get_player_location(game);
    space = game_get_space(game, player_location);
    if(strlen(dir) > 0 ){
       for(i = 0; game->objects[i] != NULL; i++){
            if(player_Has_Object(game->player, object_Get_Id(game->objects[i])) == TRUE){
                if(object_Get_Light(game->objects[i]) == TRUE){
                    player_lights = TRUE; /* Si el jugador tiene un objeto que ilumina */
                    break;
                }
            }
        }
        if(!strcmp(dir,"space") || !strcmp(dir,"s")){
            if(space){
                game->last_space = space;

            /* Si el jugador tiene un objeto que ilumina puede desocultar objetos */
            for(i = 0;  (i < 20 ) && (game->objects[i] != NULL) && (player_lights || space_get_iluminated(space));i++){
                if(space_contains_object(space, object_Get_Id(game->objects[i])))
                    object_Set_Hidden(game->objects[i], FALSE);
            }
                dialogue_inspect(game->dialogue, object, space, "space", INSPECT_OK);
                return OK;
            }
        }else{
            object = game_get_Object_byName(game, dir);
            if(object == NULL){
                dialogue_inspect(game->dialogue, object, space, dir, INSPECT_NO_OBJ);
                return ERROR;
            }
            if(object_Get_Hidden(object) == FALSE){
                object_id = object_Get_Id(object);
                if (player_Has_Object(game->player, object_id) || (space_contains_object(space, object_id) && (space_get_iluminated(space) || player_lights))){
                    game->last_object = object;
                    dialogue_inspect(game->dialogue, object, space, dir, INSPECT_OK);
                    return OK;
                }
            }
            dialogue_inspect(game->dialogue, object, space, dir, INSPECT_NO_OBJ);
            return ERROR;
        }
    }
    dialogue_inspect(game->dialogue, object, space, dir, GLOBAL_NO_ARGS);
    return ERROR;
}

/* @brief Hace que el jugador coja el objeto que hay en la casilla en la que está
 *
 * @author Mihai Blidaru
 *
 * @param game Puntero a la estructura del Juego.
 * @param cmd Una estructura tipo Command para leer los parametros de un comando cuando sea necesario
 * @return OK si se ha realizado la operación correctamente o ERROR en caso contrario
 */
STATUS game_callback_take(Game* game, Command* cmd) {
    Id space_id = NO_ID, objId = NO_ID;
    char* arg = NULL;
    Space* space = NULL;
    Object* object = NULL;

    if (!game)
        return ERROR;
    arg = Command_get_cmd_arg(cmd, 0);

    if (strlen(arg) < 1){
        dialogue_take(game->dialogue, NULL, arg, GLOBAL_NO_ARGS);
        return ERROR;
    }

    space_id = game_get_player_location(game);
    space = game_get_space(game, space_id);

    object = game_get_Object_byName(game, arg);

    if (!object){
        dialogue_take(game->dialogue, NULL, arg, NO_OBJ);
        return ERROR;
    }
    objId = object_Get_Id(object);

    if (NO_ID == space_id || !space) {
        return ERROR;
    }

    if (space_contains_object(space, objId)) {
        if(object_Get_Hidden(object) == FALSE){
            if(object_Get_Mobile(object) == TRUE){
                if(player_Add_Object(game->player, objId) == OK){
                    space_remove_object(space, objId);
                    object_Set_Moved(object, TRUE);
                    dialogue_take(game->dialogue, object, object_Get_Name(object), TAKE_OK);
                    return OK;
                }else{
                    dialogue_take(game->dialogue, object, object_Get_Name(object), INVENTORY_FULL);
                    return ERROR;
                }
            }else{
                dialogue_take(game->dialogue, object, object_Get_Name(object), NOT_MOBILE);
                return ERROR;
            }
        }
    }else{
        dialogue_take(game->dialogue, object, object_Get_Name(object), NOT_IN_SPACE);
        return ERROR;
    }
    return ERROR;
}

/* @brief Hace que el jugador suelte el objeto que tiene
 *         en la casilla en la que se encuentra.
 *
 * @author Mihai Blidaru
 *
 * @param game Puntero a la estructura del Juego.
 * @param cmd Una estructura tipo Command para leer los parametros de un comando cuando sea necesario
 * @return OK si se ha realizado la operación correctamente o ERROR en caso contrario
 */
STATUS game_callback_leave(Game* game, Command* cmd) {
    Id space_id = NO_ID, objId = NO_ID;
    char* arg = NULL;
    Space* space;
    Object* object;

    if (!game)
        return ERROR;
    arg = Command_get_cmd_arg(cmd, 0);

    if (strlen(arg) < 1){
        dialogue_leave(game->dialogue, NULL, arg, GLOBAL_NO_ARGS);
        return ERROR;
    }

    space_id = game_get_player_location(game);
    space = game_get_space(game, space_id);
    if (NO_ID == space_id || !space) {
        return ERROR;
    }

    object = game_get_Object_byName(game, arg);

    if (!object){
        dialogue_leave(game->dialogue, NULL, arg, NOT_IN_INV);
        return ERROR;
    }

    objId = object_Get_Id(object);

    if (!object)
        return ERROR;

    if (player_Has_Object(game->player, objId)) {
        player_Remove_Object(game->player, objId);
        space_add_object(space, objId);
        dialogue_leave(game->dialogue, object, arg, LEAVE_OK);
        return OK;
    }else{
        dialogue_leave(game->dialogue, object, arg, NOT_IN_INV);
    }
    return ERROR;
}

/*
 * @brief Tira el dato
 *       Usando el TAD die, se genera un número aleatorio entre 1 y 6.
 * @param game Una estructura del juego
 * @param cmd Una estructura tipo Command para leer los parametros de un comando cuando sea necesario
 * @author Javier Bernardo
 * @return OK si todo ha ido bien o ERROR en caso contrario
 */
STATUS game_callback_roll(Game* game, Command* cmd) {
    if (!game || !cmd)
        return ERROR;

    if(die_roll(game->die) == -1)
        return ERROR;
    return OK;
}

/*
 * @brief Enciende un objeto
 * @param game Una estructura del juego
 * @param cmd Una estructura tipo Command para leer los parametros de un comando cuando sea necesario
 * @author Mihai Blidaru
 * @return OK si todo ha ido bien o ERROR en caso contrario
 */
STATUS game_callback_turn_on(Game* game, Command* cmd){
    char* dir = NULL;
    Object* object = NULL;
    Id object_id = NO_ID;
    if(!game || !cmd)
        return ERROR;

    dir = Command_get_cmd_arg(cmd, 0);
    if(strlen(dir) > 0 ){
        object = game_get_Object_byName(game, dir);
        if(object == NULL){
            dialogue_turn_on(game->dialogue, object, dir, TURN_NOT_IN_INV);
            return ERROR;
        }
        object_id = object_Get_Id(object);

        if(player_Has_Object(game->player, object_id)){
            if (object_Get_Illuminates(object) == TRUE){
                if(object_Get_Light(object) == TRUE){
                    dialogue_turn_on(game->dialogue, object, dir, TURN_ALREADY);
                    return OK;
                }
                object_Set_Light(object, TRUE);
                dialogue_turn_on(game->dialogue, object, dir, TURN_OK);
                return OK;
            }else{
                dialogue_turn_on(game->dialogue, object, dir, TURN_NO_LIGHT);
                return ERROR;
            }
        }else{
            dialogue_turn_on(game->dialogue, object, dir, TURN_NOT_IN_INV);
            return ERROR;
        }
    }
    dialogue_turn_on(game->dialogue, object, dir, GLOBAL_NO_ARGS);
    return ERROR;
}

/*
 * @brief Apaga un objeto
 * @param game Una estructura del juego
 * @param cmd Una estructura tipo Command para leer los parametros de un comando cuando sea necesario
 * @author Mihai Blidaru
 * @return OK si todo ha ido bien o ERROR en caso contrario
 */
STATUS game_callback_turn_off(Game* game, Command* cmd){
    char* dir = NULL;
    Object* object = NULL;
    Id object_id = NO_ID;
    if(!game || !cmd)
        return ERROR;

    dir = Command_get_cmd_arg(cmd, 0);
    if(strlen(dir) > 0 ){
        object = game_get_Object_byName(game, dir);
        if(object == NULL){
            dialogue_turn_off(game->dialogue, object, dir, TURN_NOT_IN_INV);
            return ERROR;
        }
        object_id = object_Get_Id(object);

        if(player_Has_Object(game->player, object_id)){
            if (object_Get_Illuminates(object) == TRUE){
                if(object_Get_Light(object) == FALSE){
                    dialogue_turn_off(game->dialogue, object, dir, TURN_ALREADY);
                    return OK;
                }
                object_Set_Light(object, FALSE);
                dialogue_turn_off(game->dialogue, object, dir, TURN_OK);
                return OK;
            }else{
                dialogue_turn_off(game->dialogue, object, dir, TURN_NO_LIGHT);
                return ERROR;
            }
        }else{
            dialogue_turn_off(game->dialogue, object, dir, TURN_NOT_IN_INV);
            return ERROR;
        }
    }
    dialogue_turn_off(game->dialogue, object, dir, GLOBAL_NO_ARGS);
    return ERROR;
}

/*
 * @brief Abre un link usando un objeto
 * @param game Una estructura del juego
 * @param cmd Una estructura tipo Command para leer los parametros de un comando cuando sea necesario
 * @author Mihai Blidaru
 * @return OK si todo ha ido bien o ERROR en caso contrario
 * @bug FALTA COMPLETAR LA FUNCION
 */
STATUS game_callback_open(Game* game, Command* cmd){
    Space* space = NULL;
    Link* link = NULL;
    Link* aux = NULL;
    char* link_name = NULL;
    char* object_name = NULL;
    Object* object = NULL;
    Id link_ids[6] = {NO_ID}, link_id = NO_ID;
    int i;

    if(!game || !cmd)
        return ERROR;

    link_name = Command_get_cmd_arg(cmd, 0);
    object_name = Command_get_cmd_arg(cmd, 2);

    if(strcmp(Command_get_cmd_arg(cmd,1), "with")){
        dialogue_open(game->dialogue, object_name, link_name, WRONG_SYNTAX);
        return ERROR;
    }
        

    link = game_get_link_byName(game, link_name);
    if(!link){
        dialogue_open(game->dialogue, object_name, link_name, NO_LINK);
        return ERROR;
    }
        
    link_id = link_get_id(link);

    object = game_get_Object_byName(game, object_name);

    if(!object){
        dialogue_open(game->dialogue, object_name, link_name, NO_OBJECT);
        return ERROR;
    }

    space = game_get_space(game, game_get_player_location(game));
    if(space){
        link_ids[0] = space_get_south(space);
        link_ids[1] = space_get_north(space);
        link_ids[2] = space_get_east(space);
        link_ids[3] = space_get_west(space);
        link_ids[4] = space_get_up(space);
        link_ids[5] = space_get_down(space);

        for(i=0; i < 6; i++){
            if(link_ids[i] == link_id){
                aux = link;
                break;
            }
        }
        
        if(aux){
            if(object_Get_Open(object) == link_id){
                link_set_state(link, OPENED);
                dialogue_open(game->dialogue, object_name, link_name, OPEN_OK);
                return OK;
            }else{
                dialogue_open(game->dialogue, object_name, link_name, NOT_SAME_ID);       
                return ERROR;
            }
        }else{
            dialogue_open(game->dialogue, object_name, link_name, NO_LINK);    
            return ERROR;
        }
    }

    return ERROR;
}

/*
 * @brief Guarda la partida
 * @param game Una estructura del juego
 * @param cmd Una estructura tipo Command para leer los parametros de un comando cuando sea necesario
 * @author Sandra Benitez y Laura Bernal
 * @return OK si todo ha ido bien o ERROR en caso contrario
 */
STATUS game_callback_save(Game* game, Command* cmd){
    char* name = NULL;
    SAVE_STATUS status = -1;
    if(!game || !cmd)
        return ERROR;

    name = Command_get_cmd_arg(cmd, 0);
    status = game_management_save(game, name);
    if(status == SAVE_OK){
        dialogue_save(game->dialogue, name, SAVE_SAVE_OK);
        return OK;
    }else if(status == PROTECTED_FILE){
        dialogue_save(game->dialogue, name, SAVE_PROTECTED_FILE);
        return ERROR;
    }else{
        dialogue_save(game->dialogue, name, SAVE_WRITE_FAILED);
        return ERROR;
    }

    return ERROR;
}

/*
 * @brief Carga la partida
 * @param game Una estructura del juego
 * @param cmd Una estructura tipo Command para leer los parametros de un comando cuando sea necesario
 * @author Sandra Benitez y Laura Bernal
 * @return OK si todo ha ido bien o ERROR en caso contrario
 */
STATUS game_callback_load(Game* game, Command* cmd){
    int i;
    int numSpaces, numLinks, numObjects;
    STATUS status = UNDEFINED;
    Object **objects;
    Space **spaces;
    Link **links;
    Player* player;

    char* name = NULL;
    if(!game || !cmd)
        return ERROR;

    name = Command_get_cmd_arg(cmd, 0);
    if(strlen(name)>0){
        for(numSpaces = 0; game->spaces[numSpaces] != NULL; numSpaces++);
        for(numLinks = 0; game->links[numLinks] != NULL; numLinks++);
        for(numObjects = 0; game->objects[numObjects] != NULL; numObjects++);

        spaces = calloc(numSpaces, sizeof(Space*));
        objects = calloc(numObjects, sizeof(Object*));
        links = calloc(numLinks, sizeof(Link*));

        for(i=0; game->spaces[i] != NULL; i++){
            spaces[i] = game->spaces[i];
            game->spaces[i] = NULL;
        }

        for(i=0; game->links[i] != NULL; i++){
            links[i] = game->links[i];
            game->links[i] = NULL;
        }

        for(i=0; game->objects[i] != NULL; i++){
            objects[i] = game->objects[i];
            game->objects[i] = NULL;
        }

        player = game->player;
        game->player = NULL;
        
        status = game_management_load(game, name);
        if(status == OK){
            if(game->player != NULL && game->spaces[0] != NULL){
                for(i=0; i < numSpaces; i++){
                    space_destroy(spaces[i]);
                }
    
                for(i=0; i < numObjects; i++){
                    object_destroy(objects[i]);
                }
    
                for(i=0; i < numLinks; i++){
                    link_destroy(links[i]);
                }
                player_destroy(player);
                free(links);
                free(objects);
                free(spaces);
                dialogue_load(game->dialogue, name, LOAD_OK);
                return OK;
            }else{
                status = ERROR;
            }
        }
        
        if(status == ERROR){
            for(i=0; i < numSpaces; i++){
                game->spaces[i] = spaces[i];
            }

            for(i=0; i < numObjects; i++){
                game->objects[i] = objects[i];
            }

            for(i=0; i < numLinks; i++){
                game->links[i] = links[i];
            }
            game->player = player;
            free(links);
            free(objects);
            free(spaces);
            dialogue_load(game->dialogue, name, LOAD_ERROR);
            return ERROR;
        }
    } else{
        dialogue_load(game->dialogue, name, GLOBAL_NO_ARGS);
        return ERROR;
    }

    return OK;
}

/* @brief Implementa el comando DIR que muestra las conexiones de una casilla
 * 
 * @author Javier Bernardo
 * @param game Una estructura del juego
 * @param cmd Una estructura tipo Command para leer los parametros de un comando cuando sea necesario
 * @return OK si todo ha ido bien o ERROR en caso contrario
 */
STATUS game_callback_dir(Game* game, Command* cmd){
    if(!game || !cmd)
        return ERROR;
    dialogue_dir(game->dialogue);
    return OK;
}

/* @brief Implementa el comando Ayuda que muestra los comandos disponibles
 * 
 * @author Javier Bernardo
 * @param game Una estructura del juego
 * @param cmd Una estructura tipo Command para leer los parametros de un comando cuando sea necesario
 * @return OK si todo ha ido bien o ERROR en caso contrario
 */
STATUS game_callback_help(Game* game, Command* cmd){
    if(!game || !cmd)
        return ERROR;
    dialogue_help(game->dialogue);
    return OK;
}

/* @brief Implementa el comando atacar
 * 
 * @author Javier Bernardo
 * @param game Una estructura del juego
 * @param cmd Una estructura tipo Command para leer los parametros de un comando cuando sea necesario
 * @return OK si todo ha ido bien o ERROR en caso contrario
 */
STATUS game_callback_attack(Game* game, Command* cmd){
    Space* space = NULL;
    Link* link = NULL;
    char graphics[6][24] = {
      {"    _______________    "},
      {"   |El  guardian se|   "},
      {"   | ha asustado y |   "},
      {"   |    ha huido   |   "},
      {"   \\_______________/   "},
      {"                       "}
    };

    char graphics2[6][24] = {
      {"     .     '     ,     "},
      {"       _________       "},
      {"    _ /_|_____|_\\ _    "},
      {"      '. \\   / .'      "},
      {"        '.\\ /.'        "},
      {"          '.'          "}
    };

    if(!game || !cmd)
        return ERROR;

    space = game_get_space(game, game_get_player_location(game));
    link = game_get_link(game,9);
    if(space_get_id(space) == 8 && link_get_state(link) == CLOSED){
      if(player_Has_Object(game->player, 4)){
        link_set_state(link, OPENED);
        space_set_graphics(space, graphics);
        dialogue_attack(game->dialogue, BOSS1_OK);
      }else{
          dialogue_attack(game->dialogue, WRONG_WEAPON);
      }
    }else if(space_get_id(space) == 10 && game_get_object_location(game,game_get_object(game,14)) == NO_ID){
      if(player_Has_Object(game->player, 3)){
        if(player_Add_Object(game->player, 14) == ERROR){
          space_add_object(space, 14);
        }
        space_set_graphics(space, graphics2);
        dialogue_attack(game->dialogue, BOSS2_OK);
      }else{
          dialogue_attack(game->dialogue, WRONG_WEAPON);
      }
    }else{
        dialogue_attack(game->dialogue, NOTHING_TO_ATTACK);
    }
    return OK;
}
