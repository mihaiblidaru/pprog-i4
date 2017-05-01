/**
 * @brief Define las funciones para la prueba del modulo dialogue
 * 
 * @file dialogue_test.h
 * @author Mihai Blidaru
 * @version 1.0 
 * @date 14-03-2017
 * @copyright GNU Public License
 */

#ifndef DIALOGUE_TEST_H
#define DIALOGUE_TEST_H

/**
 * @test Prueba la función que crea un dialogo
 * @pre Se reserva memoria para el dialogo
 * @post La salida que se espera es el dialogo inicializado
 */
void test1_dialogue_ini();

/**
 * @test Prueba la funcion que devuelve el texto del dialogo
 * @pre El dialogo se ha inicializado antes
 * @post La salida es un texto no nulo
 */
void test1_dialogue_get_text();

/**
 * @test Prueba la funcion que devuelve el texto del dialogo
 * @pre El dialogo no se ha inicializado antes
 * @post La salida esperada es NULL
 */
void test2_dialogue_get_text();

/**
 * @test Prueba la funcion que construye el dialogo para el comando GO
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_go();

/**
 * @test Prueba la funcion que construye el dialogo para el comando GO
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_go();

/**
 * @test Prueba la funcion que construye el dialogo para comandos desconocidos
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_unknown();

/**
 * @test Prueba la funcion que construye el dialogo para comandos desconocidos
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_unknown();

/**
 * @test Prueba la funcion que construye el dialogo para el comando DIR
 * @pre El dialogo ha sido inicializado
 * @post La salida esperada es OK
 */
void test1_dialogue_dir();

/**
 * @test Prueba la funcion que construye el dialogo para el comando DIR
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_dir();

/**
 * @test Prueba la funcion que construye el dialogo para el comando TAKE
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_take();

/**
 * @test Prueba la funcion que construye el dialogo para el comando TAKE
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_take();

/**
 * @test Prueba la funcion que construye el dialogo para el comando LEAVE
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_leave();

/**
 * @test Prueba la funcion que construye el dialogo para el comando LEAVE
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_leave();

/**
 * @test Prueba la funcion que construye el dialogo para el comando SAVE
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_save();

/**
 * @test Prueba la funcion que construye el dialogo para el comando SAVE
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_save();

/**
 * @test Prueba la funcion que construye el dialogo para el comando LOAD
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_load();

/**
 * @test Prueba la funcion que construye el dialogo para el comando LOAD
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_load();

/**
 * @test Prueba la funcion que construye el dialogo para el comando ATTACK
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_attack();

/**
 * @test Prueba la funcion que construye el dialogo para el comando ATTACK
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_attack();

/**
 * @test Prueba la funcion que construye el dialogo para el comando INSPECT
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_inspect();

/**
 * @test Prueba la funcion que construye el dialogo para el comando INSPECT
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_inspect();

/**
 * @test Prueba la funcion que construye el dialogo para el comando OPEN
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_open();

/**
 * @test Prueba la funcion que construye el dialogo para el comando OPEN
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_open();

/**
 * @test Prueba la funcion que construye el dialogo para el comando TURN_ON
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_turn_on();

/**
 * @test Prueba la funcion que construye el dialogo para el comando TURN_ON
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_turn_on();

/**
 * @test Prueba la funcion que construye el dialogo para el comando TURN_OFF
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_turn_off();

/**
 * @test Prueba la funcion que construye el dialogo para el comando TURN_OFF
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_turn_off();

/**
 * @test Prueba la funcion que construye el dialogo para el comando HELP
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_help();

/**
 * @test Prueba la funcion que construye el dialogo para el comando HELP
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_help();

/**
 * @test Prueba la funcion que construye el dialogo para las reglas del juego
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_game_rule();

/**
 * @test Prueba la funcion que construye el dialogo para las reglas del juego
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_game_rule();

 
#endif