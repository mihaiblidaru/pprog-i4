/** 
 * @brief Define los prototipos de las funciones necesarias para cargar
 *        los datos del juego desde un archivo asi como guardar una partida
 * 
 * @file game_management.h
 * @author Javier Bernardo 
 * @author Mihai Blidaru
 * @version 1.0 
 * @date 23-01-2017
 * @copyright GNU Public License
 */
#ifndef GAMEMANAGEMENT_H
#define GAMEMANAGEMENT_H

/**
 * @brief Define los estados que puede devolver la función Save
 */
typedef enum {
    PROTECTED_FILE,       /*!< EL archivo donde se quiere guardar es un archivo protegido */
    SAVE_OK,              /*!< Se ha gaurdado todo sin problemas */
    WRITE_FAILED,         /*!< No se puede escribir en ese archivo */
    BAD_ARGUMENTS         /*!< Los argumentos de la función no son validos */
} SAVE_STATUS;

SAVE_STATUS game_management_save(Game* game, char* filename);

/** 
 * @brief Carga los datos del juego desde un archivo
 * @param game Un puntero al juego donde cargar los datos
 * @param filename nombre del archivo desde donde cargar los datos
 * @return OK si se ha cargado correctamente o ERROR en caso contrario
 */
STATUS game_management_load(Game* game, char* filename);

/** @brief Carga los datos del juego desde un archivo 
 * @author Javier Bernardo
 * 
 * @param game Puntero a la estructura del juego.
 * @param spacesFile Nombre del archivo desde donde hay que cargar los espacios
 * @param objectsFile Nombre del archivo desde donde hay que cargar los objetos
 * @param linksfile Nombre del archivo desde donde hay que cargar los links
 * @param playersFile Nombre del archivo desde donde hay que cargar los datos del jugador
 * @return OK si todo ha ido bien. ERROR en caso contrario.
 */
STATUS game_management_start_from_file(Game* game, char* spacesFile, char* objectsFile, char* linksfile, char* playersFile);


#endif