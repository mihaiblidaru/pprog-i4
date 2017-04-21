/** 
 * @brief Define las funciones para la prueba del modulo Inventory
 * 
 * @file inventory_test.h
 * @author Sandra Benítez 
 * @author Laura Bernal
 * @version 1.0 
 * @date 14-03-2017
 * @copyright GNU Public License
 */
 
#ifndef INVENTORY_TEST_H
#define INVENTORY_TEST_H

/**
 * @test Prueba la función que crea un inventario
 * @post La salida debe ser un inventario inicializado (diferente de NULL)
 */
void test1_inventory_create();

/**
 * @test Prueba la función que añade un objeto a un inventario
 * @pre El inventario ha sido inicializado previamente
 * @post La salida esperada es ERROR
 */
void test1_inventory_add_object();

/**
 * @test Prueba la función que añade un objeto a un inventario
 * @pre El inventario es un puntero a NULL
 * @post La salida esperada es ERROR
 */
void test2_inventory_add_object();

/**
 * @test Prueba la función que añade un objeto a un inventario
 * @pre El id del objeto que se quiere añadir es NO_ID
 * @post La salida esperada es ERROR
 */
void test3_inventory_add_object();

/**
 * @test Prueba la función que establece el número máximo de objetos de un inventario
 * @pre El inventario ha sido creado previamente
 * @post La salida esperada es OK
 */
void test1_inventory_set_max();

/**
 * @test Prueba la función que establece el número máximo de objetos de un inventario
 * @pre El número máximo de objetos es invalido (-5)
 * @post La salida esperada es ERROR
 */
void test2_inventory_set_max();

/**
 * @test Prueba la función que establece el número máximo de objetos de un inventario
 * @pre El inventario es un puntero a NULL
 * @post La salida esperada es ERROR
 */
void test3_inventory_set_max();

/**
 * @test Prueba la función que devuelve el número máximo de objetos de un inventario
 * @pre Se establece previamente el número máximo de objetos a 20
 * @post La salida esperada es 20
 */
void test1_inventory_get_max();

/**
 * @test Prueba la función que devuelve el número máximo de objetos de un inventario
 * @pre El inventario es un puntero a NULL
 * @post La salida esperada es -1
 */ 
void test2_inventory_get_max();

/**
 * @test Prueba la función que elimina un objeto de un inventario
 * @pre Se añade previamente un objeto con el id 10
 * @post La salida esperada es OK
 */
void test1_inventory_remove_object();

/**
 * @test Prueba la función que elimina un objeto de un inventario
 * @pre El objeto no ha sido añadido previamente
 * @post La salida esperada es ERROR
 */
void test2_inventory_remove_object();

/**
 * @test Prueba la función que elimina un objeto de un inventario
 * @pre El inventario es un puntero a NULL
 * @post La salida esperada es ERROR
 */
void test3_inventory_remove_object();

/**
 * @test Prueba la función que devuelve el set de objetos de un inventario
 * @pre El inventario ha sido inicializado previamente
 * @post La salida esperada es diferente de NULL
 */
void test1_inventory_get_set();

/**
 * @test Prueba la función que devuelve el set de objetos de un inventario
 * @pre El inventario es un puntero a NULL
 * @post La salida esperada es NULL
 */
void test2_inventory_get_set();

#endif /*INVENTORY_TEST_H*/














