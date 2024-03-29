/** 
 * @brief It defines a textual graphic engine
 * 
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 18-01-2017
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"
/**
 * @brief Definicion de la estructura de graphic engine
 */
typedef struct _Graphic_engine Graphic_engine;

/** 
 * @brief Crea el motor del juego e inicializa las areas donde se va a imprimir
 *         por pantalla
 * @author Profesores PPROG
 * @return Un puntero al graphic_engine creado
 */
Graphic_engine* graphic_engine_create();

/**
 * @brief Libera la memoria ocupada por un graphic_engine
 * 
 * @author Profesores PPROG
 * @param ge El graphic_engine que se tiene que destruir
 * @return Nada
 */
void graphic_engine_destroy(Graphic_engine* ge);

/** 
 * @brief Imprime el juego por pantalla
 * 
 * @author Profesores PPROG
 * @author Javier Bernardo
 * @param ge Puntero a un graphic_engine
 * @param game Puntero a un juego
 */
void graphic_engine_paint_game(Graphic_engine* ge, Game* game);

/**
 * @brief Imprime las direcciones adyacentes de una casilla
 * @author Mihai Blidaru
 * @param fp Descriptor del fichero donde imprimir
 * @param game Un puntero a la estructura del juego
 */
void graphic_engine_paint_directions(FILE* fp, Game* game);

/**
 * @brief Imprime la pantalla de ayuda
 * @author Javier Bernardo
 * @param fp Descriptor del fichero donde imprimir
 */
void graphic_engine_paint_help(FILE* fp);

/**
 * @brief Imprime la intro del juego
 * @author Mihai Blidaru
 * @param fp Descriptor del fichero donde imprimir
 */
void graphic_engine_play_intro(FILE* fp);

/**
 * @brief Imprime la panatlla de final de juego
 * @author Mihai Blidaru
 * @param fp Descriptor del fichero donde imprimir
 */
void graphic_engine_game_over(FILE* fp);

#endif
