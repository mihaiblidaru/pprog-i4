/**
 * @brief Programa para probar el modulo Command.
 *       Progama para probar la correcta funcionalidad del
 *       nuevo TAD Command.
 *
 * @file command_test.c
 * @author Mihai Blidaru
 * @version 1.0
 * @date 01-04-2017
 */
 
/* Cabeceras Libc*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Cabeceras Propias */
#include "tests/test.h"
#include "tests/command_test.h"
#include "types.h"
#include "command.h"

/**
 * Número maximo de tests
 * @cond
 */
#define MAX_TESTS 18

int main(int argc, char** argv) {

    int test = 0;
    int all = 1;
    
    if (argc < 2) {
        printf("Running all test for module Inventory:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
        }
    }
    
    if (all || test == 1) test1_command_ini();
    if (all || test == 2) test1_command_destroy();
    if (all || test == 3) test2_command_destroy();
    if (all || test == 4) test1_command_set_cmd();
    if (all || test == 5) test2_command_set_cmd();
    if (all || test == 6) test3_command_set_cmd();
    if (all || test == 7) test1_command_set_cmd_arg();
    if (all || test == 8) test2_command_set_cmd_arg();
    if (all || test == 9) test3_command_set_cmd_arg();
    if (all || test == 10) test4_command_set_cmd_arg();
    if (all || test == 11) test1_command_get_cmd();
    if (all || test == 12) test2_command_get_cmd();
    if (all || test == 13) test3_command_get_cmd();
    if (all || test == 14) test1_command_get_cmd_arg();
    if (all || test == 15) test2_command_get_cmd_arg();
    if (all || test == 16) test3_command_get_cmd_arg();
    if (all || test == 17) test1_command_clear();
    if (all || test == 18) test2_command_clear();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

/**
 * @endcond
 */

/*
 * @test Prueba la función de creación de un gestor de comandos
 * @pre Condiciones normales para la prueba
 * @post Un puntero no nulo al al gestor de comandos creado
 */
void test1_command_ini(){
    Command *cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(cmd != NULL);
    Command_destroy(cmd);
}

/*
 * @test Pruba la función que libera memoria usada por un gestor de comandos
 * @pre El gestor de comandos ha sido previamente inicializado
 * @post La salida esperada es OK
 */

void test1_command_destroy(){
    Command* cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(Command_destroy(cmd) == OK);
}

/*
 * @test Pruba la función que libera memoria usada por un gestor de comandos
 * @pre El gestor de comandos no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_command_destroy(){
    Command* cmd = NULL;
    PRINT_TEST_RESULT(Command_destroy(cmd) == ERROR);
}

/*
 * @test Prueba la función que guarda el tipo de comando en un gestor de comandos
 * @pre El gestor de comandos ha sido inicializado previamente
 * @post La salida esperada es OK
 */
void test1_command_set_cmd(){
    Command* cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(Command_set_cmd(cmd, GO) == OK);
    Command_destroy(cmd);
}

/*
 * @test Prueba la función que guarda el tipo de comando en un gestor de comandos
 * @pre El gestor de comandos ha sido inicializado previamente pero el comando no es valido
 * @post La salida esperada es ERROR
 */
void test2_command_set_cmd(){
    Command* cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(Command_set_cmd(cmd, -2) == ERROR);
    Command_destroy(cmd);
}

/*
 * @test Prueba la función que guarda el tipo de comando en un gestor de comandos
 * @pre El gestor de comandos no ha sido inicializado previamente
 * @post La salida esperada es ERROR
 */
void test3_command_set_cmd(){
    Command* cmd = NULL;
    PRINT_TEST_RESULT(Command_set_cmd(cmd, LEAVE) == ERROR);
}

/*
 * @test Prueba la función que guarda un argumento de un comando en un gestor de comandos
 * @pre El gestor de comandos ha sido inicializado previamente
 * @post La salida esperada es OK
 */
void test1_command_set_cmd_arg(){
    Command* cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(Command_set_cmd_arg(cmd,"test",1) == OK);
    Command_destroy(cmd);
}

/*
 * @test Prueba la función que guarda un argumento de un comando en un gestor de comandos
 * @pre La posición en la que se quiere guardar es invalida
 * @post La salida esperada es ERROR
 */
void test2_command_set_cmd_arg(){
    Command* cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(Command_set_cmd_arg(cmd,"test", -1) == ERROR);
    Command_destroy(cmd);
}

/*
 * @test Prueba la función que guarda un argumento de un comando en un gestor de comandos
 * @pre El gestor de comandos no ha sido inicializado previamente
 * @post La salida esperada es ERROR
 */
void test3_command_set_cmd_arg(){
    Command* cmd = NULL;
    PRINT_TEST_RESULT(Command_set_cmd_arg(cmd,"test", 1) == ERROR);
}

/*
 * @test Prueba la función que guarda un argumento de un comando en un gestor de comandos
 * @pre El argumento es un puntero a NULL
 * @post La salida esperada es ERROR
 */
void test4_command_set_cmd_arg(){
    Command* cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(Command_set_cmd_arg(cmd, NULL, 1) == ERROR);
    Command_destroy(cmd);
}

/*
 * @test Prueba la función que devuelve el tipo de comando guardado en un gestor de comandos
 * @pre El gestor de comandos ha sido inicializado previamente y se le ha asignado el comando GO
 * @post La salida esperada es GO, el comando previamente asignado
 */
void test1_command_get_cmd(){
    Command* cmd = NULL;
    cmd = Command_ini();
    Command_set_cmd(cmd, GO);
    PRINT_TEST_RESULT(Command_get_cmd(cmd) == GO);
    Command_destroy(cmd);
}

/*
 * @test Prueba la función que devuelve el tipo de comando guardado en un gestor de comandos
 * @pre El gestor de comandos no ha sido inicializado previamente
 * @post La salida esperada es UNKNOWN, comando desconocido
 */
void test2_command_get_cmd(){
    Command* cmd = NULL;
    PRINT_TEST_RESULT(Command_get_cmd(cmd) == UNKNOWN);
}

/*
 * @test Prueba la función que devuelve el tipo de comando guardado en un gestor de comandos
 * @pre El gestor de comandos ha sido inicializado previamente pero no se le ha asignado un comando
 * @post La salida esperada es NO_CMD
 */
void test3_command_get_cmd(){
    Command* cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(Command_get_cmd(cmd) == NO_CMD);
    Command_destroy(cmd);
}

/*
 * @test Prueba la función que devuelve un argumento de un comando guardado en un gestor de comandos
 * @pre El gestor de comandos ha sido inicializado previamente y se le ha asignado un argumento "test"
 * @post La salida esperada es "test", el argumento añadido previamente
 */
void test1_command_get_cmd_arg(){
   Command* cmd = NULL;
   cmd = Command_ini();
   Command_set_cmd_arg(cmd, "test", 1);
   PRINT_TEST_RESULT(strcmp(Command_get_cmd_arg(cmd,1), "test") == 0);
   Command_destroy(cmd);
}

/*
 * @test Prueba la función que devuelve un argumento de un comando guardado en un gestor de comandos
 * @pre El gestor de comandos no ha sido inicializado previamente
 * @post La salida esperada es NULL
 */
void test2_command_get_cmd_arg(){
   Command* cmd = NULL;
   PRINT_TEST_RESULT(Command_get_cmd_arg(cmd,1) == NULL);
}
/*
 * @test Prueba la función que devuelve un argumento de un comando guardado en un gestor de comandos
 * @pre El gestor de comandos ha sido inicializado previamente pero no se le ha asignado un argumento
 * @post La salida esperada es una cadena vacia
 */
void test3_command_get_cmd_arg(){
   Command* cmd = NULL;
   cmd = Command_ini();
   PRINT_TEST_RESULT(strcmp(Command_get_cmd_arg(cmd,1), "") == 0);
   Command_destroy(cmd);
}

/*
 * @test Prueba la función que limpia los campos de un commando
 * @pre El gestor de comandos ha sido inicializado previamente y se ha guardado un comando dentro
 * @post La salida esperada es NO_CMD y una cadena vacia
 */
void test1_command_clear(){
   Command* cmd = NULL;
   cmd = Command_ini();
   Command_set_cmd(cmd, GO);
   Command_set_cmd_arg(cmd, "south", 0);
   Command_clear(cmd);
   PRINT_TEST_RESULT(Command_get_cmd(cmd) == NO_CMD && strcmp(Command_get_cmd_arg(cmd,1), "") == 0);
   Command_destroy(cmd);
}

/*
 * @test Prueba la función que limpia los campos de un commando
 * @pre El gestor de comandos no ha sido inicializado previamente
 * @post La salida esperada es ERROR
 */
void test2_command_clear(){
   Command* cmd = NULL;
   PRINT_TEST_RESULT(Command_clear(cmd) == ERROR);
}