/**
 * @brief Programa para probar el modulo screen.
 *       Progama para probar la correcta funcionalidad del
 *       nuevo TAD screen.
 *
 * @file screen_test.c
 * @author Javier Bernardo y Mihai Blidaru
 * @version 1.0
 * @date 24-04-2017
 */
 
/* Cabeceras Libc*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Cabeceras Propias */
#include "screen.h"
#include "tests/screen_test.h"
#include "tests/test.h"
/**
 * Número maximo de tests
 * @cond
 */
#define MAX_TESTS 5

typedef void(*test_function)();

static test_function tests[MAX_TESTS] = {
        test1_screen_area_init,
        test2_screen_area_init,
        test3_screen_area_init,
        test4_screen_area_init,
        test5_screen_area_init
};

int main(int argc, char** argv){
    int test = 0;
    int all = 1;
    int i;
    
    if (argc < 2) {
        printf("Running all test for module screen:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        if (test < 1 || test > MAX_TESTS) {
            printf("Error: unknown test %d\n", test);
            return EXIT_SUCCESS;
        }
        printf("Running test %d:\t", test);
    }
    screen_init();
    if(all == 1){
        for(i = 0; i < MAX_TESTS;i++){
            (*tests[i])();
        }
    }else{
        (*tests[test-1])();
    }
    screen_destroy();
    PRINT_PASSED_PERCENTAGE;

    return 1;
}

/**
 * @endcond
 */
 
/*
 * @test Prueba la función que inicializa un area
 * @pre Todos los parametros son correctos
 * @post La salida esperada es el area inicializado
 */
void test1_screen_area_init(){
    Area* area = NULL;
    int x = 54;
    int y = 1;
    int width = 25;
    int height = 15;
    area = screen_area_init(x, y, width, height);
    PRINT_TEST_RESULT(area != NULL);
    screen_area_destroy(area);
}

/*
 * @test Prueba la función que inicializa un area
 * @pre La posición x es negativa
 * @post La salida esperada es NULL
 */
void test2_screen_area_init(){
    Area* area = NULL;
    int x = -1;
    int y = 12;
    int width = 23;
    int height = 20;
    area = screen_area_init(x, y, width, height);
    PRINT_TEST_RESULT(area == NULL);
    screen_area_destroy(area);
}

/*
 * @test Prueba la función que inicializa un area
 * @pre La posición y es negativa
 * @post La salida esperada es NULL
 */
void test3_screen_area_init(){
    Area* area = NULL;
    int x = 10;
    int y = -1;
    int width = 23;
    int height = 20;
    area = screen_area_init(x, y, width, height);
    PRINT_TEST_RESULT(area == NULL);
    screen_area_destroy(area);
}

/*
 * @test Prueba la función que inicializa un area
 * @pre El ancho del area es negativo
 * @post La salida esperada es NULL
 */
void test4_screen_area_init(){
    Area* area = NULL;
    int x = 10;
    int y = 12;
    int width = -1;
    int height = 20;
    area = screen_area_init(x, y, width, height);
    PRINT_TEST_RESULT(area == NULL);
    screen_area_destroy(area);
}

/*
 * @test Prueba la función que inicializa un area
 * @pre El alto del area es negativo
 * @post La salida esperada es NULL
 */
void test5_screen_area_init(){
    Area* area = NULL;
    int x = 10;
    int y = 12;
    int width = 23;
    int height = -1;
    area = screen_area_init(x, y, width, height);
    PRINT_TEST_RESULT(area == NULL);
    screen_area_destroy(area);
}
