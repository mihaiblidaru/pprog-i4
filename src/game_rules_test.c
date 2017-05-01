/**
 * @brief Programa para probar el modulo game_management.
 *       Progama para probar la correcta funcionalidad del
 *       nuevo TAD Game_management.
 *
 * @file game_rules_test.c
 * @author Mihai Blidaru
 * @author Laura Bernal
 * @version 1.0
 * @date 24-04-2017
 */
 
/* Cabeceras Libc*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Cabeceras Propias */
#include "game.h"
#include "space.h"
#include "game_rules.h"
#include "game_management.h"
#include "tests/game_rules_test.h"
#include "tests/test.h"

/**
 * Número maximo de tests
 * @cond
 */
#define MAX_TESTS 2

typedef void(*test_function)();

static test_function tests[MAX_TESTS] = {
    test1_game_rules_run_random_rule,
    test2_game_rules_run_random_rule
};

int main(int argc, char** argv){
    int test = 0;
    int all = 1;
    int i;
    
    if (argc < 2) {
        printf("Running all test for module game_rules:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        if (test < 1 || test > MAX_TESTS) {
            printf("Error: unknown test %d\n", test);
            return EXIT_SUCCESS;
        }
        printf("Running test %d:\t", test);
    }
    
    if(all == 1){
        for(i = 0; i < MAX_TESTS;i++){
            (*tests[i])();
        }
    }else{
        (*tests[test-1])();
    }
    
    PRINT_PASSED_PERCENTAGE;

    return 1;
}
/**
 * Número maximo de tests
 * @endcond
 */
/*
 * @test Prueba la funcion que ejecuta una regla aleatoria
 * @pre El juego se ha inicializado previamente
 * @post La salida esperada es OK
 */
void test1_game_rules_run_random_rule(){
    Game* game;
    game = game_create();
    game_management_start_from_file(game, "space.dat", "objects.dat", "links.dat", "player.dat");
    PRINT_TEST_RESULT(game_rules_run_random_rule(game) == OK);
    game_destroy(game);
}

/*
 * @test Prueba la funcion que ejecuta una regla aleatoria
 * @pre El juego no se ha inicializado previamente
 * @post La salida esperada es ERROR
 */
void test2_game_rules_run_random_rule(){
    Game* game = NULL;
    PRINT_TEST_RESULT(game_rules_run_random_rule(game) == ERROR);
}