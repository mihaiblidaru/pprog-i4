/** 
 * @brief Define los prototipos de las funciones necesarias para el
 *        funcionamiento de las funciones de game_rules.c
 * 
 * @file game_rules.h
 * @author Laura Bernal
 * @author Sandra Benítez
 * @version 1.0 
 * @date 28-04-2017
 * @copyright GNU Public License
 */
#ifndef GAME_RULES_H
#define GAME_RULES_H

/** 
 * @brief Ejecuta una regla aleatoria que está en la lista de reglas
 * @author Laura Bernal
 * @param game Un puntero a la estructura del juego
 * @return OK si todo ha ido bien o ERROR en caso contrario
 */
STATUS game_rules_run_random_rule(Game* game);

#endif /*GAME_RULES_H*/