/** 
 * @brief It defines the game interface
 * for each command
 * 
 * @file game.h
 * @author Profesores PPROG
 * @author Javier Bernardo
 * @author Mihai Blidaru
 * @version 2.0 
 * @date 20-02-2017 
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

/* Cabeceras propias */
#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "types.h"
#include "die.h"
#include "set.h"
#include "link.h"
#include "dialogue.h"
/**
 * Numero maximo de objetos 
 */
#define MAX_OBJECTS 20

/**
 * Número máximo de casillas permitidas en el juegos
 */
#define MAX_SPACES 10000


/** Estructura game
 * Guarda los datos del juego: Jugador, Objetos, Casillas, Dado, ultimo comando
 * ejecutado el resultado de este comando.
 */
typedef struct _Game Game;

/** 
 * @brief Inicializa los datos del juego
 *      Esta función inicializa los espacios, crea e inicializa
 *      el jugador, los objetos y el dado
 * @author Profesores PPROG 
 * @author Mihai Blidaru
 *  
 * @return OK si todo ha ido bien. En caso contrario ERROR
 */
Game* game_create();

/** 
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
STATUS game_destroy(Game* game);

/** @brief Ejecuta una de las funciones callback en funcion del comando recibido
 * 
 * @author Profesores PPROG
 * 
 * @param game Puntero a la estructura del juego
 * @param command Comando que se tiene que ejecutar
 * @return 
 */
STATUS game_update(Game* game, Command* command);

/**
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
BOOL game_is_over(Game* game);

/**
 * @brief Añade un objeto al juego
 *
 * @author Javier Bernardo
 * 
 * @param game El puntero al juego 
 * @param object Un puntero al objeto 
 * @return OK si se ha añadido correctamente, sino ERROR
 */
STATUS game_add_object(Game* game, Object* object);

/**
 * @brief Añade un espacio al juego
 *
 * @author Profesores PPROG
 * 
 * @param game El puntero al juego 
 * @param space Un puntero al espacio 
 * @return OK si se ha añadido correctamente, sino ERROR
 */
STATUS game_add_space(Game* game , Space* space);

/**
 * @brief Añade un objeto al juego
 *
 * @author Mihai Blidaru
 * 
 * @param game El puntero al juego 
 * @param link Un puntero al objeto 
 * @return OK si se ha añaido correctamente, sino ERROR
 */
STATUS game_add_link(Game* game, Link* link);

/**
 * @brief Añade un jugador al juego. Si el jugador ya está inicializado, lo sustituye por otro.
 *
 * @author Mihai Blidaru
 * 
 * @param game El puntero al juego 
 * @param player Un puntero al jugador
 * @return OK si se ha añaido correctamente, sino ERROR
 */
STATUS game_add_player(Game* game, Player* player);

/**
 * @brief Devuelve un puntero al link que tiene el Id igual al Id pasado como parametro.
 * 
 * @author Profesores PPROG
 * @param game Puntero a la estructura del juego
 * @param link_id Id del link
 * @return Puntero al link que tiene el Id igual al Id pasado como parametro. NULL si no existe.
 */
Link* game_get_link(Game* game, Id link_id);

/** 
 * @brief Develve el link en una posición dada.
 *  
 * @author Mihai Blidaru
 *  
 * @param game Puntero a la estructura del juego
 * @param index La posición de la cual se quiere encontrar el link
 *  
 * @return El espacio en la posición dada.Null si la posición es invalida.
 */
Link* game_get_link_at(Game* game, int index);

/**
 * @brief Devuelve un puntero al space que tiene el Id igual al Id pasado como parametro.
 * 
 * @author Profesores PPROG
 * @param game Puntero a la estructura del juego
 * @param space_id Id del espacio
 * @return Puntero al espacio que tiene el Id igual al Id pasado como parametro. NULL si no existe.
 */
Space* game_get_space(Game* game, Id space_id);

/** 
 * @brief Develve el espacop una posición dada.
 *  
 * @author Mihai Blidaru
 *  
 * @param game Puntero a la estructura del juego
 * @param index La posición de la cual se quiere encontrar el espacio
 *  
 * @return El espacio en la posición dada.Null si la posición es invalida.
 */
Space* game_get_space_at(Game* game, int index);


/** 
 * @brief Develve el objeto una posición dada.
 *  
 * @author Mihai Blidaru
 *  
 * @param game Puntero a la estructura del juego
 * @param index La posición de la cual se quiere encontrar el objeto
 *  
 * @return El objeto en la posición dada. Null si la posición es invalida.
 */
Object* game_get_object_at(Game* game, int index);

/** 
 * @brief Devuelve el dado del juego
 * 
 * @author Mihai Blidaru
 * @param game Puntero a la estructura del juego
 * @return Dado del juego.
 */
Die* game_get_die(Game* game);

/**
 * @brief Devuelve el jugador del juego
 * 
 * @author Mihai Blidaru
 * @param game Puntero a la estructura del juego
 * @return Jugador del juego.
 */
Player* game_get_player(Game* game);

/** 
 * @brief Devuelve la lista de objetos de una casilla como cadena
 * @author Mihai Blidaru
 * @param game Un puntero a la estructura game
 * @param space Un puntero a la casilla desde la cual leer los objetos
 * @return Una cadena con la lista de los objetos. Quien use esta funciónse tiene
 *         que encargar de liberar la memoria usada.
 */
char* game_get_obj_list_as_str(Game* game, Space* space);


/** 
 * @brief Devuelve el último espacio inspeccionado
 * @author Laura Bernal y Sandra Benitez
 * @param game Un puntero a la estructura game
 *  
 * @return El ultimo espacio inspeccionado
 */
Space* game_get_last_inspected_space(Game* game);

/** 
 * @brief Devuelve el ultimo objeto inspeccionado
 *  @author Laura Bernal y Sandra Benitez
 *  @param game Un puntero a la estructura game
 *  
 *  @return El ultimo objeto inspeccionado
 */
Object* game_get_last_inspected_object(Game* game);

/** 
 * @brief Devuelve la localización del jugador.
 * 
 * @author Mihai Blidaru
 * 
 * @param game Puntero a la estructura de l juego.
 * @return La localización del jugador. NO_ID si hay algun error.
 */
Id game_get_player_location(Game* game);

/** 
 * @brief Obtiene la localización  de un objeto.
 * 
 * @author Javier Bernardo
 * 
 * @param game Puntero a la estructura de el juego.
 * @param object El objeto del que quieres obtener la posicion.
 * @return La posicion del objeto o NO_ID en caso de error
 */
Id game_get_object_location(Game* game, Object* object);

/** 
 * @brief Imprime la información del juego
 * 
 * @author Profesores PPROG
 * @author Javier Bernardo
 * 
 * @param game Puntero a la estructura del juego.
 * @return Nada
 */
void game_print_data(Game* game);

/**
 * @brief  Devuelve un puntero al modulo dialogo del juego
 * 
 * @author Mihai Blidaru
 * @param game Puntero a la estructura del juego.
 * @return Un puntero al modulo dialogo del juego o NULL si hay algun error
 */
Dialogue* game_get_dialogue(Game* game);


#endif
