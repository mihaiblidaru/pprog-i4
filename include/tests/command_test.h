 /**
 * @brief Define las funciones para la prueba del modulo Command
 * 
 * @file command_test.h
 * @author Mihai Blidaru
 * @version 1.0 
 * @date 14-03-2017
 * @copyright GNU Public License
 */
 
#ifndef COMMAND_TEST_H
#define COMMAND_TEST_H

/**
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

/**
 * @test Pruba la función que libera memoria usada por un gestor de comandos
 * @pre El gestor de comandos ha sido previamente inicializado
 * @post La salida esperada es OK
 */

void test1_command_destroy(){
    Command* cmd = NULL;
    cmd = Command_ini();
    PRINT_TEST_RESULT(Command_destroy(cmd) == OK);
}

/**
 * @test Pruba la función que libera memoria usada por un gestor de comandos
 * @pre El gestor de comandos no ha sido inicializado
 * @post La salida esperada es ERROR
 */
void test2_command_destroy(){
    Command* cmd = NULL;
    PRINT_TEST_RESULT(Command_destroy(cmd) == ERROR);
}

/**
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

/**
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

/**
 * @test Prueba la función que guarda el tipo de comando en un gestor de comandos
 * @pre El gestor de comandos no ha sido inicializado previamente
 * @post La salida esperada es ERROR
 */
void test3_command_set_cmd(){
    Command* cmd = NULL;
    PRINT_TEST_RESULT(Command_set_cmd(cmd, LEAVE) == ERROR);
}

/**
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

/**
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

/**
 * @test Prueba la función que guarda un argumento de un comando en un gestor de comandos
 * @pre El gestor de comandos no ha sido inicializado previamente
 * @post La salida esperada es ERROR
 */
void test3_command_set_cmd_arg(){
    Command* cmd = NULL;
    PRINT_TEST_RESULT(Command_set_cmd_arg(cmd,"test", 1) == ERROR);
}

/**
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

/**
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

/**
 * @test Prueba la función que devuelve el tipo de comando guardado en un gestor de comandos
 * @pre El gestor de comandos no ha sido inicializado previamente
 * @post La salida esperada es UNKNOWN, comando desconocido
 */
void test2_command_get_cmd(){
    Command* cmd = NULL;
    PRINT_TEST_RESULT(Command_get_cmd(cmd) == UNKNOWN);
}

/**
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

/**
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

/**
 * @test Prueba la función que devuelve un argumento de un comando guardado en un gestor de comandos
 * @pre El gestor de comandos no ha sido inicializado previamente
 * @post La salida esperada es NULL
 */
void test2_command_get_cmd_arg(){
   Command* cmd = NULL;
   PRINT_TEST_RESULT(Command_get_cmd_arg(cmd,1) == NULL);
}
/**
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

/**
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

/**
 * @test Prueba la función que limpia los campos de un commando
 * @pre El gestor de comandos no ha sido inicializado previamente
 * @post La salida esperada es ERROR
 */
void test2_command_clear(){
   Command* cmd = NULL;
   PRINT_TEST_RESULT(Command_clear(cmd) == ERROR);
}


#endif