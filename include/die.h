/**
 * @brief Primitivas del TAD Die en el juego
 *
 * @file die.h
 * @author Javier Bernando
 * @version 1.0
 * @date 20-02-2017
 */
#ifndef DIE_H
#define DIE_H

#include "types.h"

/**
 * Id del dado por defecto 
 */
#define DIE_ID 1

/**
 *Definición del tipo
 */
typedef struct _Die Die;

/** @brief Crea un nuevo dado
 * 
 * @author Javier Bernardo
 * 
 * @param die_id Id que define el dado
 * @return dado creado
 */
Die* die_create(Id die_id);

/** @brief Destruir un nuevo dado
 * 
 * @author Javier Bernardo
 * 
 * @param  die Die que quieres destruir
 * @return OK si se elimina, ERROR en caso contrario
 */
STATUS die_destroy(Die* die);

/** @brief Lanza el dado
 * 
 * @author Javier Bernardo
 * 
 * @param  die Die que quieres lanzar
 * @return Devuelve el valor del dado lanzado con valores entre 1 y 6
 */
unsigned short die_roll(Die* die);

/** @brief Imprimir el dado
 * 
 * @author Javier Bernardo
 * 
 * @param  die Die que quieres imprimir 
 * @return Impresion por pantalla del dado y su valor
 */
int die_print(Die* die);

/** @brief Obtiene el ultimo valor del dado
 * 
 * @author Javier Bernardo
 * 
 * @param  die Die del que quieres saber su valor 
 * @return Devuelve el valor en int de la estructura numero del dado
 */
int die_get_number(Die* die);

#endif
