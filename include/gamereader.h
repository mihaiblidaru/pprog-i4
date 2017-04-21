/** 
 * @brief Define los prototipos de las funciones necesarias para cargar
 *        los datos del juego desde un archivo
 * 
 * @file gamereader.h
 * @author Javier Bernardo 
 * @author Mihai Blidaru
 * Pareja 7
 * @version 1.0 
 * @date 31-01-2017
 * @copyright GNU Public License
 */

#ifndef GAMEREADER_H
#define GAMEREADER_H

#include "game.h"
#include "types.h"

/** @brief Carga los datos del juego desde un archivo e inicializa la posición
 *         inicial del jugador y del objeto
 *  
 * @author Profesores PPROG
 * 
 * @param game Puntero a la estructura del juego.
 * @param spacesFile Nombre del archivo desde donde hay que cargar los espacios
 * @param objectsFile Nombre del archivo desde donde hay que cargar los objetos
 * @param linksfile Nombre del archivo desde donde hay que cargar los links
 * @param playersFile Nombre del archivo desde donde hay que cargar los datos del jugador
 * @return OK si todo ha ido bien. ERROR en caso contrario.
 */
STATUS game_create_from_file(Game* game, char* spacesFile, char* objectsFile, char* linksfile, char* playersFile);

/**
 * @brief Carga los espacio del juego y los objetos de cada espacio
 *  
 * @author Mihai Blidaru
 * 
 * @param game Un puntero a la estructura del juego
 * @param filename El nombre del archivo 
 * @return ERROR si se ha cargado mal los espacio u OK si se ha cargado bien los espacios.
 */
STATUS game_load_spaces(Game* game, char* filename);

/**
 * @brief Carga los objetos de cada espacio
 *  
 * @author Javier Bernardo
 * 
 * @param game Un puntero a la estructura del juego
 * @param filename El nombre del archivo 
 * @return ERROR si se ha cargado mal los espacio u OK si se ha cargado bien los espacios.
 */
STATUS game_load_objects(Game* game, char* filename);

/** @brief Carga los enlaces desde un archivo
 *  @author Mihai Blidaru
 *  @param game Un juego
 *  @param filename Nombre del archivo desde el cual se cargan los enlaces
 *  
 *  @return OK si ha conseguido cargar correctamente o ERROR en caso contrario.
 */
STATUS game_load_links(Game* game, char* filename);

/** @brief Carga los datos del jugador desde un archivo
*  @author Mihai Blidaru
*  @param game Un juego
*  @param filename Nombre del archivo desde el cual se cargan los datos del jugador
*  
*  @return OK si ha conseguido cargar correctamente o ERROR en caso contrario.
*/
STATUS game_load_players(Game* game, char* filename);

#endif
