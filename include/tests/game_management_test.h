/** 
 * @brief Define las funciones para la prueba del modulo Game_Management
 * 
 * @file inventory_test.h
 * @author Sandra Benítez 
 * @author Laura Bernal
 * @version 1.0 
 * @date 24-04-2017
 * @copyright GNU Public License
 */
 
#ifndef GAME_MANAGEMENT_TEST_H
#define GAME_MANAGEMENT_TEST_H

/**
 * @test Prueba la función que carga los datos del juego desde un archivo 
 * @pre 
 * @post La salida esperada es OK
 */
void test1_game_management_start_from_file();

/**
 * @test Prueba la función que carga los datos del juego desde un archivo 
 * @pre 
 * @post La salida esperada es ERROR
 */
void test2_game_management_start_from_file();
 
/**
 * @test Prueba que la función guarde los datos de la partida con el mismo formato que los ficheros de carga
 * @pre 
 * @post La salida esperada es OK
 */
void test1_game_management_save();

/**
 * @test Prueba que la función guarde los datos de la partida con el mismo formato que los ficheros de carga
 * @pre 
 * @post La salida esperada es ERROR
 */
void test2_game_management_save();
 
/**
 * @test Prueba la función que carga los datos del juego desde un archivo
 * @pre 
 * @post La salida esperada es OK
 */
void test1_game_management_load();
 
/**
 * @test Prueba la función que carga los datos del juego desde un archivo
 * @pre 
 * @post La salida esperada es ERROR
 */
void test2_game_management_load();


#endif /*GAME_MANAGEMENT_TEST_H*/