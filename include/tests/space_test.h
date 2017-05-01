/**
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Javier Bernardo
 * @author Sandra Benitez
 * @version 2.0 
 * @date 29-03-2016
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Prueba la función de creación de un espacio
 * @pre Un identificador como parámetro
 * @post Un puntero no nulo al espacio creado
 */
void test1_space_create();

/**
 * @test Prueba la función de creación de un espacio
 * @pre Un identificador como parámetro
 * @post El identificador del espacio es el introducido
 */
void test2_space_create();

/**
 * @test Prueba la función de creación de un espacio
 * @pre El identificador del espacio es NO_ID
 * @post La salida esperada es un puntero a NULL
 */
void test3_space_create();

/**
 * @test Prueba la función para establecer el nombre de un espacio
 * @pre Nombre que establecer al espacio
 * @post La salida debe ser OK
 */
void test1_space_set_name();

/**
 * @test Prueba la función para establecer el nombre de un espacio
 * @pre El espacio al que establecer el nombre es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_name();

/**
 * @test Prueba la función para establecer el nombre de un espacio
 * @pre El espacio es un puntero no NULL, pero el nombre a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_space_set_name();

/**
 * @test Prueba la función para establecer la descripción de un espacio
 * @pre Nombre que establecer al espacio
 * @post La salida debe ser OK
 */
void test1_space_set_description();

/**
 * @test Prueba la función para establecer la descripción de un espacio
 * @pre El espacio al que establecer la descripción es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_description();

/**
 * @test Prueba la función para establecer la descripción de un espacio
 * @pre El espacio es un puntero no NULL, pero la descripción a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_space_set_description();

/**
 * @test Prueba la función para establecer la descripción larga de un espacio
 * @pre Nombre que establecer al espacio
 * @post La salida debe ser OK
 */
void test1_space_set_long_description();

/**
 * @test Prueba la función para establecer la descripción larga de un espacio
 * @pre El espacio al que establecer la descripción es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_long_description();

/**
 * @test Prueba la función para establecer la descripción larga de un espacio
 * @pre El espacio es un puntero no NULL, pero la descripción a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_space_set_long_description();

/**
 * @test Prueba la función que establece los graficos de una casilla
 * @pre Unos graficos aleatorios
 * @post La salida esperada es un puntero al espacio
 */
void test1_space_set_graphics();

/**
 * @test Prueba la función que establece los graficos de una casilla
 * @pre El espacio es un puntero a NULL
 * @post La salida esperada es un puntero a NULL
 */ 
void test2_space_set_graphics();

/**
 * @test Prueba la función que establece el enlace norte de un espacio
 * @pre Id del enlace
 * @post La salida esperada es OK
 */
void test1_space_set_north();

/**
 * @test Prueba la función que establece el enlace norte de un espacio
 * @pre El espacio al que establecer el enclace es un puntero a NULL
 * @post La salida esperada es ERROR
 */
void test2_space_set_north();

/**
 * @test Prueba la función que establece el enlace norte de un espacio
 * @pre El id que se le pasa a la función es NO_ID
 * @post La salida esperada es ERROR
 */ 
void test3_space_set_north();

/**
 * @test Prueba la función que establece el enlace sur de un espacio
 * @pre A la función se le pasa el identificador 4
 * @post La salida esperada es OK
 */
void test1_space_set_south();

/**
 * @test Prueba la función que establece el enlace sur de un espacio
 * @pre El espacio al que establecer el enclace es un puntero a NULL
 * @post
 */
void test2_space_set_south();

/**
 * @test Prueba la función que establece el enlace sur de un espacio
 * @pre El id que se le pasa a la función es NO_ID
 * @post La salida esperada es ERROR
 */ 
void test3_space_set_south();

/**
 * @test Prueba la función que establece el enlace este de un espacio
 * @pre A la función se le pasa el identificador 4
 * @post La salida esperada es OK
 */
void test1_space_set_east();

/**
 * @test Prueba la función que establece el enlace este de un espacio
 * @pre El espacio al que establecer el enclace es un puntero a NULL
 * @post La saida esperada es ERROR
 */
void test2_space_set_east();

/**
 * @test Prueba la función que establece el enlace este de un espacio
 * @pre El id que se le pasa a la función es NO_ID
 * @post La salida esperada es ERROR
 */ 
void test3_space_set_east();

/**
 * @test Prueba la función que establece el enlace oeste de un espacio
 * @pre A la función se le pasa el identificador 4
 * @post La salida esperada es OK
 */
void test1_space_set_west();

/**
 * @test Prueba la función que establece el enlace oeste de un espacio
 * @pre El espacio al que establecer el enclace es un puntero a NULL
 * @post La salida esperada es ERROR
 */
void test2_space_set_west();

/**
 * @test Prueba la función que establece el enlace oeste de un espacio
 * @pre El id que se le pasa a la función es NO_ID
 * @post La salida esperada es ERROR
 */ 
void test3_space_set_west();

/**
 * @test Prueba la función que establece el enlace superior de un espacio
 * @pre A la función se le pasa el identificador 4
 * @post La salida esperada es OK
 */
void test1_space_set_up();

/**
 * @test Prueba la función que establece el enlace superior de un espacio
 * @pre El espacio al que establecer el enclace es un puntero a NULL
 * @post La salida esperada es ERROR
 */
void test2_space_set_up();

/**
 * @test Prueba la función que establece el enlace superior de un espacio
 * @pre El id que se le pasa a la función es NO_ID
 * @post La salida esperada es ERROR
 */ 
void test3_space_set_up();

/**
 * @test Prueba la función que establece el enlace inferior de un espacio
 * @pre A la función se le pasa el identificador 4
 * @post La salida esperada es OK
 */
void test1_space_set_down();

/**
 * @test Prueba la función que establece el enlace inferior de un espacio
 * @pre El espacio al que establecer el enclace es un puntero a NULL
 * @post La salida esperada es ERROR
 */
void test2_space_set_down();

/**
 * @test Prueba la función que establece el enlace inferior de un espacio
 * @pre El id que se le pasa a la función es NO_ID
 * @post La salida esperada es ERROR
 */ 
void test3_space_set_down();

/**
 * @test Prueba la función que devuelve el id de una casilla
 * @pre Al espacio se le ha establecido un id (12)
 * @post La salida esperada es el id establecido 12
 */
void test1_space_get_id();

/**
 * @test Prueba la función que devuelve el id de una casilla
 * @pre El espacio es un puntero a NULL
 * @post La salida esperada es NO_ID
 */
void test2_space_get_id();

/**
 * @test Prueba la función que devuelve el nombre de una casilla
 * @pre Al espacio se le ha establecido un nombre previamente
 * @post La salda debe ser el nombre previamente establecido
 */
void test1_space_get_name();

/**
 * @test Prueba la función que devuelve el nombre de una casilla
 * @pre El espacio es un puntero a NULL
 * @post La salda debe ser un puntero a NULL
 */
void test2_space_get_name();

/**
 * @test Prueba la función que devuelve el nombre de una casilla
 * @pre El espacio ha sido inicializado pero no se le ha establecido ningun nombre
 * @post La salida debe ser una cadena vacila
 */
void test3_space_get_name();

/**
 * @test Prueba la función que devuelve la descripción de una casilla
 * @pre Al espacio se le ha establecido una descripción previamente
 * @post La salda debe ser la descripción previamente establecida
 */
void test1_space_get_description();

/**
 * @test Prueba la función que devuelve la descripción de una casilla
 * @pre El espacio es un puntero a NULL
 * @post La salda debe ser un puntero a NULL
 */
void test2_space_get_description();

/**
 * @test Prueba la función que devuelve la descripción de una casilla
 * @pre El espacio ha sido inicializado pero no se le ha establecido ninguna descripción
 * @post La salida debe ser una cadena vacila
 */
void test3_space_get_description();

/**
 * @test Prueba la función que devuelve la descripción larga de una casilla
 * @pre Al espacio se le ha establecido una descripción previamente
 * @post La salda debe ser la descripción previamente establecida
 */
void test1_space_get_long_description();

/**
 * @test Prueba la función que devuelve la descripción larga de una casilla
 * @pre El espacio es un puntero a NULL
 * @post La salda debe ser un puntero a NULL
 */
void test2_space_get_long_description();

/**
 * @test Prueba la función que devuelve la descripción larga de una casilla
 * @pre El espacio ha sido inicializado pero no se le ha establecido ninguna descripción
 * @post La salida debe ser una cadena vacila
 */
void test3_space_get_long_description();

/**
 * @test Prueba la función que devuelve los graficos de una casilla
 * @pre A la casilla se le han establecido graficos previamente
 * @post La salida tiene que ser igual a los graficos establecidos previamente
 */
void test1_space_get_graphics();

/**
 * @test Prueba la función que devuelve los graficos de una casilla
 * @pre El espacio ha sido inicializado pero no se le han establecido graficos
 * @post La salida debe ser una matriz de 3 cadenas de 7 caracteres llenas de espacios
 */
void test2_space_get_graphics();

/**
 * @test Prueba la función que devuelve el set de objetos de una casilla
 * @pre El espacio ha sido previamente inicializado.
 * @post La salida debe ser diferente de NULL.
 */
void test1_space_get_objects();

/**
 * @test Prueba la función que devuelve el set de objetos de una casilla
 * @pre El espacio es un puntero a NULL
 * @post La salida debe ser NULL
 */
void test2_space_get_objects();

/**
 * @test Prueba la función que devuelve el enlace norte de una casilla
 * @pre Se ha añadido previamente un enlace on id 7
 * @post La salida debe ser el id del enlace 7
 */
void test1_space_get_north();

/**
 * @test Prueba la función que devuelve el enlace norte de una casilla
 * @pre El espacio es un puntero a NULL.
 * @post La salida debe ser NO_ID.
 */
void test2_space_get_north();

/**
 * @test Prueba la función que devuelve el enlace norte de una casilla
 * @pre No se ha establecido ningun enlace previamente
 * @post La salida debe ser NO_ID.
 */
void test3_space_get_north();

/**
 * @test Prueba la función que devuelve el enlace sur de una casilla
 * @pre Se ha añadido previamente un enlace on id 7
 * @post La salida debe ser el id del enlace 7
 */
void test1_space_get_south();

/**
 * @test Prueba la función que devuelve el enlace sur de una casilla
 * @pre El espacio es un puntero a NULL.
 * @post La salida debe ser NO_ID.
 */
void test2_space_get_south();

/**
 * @test Prueba la función que devuelve el enlace sur de una casilla
 * @pre No se ha establecido ningun enlace previamente
 * @post La salida debe ser NO_ID.
 */
void test3_space_get_south();

/**
 * @test Prueba la función que devuelve el enlace este de una casilla
 * @pre Se ha añadido previamente un enlace on id 7
 * @post La salida debe ser el id del enlace 7
 */
void test1_space_get_east();

/**
 * @test Prueba la función que devuelve el enlace este de una casilla
 * @pre El espacio es un puntero a NULL.
 * @post La salida debe ser NO_ID.
 */
void test2_space_get_east();

/**
 * @test Prueba la función que devuelve el enlace este de una casilla
 * @pre No se ha establecido ningun enlace previamente
 * @post La salida debe ser NO_ID.
 */
void test3_space_get_east();

/**
 * @test Prueba la función que devuelve el enlace oeste de una casilla
 * @pre Se ha añadido previamente un enlace on id 7
 * @post La salida debe ser el id del enlace 7
 */
void test1_space_get_west();

/**
 * @test Prueba la función que devuelve el enlace oeste de una casilla
 * @pre El espacio es un puntero a NULL.
 * @post La salida debe ser NO_ID.
 */
void test2_space_get_west();

/**
 * @test Prueba la función que devuelve el enlace oeste de una casilla
 * @pre No se ha establecido ningun enlace previamente
 * @post La salida debe ser NO_ID.
 */ 
void test3_space_get_west();

/**
 * @test Prueba la función que devuelve el enlace superior de una casilla
 * @pre Se ha añadido previamente un enlace on id 7
 * @post La salida debe ser el id del enlace 7
 */
void test1_space_get_up();

/**
 * @test Prueba la función que devuelve el enlace superior de una casilla
 * @pre El espacio es un puntero a NULL.
 * @post La salida debe ser NO_ID.
 */
void test2_space_get_up();

/**
 * @test Prueba la función que devuelve el enlace superior de una casilla
 * @pre No se ha establecido ningun enlace previamente
 * @post La salida debe ser NO_ID.
 */ 
void test3_space_get_up();

/**
 * @test Prueba la función que devuelve el enlace inferior de una casilla
 * @pre Se ha añadido previamente un enlace on id 7
 * @post La salida debe ser el id del enlace 7
 */
void test1_space_get_down();

/**
 * @test Prueba la función que devuelve el enlace inferior de una casilla
 * @pre El espacio es un puntero a NULL.
 * @post La salida debe ser NO_ID.
 */
void test2_space_get_down();

/**
 * @test Prueba la función que devuelve el enlace inferior de una casilla
 * @pre No se ha establecido ningun enlace previamente
 * @post La salida debe ser NO_ID.
 */ 
void test3_space_get_down();

/**
 * @test Prueba la función que añade un objeto a una casilla
 * @pre El espacio es un puntero a NULL.
 * @post La salida debe ser ERROR.
 */ 
void test1_space_add_object();

/**
 * @test Prueba la función que añade un objeto a una casilla
 * @pre Se añade un objeto con id 10
 * @post La salida debe ser OK.
 */ 
void test2_space_add_object();

/**
 * @test Prueba la función que añade un objeto a una casilla
 * @pre El id del objeto es -1 (NO_ID)
 * @post La salida debe ser ERROR.
 */ 
void test3_space_add_object();

/**
 * @test Prueba la función que quita un objeto de una casilla
 * @pre Se añade un objeto previamente
 * @post La salida debe ser OK.
 */ 
void test1_space_remove_object();

/**
 * @test Prueba la función que quita un objeto de una casilla
 * @pre Todavia no he ha añadido ningun objeto
 * @post La salida debe ser ERROR.
 */ 
void test2_space_remove_object();

/**
 * @test Prueba la función que quita un objeto de una casilla
 * @pre El espacio no se ha inicializado previamente
 * @post La salida debe ser ERROR.
 */ 
void test3_space_remove_object();

/**
 * @test Prueba la función que quita un objeto de una casilla
 * @pre El objeto ya ha sido eliminado previamente
 * @post La salida debe ser ERROR.
 */ 
void test4_space_remove_object();

/**
 * @test Prueba la función que comprueba si una casilla contiene un objeto
 * @pre El espacio se ha inicializado y se ha añadido un objeto
 * @post La salida esperada es TRUE
 */
void test1_space_contains_object();

/**
 * @test Prueba la función que comprueba si una casilla contiene un objeto
 * @pre El espacio no se ha inicializado.
 * @post La salida esperada es FALSE
 */
void test2_space_contains_object();

/**
 * @test Prueba la función que comprueba si una casilla contiene un objeto
 * @pre El espacio se ha creado pero no se ha añadido ningun objeto
 * @post La salida esperada es FALSE
 */
void test3_space_contains_object();

/**
 * @test Prueba la función que comprueba si los graficos de una casilla están vacios.
 * @pre El espacio se ha creado y se le han establecido unos graficos
 * @post La salida esperada es FALSE
 */
void test1_space_graphics_areEmpty();

/**
 * @test Prueba la función que comprueba si los graficos de una casilla están vacios.
 * @pre El espacio no se ha inicializado
 * @post La salida esperada es TRUE.
 */
void test2_space_graphics_areEmpty();

/**
 * @test Prueba la función que comprueba si los graficos de una casilla están vacios.
 * @pre El espacio se ha creado pero no se le han establecido graficos
 * @post La salida esperada es TRUE
 */
void test3_space_graphics_areEmpty();

/**
 * @test Prueba la funcion que pone el estado de la iluminacion en una casilla
 * @pre Se ha creado una casiilla con id 5
 * @post La salida esperada es OK
 */
void test1_space_set_iluminated();

/**
 * @test Prueba la funcion que pone el estado de la iluminacion en una casilla
 * @pre No se ha creado la casilla
 * @post La salida esperada es ERROR
 */
void test2_space_set_iluminated();

/**
 * @test Prueba la funcion que devuelve el estado de la iluminacion en una casilla
 * @pre Se ha creado e iluminado la casilla
 * @post La salida esperada es TRUE
 */
void test1_space_get_iluminated();

/**
 * @test Prueba la funcion que devuelve el estado de la iluminacion en una casilla
 * @pre No se ha creado la casilla
 * @post La salida esperada es FALSE
 */
void test2_space_get_iluminated();

#endif
