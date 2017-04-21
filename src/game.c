/** 
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 * 
 * @file game.c
 * @author Profesores PPROG
 * @author Javier Bernardo
 * @author Mihai Blidaru
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
#include "game_management.h"

/**
 * @cond HIDDEN_SYMBOLS
 * Número de funciones callbacks
 * 
 */
#define N_CALLBACK 12

/**
 * @brief Define the function type for the callbacks
 */
typedef STATUS(*callback_fn)(Game* game, Command* cmd);

/**
 * Ancho de una casilla 
 */
#define SPACE_DRAW_WIDTH 13

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
    T_Command last_cmd;              /*!< Ultimo comando */
    STATUS last_status;              /*!< Ultimo status */
    Space* last_space;               /*!< Puntero al ultimo space */
    Object* last_object;             /*!< Puntero al ultimo objeto */
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
    game_callback_load
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
      
    game->last_object = NULL;
    game->last_space = NULL;

    for (i = 0; i < MAX_OBJECTS; i++)
        game->objects[i] = NULL;
    
    /* Inicializar la estructura del jugador */

    player_Set_Name(game->player, "Player 1");
    player_Set_Id(game->player, GENERIC_ID);
    game->last_status = -1;
    game->last_cmd = NO_CMD;
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

    if (space == NULL) {
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
    char copy[20];
    

    if (!game || !name)
        return NULL;
    
    for (i = 0; name[i]; i++) {
            name[i] = toupper(name[i]);
    }
    
    for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) {
        strcpy(copy, object_Get_Name(game->objects[i]));
        
        for (j = 0; copy[j]; j++) {
            copy[j] = toupper(copy[j]);
        }
        
        if (strcmp(copy, name) == 0) {
            return game->objects[i];
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

    for (i = 0; i < MAX_SPACES; i++) {
        if (space_contains_object(game->spaces[i], objId)) {
            return space_get_id(game->spaces[i]);
        }
    }

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

    if (!(string = calloc(30, sizeof (char))))
        return NULL;

    strcat(string, " ");
    for (i = 0; i < MAX_OBJECTS && game->objects[i]; i++) {
        if (space_contains_object(space,object_Get_Id(game->objects[i]))) {
            sprintf(string, "%sO%ld ", string, object_Get_Id(game->objects[i]));
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
 * @brief Devuelve el útimo comando recibido.
 * 
 * @author Profesores PPROG
 * 
 * @param game Puntero a la estructura del juego.
 * @return El útimo comando recibido.
 */
T_Command game_get_last_command(Game* game) {
    if (!game)
        return NO_CMD;

    return game->last_cmd;
}

/* 
 * @brief Devuelve resultado del útimo comando recibido.
 * 
 * @author Mihai Blidaru
 * 
 * @param game Puntero a la estructura del juego.
 * @return El resultado del útimo comando recibido.
 */
STATUS game_get_last_status(Game* game) {
    if (!game)
        return -1;

    return game->last_status;
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
    if (!game || !command)
        return ERROR;

    game->last_cmd = Command_get_cmd(command);
    game_clear_inspect(game);
    game->last_status = (*game_callback_fn_list[Command_get_cmd(command)])(game, command);
    
    return game->last_status;
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
    
    if(!game || !cmd)
        return ERROR;
        
    dir = Command_get_cmd_arg(cmd, 0);
    player_location = game_get_player_location(game);
    
    space = game_get_space(game, player_location);
    
    if(!space)
        return ERROR;
    if(!strcmp(dir,"north") || !strcmp(dir,"n")){
        link = game_get_link(game, space_get_north(space));    
    }else if(!strcmp(dir,"south") || !strcmp(dir,"s")){
        link = game_get_link(game, space_get_south(space));    
    }else if(!strcmp(dir,"east") || !strcmp(dir,"e")){
       link = game_get_link(game, space_get_east(space));    
    }else if(!strcmp(dir,"west") || !strcmp(dir,"w")){
        link = game_get_link(game, space_get_west(space));    
    }else if(!strcmp(dir,"up") || !strcmp(dir,"u")){
        link = game_get_link(game, space_get_up(space));    
    }else if(!strcmp(dir,"down") || !strcmp(dir,"d")){
        link = game_get_link(game, space_get_down(space));    
    }
    
    
    if(!link || link_get_state(link) == CLOSED)
        return ERROR;
    
    dest_id = link_get_dest_from(link, player_location);
    if(dest_id == NO_ID)
        return ERROR;
        
    game_set_player_location(game,dest_id);
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
    Id player_location = NO_ID, object_id = NO_ID;
    if(!game || !cmd)
        return ERROR;
    
    dir = Command_get_cmd_arg(cmd, 0);
    player_location = game_get_player_location(game);
    space = game_get_space(game, player_location);
    if(strlen(dir) > 0 ){
        if(!strcmp(dir,"space") || !strcmp(dir,"s")){
            if(space){
                game->last_space = space;
                return OK;
            }
        }else{
            object = game_get_Object_byName(game, dir);
            if(object == NULL)
                return ERROR;
            object_id = object_Get_Id(object);
            if (player_Has_Object(game->player, object_id) || space_contains_object(space, object_id)){
                game->last_object = object;
                return OK;
            }
        }
    }
    
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

    if (strlen(arg) < 1)
        return ERROR;
    
    space_id = game_get_player_location(game);
    space = game_get_space(game, space_id);
    
    object = game_get_Object_byName(game, arg);

    if (!object)
        return ERROR;

    objId = object_Get_Id(object);

    if (NO_ID == space_id || !space) {
        return ERROR;
    }

    if (space_contains_object(space, objId) && object_Get_Mobile(object) == TRUE) {
        if(player_Add_Object(game->player, objId) == ERROR){
            return ERROR;        
        }
        space_remove_object(space, objId);
        object_Set_Moved(object, TRUE);
        return OK;
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

    if (strlen(arg) < 1)
        return ERROR;



    space_id = game_get_player_location(game);
    space = game_get_space(game, space_id);
    if(strlen(arg) < 4){
        if(arg[0] == 'o' || arg[0] == 'O'){
            objId = atol(arg+1);
            if((object = game_get_object(game, objId))){
                if (player_Has_Object(game->player, objId)) {
                    player_Remove_Object(game->player, objId);
                    space_add_object(space, objId);
                    return OK;
                }
            }
        }
        
    }

    if (NO_ID == space_id || !space) {
        return ERROR;
    }

    object = game_get_Object_byName(game, arg);

    if (!object)
        return ERROR;

    objId = object_Get_Id(object);

    if (!object)
        return ERROR;

    if (player_Has_Object(game->player, objId)) {
        player_Remove_Object(game->player, objId);
        space_add_object(space, objId);
        return OK;
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
        if(object == NULL)
            return ERROR;
        object_id = object_Get_Id(object);
        
        if(player_Has_Object(game->player, object_id)){
            if (object_Get_Illuminates(object) == TRUE){
                object_Set_Light(object, TRUE);
                return OK;
            }
        }
            
    }
    
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
        if(object == NULL)
            return ERROR;
        object_id = object_Get_Id(object);
        
        if(player_Has_Object(game->player, object_id)){
            if (object_Get_Illuminates(object) == TRUE){
                object_Set_Light(object, FALSE);
                return OK;
            }
        }
            
    }
    
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
    Link* link = {NULL};
    char* link_name = NULL;
    char* object_name = NULL;
    Object* object = NULL;
    BOOL link_found = FALSE;
    
    
    Id space_id = NO_ID, link_id = NO_ID;
    
    if(!game || !cmd)
        return ERROR;
    
    link_name = Command_get_cmd_arg(cmd, 0);
    object_name = Command_get_cmd_arg(cmd, 2);
    
    if(strcmp(Command_get_cmd_arg(cmd,1), "with"))
        return ERROR;
    
    space_id = game_get_player_location(game);
    space = game_get_space(game, space_id);
    
    object = game_get_Object_byName(game, object_name);
    
    if(!object)
        return ERROR;
    
    if((link_id = space_get_north(space)) != NO_ID){
        link = game_get_link(game, link_id);
        if(!link && !strcmp(link_name, link_get_name(link))){
            link_found = TRUE;
        }
    }else if(link_found == FALSE && ((link_id = space_get_south(space)) != NO_ID)){
        link = game_get_link(game, link_id);
        if(!link && !strcmp(link_name, link_get_name(link))){
            link_found = TRUE;
        }
    }else if(link_found == FALSE && ((link_id = space_get_east(space)) != NO_ID)){
        link = game_get_link(game, link_id);
        if(!link && !strcmp(link_name, link_get_name(link))){
            link_found = TRUE;
        }
    }else if(link_found == FALSE && ((link_id = space_get_west(space)) != NO_ID)){
        link = game_get_link(game, link_id);
        if(!link && !strcmp(link_name, link_get_name(link))){
            link_found = TRUE;
        }
    }else if(link_found == FALSE && ((link_id = space_get_up(space)) != NO_ID)){
        link = game_get_link(game, link_id);
        if(!link && !strcmp(link_name, link_get_name(link))){
            link_found = TRUE;
        }
    }else if(link_found == FALSE && ((link_id = space_get_down(space)) != NO_ID)){
        link = game_get_link(game, link_id);
        if(!link && !strcmp(link_name, link_get_name(link))){
            link_found = TRUE;
        }
    }
    
    if(!link)
        return ERROR;
    
    if(object_Get_Open(object) == link_get_id(link)){
        link_set_state(link, OPENED);
        return OK;
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
    if(!game || !cmd)
        return ERROR;
    name = Command_get_cmd_arg(cmd, 0);
    if(strlen(name)>0){
        game_management_save(game, name);
    } else{
        return ERROR;    
    }
    
    return OK;
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
    char* name = NULL;
    if(!game || !cmd)
        return ERROR;
        
    name = Command_get_cmd_arg(cmd, 0);
    if(strlen(name)>0){
        for(i=0; game->spaces[i] != NULL; i++){
            space_destroy(game->spaces[i]);
            game->spaces[i] = NULL;
        }
        
        for(i=0; game->links[i] != NULL; i++){
            link_destroy(game->links[i]);
            game->links[i] = NULL;
        }
        
        for(i=0; game->objects[i] != NULL; i++){
            object_destroy(game->objects[i]);
            game->objects[i] = NULL;
        }
        
        player_destroy(game->player);
        game->player = NULL;
        
        game_management_load(game, name);
    } else{
        return ERROR;    
    }   
    
    return OK;
}