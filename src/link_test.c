/**
 * @brief Programa que prueba la funcionalidad del TAD link.
 * @file link_test.c
 * @author Javier Bernardo
 * @date 29/03/2017
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "link.h"
#include "tests/link_test.h"
#include "tests/test.h"
/**
 * Número máximo de tests
 * @cond
 */
#define MAX_TESTS 30

int main(int argc, char** argv) {

    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module Link:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_link_create();
    if (all || test == 2) test1_link_set_id();
    if (all || test == 3) test2_link_set_id();
    if (all || test == 4) test3_link_set_id();
    if (all || test == 5) test1_link_set_name();
    if (all || test == 6) test2_link_set_name();
    if (all || test == 7) test3_link_set_name();
    if (all || test == 8) test1_link_set_space1();
    if (all || test == 9) test2_link_set_space1();
    if (all || test == 10) test3_link_set_space1();
    if (all || test == 11) test1_link_set_space2();
    if (all || test == 12) test2_link_set_space2();
    if (all || test == 13) test3_link_set_space2();
    if (all || test == 14) test1_link_set_state();
    if (all || test == 15) test2_link_set_state();
    if (all || test == 16) test3_link_set_state();
    if (all || test == 17) test1_link_get_name();
    if (all || test == 18) test2_link_get_name();
    if (all || test == 19) test1_link_get_id();
    if (all || test == 20) test2_link_get_id();
    if (all || test == 21) test1_link_get_space1();
    if (all || test == 22) test2_link_get_space1();
    if (all || test == 23) test1_link_get_space2();
    if (all || test == 24) test2_link_get_space2();
    if (all || test == 25) test1_link_get_state();
    if (all || test == 26) test2_link_get_state();
    if (all || test == 27) test1_link_get_dest_from();
    if (all || test == 28) test2_link_get_dest_from();
    if (all || test == 29) test3_link_get_dest_from();
    if (all || test == 30) test4_link_get_dest_from();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

/**
 * @endcond
 */
 
/*
 * @test Prueba la función de creación de un link
 * @pre Un identificador como parámetro
 * @post Un puntero no nulo al espacio creado
 */
void test1_link_create(){
    int result = 0;
    Link *l = NULL;
    l = link_create();
    result = l != NULL;
    PRINT_TEST_RESULT(result);
    link_destroy(l);
}

/*
 * @test Prueba la función para establecer el id de un link
 * @pre El enlace ha sido inicializado previamente
 * @post La salida debe ser OK
 */
void test1_link_set_id(){
    Link *l = NULL;
    l = link_create();
    PRINT_TEST_RESULT(link_set_id(l, 15) == OK);
    link_destroy(l);
}

/*
 * @test Prueba la función para establecer el id de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_set_id(){
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_id(l, 15) == ERROR);
}

/*
 * @test Prueba la función para establecer el id de un link
 * @pre El id que se quiere establecer es NO_ID
 * @post La salida debe ser ERROR
 */
void test3_link_set_id(){
    Link *l = NULL;
    l = link_create();
    PRINT_TEST_RESULT(link_set_id(l, NO_ID) == ERROR);
    link_destroy(l);
}

/*
 * @test Prueba la función para establecer el nombre de un link
 * @pre El link ha sido creado previamente y se le pone un nombre
 * @post La salida debe ser OK
 */
void test1_link_set_name(){
    Link *l = NULL;
    l = link_create();
    PRINT_TEST_RESULT(link_set_name(l, "hola") == OK);
    link_destroy(l);
}

/*
 * @test Prueba la función para establecer el nombre de un link
 * @pre El link al que establecer el nombre es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_set_name(){
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_name(l, "hola") == ERROR);
}

/*
 * @test Prueba la función para establecer el nombre de un link
 * @pre El link es un puntero no NULL, pero el nombre a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_link_set_name(){
    Link *l = NULL;
    l = link_create();
    PRINT_TEST_RESULT(link_set_name(l, NULL) == ERROR);
    link_destroy(l);
}

/*
 * @test Prueba la función para establecer el space1 de un link
 * @pre El enlace ha sido inicializado previamente
 * @post La salida debe ser OK
 */
void test1_link_set_space1(){
    Link *l = NULL;
    l = link_create();
    PRINT_TEST_RESULT(link_set_space1(l, 15) == OK);
    link_destroy(l);
}

/*
 * @test Prueba la función para establecer el space1 de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_set_space1(){
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_space1(l, 15) == ERROR);
}

/*
 * @test Prueba la función para establecer el space1 de un link
 * @pre El id que se quiere establecer es NO_ID
 * @post La salida debe ser ERROR
 */
void test3_link_set_space1(){
    Link *l = NULL;
    l = link_create();
    PRINT_TEST_RESULT(link_set_space1(l, NO_ID) == ERROR);
    link_destroy(l);
}

/*
 * @test Prueba la función para establecer el space2 de un link
 * @pre El enlace ha sido creado previamente
 * @post La salida debe ser OK
 */
void test1_link_set_space2(){
    Link *l = NULL;
    l = link_create();
    PRINT_TEST_RESULT(link_set_space2(l, 18) == OK);
    link_destroy(l);
}

/*
 * @test Prueba la función para establecer el space2 de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_set_space2(){
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_space2(l, 18) == ERROR);
}

/*
 * @test Prueba la función para establecer el space2 de un link
 * @pre El id que se quiere establecer es NO_ID
 * @post La salida debe ser ERROR
 */
void test3_link_set_space2(){
    Link *l = NULL;
    l = link_create();
    PRINT_TEST_RESULT(link_set_space2(l, NO_ID) == ERROR);
    link_destroy(l);
}

/*
 * @test Prueba la función para establecer el estado de un link
 * @pre El link se crea previamente
 * @post La salida debe ser OK
 */
void test1_link_set_state(){
    Link *l = NULL;
    l = link_create();
    PRINT_TEST_RESULT(link_set_state(l, 1) == OK);
    link_destroy(l);
}

/*
 * @test Prueba la función para establecer el estado de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_set_state(){
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_state(l, 0) == ERROR);
}

/*
 * @test Prueba la función para establecer el estado de un link
 * @pre El estado que se le quiere poner al link es invalido
 * @post La salida debe ser ERROR
 */
void test3_link_set_state(){
    Link *l = NULL;
    l = link_create();
    PRINT_TEST_RESULT(link_set_state(l, 9999) == ERROR);
    link_destroy(l);
}

/*
 * @test Prueba la función para obtener el nombre de un link
 * @pre Al link se le pone un nombre previamente
 * @post La salida debe ser el mismo nombre establecido
 */
void test1_link_get_name(){
    Link *l = NULL;
    l = link_create();
    link_set_name(l, "adios");
    PRINT_TEST_RESULT(strcmp(link_get_name(l), "adios") == 0);
    link_destroy(l);
}

/*
 * @test Prueba la función para obtener el nombre de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser NULL
 */
void test2_link_get_name(){
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_name(l) == NULL);
}

/*
 * @test Prueba la función para obtener el id de un link
 * @pre Se establece previamente el id del link a 25
 * @post La salida debe ser el mismo id: 25
 */
void test1_link_get_id(){
    Link *l = NULL;
    l = link_create();
    link_set_id(l,25);
    PRINT_TEST_RESULT(link_get_id(l) == 25);
    link_destroy(l);
}

/*
 * @test Prueba la función para obtener el id de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser NO_ID
 */
void test2_link_get_id(){
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_id(l) == NO_ID);
}

/*
 * @test Prueba la función para obtener el space1 de un link
 * @pre Se ha establecido el space1 del link a 26
 * @post La salida debe ser el mismo id: 26
 */
void test1_link_get_space1(){
    Link *l = NULL;
    l = link_create();
    link_set_space1(l,26);
    PRINT_TEST_RESULT(link_get_space1(l) == 26);
    link_destroy(l);
    
}

/*
 * @test Prueba la función para obtener el space1 de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser NO_ID
 */
void test2_link_get_space1(){
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_space1(l) == NO_ID);
}

/*
 * @test Prueba la función para obtener el space2 de un link
 * @pre Se ha establecido el space2 del link a 27
 * @post La salida debe ser 27
 */
void test1_link_get_space2(){
    Link *l = NULL;
    l = link_create();
    link_set_space2(l,27);
    PRINT_TEST_RESULT(link_get_space2(l) == 27);
    link_destroy(l);
}

/*
 * @test Prueba la función para obtener el space2 de un link
 * @pre El enlace es un puntero a NULL
 * @post La salida debe ser NO_ID
 */
void test2_link_get_space2(){
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_space2(l) == NO_ID);
}
   
/*
 * @test Prueba la función para obtener el estado de un link
 * @pre Se establece el estado del enlace como CLOSED
 * @post La salida debe ser CLOSED
 */
void test1_link_get_state(){
    Link *l = NULL;
    l = link_create();
    link_set_state(l, CLOSED);
    PRINT_TEST_RESULT(link_get_state(l) == CLOSED);
    link_destroy(l);
}

/*
 * @test Prueba la función para obtener el estado de un link
 * @pre El link es un puntero a NULL
 * @post La salida debe ser -1
 */
void test2_link_get_state(){
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_state(l) == -1);
}

/*
 * @test Prueba la función que devuelve la casilla destino desde otra casilla
 * @pre El enlace se inicializa a (1, 2) y se establece que el id de origen es 1
 * @post La salida tiene que ser 2
 */
void test1_link_get_dest_from(){
    Link *l = NULL;
    l = link_create();
    link_set_space1(l, 1);
    link_set_space2(l, 2);
    PRINT_TEST_RESULT(link_get_dest_from(l,1) == 2);
    link_destroy(l);
}

/*
 * @test Prueba la función que devuelve la casilla destino desde otra casilla
 * @pre El enlace se inicializa a (1, 2) y se establece que el id de origen es 2
 * @post La salida tiene que ser 1
 */
void test2_link_get_dest_from(){
    Link *l = NULL;
    l = link_create();
    link_set_space1(l, 1);
    link_set_space2(l, 2);
    PRINT_TEST_RESULT(link_get_dest_from(l, 2) == 1);
    link_destroy(l);
}

/*
 * @test Prueba la función que devuelve la casilla destino desde otra casilla
 * @pre El enlace es un puntero a NULL
 * @post La salida tiene que ser NO_ID
 */
void test3_link_get_dest_from(){
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_dest_from(l,1) == NO_ID);
}

/*
 * @test Prueba la función que devuelve la casilla destino desde otra casilla
 * @pre El id de origen no está en el enlace
 * @post La salida tiene que ser NO_ID
 */
void test4_link_get_dest_from(){
    Link *l = NULL;
    l = link_create();
    link_set_space1(l, 3);
    link_set_space2(l, 4);
    PRINT_TEST_RESULT(link_get_dest_from(l,1) == NO_ID);
    link_destroy(l);
}