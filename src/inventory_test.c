/*
 * @brief Programa para probar el modulo Inventory.
 *       Progama para probar la correcta funcionalidad del
 *       nuevo TAD Inventory.
 *
 * @file inventory_test.c
 * @author Sandra Benítez 
 * @author Laura Bernal
 * @version 1.0
 * @date 01-04-2017
 */
 
/* Cabeceras Libc*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Cabeceras Propias */
#include "test.h"
#include "tests/inventory_test.h"
#include "inventory.h"

/**
 * Número maximo de tests
 * @cond
 */
#define MAX_TESTS 14

int main(int argc, char** argv) {

    int test = 0;
    int all = 1;
    
    if (argc < 2) {
        printf("Running all test for module Inventory:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
        }
    }
    
    if (all || test == 1) test1_inventory_create();
    if (all || test == 2) test1_inventory_add_object();
    if (all || test == 3) test2_inventory_add_object();
    if (all || test == 4) test3_inventory_add_object();
    if (all || test == 5) test1_inventory_set_max();
    if (all || test == 6) test2_inventory_set_max();
    if (all || test == 7) test3_inventory_set_max();
    if (all || test == 8) test1_inventory_get_max();
    if (all || test == 9) test2_inventory_get_max();
	if (all || test == 10) test1_inventory_remove_object();
	if (all || test == 11) test2_inventory_remove_object();
	if (all || test == 12) test3_inventory_remove_object();
	if (all || test == 13) test1_inventory_get_set();
	if (all || test == 14) test2_inventory_get_set();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

/**
 * @endcond
 */
 
/*
 * @test Prueba la función que crea un inventario
 * @post La salida debe ser un inventario inicializado (diferente de NULL)
 */
void test1_inventory_create(){
  Inventory* i = NULL;
  int result = 0;
  i = inventory_create();
   result = i != NULL;
  PRINT_TEST_RESULT(result);
  inventory_destroy(i);
  
}

/*
 * @test Prueba la función que añade un objeto a un inventario
 * @pre El inventario ha sido inicializado previamente
 * @post La salida esperada es ERROR
 */
void test1_inventory_add_object(){
    Inventory *i = NULL;
    i = inventory_create();
    inventory_set_max(i, 1);
    PRINT_TEST_RESULT(inventory_add_object(i, 10) == OK);
    inventory_destroy(i);
}

/*
 * @test Prueba la función que añade un objeto a un inventario
 * @pre El inventario es un puntero a NULL
 * @post La salida esperada es ERROR
 */
void test2_inventory_add_object(){
    Inventory* i = NULL;
    PRINT_TEST_RESULT(inventory_add_object(i, 10) == ERROR);
    inventory_destroy(i);
}

/*
 * @test Prueba la función que añade un objeto a un inventario
 * @pre El id del objeto que se quiere añadir es NO_ID
 * @post La salida esperada es ERROR
 */
void test3_inventory_add_object(){
    Inventory *inventory = NULL;
    inventory = inventory_create();
    inventory_set_max(inventory, 1);
    PRINT_TEST_RESULT(inventory_add_object(inventory, NO_ID) == ERROR);
    inventory_destroy(inventory);
}

/*
 * @test Prueba la función que establece el número máximo de objetos de un inventario
 * @pre El inventario ha sido creado previamente
 * @post La salida esperada es OK
 */
void test1_inventory_set_max(){
    Inventory *i = NULL;
    i = inventory_create();
    PRINT_TEST_RESULT(inventory_set_max(i, 4) == OK);
    inventory_destroy(i);
}

/*
 * @test Prueba la función que establece el número máximo de objetos de un inventario
 * @pre El número máximo de objetos es invalido (-5)
 * @post La salida esperada es ERROR
 */
void test2_inventory_set_max(){
    Inventory *i = NULL;
    i = inventory_create();
    PRINT_TEST_RESULT(inventory_set_max(i,-5) == ERROR);
    inventory_destroy(i);
}

/*
 * @test Prueba la función que establece el número máximo de objetos de un inventario
 * @pre El inventario es un puntero a NULL
 * @post La salida esperada es ERROR
 */
void test3_inventory_set_max(){
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_set_max(i,4) == ERROR);
}

/*
 * @test Prueba la función que devuelve el número máximo de objetos de un inventario
 * @pre Se establece previamente el número máximo de objetos a 20
 * @post La salida esperada es 20
 */
void test1_inventory_get_max(){
    Inventory *i = NULL;
    i = inventory_create();
    inventory_set_max(i, 20);
    PRINT_TEST_RESULT(inventory_get_max(i) == 20);
    inventory_destroy(i);
}

/*
 * @test Prueba la función que devuelve el número máximo de objetos de un inventario
 * @pre El inventario es un puntero a NULL
 * @post La salida esperada es -1
 */ 
void test2_inventory_get_max(){
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_get_max(i) == -1);
}

/*
 * @test Prueba la función que elimina un objeto de un inventario
 * @pre Se añade previamente un objeto con el id 10
 * @post La salida esperada es OK
 */
void test1_inventory_remove_object(){
    Inventory* i = NULL;
    i = inventory_create();
    inventory_set_max(i, 1);
    inventory_add_object(i, 10);
    PRINT_TEST_RESULT(inventory_remove_object(i, 10) == OK);
    inventory_destroy(i);
}

/*
 * @test Prueba la función que elimina un objeto de un inventario
 * @pre El objeto no ha sido añadido previamente
 * @post La salida esperada es ERROR
 */
void test2_inventory_remove_object(){
    Inventory *i = NULL;
    i = inventory_create();
    PRINT_TEST_RESULT(inventory_remove_object(i, 2) == ERROR);
    inventory_destroy(i);
}

/*
 * @test Prueba la función que elimina un objeto de un inventario
 * @pre El inventario es un puntero a NULL
 * @post La salida esperada es ERROR
 */
void test3_inventory_remove_object(){
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_remove_object(i, 10) == ERROR);
}

/*
 * @test Prueba la función que devuelve el set de objetos de un inventario
 * @pre El inventario ha sido inicializado previamente
 * @post La salida esperada es diferente de NULL
 */
void test1_inventory_get_set(){
    Inventory *i = NULL;
    i = inventory_create();
    PRINT_TEST_RESULT(inventory_get_set(i) != NULL);
    inventory_destroy(i);
}

/*
 * @test Prueba la función que devuelve el set de objetos de un inventario
 * @pre El inventario es un puntero a NULL
 * @post La salida esperada es NULL
 */
void test2_inventory_get_set(){
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_get_set(i) == NULL);
}