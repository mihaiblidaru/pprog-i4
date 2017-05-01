/** @brief Modulo necesario para imprimir por pantalla las areas del juego.
 *
 *  @file screen.c
 *  @author Profesores PPROG
 *  @date 11-01-2017
 *  @copyright GNU Public License
 */

/**
 * Cabeceras Libc
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Cabeceras propias */
#include "screen.h"

#pragma GCC diagnostic ignored "-Wpedantic"

/**
 * @cond
 * @brief Declaracion de la variable ROWS
 */
#define ROWS 22

/**
 * @brief Declaracion de la variable COLUMNS
 */
#define COLUMNS 80

/**
 * @brief Declaracion de la variable TOTAL_DATA
 */
#define TOTAL_DATA (ROWS * COLUMNS) + 1

/**
 * @brief Declaracion de la variable BG_CHAR
 */
#define BG_CHAR '~'

/**
 * @brief Declaracion de la variable FG_CHAR
 */
#define FG_CHAR ' '

/**
 * @brief Declaracion de la variable PROMPT
 */
#define PROMPT " prompt:> "

/**
 * @brief Declaracion de la macro ACCESS
 */
#define ACCESS(d, x, y) (d + ((y) * COLUMNS) + (x))


#define BEGIN_GREEN '['
#define BEGIN_RED ']'
#define BEGIN_YELlOW '{'
#define END_COLOR '}'
#define COLOR_RED     "\x1b[1;31m"
#define COLOR_GREEN   "\x1b[1;32m"
#define COLOR_YELLOW  "\x1b[1;33m"
#define COLOR_RESET   "\x1b[0m"

/*
 * @brief Estructura de Area
 *
 *
 */
struct _Area {
    int x;                   /*!< Variable x */
    int y;                   /*!< Variable y */
    int width;               /*!< Variable anchura */
    int height;              /*!< Variable altura */
    char *cursor;            /*!< Puntero a cursor */
};

/**
 * @brief Puntero a data
 */
char *__data;


/****************************/
/*     Private functions    */
/****************************/
int screen_area_cursor_is_out_of_bounds(Area* area); /*!< @private */
void screen_area_scroll_up(Area* area); /*!< @private */
void screen_utils_replaces_special_chars(char* str); /*!< @private */
void screen_print_colors(char* str);/*!< @private */
/**
 * @endcond
 */

/****************************/
/* Functions implementation */

/****************************/

/**
 * @brief Inicializa los datos para imprimir el juego en pantalla.
 */
void screen_init() {
    screen_destroy(); /* Dispose if previously initialized */
    __data = (char *) malloc(sizeof (char) * TOTAL_DATA);

    if (__data) {
        memset(__data, (int) BG_CHAR, TOTAL_DATA); /*Fill the background*/
        *(__data + TOTAL_DATA - 1) = '\0'; /*NULL-terminated string*/
    }
}

/**
 * @brief Destruye los datos usados para imprimir el juego en pantalla
 */
void screen_destroy() {
    if (__data)
        free(__data);
}

/*
 * @brief Imprime el juego en pantalla
 */
void screen_paint() {
    char *src = NULL;
    char dest[COLUMNS + 1];

    memset(dest, 0, COLUMNS + 1);

    if (__data) {
        /* puts(__data); */ /*Dump data directly to the terminal*/
        /*It works fine if the terminal window has the right size*/

        puts("\033[2J"); /*Clear the terminal*/
        for (src = __data; src < (__data + TOTAL_DATA - 1); src += COLUMNS) {
            memcpy(dest, src, COLUMNS);
            screen_print_colors(dest);
        }
    }
}

void screen_print_colors(char* str){
      int i;
      int len = 0;
      len = strlen(str);
      for(i=0; i < len; i++){
        if(str[i] == BEGIN_GREEN){
          printf(" %s", COLOR_GREEN);
        }else if(str[i] == BEGIN_RED){
          printf(" %s", COLOR_RED);
        }else if(str[i] == BEGIN_YELlOW){
          printf(" %s", COLOR_YELLOW);
        }else if(str[i] == END_COLOR){
          printf(" %s", COLOR_RESET);
        }else{
          putc(str[i],stdout);
        }
      }
       fprintf(stdout,"\n");
      /*fprintf(stdout, "%s\n", str);*/
}


/**
 * @brief Obtiene una pantalla
 * @param str Puntero a cadena para indicar que pantalla cojer
 */
void screen_gets(char *str) {
    fprintf(stdout, PROMPT);
    if (fgets(str, COLUMNS, stdin))
        *(str + strlen(str) - 1) = 0; /* Replaces newline character with '\0' */
}

/*
 * @brief Crea un area
 * @param x Posición x del area
 * @param y Posición y del area
 * @param width Ancho del area
 * @param height Alto del area
 *
 * @return area creada
 */
Area* screen_area_init(int x, int y, int width, int height) {
    int i = 0;
    Area* area = NULL;
    if(x < 1 || y < 1 || width < 1 || height < 1)
        return NULL;

    if ((area = (Area*) malloc(sizeof (struct _Area)))) {
      *area = (struct _Area){
        x,
        y,
        width,
        height,
        ACCESS(__data, x, y)
      };

        for (i = 0; i < area->height; i++)
            memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
    }

    return area;
}

/*
 * @brief Destruye un area
 * @param area Area que tiene que destruir
 */
void screen_area_destroy(Area* area) {
    if (area)
        free(area);
}

/*
 * @brief Despeja un area
 * @param area Area del cual tiene que quitar el texto
 *
 */
void screen_area_clear(Area* area) {
    int i = 0;

    if (area) {
        screen_area_reset_cursor(area);

        for (i = 0; i < area->height; i++)
            memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
    }
}

/*
 * @brief Resetea el cursor en un area
 * @param area Area del cual se quiere resetear el cursor
 *
 */
void screen_area_reset_cursor(Area* area) {
    if (area)
        area->cursor = ACCESS(__data, area->x, area->y);
}

/*
 * @brief Escribe texto en un area
 * @param area Area en el cual escribir
 * @param str Cadena de texto que se quiere imprimir en el area
 */
void screen_area_puts(Area* area, char *str) {
    int len = 0;
    char *ptr = NULL;
    if (screen_area_cursor_is_out_of_bounds(area))
        screen_area_scroll_up(area);

    screen_utils_replaces_special_chars(str);

    for (ptr = str; ptr < (str + strlen(str)); ptr += area->width) {
        memset(area->cursor, FG_CHAR, area->width);
        len = (strlen(ptr) < area->width) ? strlen(ptr) : area->width;
        memcpy(area->cursor, ptr, len);
        area->cursor += COLUMNS;
    }
}

/**
 * @cond
 * @brief Indica un error de cursor fuera del area
 * @param area Area en el cual se hace la comprobación
 *
 */
int screen_area_cursor_is_out_of_bounds(Area* area) {
    return area->cursor > ACCESS(__data,
            area->x + area->width,
            area->y + area->height - 1);
}

/**
 * @brief Desplaza hace scroll en un area.
 *          A medida que un area se va llenando con texto, si se sobrepasa
 *          el numero de filas del area, se hace un scroll y se descarta lo que
 *          no entra en pantalla.
 * @param area Area en la cual se hace scroll
 *
 */
void screen_area_scroll_up(Area* area) {
    for (area->cursor = ACCESS(__data, area->x, area->y);
            area->cursor < ACCESS(__data, area->x + area->width, area->y + area->height - 2);
            area->cursor += COLUMNS) {
        memcpy(area->cursor, area->cursor + COLUMNS, area->width);
    }
}

/**
 * @brief Reemplaza caracteres no imprimibles en una cadena
 * @param str Cadena en la cual sustituir esos caracteres
 * @author Profesores PPROG
 *
 */
void screen_utils_replaces_special_chars(char* str) {
    char *pch = NULL;

    /* Replaces acutes and tilde with '??' */
    while ((pch = strpbrk(str, "ÁÉÍÓÚÑáéíóúñ")))
        memcpy(pch, "??", 2);
}
/**
 * @endcond
 */
