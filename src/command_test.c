/*
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
#include "test.h"
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
    if (test < 1 && test > MAX_TESTS) {
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


void test1_command_ini(){
    Command *cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(cmd != NULL);
    Command_destroy(cmd);
}

void test1_command_destroy(){
    Command* cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(Command_destroy(cmd) == OK);
}

void test2_command_destroy(){
    Command* cmd = NULL;
    PRINT_TEST_RESULT(Command_destroy(cmd) == ERROR);
}

void test1_command_set_cmd(){
    Command* cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(Command_set_cmd(cmd, GO) == OK);
    Command_destroy(cmd);
}

void test2_command_set_cmd(){
    Command* cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(Command_set_cmd(cmd, -2) == ERROR);
    Command_destroy(cmd);
}

void test3_command_set_cmd(){
    Command* cmd = NULL;
    PRINT_TEST_RESULT(Command_set_cmd(cmd, LEAVE) == ERROR);
}

void test1_command_set_cmd_arg(){
    Command* cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(Command_set_cmd_arg(cmd,"test",1) == OK);
    Command_destroy(cmd);
}

void test2_command_set_cmd_arg(){
    Command* cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(Command_set_cmd_arg(cmd,"test", -1) == ERROR);
    Command_destroy(cmd);
}

void test3_command_set_cmd_arg(){
    Command* cmd = NULL;
    PRINT_TEST_RESULT(Command_set_cmd_arg(cmd,"test", 1) == ERROR);
}

void test4_command_set_cmd_arg(){
    Command* cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(Command_set_cmd_arg(cmd, NULL, 1) == ERROR);
    Command_destroy(cmd);
}

void test1_command_get_cmd(){
    Command* cmd = NULL;
    cmd = Command_ini();
    Command_set_cmd(cmd, GO);
    PRINT_TEST_RESULT(Command_get_cmd(cmd) == GO);
    Command_destroy(cmd);
}

void test2_command_get_cmd(){
    Command* cmd = NULL;
    PRINT_TEST_RESULT(Command_get_cmd(cmd) == UNKNOWN);
}

void test3_command_get_cmd(){
    Command* cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(Command_get_cmd(cmd) == NO_CMD);
    Command_destroy(cmd);
}

void test1_command_get_cmd_arg(){
   Command* cmd = NULL;
   cmd = Command_ini();
   Command_set_cmd_arg(cmd,"test",1);
   PRINT_TEST_RESULT(strcmp(Command_get_cmd_arg(cmd,1), "test") == 0);
   Command_destroy(cmd);
}

void test2_command_get_cmd_arg(){
   Command* cmd = NULL;
   PRINT_TEST_RESULT(Command_get_cmd_arg(cmd,1) == NULL);
}

void test3_command_get_cmd_arg(){
   Command* cmd = NULL;
   cmd = Command_ini();
   PRINT_TEST_RESULT(strcmp(Command_get_cmd_arg(cmd,1), "") == 0);
   Command_destroy(cmd);
}

void test1_command_clear(){
   Command* cmd = NULL;
   cmd = Command_ini();
   Command_set_cmd(cmd, GO);
   Command_set_cmd_arg(cmd, "south", 0);
   Command_clear(cmd);
   PRINT_TEST_RESULT(Command_get_cmd(cmd) == NO_CMD && strcmp(Command_get_cmd_arg(cmd,1), "") == 0);
   Command_destroy(cmd);
}

void test2_command_clear(){
   Command* cmd = NULL;
   PRINT_TEST_RESULT(Command_clear(cmd) == ERROR);
}