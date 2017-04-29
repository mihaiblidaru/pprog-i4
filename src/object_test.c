/** 
 * @brief Prueba el módulo Object
 * 
 * @file object_test.c
 * @author Javier Bernardo
 * @version 2.0 
 * @date 24-04-2017
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test.h"
#include "tests/object_test.h"
#include "object.h"

/**
 * @cond
 * Número máximo de Pruebas para el módulo Object
 * 
 */
#define MAX_TESTS 41

/** 
 * @brief Funcion principal de pruebas para el modulo Object.
 * 
 * Dos modos de ejecucion:
 *   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas 
 *   2.-Si se ejecuta con un numero entre 1 y el numero de pruebas solo ejecuta 
 *      la prueba indicada  
 *  @private
 */
int main(int argc, char** argv) {

    int test = 0;
    int all = 1;
    
    if (argc < 2) {
        printf("Running all test for module Object:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
        }  
    }
    
    if (all || test == 1) test1_object_create();
    if (all || test == 2) test1_object_set_name();
    if (all || test == 3) test2_object_set_name();
    if (all || test == 4) test1_object_set_Id();
    if (all || test == 5) test2_object_set_Id();
    if (all || test == 6) test1_object_set_description();
    if (all || test == 7) test2_object_set_description();
    if (all || test == 8) test1_object_set_description2();
    if (all || test == 9) test2_object_set_description2();
    if (all || test == 10) test1_object_set_Mobile(); 
    if (all || test == 11) test2_object_set_Mobile();
    if (all || test == 12) test1_object_set_Moved(); 
    if (all || test == 13) test2_object_set_Moved(); 
    if (all || test == 14) test1_object_set_Hidden(); 
    if (all || test == 15) test2_object_set_Hidden();
    if (all || test == 16) test1_object_set_Open(); 
    if (all || test == 17) test2_object_set_Open(); 
    if (all || test == 18) test1_object_set_Illuminates(); 
    if (all || test == 19) test2_object_set_Illuminates(); 
    if (all || test == 20) test1_object_set_Light(); 
    if (all || test == 21) test2_object_set_Light(); 
    if (all || test == 22) test1_object_Get_Name();
    if (all || test == 23) test2_object_Get_Name();
    if (all || test == 24) test1_object_Get_Id();
    if (all || test == 25) test2_object_Get_Id();
    if (all || test == 26) test1_object_Get_Description();
    if (all || test == 27) test2_object_Get_Description();
    if (all || test == 28) test1_object_Get_Description2();
    if (all || test == 29) test2_object_Get_Description2();
    if (all || test == 30) test1_object_Get_Mobile();
    if (all || test == 31) test2_object_Get_Mobile();
    if (all || test == 32) test1_object_Get_Moved();
    if (all || test == 33) test2_object_Get_Moved();
    if (all || test == 34) test1_object_Get_Hidden();
    if (all || test == 35) test2_object_Get_Hidden();
    if (all || test == 36) test1_object_Get_Open();
    if (all || test == 37) test2_object_Get_Open();
    if (all || test == 38) test1_object_Get_Illuminates();
    if (all || test == 39) test2_object_Get_Illuminates();
    if (all || test == 40) test1_object_Get_Light();
    if (all || test == 41) test2_object_Get_Light();
    PRINT_PASSED_PERCENTAGE;
    return 0;
}
/**
 * @endcond
 */
 
/* 
 * @test Prueba si se crea correctamente un objeto
 * @post Un puntero no nulo al objeto creado
 */ 
void test1_object_create(){
    Object* object = NULL;
    object = object_create();
    PRINT_TEST_RESULT(object != NULL);
    object_destroy(object);
}

/* 
 * @test Prueba si se le asigna correctamente un nombre a un objeto
 * @pre El nombre del objeto
 * @post La salida tiene que ser el puntero al objeto
 */  
void test1_object_set_name() {
    Object *object;
    object = object_create();
    PRINT_TEST_RESULT(object_Set_Name(object, "Bob") == object);
    object_destroy(object);
}

/* 
 * @test Prueba asignar un nombre a un objeto sin inicializar
 * @pre El objeto al que establecer el nombre es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_name() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Set_Name(object, "hola") == NULL);
}

/* 
 * @test Prueba si se le asigna correctamente un Id a un objeto
 * @pre El Id del objeto
 * @post La salida tiene que ser el puntero al objeto
 */  
void test1_object_set_Id() {
    Object *object;
    object = object_create();
    PRINT_TEST_RESULT(object_Set_Id(object, 1) == object);
    object_destroy(object);
}

/* 
 * @test Prueba asignar un Id a un objeto sin inicializar
 * @pre El objeto al que establecer el Id es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_Id() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Set_Id(object, 1) == NULL);
}

/* 
 * @test Prueba si se le asigna correctamente una descripcion a un objeto
 * @pre La descripcion del objeto
 * @post La salida tiene que ser el puntero al objeto
 */  
void test1_object_set_description() {
    Object *object;
    object = object_create();
    PRINT_TEST_RESULT(object_Set_Description(object, "Aqui esta el objeto") == object);
    object_destroy(object);
}

/* 
 * @test Prueba asignar una descripcion a un objeto sin inicializar
 * @pre El objeto al que establecer la descripcion es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_description() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Set_Description(object, "Aqui esta el objeto") == NULL);
}

/* 
 * @test Prueba si se le asigna correctamente una descripcion2 a un objeto
 * @pre La descripcion2 del objeto
 * @post La salida tiene que ser el puntero al objeto
 */  
void test1_object_set_description2() {
    Object *object;
    object = object_create();
    PRINT_TEST_RESULT(object_Set_Description2(object, "Aqui tambien esta el objeto") == object);
    object_destroy(object);
}

/* 
 * @test Prueba asignar una descripcion2 a un objeto sin inicializar
 * @pre El objeto al que establecer la descripcion2 es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_description2() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Set_Description2(object, "Aqui tambien está el objeto") == NULL);
}

/* 
 * @test Prueba si se le asigna correctamente una movilidad a un objeto
 * @pre La movilidad del objeto
 * @post La salida tiene que ser el puntero al objeto
 */ 
void test1_object_set_Mobile() {
    Object *object;
    object = object_create();
    PRINT_TEST_RESULT(object_Set_Mobile(object, TRUE) == OK);
    object_destroy(object);
}

/* 
 * @test Prueba asignar una movilidad a un objeto sin inicializar
 * @pre El objeto al que establecer la movilidad es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_Mobile() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Set_Mobile(object, FALSE) == ERROR);
}

/* 
 * @test Prueba si se le asigna correctamente una movilidad a un objeto
 * @pre La movilidad del objeto
 * @post La salida tiene que ser el puntero al objeto
 */ 
void test1_object_set_Moved() {
    Object *object;
    object = object_create();
    PRINT_TEST_RESULT(object_Set_Moved(object, TRUE) == OK);
    object_destroy(object);
}

/* 
 * @test Prueba asignar una movilidad a un objeto sin inicializar
 * @pre El objeto al que establecer la movilidad es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_Moved() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Set_Moved(object, FALSE) == ERROR);
}

/* 
 * @test Prueba si se le asigna correctamente una situacion a un objeto
 * @pre La situacion del objeto
 * @post La salida tiene que ser el puntero al objeto
 */ 
void test1_object_set_Hidden() {
    Object *object;
    object = object_create();
    PRINT_TEST_RESULT(object_Set_Hidden(object, TRUE) == OK);
    object_destroy(object);
}

/* 
 * @test Prueba asignar una situacion a un objeto sin inicializar
 * @pre El objeto al que establecer la situacion es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_Hidden() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Set_Hidden(object, FALSE) == ERROR);
}

/* 
 * @test Prueba si se le asigna correctamente una situacion a un objeto
 * @pre La situacion del objeto
 * @post La salida tiene que ser el puntero al objeto
 */ 
void test1_object_set_Open() {
    Object *object;
    object = object_create();
    PRINT_TEST_RESULT(object_Set_Open(object, 10) == OK);
    object_destroy(object);
}

/* 
 * @test Prueba asignar una situacion a un objeto sin inicializar
 * @pre El objeto al que establecer la situacion es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_Open() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Set_Open(object, NO_ID) == ERROR);
}

/* 
 * @test Prueba si se le asigna correctamente una iluminacion a un objeto
 * @pre La iluminacion del objeto
 * @post La salida tiene que ser el puntero al objeto
 */ 
void test1_object_set_Illuminates() {
    Object *object;
    object = object_create();
    PRINT_TEST_RESULT(object_Set_Illuminates(object, TRUE) == OK);
    object_destroy(object);
}

/* 
 * @test Prueba asignar una iluminacion a un objeto sin inicializar
 * @pre El objeto al que establecer la iluminacion es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_Illuminates() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Set_Illuminates(object, FALSE) == ERROR);
}

/* 
 * @test Prueba si se le asigna correctamente una iluminacion a un objeto
 * @pre La iluminacion del objeto
 * @post La salida tiene que ser el puntero al objeto
 */ 
void test1_object_set_Light() {
    Object *object;
    object = object_create();
    object_Set_Illuminates(object, TRUE);
    PRINT_TEST_RESULT(object_Set_Light(object, TRUE) == OK);
    object_destroy(object);
}

/* 
 * @test Prueba asignar una iluminacion a un objeto sin inicializar
 * @pre El objeto al que establecer la iluminacion es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_Light() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Set_Light(object, FALSE) == ERROR);
}

/*
 * @test Prueba leer el nombre de un objeto
 * @pre Al nombre se le ha asignado previamente el nombre Bryan
 * @post La salida esperada es el id asignado antes "Bryan"
 */
void test1_object_Get_Name(){
    Object *object = NULL;
    object = object_create();
    object_Set_Name(object, "Bryan");
    PRINT_TEST_RESULT(strcmp(object_Get_Name(object), "Bryan") == 0);
    object_destroy(object);
}

/*
 * @test Prueba leer el nombre de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es NULL
 */
void test2_object_Get_Name(){
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Get_Name(object) == NULL);
}

/*
 * @test Prueba leer el id de un objeto
 * @pre Al objeto se le ha asignado previamente el id 12
 * @post La salida esperada es el id asignado antes (12)
 */
void test1_object_Get_Id(){
    Object *object = NULL;
    object = object_create();
    object_Set_Id(object, 12);
    PRINT_TEST_RESULT(object_Get_Id(object) == 12);
    object_destroy(object);
}

/*
 * @test Prueba leer el id de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es NO_ID
 */
void test2_object_Get_Id(){
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Get_Id(object) == NO_ID);
}

/*
 * @test Prueba leer la descripcion de un objeto
 * @pre Al objeto se le ha asignado previamente la descripcion
 * @post La salida esperada es la descripcion asignado antes 
 */
void test1_object_Get_Description(){
    Object *object = NULL;
    object = object_create();
    object_Set_Description(object, "Todo es uno y uno es todo");
    PRINT_TEST_RESULT(strcmp(object_Get_Description(object), "Todo es uno y uno es todo") == 0);
    object_destroy(object);
}

/*
 * @test Prueba leer la descripcion de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es NULL
 */
void test2_object_Get_Description(){
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Get_Description(object) == NULL);
}

/*
 * @test Prueba leer la descripcion de un objeto
 * @pre Al objeto se le ha asignado previamente la descripcion
 * @post La salida esperada es la descripcion asignado antes 
 */
void test1_object_Get_Description2(){
    Object *object = NULL;
    object = object_create();
    object_Set_Description2(object, "Sin sacrificio no hay victoria, Para ganar algo en la vida debes de pagar algo de igual precio");
    PRINT_TEST_RESULT(strcmp(object_Get_Description2(object), "Sin sacrificio no hay victoria, Para ganar algo en la vida debes de pagar algo de igual precio") == 0);
    object_destroy(object);
}

/*
 * @test Prueba leer la descripcion de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es NULL
 */
void test2_object_Get_Description2(){
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Get_Description2(object) == NULL);
}

/*
 * @test Prueba leer la movilidad de un objeto
 * @pre Al objeto se le ha asignado previamente la movilidad
 * @post La salida esperada es la movilidad asignada antes 
 */
void test1_object_Get_Mobile(){
    Object *object = NULL;
    object = object_create();
    object_Set_Mobile(object, TRUE);
    PRINT_TEST_RESULT(object_Get_Mobile(object) == TRUE);
    object_destroy(object);
}

/*
 * @test Prueba leer la movilidad de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es FALSE
 */
void test2_object_Get_Mobile(){
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Get_Mobile(object) == FALSE);
}

/*
 * @test Prueba leer si se ha movido un objeto
 * @pre Al objeto se le ha asignado previamente la movilidad
 * @post La salida esperada es la movilidad asignada antes 
 */
void test1_object_Get_Moved(){
    Object *object = NULL;
    object = object_create();
    object_Set_Moved(object, TRUE);
    PRINT_TEST_RESULT(object_Get_Moved(object) == TRUE);
    object_destroy(object);
}

/*
 * @test Prueba leer la movilidad de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es FALSE
 */
void test2_object_Get_Moved(){
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Get_Moved(object) == FALSE);
} 

/*
 * @test Prueba leer si se ha escondido un objeto
 * @pre Al objeto se le ha asignado previamente la invibisibilidad
 * @post La salida esperada es la movilidad asignada antes 
 */
void test1_object_Get_Hidden(){
    Object *object = NULL;
    object = object_create();
    object_Set_Hidden(object, TRUE);
    PRINT_TEST_RESULT(object_Get_Hidden(object) == TRUE);
    object_destroy(object);
}

/*
 * @test Prueba leer la situacion de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es FALSE
 */
void test2_object_Get_Hidden(){
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Get_Hidden(object) == FALSE);
} 

/*
 * @test Prueba leer si se ha abierto el link a un objeto
 * @pre Al objeto se le ha asignado previamente la disponibilidad
 * @post La salida esperada es la movilidad asignada antes 
 */
void test1_object_Get_Open(){
    Object *object = NULL;
    object = object_create();
    object_Set_Open(object, 10);
    PRINT_TEST_RESULT(object_Get_Open(object) == 10);
    object_destroy(object);
}

/*
 * @test Prueba leer la situacion del link a un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es NO_ID
 */
void test2_object_Get_Open(){
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Get_Open(object) == NO_ID);
} 

/*
 * @test Prueba leer si se ha iluminado un objeto
 * @pre Al objeto se le ha asignado previamente la posibilidad de iluminar
 * @post La salida esperada es la movilidad asignada antes 
 */
void test1_object_Get_Illuminates(){
    Object *object = NULL;
    object = object_create();
    object_Set_Illuminates(object, TRUE);
    PRINT_TEST_RESULT(object_Get_Illuminates(object) == TRUE);
    object_destroy(object);
}

/*
 * @test Prueba leer la situacion de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es FALSE
 */
void test2_object_Get_Illuminates(){
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Get_Illuminates(object) == FALSE);
} 

/*
 * @test Prueba leer si se puede iluminar un objeto
 * @pre Al objeto se le ha asignado previamente la posibilidad de iluminar
 * @post La salida esperada es la movilidad asignada antes 
 */
void test1_object_Get_Light(){
    Object *object = NULL;
    object = object_create();
    object_Set_Illuminates(object, TRUE);
    object_Set_Light(object, TRUE);
    PRINT_TEST_RESULT(object_Get_Light(object) == TRUE);
    object_destroy(object);
}

/*
 * @test Prueba leer la situacion de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es FALSE
 */
void test2_object_Get_Light(){
    Object *object = NULL;
    PRINT_TEST_RESULT(object_Get_Light(object) == FALSE);
} 

