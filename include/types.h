/** 
 * @brief Define tipos de datos comunes
 * 
 * @file types.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

/**
 * @brief Definicion del tamaño global de cadenas de textp
 */
#define WORD_SIZE 1000
/**
 * @brief Definicion de la constante NO_ID (Id no valido)
 */
#define NO_ID -1
/**
 * @brief Definicion de un id generico
 */
#define GENERIC_ID 1

/**
 * @brief Definicion de Id
 */
typedef long Id;


/**
 * @brief Definicion de la enumeración BOOL
 */
typedef enum {
    FALSE, TRUE
} BOOL;

/**
 * @brief Definicion de la enumeración STATUS
 */
typedef enum {
    ERROR, OK, UNDEFINED
} STATUS;

#endif
