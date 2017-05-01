/**
 * @brief Programa para probar el modulo dialogue.
 *       Progama para probar la correcta funcionalidad del
 *       nuevo TAD dialogue.
 *
 * @file dialogue_test.c
 * @author Javier Bernardo
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
#include "dialogue.h"
#include "tests/dialogue_test.h"
#include "tests/test.h"

/**
 * Número maximo de tests
 * @cond
 */
#define MAX_TESTS 31

typedef void(*test_function)();

static test_function tests[MAX_TESTS] = {
        test1_dialogue_ini,
        test1_dialogue_get_text,
        test2_dialogue_get_text,
        test1_dialogue_go,
        test2_dialogue_go,
        test1_dialogue_unknown,
        test2_dialogue_unknown,
        test1_dialogue_dir,
        test2_dialogue_dir,
        test1_dialogue_take,
        test2_dialogue_take,
        test1_dialogue_leave,
        test2_dialogue_leave,
        test1_dialogue_save,
        test2_dialogue_save,
        test1_dialogue_load,
        test2_dialogue_load,
        test1_dialogue_attack,
        test2_dialogue_attack,
        test1_dialogue_inspect,
        test2_dialogue_inspect,
        test1_dialogue_open,
        test2_dialogue_open,
        test1_dialogue_turn_on,
        test2_dialogue_turn_on,
        test1_dialogue_turn_off,
        test2_dialogue_turn_off,
        test1_dialogue_help,
        test2_dialogue_help,
        test1_dialogue_game_rule,
        test2_dialogue_game_rule
};

int main(int argc, char** argv){
    int test = 0;
    int all = 1;
    int i;
    
    if (argc < 2) {
        printf("Running all test for module Dialogue:\n");
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
 * @test Prueba la función que crea un dialogo
 * @pre Se reserva memoria para el dialogo
 * @post La salida que se espera es el dialogo inicializado
 */
void test1_dialogue_ini(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    PRINT_TEST_RESULT(d != NULL);
    dialogue_destroy(d);
}

/*
 * @test Prueba la funcion que devuelve el texto del dialogo
 * @pre El dialogo se ha inicializado antes
 * @post La salida es un texto no nulo
 */
void test1_dialogue_get_text(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    dialogue_unknown(d);
    PRINT_TEST_RESULT(strlen(dialogue_get_text(d))>0);
    dialogue_destroy(d);    
}

/*
 * @test Prueba la funcion que devuelve el texto del dialogo
 * @pre El dialogo no se ha inicializado antes
 * @post La salida esperada es NULL
 */
void test2_dialogue_get_text(){
    Dialogue* d = NULL;
    dialogue_unknown(d);
    PRINT_TEST_RESULT(dialogue_get_text(d) == NULL);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando GO
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_go(){
    Dialogue* d = NULL;
    Space* space = NULL;
    Link* link = NULL;
    d = dialogue_ini();
    space = space_create(1);
    link = link_create();
    PRINT_TEST_RESULT(dialogue_go(d, NORTH, space, OK, "north", link) == OK);
    link_destroy(link);
    space_destroy(space);
    dialogue_destroy(d);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando GO
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_go(){
    Dialogue* d = NULL;
    Space* space = NULL;
    Link* link = NULL;
    space = space_create(1);
    link = link_create();
    PRINT_TEST_RESULT(dialogue_go(d, NORTH, space, OK, "north", link) == ERROR);
    link_destroy(link);
    space_destroy(space);
}

/*
 * @test Prueba la funcion que construye el dialogo para comandos desconocidos
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_unknown(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    PRINT_TEST_RESULT(dialogue_unknown(d) == OK);
    dialogue_destroy(d);
}

/*
 * @test Prueba la funcion que construye el dialogo para comandos desconocidos
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_unknown(){
    Dialogue* d = NULL;
    PRINT_TEST_RESULT(dialogue_unknown(d) == ERROR);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando DIR
 * @pre El dialogo ha sido inicializado
 * @post La salida esperada es OK
 */
void test1_dialogue_dir(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    PRINT_TEST_RESULT(dialogue_dir(d) == OK);
    dialogue_destroy(d);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando DIR
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_dir(){
    Dialogue* d = NULL;
    PRINT_TEST_RESULT(dialogue_dir(d) == ERROR);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando TAKE
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_take(){
    Dialogue* d = NULL;
    Object* object = NULL;
    d = dialogue_ini();
    object = object_create();
    PRINT_TEST_RESULT(dialogue_take(d, object, "test", TAKE_OK) == OK);
    object_destroy(object);
    dialogue_destroy(d);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando TAKE
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_take(){
    Dialogue* d = NULL;
    Object* object = NULL;
    object = object_create();
    PRINT_TEST_RESULT(dialogue_take(d, object, "test", TAKE_OK) == ERROR);
    object_destroy(object);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando LEAVE
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_leave(){
    Dialogue* d = NULL;
    Object* object = NULL;
    d = dialogue_ini();
    object = object_create();
    PRINT_TEST_RESULT(dialogue_leave(d, object, "test", LEAVE_OK) == OK);
    object_destroy(object);
    dialogue_destroy(d);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando LEAVE
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_leave(){
    Dialogue* d = NULL;
    Object* object = NULL;
    object = object_create();
    PRINT_TEST_RESULT(dialogue_leave(d, object, "test", LEAVE_OK) == ERROR);
    object_destroy(object);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando SAVE
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_save(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    PRINT_TEST_RESULT(dialogue_save(d, "mysave.dat",SAVE_SAVE_OK) == OK);
    dialogue_destroy(d);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando SAVE
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_save(){
    Dialogue* d = NULL;
    PRINT_TEST_RESULT(dialogue_save(d, "mysave.dat", SAVE_SAVE_OK) == ERROR);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando LOAD
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_load(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    PRINT_TEST_RESULT(dialogue_load(d, "mysave.dat",LOAD_OK) == OK);
    dialogue_destroy(d);   
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando LOAD
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_load(){
    Dialogue* d = NULL;
    PRINT_TEST_RESULT(dialogue_load(d, "mysave.dat",LOAD_OK) == ERROR);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando ATTACK
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_attack(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    PRINT_TEST_RESULT(dialogue_attack(d, NOTHING_TO_ATTACK) == OK);
    dialogue_destroy(d);   
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando ATTACK
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_attack(){
    Dialogue* d = NULL;
    PRINT_TEST_RESULT(dialogue_attack(d, NOTHING_TO_ATTACK) == ERROR);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando INSPECT
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_inspect(){
    Dialogue* d = NULL;
    Object* object = NULL;
    Space* space = NULL;
    d = dialogue_ini();
    space = space_create(1);
    object = object_create();
    PRINT_TEST_RESULT(dialogue_inspect(d, object, space, "north", INSPECT_NO_OBJ) == OK);
    space_destroy(space);
    object_destroy(object);
    dialogue_destroy(d);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando INSPECT
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_inspect(){
    Dialogue* d = NULL;
    Object* object = NULL;
    Space* space = NULL;
    space = space_create(1);
    object = object_create();
    PRINT_TEST_RESULT(dialogue_inspect(d, object, space, "north", INSPECT_NO_OBJ) == ERROR);
    space_destroy(space);
    object_destroy(object);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando OPEN
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_open(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    PRINT_TEST_RESULT(dialogue_open(d, "llave", "puerta", OPEN_OK) == OK);
    dialogue_destroy(d);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando OPEN
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_open(){
    Dialogue* d = NULL;
    PRINT_TEST_RESULT(dialogue_open(d, "llave", "puerta", OPEN_OK) == ERROR);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando TURN_ON
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_turn_on(){
    Dialogue* d = NULL;
    Object* object = NULL;
    d = dialogue_ini();
    object = object_create();
    PRINT_TEST_RESULT(dialogue_turn_on(d, object, "test", TURN_OK) == OK);
    object_destroy(object);
    dialogue_destroy(d);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando TURN_ON
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_turn_on(){
    Dialogue* d = NULL;
    Object* object = NULL;
    object = object_create();
    PRINT_TEST_RESULT(dialogue_turn_off(d, object, "test", TURN_OK) == ERROR);
    object_destroy(object);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando TURN_OFF
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_turn_off(){
    Dialogue* d = NULL;
    Object* object = NULL;
    d = dialogue_ini();
    object = object_create();
    PRINT_TEST_RESULT(dialogue_turn_off(d, object, "test", TURN_OK) == OK);
    object_destroy(object);
    dialogue_destroy(d);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando TURN_OFF
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_turn_off(){
    Dialogue* d = NULL;
    Object* object = NULL;
    object = object_create();
    PRINT_TEST_RESULT(dialogue_turn_off(d, object, "test", TURN_OK) == ERROR);
    object_destroy(object);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando HELP
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_help(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    PRINT_TEST_RESULT(dialogue_help(d) == OK);
    dialogue_destroy(d);
}

/*
 * @test Prueba la funcion que construye el dialogo para el comando HELP
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_help(){
    Dialogue* d = NULL;
    PRINT_TEST_RESULT(dialogue_help(d) == ERROR);
}

/*
 * @test Prueba la funcion que construye el dialogo para las reglas del juego
 * @pre Todos los parametros han sido inicializados
 * @post La salida esperada es OK
 */
void test1_dialogue_game_rule(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    PRINT_TEST_RESULT(dialogue_game_rule(d, LOSE_OBJECT) == OK);
    dialogue_destroy(d);
}

/*
 * @test Prueba la funcion que construye el dialogo para las reglas del juego
 * @pre El dialogo no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_dialogue_game_rule(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    PRINT_TEST_RESULT(dialogue_game_rule(d, LOSE_OBJECT) == OK);
    dialogue_destroy(d);
}
