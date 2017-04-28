/**
 * @brief Implememtacion del dado del juego
 *
 * @file die.c
 * @author Javier Bernando
 * @version 1.0
 * @date 20-02-2017
 */

/*
 * Cabeceras libc
 */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/*
 * Cabeceras propias 
 */
#include "die.h"

/**
 * @brief Estructura de Die
 * 
 */
struct _Die {
    Id id;                      /*!< Identidad del dado */
	unsigned short number;		/*!< Valor de la última tirada del dado */
    int faces;                  /*!< Valor del numero de caras*/
};

/* @brief Crea un nuevo dado
 * 
 * @author Javier Bernardo
 * 
 * @param die_id Id que define el dado
 * @return dado creado
 */
Die* die_create(Id die_id) {
    Die* die = (Die*) malloc(sizeof (Die));
    if (!die)
        return NULL;
    die->id = die_id;
    die->number = 0;

    return die;
}

/* @brief Destruir un nuevo dado
 * 
 * @author Javier Bernardo
 * 
 * @param  die Die que quieres destruir
 * @return OK si se elimina, ERROR en caso contrario
 */
STATUS die_destroy(Die *die) {
    if (!die)
        return ERROR;
    free(die);
    return OK;
}

/* @brief Lanza el dado
 * 
 * @author Javier Bernardo
 * 
 * @param  die Die que quieres lanzar
 * @return Devuelve el valor del dado lanzado con valores entre 1 y el numero de caras
 */
unsigned short die_roll(Die* die) {
    int r = 0;
    if (!die)
        return -1;
    srand(time(NULL));
    r = rand() % die->faces;
    die->number = (r + 1);
    return (r + 1);
}

/* @brief Obtiene el ultimo valor del dado
 * 
 * @author Javier Bernardo
 * 
 * @param  die Die del que quieres saber su valor 
 * @return Devuelve el valor en int de la estructura numero del dado
 */
int die_get_number(Die* die) {
    if (!die)
        return -1;
    return (int) die->number;
}

/* @brief Imprimir el dado
 * 
 * @author Javier Bernardo
 * 
 * @param  die Die que quieres imprimir 
 * @return Impresion por pantalla del dado y su valor
 */
int die_print(Die* die) {
    if (!die)
        return -1;
    return printf("Die %ld has number: %hu\n", die->id, die->number);
}

/* @brief Coloca un numero de caras al dado
 * 
 * @author Javier Bernardo
 * 
 * @param  die Die que quieres lanzar
 * @param faces Numero de caras del dado
 * @return  OK si lo hace bien o ERROR si da algun problema
 */

STATUS die_set_faces(Die* die, int faces){
    if(!die)
        return ERROR;
    die->faces = faces;
    return OK;
}

/* @brief Coloca un numero de caras al dado
 * 
 * @author Javier Bernardo
 * 
 * @param  die Die que quieres lanzar
 * @return  El numero de caras del dado
 */
 
int die_get_faces(Die *die){
     if (!die)
        return -1;
        
    return die->faces;
 }