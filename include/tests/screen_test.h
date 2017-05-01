/** 
 * @brief Define las funciones para la prueba del modulo Screen
 * 
 * @file screen_test.h
 * @author Javier Bernardo
 * @version 1.0 
 * @date 24-04-2017
 * @copyright GNU Public License
 */
#ifndef SCREEN_TEST_H
#define SCREEN_TEST_H

/**
 * @test Prueba la función que inicializa un area
 * @pre Todos los parametros son correctos
 * @post La salida esperada es el area inicializado
 */
void test1_screen_area_init();

/**
 * @test Prueba la función que inicializa un area
 * @pre La posición x es negativa
 * @post La salida esperada es NULL
 */
void test2_screen_area_init();

/**
 * @test Prueba la función que inicializa un area
 * @pre La posición y es negativa
 * @post La salida esperada es NULL
 */
void test3_screen_area_init();

/**
 * @test Prueba la función que inicializa un area
 * @pre El ancho del area es negativo
 * @post La salida esperada es NULL
 */
void test4_screen_area_init();

/**
 * @test Prueba la función que inicializa un area
 * @pre El alto del area es negativo
 * @post La salida esperada es NULL
 */
void test5_screen_area_init();

#endif