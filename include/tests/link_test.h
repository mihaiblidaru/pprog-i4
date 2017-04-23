/**
 * @brief Pruebas para el modulo Link
 * @file link_test.h
 * @author Javier Bernardo
 * @date 27/03/2017
 */
#ifndef LINK_TEST_H
#define LINK_TEST_H

/**
 * @test Prueba la función de creación de un link
 * @pre Un identificador como parámetro
 * @post Un puntero no nulo al espacio creado
 */
void test1_link_create();

/**
 * @test Prueba la función para establecer el id de un link
 * @pre El enlace ha sido inicializado previamente
 * @post La salida debe ser OK
 */
void test1_link_set_id();

/**
 * @test Prueba la función para establecer el id de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_set_id();

/**
 * @test Prueba la función para establecer el id de un link
 * @pre El id que se quiere establecer es NO_ID
 * @post La salida debe ser ERROR
 */
void test3_link_set_id();

/**
 * @test Prueba la función para establecer el nombre de un link
 * @pre El link ha sido creado previamente y se le pone un nombre
 * @post La salida debe ser OK
 */
void test1_link_set_name();

/**
 * @test Prueba la función para establecer el nombre de un link
 * @pre El link al que establecer el nombre es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_set_name();

/**
 * @test Prueba la función para establecer el nombre de un link
 * @pre El link es un puntero no NULL, pero el nombre a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_link_set_name();

/**
 * @test Prueba la función para establecer el space1 de un link
 * @pre El enlace ha sido inicializado previamente
 * @post La salida debe ser OK
 */
void test1_link_set_space1();

/**
 * @test Prueba la función para establecer el space1 de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_set_space1();

/**
 * @test Prueba la función para establecer el space1 de un link
 * @pre El id que se quiere establecer es NO_ID
 * @post La salida debe ser ERROR
 */
void test3_link_set_space1();

/**
 * @test Prueba la función para establecer el space2 de un link
 * @pre El enlace ha sido creado previamente
 * @post La salida debe ser OK
 */
void test1_link_set_space2();

/**
 * @test Prueba la función para establecer el space2 de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_set_space2();

/**
 * @test Prueba la función para establecer el space2 de un link
 * @pre El id que se quiere establecer es NO_ID
 * @post La salida debe ser ERROR
 */
void test3_link_set_space2();

/**
 * @test Prueba la función para establecer el estado de un link
 * @pre El link se crea previamente
 * @post La salida debe ser OK
 */
void test1_link_set_state();

/**
 * @test Prueba la función para establecer el estado de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_set_state();

/**
 * @test Prueba la función para establecer el estado de un link
 * @pre El estado que se le quiere poner al link es invalido
 * @post La salida debe ser ERROR
 */
void test3_link_set_state();

/**
 * @test Prueba la función para obtener el nombre de un link
 * @pre Al link se le pone un nombre previamente
 * @post La salida debe ser el mismo nombre establecido
 */
void test1_link_get_name();

/**
 * @test Prueba la función para obtener el nombre de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser NULL
 */
void test2_link_get_name();

/**
 * @test Prueba la función para obtener el id de un link
 * @pre Se establece previamente el id del link a 25
 * @post La salida debe ser el mismo id: 25
 */
void test1_link_get_id();

/**
 * @test Prueba la función para obtener el id de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser NO_ID
 */
void test2_link_get_id();

/**
 * @test Prueba la función para obtener el space1 de un link
 * @pre Se ha establecido el space1 del link a 26
 * @post La salida debe ser el mismo id: 26
 */
void test1_link_get_space1();

/**
 * @test Prueba la función para obtener el space1 de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser NO_ID
 */
void test2_link_get_space1();

/**
 * @test Prueba la función para obtener el space2 de un link
 * @pre Se ha establecido el space2 del link a 27
 * @post La salida debe ser 27
 */
void test1_link_get_space2();

/**
 * @test Prueba la función para obtener el space2 de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser NO_ID
 */
void test2_link_get_space2();

/**
 * @test Prueba la función para obtener el estado de un link
 * @pre Se establece el estado del enlace como CLOSED
 * @post La salida debe ser CLOSED
 */
void test1_link_get_state();

/**
 * @test Prueba la función para obtener el estado de un link
 * @pre El link es un puntero a NULL
 * @post La salida debe ser -1
 */
void test2_link_get_state();

/**
 * @test Prueba la función que devuelve la casilla destino desde otra casilla
 * @pre El enlace se inicializa a (1, 2) y se establece que el id de origen es 1
 * @post La salida tiene que ser 2
 */
void test1_link_get_dest_from();

/**
 * @test Prueba la función que devuelve la casilla destino desde otra casilla
 * @pre El enlace se inicializa a (1, 2) y se establece que el id de origen es 2
 * @post La salida tiene que ser 1
 */
void test2_link_get_dest_from();

/**
 * @test Prueba la función que devuelve la casilla destino desde otra casilla
 * @pre El enlace es un puntero a NULL
 * @post La salida tiene que ser NO_ID
 */
void test3_link_get_dest_from();

/**
 * @test Prueba la función que devuelve la casilla destino desde otra casilla
 * @pre El id de origen no está en el enlace
 * @post La salida tiene que ser NO_ID
 */
void test4_link_get_dest_from();

#endif