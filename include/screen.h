/** 
 * @brief Define la intefaz pública del TAD screen
 * 
 * @file screen.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 11-01-2017
 * @copyright GNU Public License
 */

#ifndef __SCREEN__
#define __SCREEN__

/**
 * Definicion de la variable SCREEN_MAX_STR
 */
#define SCREEN_MAX_STR 80

/**
 * Definicion de la estructura Area
 */
typedef struct _Area Area;

/**
 * @brief Inicializa los datos para imprimir el juego en pantalla.
 */
void screen_init();

/**
 * @brief Destruye los datos usados para imprimir el juego en pantalla
 */
void screen_destroy();

/**
 * @brief Imprime el juego en pantalla
 */
void screen_paint();
void screen_gets(char *str);

/**
 * @brief Crea un area
 * @param x Posición x del area
 * @param y Posición y del area
 * @param width Ancho del area
 * @param height Alto del area
 * 
 * @return area creada
 */
Area* screen_area_init(int x, int y, int width, int height);

/**
 * @brief Destruye un area
 * @param area Area que tiene que destruir
 */
void screen_area_destroy(Area* area);

/**
 * @brief Despeja un area
 * @param area Area del cual tiene que quitar el texto
 * 
 */
void screen_area_clear(Area* area);

/**
 * @brief Resetea el cursor en un area
 * @param area Area del cual se quiere resetear el cursor
 * 
 */
void screen_area_reset_cursor(Area* area);

/**
 * @brief Escribe texto en un area
 * @param area Area en el cual escribir
 * @param str Cadena de texto que se quiere imprimir en el area
 */
void screen_area_puts(Area* area, char *str);

#endif
