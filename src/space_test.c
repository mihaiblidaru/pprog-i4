/** 
 * @brief It tests space module
 * 
 * @file space_test.c
 * @author Profesores Pprog
 * @version 2.0 
 * @date 16-01-2015
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "space.h"
#include "space_test.h"
#include "test.h"

/**
 * Número máximo de pruebas para el módulo space
 * @cond
 */
#define MAX_TESTS 58

/** 
 * @brief Funcion principal de pruebas para el modulo Space. 
 * 
 * Dos modos de ejecucion:
 *   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas 
 *   2.-Si se ejecuta con un numero entre 1 y el numero de pruebas solo ejecuta 
 *      la prueba indicada  
 *  @private
 */
int main(int argc, char** argv) {

    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module Space:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_space_create();
    if (all || test == 2) test2_space_create();
    if (all || test == 3) test3_space_create();
    if (all || test == 4) test1_space_set_name();
    if (all || test == 5) test2_space_set_name();
    if (all || test == 6) test3_space_set_name();
    if (all || test == 7) test1_space_set_description();
    if (all || test == 8) test2_space_set_description();
    if (all || test == 9) test3_space_set_description();
    if (all || test == 10) test1_space_set_graphics();
    if (all || test == 11) test2_space_set_graphics();
    if (all || test == 12) test1_space_set_north();
    if (all || test == 13) test2_space_set_north();
    if (all || test == 14) test3_space_set_north();
    if (all || test == 15) test1_space_set_south();
    if (all || test == 16) test2_space_set_south();
    if (all || test == 17) test3_space_set_south();
    if (all || test == 18) test1_space_set_east();
    if (all || test == 19) test2_space_set_east();
    if (all || test == 20) test3_space_set_east();
    if (all || test == 21) test1_space_set_west();
    if (all || test == 22) test2_space_set_west();
    if (all || test == 23) test3_space_set_west();
    if (all || test == 24) test1_space_get_id();
    if (all || test == 25) test2_space_get_id();
    if (all || test == 26) test1_space_get_name();
    if (all || test == 27) test2_space_get_name();
    if (all || test == 28) test3_space_get_name();
    if (all || test == 29) test1_space_get_description();
    if (all || test == 30) test2_space_get_description();
    if (all || test == 31) test3_space_get_description();
    if (all || test == 32) test1_space_get_graphics();
    if (all || test == 33) test2_space_get_graphics();
    if (all || test == 34) test1_space_get_objects();
    if (all || test == 35) test1_space_get_objects();
    if (all || test == 36) test1_space_get_north();
    if (all || test == 37) test2_space_get_north();
    if (all || test == 38) test3_space_get_north();
    if (all || test == 39) test1_space_get_south();
    if (all || test == 40) test2_space_get_south();
    if (all || test == 41) test3_space_get_south();
    if (all || test == 42) test1_space_get_east();
    if (all || test == 43) test2_space_get_east();
    if (all || test == 44) test3_space_get_east();
    if (all || test == 45) test1_space_get_west();
    if (all || test == 46) test2_space_get_west();
    if (all || test == 47) test3_space_get_west();
    if (all || test == 48) test1_space_add_object();
    if (all || test == 49) test2_space_add_object();
    if (all || test == 50) test3_space_add_object();
    if (all || test == 51) test1_space_remove_object();
    if (all || test == 52) test2_space_remove_object();
    if (all || test == 53) test3_space_remove_object();
    if (all || test == 54) test4_space_remove_object();
    if (all || test == 55) test1_space_contains_object();
    if (all || test == 56) test2_space_contains_object();
    if (all || test == 57) test3_space_contains_object();
    if (all || test == 58) test1_space_graphics_areEmpty();
    if (all || test == 59) test2_space_graphics_areEmpty();
    if (all || test == 60) test3_space_graphics_areEmpty();
    PRINT_PASSED_PERCENTAGE;

    return 1;
}

/**
 * @endcond
 */

/*
 * @test Prueba la función de creación de un espacio
 * @pre Un identificador como parámetro
 * @post Un puntero no nulo al espacio creado
 */
void test1_space_create() {
  Space* s = NULL;
  int result = 0;
  s = space_create(5);
  result = s != NULL;
  PRINT_TEST_RESULT(result);
  space_destroy(s);
}

/*
 * @test Prueba la función de creación de un espacio
 * @pre Un identificador como parámetro
 * @post El identificador del espacio es el introducido
 */
void test2_space_create() {
    Space *s = NULL;
    s = space_create(4);
    PRINT_TEST_RESULT(space_get_id(s) == 4);
    space_destroy(s);
}

/*
 * @test Prueba la función de creación de un espacio
 * @pre El identificador del espacio es NO_ID
 * @post La salida esperada es un puntero a NULL
 */
void test3_space_create() {
    Space *s = NULL;
    s = space_create(NO_ID);
    PRINT_TEST_RESULT(s == NULL);
}

/*
 * @test Prueba la función para establecer el nombre de un espacio
 * @pre Nombre que establecer al espacio
 * @post La salida debe ser OK
 */
void test1_space_set_name() {
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
    space_destroy(s);
}

/*
 * @test Prueba la función para establecer el nombre de un espacio
 * @pre El espacio al que establecer el nombre es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_name() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}

/*
 * @test Prueba la función para establecer el nombre de un espacio
 * @pre El espacio es un puntero no NULL, pero el nombre a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_space_set_name() {
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
    space_destroy(s);
}

/*
 * @test Prueba la función para establecer la descripción de un espacio
 * @pre Nombre que establecer al espacio
 * @post La salida debe ser OK
 */
void test1_space_set_description() {
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_description(s, "hola") == OK);
    space_destroy(s);
}

/*
 * @test Prueba la función para establecer la descripción de un espacio
 * @pre El espacio al que establecer la descripción es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_description() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_description(s, "hola") == ERROR);
}

/*
 * @test Prueba la función para establecer la descripción de un espacio
 * @pre El espacio es un puntero no NULL, pero la descripción a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_space_set_description() {
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_description(s, NULL) == ERROR);
    space_destroy(s);
}

/*
 * @test Prueba la función que establece los graficos de una casilla
 * @pre Unos graficos aleatorios
 * @post La salida esperada es un puntero al espacio
 */
void test1_space_set_graphics(){
    Space *s = NULL;
    char graphics[G_ROWS][G_COLUMNS] = {"aaaaaaa", "bbbbbbb", "ccccccc"};
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_graphics(s, graphics) == s);
    space_destroy(s);
}

/*
 * @test Prueba la función que establece los graficos de una casilla
 * @pre El espacio es un puntero a NULL
 * @post La salida esperada es un puntero a NULL
 */ 
void test2_space_set_graphics(){
    Space *s = NULL;
    char graphics[G_ROWS][G_COLUMNS] = {"aaaaaaa", "bbbbbbb", "ccccccc"};
    PRINT_TEST_RESULT(space_set_graphics(s, graphics) == NULL);
}

/*
 * @test Prueba la función que establece el enlace norte de un espacio
 * @pre Id del enlace
 * @post La salida esperada es OK
 */
void test1_space_set_north() {
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_north(s, 4) == OK);
    space_destroy(s);
}

/*
 * @test Prueba la función que establece el enlace norte de un espacio
 * @pre El espacio al que establecer el enclace es un puntero a NULL
 * @post La salida esperada es ERROR
 */
void test2_space_set_north() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_north(s, 4) == ERROR);
}

/*
 * @test Prueba la función que establece el enlace norte de un espacio
 * @pre El id que se le pasa a la función es NO_ID
 * @post La salida esperada es ERROR
 */ 
void test3_space_set_north(){
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_north(s, NO_ID) == ERROR);
    space_destroy(s);
}

/*
 * @test Prueba la función que establece el enlace sur de un espacio
 * @pre A la función se le pasa el identificador 4
 * @post La salida esperada es OK
 */
void test1_space_set_south() {
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_south(s, 4) == OK);
    space_destroy(s);
}

/*
 * @test Prueba la función que establece el enlace sur de un espacio
 * @pre El espacio al que establecer el enclace es un puntero a NULL
 * @post
 */
void test2_space_set_south() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_south(s, 4) == ERROR);
}

/*
 * @test Prueba la función que establece el enlace sur de un espacio
 * @pre El id que se le pasa a la función es NO_ID
 * @post La salida esperada es ERROR
 */ 
void test3_space_set_south(){
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_south(s, NO_ID) == ERROR);
    space_destroy(s);
}

/*
 * @test Prueba la función que establece el enlace este de un espacio
 * @pre A la función se le pasa el identificador 4
 * @post La salida esperada es OK
 */
void test1_space_set_east() {
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_east(s, 4) == OK);
    space_destroy(s);
}

/*
 * @test Prueba la función que establece el enlace este de un espacio
 * @pre El espacio al que establecer el enclace es un puntero a NULL
 * @post
 */
void test2_space_set_east() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_east(s, 4) == ERROR);
}

/*
 * @test Prueba la función que establece el enlace este de un espacio
 * @pre El id que se le pasa a la función es NO_ID
 * @post La salida esperada es ERROR
 */ 
void test3_space_set_east(){
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_east(s, NO_ID) == ERROR);
    space_destroy(s);
}

/*
 * @test Prueba la función que establece el enlace oeste de un espacio
 * @pre A la función se le pasa el identificador 4
 * @post La salida esperada es OK
 */
void test1_space_set_west() {
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_west(s, 4) == OK);
    space_destroy(s);
}

/*
 * @test Prueba la función que establece el enlace oeste de un espacio
 * @pre El espacio al que establecer el enclace es un puntero a NULL
 * @post La salida esperada es ERROR
 */
void test2_space_set_west() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_west(s, 4) == ERROR);
}

/*
 * @test Prueba la función que establece el enlace oeste de un espacio
 * @pre El id que se le pasa a la función es NO_ID
 * @post La salida esperada es ERROR
 */ 
void test3_space_set_west(){
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_west(s, NO_ID) == ERROR);
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve el id de una casilla
 * @pre Al espacio se le ha establecido un id (12)
 * @post La salida esperada es el id establecido 12
 */
void test1_space_get_id(){
    Space *s = NULL;
    s = space_create(12);
    PRINT_TEST_RESULT(space_get_id(s) == 12);
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve el id de una casilla
 * @pre El espacio es un puntero a NULL
 * @post La salida esperada es NO_ID
 */
void test2_space_get_id(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

/*
 * @test Prueba la función que devuelve el nombre de una casilla
 * @pre Al espacio se le ha establecido un nombre previamente
 * @post La salda debe ser el nombre previamente establecido
 */
void test1_space_get_name(){
    Space *s = NULL;
    s = space_create(5);
    space_set_name(s,"Casilla");
    PRINT_TEST_RESULT(strcmp(space_get_name(s), "Casilla") == 0);
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve el nombre de una casilla
 * @pre El espacio es un puntero a NULL
 * @post La salda debe ser un puntero a NULL
 */
void test2_space_get_name(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

/*
 * @test Prueba la función que devuelve el nombre de una casilla
 * @pre El espacio ha sido inicializado pero no se le ha establecido ningun nombre
 * @post La salida debe ser una cadena vacila
 */
void test3_space_get_name(){
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(strcmp(space_get_name(s), "") == 0);
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve la descripción de una casilla
 * @pre Al espacio se le ha establecido una descripción previamente
 * @post La salda debe ser la descripción previamente establecida
 */
void test1_space_get_description(){
    Space *s = NULL;
    s = space_create(5);
    space_set_description(s,"Casilla");
    PRINT_TEST_RESULT(strcmp(space_get_description(s), "Casilla") == 0);
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve la descripción de una casilla
 * @pre El espacio es un puntero a NULL
 * @post La salda debe ser un puntero a NULL
 */
void test2_space_get_description(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_description(s) == NULL);
}

/*
 * @test Prueba la función que devuelve la descripción de una casilla
 * @pre El espacio ha sido inicializado pero no se le ha establecido ninguna descripción
 * @post La salida debe ser una cadena vacila
 */
void test3_space_get_description(){
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(strcmp(space_get_description(s), "") == 0);
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve los graficos de una casilla
 * @pre A la casilla se le han establecido graficos previamente
 * @post La salida tiene que ser igual a los graficos establecidos previamente
 */
void test1_space_get_graphics(){
    Space *s = NULL;
    char graphics[G_ROWS][G_COLUMNS] = {"aaaaaaa", "bbbbbbb", "ccccccc"};
    char ret[G_ROWS][G_COLUMNS];
    s = space_create(5);
    space_set_graphics(s, graphics);
    space_get_graphics(s, ret);
    PRINT_TEST_RESULT(!strcmp(ret[0],graphics[0]) || !strcmp(ret[1],graphics[1]) || !strcmp(ret[2],graphics[2]));
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve los graficos de una casilla
 * @pre El espacio ha sido inicializado pero no se le han establecido graficos
 * @post La salida debe ser una matriz de 3 cadenas de 7 caracteres llenas de espacios
 */
void test2_space_get_graphics(){
    Space *s = NULL;
    char ret[G_ROWS][G_COLUMNS];
    s = space_create(5);
    space_get_graphics(s, ret);
    PRINT_TEST_RESULT(!strcmp(ret[0],"       ") || !strcmp(ret[1],"       ") || !strcmp(ret[2],"       "));
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve el set de objetos de una casilla
 * @pre El espacio ha sido previamente inicializado.
 * @post La salida debe ser diferente de NULL.
 */
void test1_space_get_objects(){
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_get_objects(s) != NULL);
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve el set de objetos de una casilla
 * @pre El espacio es un puntero a NULL
 * @post La salida debe ser NULL
 */
void test2_space_get_objects(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_objects(s) == NULL);
}

/*
 * @test Prueba la función que devuelve el enlace norte de una casilla
 * @pre Se ha añadido previamente un enlace on id 7
 * @post La salida debe ser el id del enlace 7
 */
void test1_space_get_north(){
    Space *s = NULL;
    s = space_create(5);
    space_set_north(s, 7);
    PRINT_TEST_RESULT(space_get_north(s) == 7);
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve el enlace norte de una casilla
 * @pre El espacio es un puntero a NULL.
 * @post La salida debe ser NO_ID.
 */
void test2_space_get_north(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_north(s) == NO_ID);
}

/*
 * @test Prueba la función que devuelve el enlace norte de una casilla
 * @pre No se ha establecido ningun enlace previamente
 * @post La salida debe ser NO_ID.
 */
void test3_space_get_north(){
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_get_north(s) == NO_ID);
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve el enlace sur de una casilla
 * @pre Se ha añadido previamente un enlace on id 7
 * @post La salida debe ser el id del enlace 7
 */
void test1_space_get_south(){
    Space *s = NULL;
    s = space_create(5);
    space_set_south(s, 7);
    PRINT_TEST_RESULT(space_get_south(s) == 7);
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve el enlace sur de una casilla
 * @pre El espacio es un puntero a NULL.
 * @post La salida debe ser NO_ID.
 */
void test2_space_get_south(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_south(s) == NO_ID);
}

/*
 * @test Prueba la función que devuelve el enlace sur de una casilla
 * @pre No se ha establecido ningun enlace previamente
 * @post La salida debe ser NO_ID.
 */
void test3_space_get_south(){
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_get_south(s) == NO_ID);
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve el enlace este de una casilla
 * @pre Se ha añadido previamente un enlace on id 7
 * @post La salida debe ser el id del enlace 7
 */
void test1_space_get_east(){
    Space *s = NULL;
    s = space_create(5);
    space_set_east(s, 7);
    PRINT_TEST_RESULT(space_get_east(s) == 7);
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve el enlace este de una casilla
 * @pre El espacio es un puntero a NULL.
 * @post La salida debe ser NO_ID.
 */
void test2_space_get_east(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_east(s) == NO_ID);
}

/*
 * @test Prueba la función que devuelve el enlace este de una casilla
 * @pre No se ha establecido ningun enlace previamente
 * @post La salida debe ser NO_ID.
 */
void test3_space_get_east(){
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_get_east(s) == NO_ID);
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve el enlace oeste de una casilla
 * @pre Se ha añadido previamente un enlace on id 7
 * @post La salida debe ser el id del enlace 7
 */
void test1_space_get_west(){
    Space *s = NULL;
    s = space_create(5);
    space_set_west(s, 7);
    PRINT_TEST_RESULT(space_get_west(s) == 7);
    space_destroy(s);
}

/*
 * @test Prueba la función que devuelve el enlace oeste de una casilla
 * @pre El espacio es un puntero a NULL.
 * @post La salida debe ser NO_ID.
 */
void test2_space_get_west(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_west(s) == NO_ID);
}

/*
 * @test Prueba la función que devuelve el enlace oeste de una casilla
 * @pre No se ha establecido ningun enlace previamente
 * @post La salida debe ser NO_ID.
 */ 
void test3_space_get_west(){
    Space *s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_get_west(s) == NO_ID);
    space_destroy(s);
}

/*
 * @test Prueba la función que añade un objeto a una casilla
 * @pre El espacio es un puntero a NULL.
 * @post La salida debe ser ERROR.
 */ 
void test1_space_add_object(){
    Space* s = NULL;
    PRINT_TEST_RESULT(space_add_object(s, 10) == ERROR);
}

/*
 * @test Prueba la función que añade un objeto a una casilla
 * @pre Se añade un objeto con id 10
 * @post La salida debe ser OK.
 */ 
void test2_space_add_object(){
    Space* s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_add_object(s, 10) == OK);
    space_destroy(s);
}

/*
 * @test Prueba la función que añade un objeto a una casilla
 * @pre El id del objeto es -1 (NO_ID)
 * @post La salida debe ser ERROR.
 */ 
void test3_space_add_object(){
    Space* s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_add_object(s, -1) == ERROR);
    space_destroy(s);
}

/*
 * @test Prueba la función que quita un objeto de una casilla
 * @pre Se añade un objeto previamente
 * @post La salida debe ser OK.
 */ 
void test1_space_remove_object(){
    Space* s = NULL;
    s = space_create(5);
    space_add_object(s, 2);
    PRINT_TEST_RESULT(space_remove_object(s, 2) == OK);
    space_destroy(s);
}

/*
 * @test Prueba la función que quita un objeto de una casilla
 * @pre Todavia no he ha añadido ningun objeto
 * @post La salida debe ser ERROR.
 */ 
void test2_space_remove_object(){
    Space* s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_remove_object(s, 2) == ERROR);
    space_destroy(s);
}

/*
 * @test Prueba la función que quita un objeto de una casilla
 * @pre El espacio no se ha inicializado previamente
 * @post La salida debe ser ERROR.
 */ 
void test3_space_remove_object(){
    Space* s = NULL;
    PRINT_TEST_RESULT(space_remove_object(s, 2) == ERROR);
}

/*
 * @test Prueba la función que quita un objeto de una casilla
 * @pre El objeto ya ha sido eliminado previamente
 * @post La salida debe ser ERROR.
 */ 
void test4_space_remove_object(){
    Space* s = NULL;
    s = space_create(5);
    space_add_object(s, 2);
    space_remove_object(s, 2);
    PRINT_TEST_RESULT(space_remove_object(s, 2) == ERROR);
    space_destroy(s);
}

/*
 * @test Prueba la función que comprueba si una casilla contiene un objeto
 * @pre El espacio se ha inicializado y se ha añadido un objeto
 * @post La salida esperada es TRUE
 */
void test1_space_contains_object(){
    Space* s = NULL;
    s = space_create(5);
    space_add_object(s, 1);
    PRINT_TEST_RESULT(space_contains_object(s, 1) == TRUE);
    space_destroy(s);
}

/*
 * @test Prueba la función que comprueba si una casilla contiene un objeto
 * @pre El espacio no se ha inicializado.
 * @post La salida esperada es FALSE
 */
void test2_space_contains_object(){
    Space* s = NULL;
    PRINT_TEST_RESULT(space_contains_object(s, 1) == FALSE);
}

/*
 * @test Prueba la función que comprueba si una casilla contiene un objeto
 * @pre El espacio se ha creado pero no se ha añadido ningun objeto
 * @post La salida esperada es FALSE
 */
void test3_space_contains_object(){
    Space* s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_contains_object(s, 1) == FALSE);
    space_destroy(s);
}

/*
 * @test Prueba la función que comprueba si los graficos de una casilla están vacios.
 * @pre El espacio se ha creado y se le han establecido unos graficos
 * @post La salida esperada es FALSE
 */
void test1_space_graphics_areEmpty(){
    Space* s = NULL;
    char graphics[G_ROWS][G_COLUMNS] = {"aaaaaaa", "bbbbbbb", "ccccccc"};
    s = space_create(5);
    space_set_graphics(s, graphics);
    PRINT_TEST_RESULT(space_graphics_areEmpty(s) == FALSE);
    space_destroy(s);
}

/*
 * @test Prueba la función que comprueba si los graficos de una casilla están vacios.
 * @pre El espacio no se ha inicializado
 * @post La salida esperada es TRUE.
 */
void test2_space_graphics_areEmpty(){
    Space* s = NULL;
    PRINT_TEST_RESULT(space_graphics_areEmpty(s) == TRUE);
}

/*
 * @test Prueba la función que comprueba si los graficos de una casilla están vacios.
 * @pre El espacio se ha creado pero no se le han establecido graficos
 * @post La salida esperada es TRUE
 */
void test3_space_graphics_areEmpty(){
    Space* s = NULL;
    s = space_create(5);
    PRINT_TEST_RESULT(space_graphics_areEmpty(s) == TRUE);   
    space_destroy(s);
}