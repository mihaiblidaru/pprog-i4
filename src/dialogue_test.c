/*
 * @brief Programa para probar el modulo game_management.
 *       Progama para probar la correcta funcionalidad del
 *       nuevo TAD Game_management.
 *
 * @file inventory_test.c
 * @author Sandra Benítez 
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
#include "dialogue.h"
#include "tests/dialogue_test.h"
#include "test.h"

/**
 * Número maximo de tests
 * @cond
 */
#define MAX_TESTS 23

typedef void(*test_function)();

static test_function tests[MAX_TESTS] = {
         test1_dialogue_ini,
         test1_dialogue_get_text,
         test1_dialogue_get_text,
         test1_dialogue_go,
         test2_dialogue_go,
         test1_dialogue_unknown,
         test2_dialogue_unknown,
         test1_dialogue_dir,
         test2_dialogue_dir,
         test1_dialogue_help,
         test2_dialogue_help,
         test1_dialogue_take,
         test2_dialogue_take,
         test1_dialogue_leave,
         test2_dialogue_leave,
         test1_dialogue_turn_on,
         test2_dialogue_turn_on,
         test1_dialogue_turn_off,
         test2_dialogue_turn_off,
         test1_dialogue_inspect,
         test2_dialogue_inspect,
         test1_dialogue_save,
         test2_dialogue_save
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

void test1_dialogue_ini(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    PRINT_TEST_RESULT(d != NULL);
    dialogue_destroy(d);
}

void test1_dialogue_get_text(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    dialogue_unknown(d);
    PRINT_TEST_RESULT(strlen(dialogue_get_text(d))>0);
    dialogue_destroy(d);    
}

void test2_dialogue_get_text(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    dialogue_unknown(d);
    PRINT_TEST_RESULT(dialogue_get_text(d) == NULL);
}


void test1_dialogue_go(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    Space* space = NULL;
    Link* link = NULL;
    space = space_create(1);
    link = link_create();
    PRINT_TEST_RESULT(dialogue_go(d, NORTH, space, OK, "north", link) == OK);
    link_destroy(link);
    space_destroy(space);
    dialogue_destroy(d);
}

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

void test1_dialogue_unknown(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    PRINT_TEST_RESULT(dialogue_unknown(d) == OK);
    dialogue_destroy(d);
}

void test2_dialogue_unknown(){
    Dialogue* d = NULL;
    PRINT_TEST_RESULT(dialogue_unknown(d) == ERROR);
}

void test1_dialogue_dir(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    PRINT_TEST_RESULT(dialogue_dir(d) == OK);
    dialogue_destroy(d);
}

void test2_dialogue_dir(){
    Dialogue* d = NULL;
    PRINT_TEST_RESULT(dialogue_dir(d) == ERROR);
}

void test1_dialogue_help(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    PRINT_TEST_RESULT(dialogue_help(d) == OK);
    dialogue_destroy(d);
}

void test2_dialogue_help(){
    Dialogue* d = NULL;
    PRINT_TEST_RESULT(dialogue_help(d) == ERROR);
}

void test1_dialogue_take(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    Object* object = NULL;
    object = object_create();
    PRINT_TEST_RESULT(dialogue_take(d, object, "test", TAKE_OK) == OK);
    object_destroy(object);
    dialogue_destroy(d);
}

void test2_dialogue_take(){
    Dialogue* d = NULL;
    Object* object = NULL;
    object = object_create();
    PRINT_TEST_RESULT(dialogue_take(d, object, "test", TAKE_OK) == ERROR);
    object_destroy(object);
}

void test1_dialogue_leave(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    Object* object = NULL;
    object = object_create();
    PRINT_TEST_RESULT(dialogue_leave(d, object, "test", LEAVE_OK) == OK);
    object_destroy(object);
    dialogue_destroy(d);
}

void test2_dialogue_leave(){
    Dialogue* d = NULL;
    Object* object = NULL;
    object = object_create();
    PRINT_TEST_RESULT(dialogue_leave(d, object, "test", LEAVE_OK) == ERROR);
    object_destroy(object);
}

void test1_dialogue_turn_on(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    Object* object = NULL;
    object = object_create();
    PRINT_TEST_RESULT(dialogue_turn_on(d, object, "test", TURN_OK) == OK);
    object_destroy(object);
    dialogue_destroy(d);
}

void test2_dialogue_turn_on(){
    Dialogue* d = NULL;
    Object* object = NULL;
    object = object_create();
    PRINT_TEST_RESULT(dialogue_turn_off(d, object, "test", TURN_OK) == ERROR);
    object_destroy(object);
}

void test1_dialogue_turn_off(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    Object* object = NULL;
    object = object_create();
    PRINT_TEST_RESULT(dialogue_turn_off(d, object, "test", TURN_OK) == OK);
    object_destroy(object);
    dialogue_destroy(d);
}

void test2_dialogue_turn_off(){
    Dialogue* d = NULL;
    Object* object = NULL;
    object = object_create();
    PRINT_TEST_RESULT(dialogue_turn_off(d, object, "test", TURN_OK) == ERROR);
    object_destroy(object);
}

void test1_dialogue_inspect(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    Object* object = NULL;
    Space* space = NULL;
    space = space_create(1);
    object = object_create();
    PRINT_TEST_RESULT(dialogue_inspect(d, object, space, "north", INSPECT_NO_OBJ) == OK);
    space_destroy(space);
    object_destroy(object);
    dialogue_destroy(d);
}

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


void test1_dialogue_save(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    PRINT_TEST_RESULT(dialogue_save(d, "mysave.dat",SAVE_SAVE_OK) == OK);
    dialogue_destroy(d);
}

void test2_dialogue_save(){
    Dialogue* d = NULL;
    PRINT_TEST_RESULT(dialogue_save(d, "mysave.dat", SAVE_SAVE_OK) == ERROR);
}

/*
void plantilla(){
    Dialogue* d = NULL;
    d = dialogue_ini();
    Object* object = NULL;
    Space* space = NULL;
    Link* link = NULL;
    space = space_create(1);
    link = link_create()
    object = object_create();
    PRINT_TEST_RESULT(dialogue_go(d, NORTH, space, OK, "north", link) == OK);
    link_destroy(link);
    space_destroy(space);
    object_destroy(object);
    dialogue_destroy(d);
}*/