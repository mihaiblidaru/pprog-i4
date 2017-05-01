/**
 * @brief Define las funciones para la prueba del modulo game_rules
 * 
 * @file game_rules_test.h
 * @author Mihai Blidaru
 * @version 1.0 
 * @date 14-03-2017
 * @copyright GNU Public License
 */
#ifndef GAME_RULES_TEST
#define GAME_RULES_TEST

/**
 * @test Prueba la funcion que ejecuta una regla aleatoria
 * @pre El juego se ha inicializado previamente
 * @post La salida esperada es OK
 */
void test1_game_rules_run_random_rule();

/**
 * @test Prueba la funcion que ejecuta una regla aleatoria
 * @pre El juego no se ha inicializado previamente
 * @post La salida esperada es ERROR
 */
void test2_game_rules_run_random_rule();
    
#endif