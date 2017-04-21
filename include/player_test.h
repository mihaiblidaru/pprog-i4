/** 
 * @brief It declares the tests for the player module
 * 
 * @file player_test.h
 * @author Mihai Blidaru
 * @version 1.0 
 * @date 19-01-2016
 * @copyright GNU Public License
 */
#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

/** 
 * @test Prueba si se crea correctamente un jugador
 * @post Un puntero no nulo al jugador creado
 */ 
void test1_player_create();

/** 
 * @test Prueba si se le asigna correctamente un nombre a un jugador
 * @pre El nombre del jugador
 * @post La salida tiene que ser el puntero al jugador
 */  
void test1_player_set_name();

/** 
 * @test Prueba asignar un nombre a un jugador sin inicializar
 * @pre El jugador al que establecer el nombre es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_player_set_name();

/** 
 * @test Prueba asignarle un nombre nulo a un jugador
 * @pre La cadena que se quiere asignar es un puntero a NULL
 * @post La salida tiene que ser NULL
 */  
void test3_player_set_name();

/** 
 * @test Prueba asignar un id a un jugador en condiciones normales
 * @pre Al jugador se le asigna un id cualquiera mayor que cero
 * @post La salida tiene que ser el puntero al jugador
 */ 
void test1_player_set_id();

/** 
 * @test Prueba asignar un id a un jugador sin inicializar
 * @pre El jugador al que establecer el nombre es un puntero a NULL
 * @post La salida esperada es NULL
 */ 
void test2_player_set_id();

/**
 * @test Prueba asignar un id a un jugador
 * @pre El id que se quiere asignar es NO_ID
 * @post La salida que se espera es NULL
 */
void test3_player_set_id();

/** 
 * @test Prueba asignarle una localización a un jugador en condiciones 
 * @pre El jugador ha sido previamente inicializado y la localización que se le asigna es valida
 * @post La salida es el puntero al jugador
 */
void test1_player_set_location();

/** 
 * @test Prueba asignarle una localización a un jugador sin inicializar.
 * @pre El jugador no ha sido inicializado previamente
 * @post La salida que se espera es NULL
 */
void test2_player_set_location();

/**
 * @test Prueba asignarle una localización invalida a un jugador.
 * @pre La localización que se quiere asignar al jugador es es negativa
 * @post La salida esperada es NULL
 */
void test3_player_set_location();

/**
 * @test Prueba leer el id de un jugador
 * @pre Al jugador se le ha asignado previamente el id 12
 * @post La salida esperada es el id asignado antes (12)
 */
void test1_player_get_id();

/**
 * @test Prueba leer el id de un jugador
 * @pre El jugador no ha sido inicializado previamente
 * @post La salida esperada es NO_ID
 */
void test2_player_get_id();

/**
 * @test Intenta leer el id del jugador
 * @pre Al jugador no se le ha asignado ninguna id todavia
 * @post La salida esperada es NO_ID
*/
void test3_player_get_id();

/**
 * @test Intenta leer el nombre de un jugador
 * @pre Al jugador se le ha asignado previamente el nombre "Bob"
 * @post La salida esperada es el nombre asignado antes : "Bob"
*/
void test1_player_get_name();

/**
 * @test Prueba leer el nombre de un jugador
 * @pre El jugador está sin inicializar
 * @post La salida debe ser NULL
 */
void test2_player_get_name();

/**
 * @test Prueba leer el nombre de un jugador
 * @pre Al jugador no se le ha dado ningun nombre previamente
 * @post La salida esperada es una cadena vacía
 */
void test3_player_get_name();

/**
 * @test Leer la localización de un jugador
 * @pre Al jugador se le ha asignado previamente la localización 12
 * @post La salida esperada es la localización previamente asignada (12)
 */
void test1_player_get_location();

/**
 * @test Prueba leer la localización del jugador
 * @pre El jugador no ha sido inicializado
 * @post La salida esperada es NO_ID
 */
void test2_player_get_location();

/**
 * @test Prueba leer la localización del jugador
 * @pre Al jugador no se le ha asignado ninguna localización todavía
 * @post La salida que se espera es NO_ID
 */
void test3_player_get_location();

/**
 * @test Prueba añadir un objeto a un jugador
 * @pre El jugador está sin inicializar
 * @post La salida que se espera es ERROR
*/
void test1_player_add_object();

/**
 * @test Prueba añadir un objeto a un jugador en condiciones normales
 * @pre El jugador ha sido correctamente inicializado y el id del objeto es valido
 * @post La salida debe ser OK
 */
void test2_player_add_object();

/**
 * @test Prueba añadir un objeto al inventario del jugador
 * @pre El objeto tiene id -1
 * @post La salida que se espera es ERROR
 */
void test3_player_add_object();

/**
 * @test Prueba quitar un objeto al jugador en condiciones normales
 * @pre Al jugador se le añade un objeto
 * @post La salida que se espera es OK
 */
void test1_player_remove_object();

/**
 * @test Prueba quitar un objeto a un jugador
 * @pre Al jugador no se le ha añadido todavía ningun objeto
 * @post La salida que se espera es ERROR
 */
void test2_player_remove_object();

/**
 * @test Prueba quitar un objeto a un jugador
 * @pre El jugador está sin inicializar
 * @post La salida que se espera es ERROR
 */
void test3_player_remove_object();

/**
 * @test Prueba quitar un objeto al jugador
 * @pre El objeto ya ha sido borrado anteriormente
 * @post La salida que se espera es ERROR
 */
void test4_player_remove_object();

/**
 * @test Prueba poner el número máximo de objetos de un jugador
 * @pre Las condiciones son normales: jugador inicializado, número de objeto dentro de limites.
 * @post La salida debe ser el puntero al jugador
 */
void test1_player_set_max_objects();

/**
 * @test Prueba poner el número máximo de objetos de un jugador
 * @pre El número de objetos está por encima del limite permitido
 * @post La salida debe ser NULL
 */
void test2_player_set_max_objects();

/**
 * @test Prueba poner el número máximo de objetos de un jugador
 * @pre El jugador está sin inicializar
 * @post La salida debe ser NULL
 */
void test3_player_set_max_objects();

/**
 * @test Prueba poner el numero máximo de objetos de un jugador
 * @pre El número de objetos es un número negativo
 * @post La salida debe ser NULL
 */
void test4_player_set_max_objects();

/**
 * @test Prubea si el jugador tiene un objeto en condiciones normales
 * @pre Se le añade un objeto al jugador
 * @post La salida debe ser TRUE
 */
void test1_player_has_object();

/*
 * @test Prueba si el jugador tiene un objeto
 * @pre El jugador está sin inicializar
 * @post La salida debe ser FALSE
 */
void test2_player_has_object();

/*
 * @test Prueba si el jugador tiene un objeto
 * @pre El jugador está inicializado pero no tiene ningun objeto
 * @post La salida debe ser FALSE
 */
void test3_player_has_object();

#endif