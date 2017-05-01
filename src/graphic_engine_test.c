/**
 * @brief Programa para probar el modulo graphic_engine.
 *       Progama para probar la correcta funcionalidad del
 *       nuevo TAD graphic_engine.
 *
 * @file graphic_engine_test.c
 * @author Mihai Blidaru
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
#include "graphic_engine.h"
#include "tests/graphic_engine_test.h"
#include "tests/test.h"
/**
 * Número maximo de tests
 * @cond
 */
#define MAX_TESTS 1

typedef void(*test_function)();

static test_function tests[MAX_TESTS] = {
		test1_graphic_engine_create
};

int main(int argc, char** argv){
    int test = 0;
    int all = 1;
    int i;
    
    if (argc < 2) {
        printf("Running all test for module graphic_engine:\n");
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
 * @endcond
 */

/*
 * @test Prueba la función que crea el motor grafico
 * @pre El motor grafico se reserva
 * @post La salida esperada es el motor grafico inicializado
 */
void test1_graphic_engine_create(){
	Graphic_engine* ge = NULL;
	ge = graphic_engine_create();
	PRINT_TEST_RESULT(ge != NULL);
	graphic_engine_destroy(ge);
}
