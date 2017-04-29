/**
 * @brief Pruebas para el modulo Object
 * @file object_test.h
 * @author Javier Bernardo
 * @date 24/04/2017
 */
#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H


/* 
 * @test Prueba si se crea correctamente un objeto
 * @post Un puntero no nulo al objeto creado
 */ 
void test1_object_create();

/** 
 * @test Prueba si se le asigna correctamente un nombre a un objeto
 * @pre El nombre del objeto
 * @post La salida tiene que ser el puntero al objeto
 */  
void test1_object_set_name();

/** 
 * @test Prueba asignar un nombre a un objeto sin inicializar
 * @pre El objeto al que establecer el nombre es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_name();

/** 
 * @test Prueba si se le asigna correctamente un Id a un objeto
 * @pre El Id del objeto
 * @post La salida tiene que ser el puntero al objeto
 */  
void test1_object_set_Id();

/** 
 * @test Prueba asignar un Id a un objeto sin inicializar
 * @pre El objeto al que establecer el Id es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_Id();

/** 
 * @test Prueba si se le asigna correctamente una descripcion a un objeto
 * @pre La descripcion del objeto
 * @post La salida tiene que ser el puntero al objeto
 */  
void test1_object_set_description();

/** 
 * @test Prueba asignar una descripcion a un objeto sin inicializar
 * @pre El objeto al que establecer la descripcion es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_description();

/** 
 * @test Prueba si se le asigna correctamente una descripcion2 a un objeto
 * @pre La descripcion2 del objeto
 * @post La salida tiene que ser el puntero al objeto
 */  
void test1_object_set_description2();

/** 
 * @test Prueba asignar una descripcion2 a un objeto sin inicializar
 * @pre El objeto al que establecer la descripcion2 es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_description2();
/** 
 * @test Prueba si se le asigna correctamente una movilidad a un objeto
 * @pre La movilidad del objeto
 * @post La salida tiene que ser el puntero al objeto
 */ 
void test1_object_set_Mobile();
/** 
 * @test Prueba asignar una movilidad a un objeto sin inicializar
 * @pre El objeto al que establecer la movilidad es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_Mobile();

/** 
 * @test Prueba si se le asigna correctamente una movilidad a un objeto
 * @pre La movilidad del objeto
 * @post La salida tiene que ser el puntero al objeto
 */ 
void test1_object_set_Moved();

/** 
 * @test Prueba asignar una movilidad a un objeto sin inicializar
 * @pre El objeto al que establecer la movilidad es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_Moved();

/** 
 * @test Prueba si se le asigna correctamente una situacion a un objeto
 * @pre La situacion del objeto
 * @post La salida tiene que ser el puntero al objeto
 */ 
void test1_object_set_Hidden();

/** 
 * @test Prueba asignar una situacion a un objeto sin inicializar
 * @pre El objeto al que establecer la situacion es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_Hidden();
/** 
 * @test Prueba si se le asigna correctamente una situacion a un objeto
 * @pre La situacion del objeto
 * @post La salida tiene que ser el puntero al objeto
 */ 
void test1_object_set_Open();
/** 
 * @test Prueba asignar una situacion a un objeto sin inicializar
 * @pre El objeto al que establecer la situacion es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_Open();

/** 
 * @test Prueba si se le asigna correctamente una iluminacion a un objeto
 * @pre La iluminacion del objeto
 * @post La salida tiene que ser el puntero al objeto
 */ 
void test1_object_set_Illuminates();

/** 
 * @test Prueba asignar una iluminacion a un objeto sin inicializar
 * @pre El objeto al que establecer la iluminacion es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_Illuminates();

/** 
 * @test Prueba si se le asigna correctamente una iluminacion a un objeto
 * @pre La iluminacion del objeto
 * @post La salida tiene que ser el puntero al objeto
 */ 
void test1_object_set_Light();
/** 
 * @test Prueba asignar una iluminacion a un objeto sin inicializar
 * @pre El objeto al que establecer la iluminacion es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_object_set_Light();
/**
 * @test Prueba leer el nombre de un objeto
 * @pre Al nombre se le ha asignado previamente el nombre Bryan
 * @post La salida esperada es el id asignado antes "Bryan"
 */
void test1_object_Get_Name();

/**
 * @test Prueba leer el nombre de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es NULL
 */
void test2_object_Get_Name();

/**
 * @test Prueba leer el id de un objeto
 * @pre Al objeto se le ha asignado previamente el id 12
 * @post La salida esperada es el id asignado antes (12)
 */
void test1_object_Get_Id();

/**
 * @test Prueba leer el id de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es NO_ID
 */
void test2_object_Get_Id();

/**
 * @test Prueba leer la descripcion de un objeto
 * @pre Al objeto se le ha asignado previamente la descripcion
 * @post La salida esperada es la descripcion asignado antes 
 */
void test1_object_Get_Description();

/**
 * @test Prueba leer la descripcion de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es NULL
 */
void test2_object_Get_Description();

/**
 * @test Prueba leer la descripcion de un objeto
 * @pre Al objeto se le ha asignado previamente la descripcion
 * @post La salida esperada es la descripcion asignado antes 
 */
void test1_object_Get_Description2();

/**
 * @test Prueba leer la descripcion de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es NULL
 */
void test2_object_Get_Description2();

/**
 * @test Prueba leer la movilidad de un objeto
 * @pre Al objeto se le ha asignado previamente la movilidad
 * @post La salida esperada es la movilidad asignada antes 
 */
void test1_object_Get_Mobile();

/**
 * @test Prueba leer la movilidad de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es FALSE
 */
void test2_object_Get_Mobile();
/**
 * @test Prueba leer si se ha movido un objeto
 * @pre Al objeto se le ha asignado previamente la movilidad
 * @post La salida esperada es la movilidad asignada antes 
 */
void test1_object_Get_Moved();

/**
 * @test Prueba leer la movilidad de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es FALSE
 */
void test2_object_Get_Moved();

/**
 * @test Prueba leer si se ha escondido un objeto
 * @pre Al objeto se le ha asignado previamente la invibisibilidad
 * @post La salida esperada es la movilidad asignada antes 
 */
void test1_object_Get_Hidden();

/**
 * @test Prueba leer la situacion de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es FALSE
 */
void test2_object_Get_Hidden();

/**
 * @test Prueba leer si se ha abierto el link a un objeto
 * @pre Al objeto se le ha asignado previamente la disponibilidad
 * @post La salida esperada es la movilidad asignada antes 
 */
void test1_object_Get_Open();
/**
 * @test Prueba leer la situacion del link a un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es NO_ID
 */
void test2_object_Get_Open();

/**
 * @test Prueba leer si se ha iluminado un objeto
 * @pre Al objeto se le ha asignado previamente la posibilidad de iluminar
 * @post La salida esperada es la movilidad asignada antes 
 */
void test1_object_Get_Illuminates();

/**
 * @test Prueba leer la situacion de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es FALSE
 */
void test2_object_Get_Illuminates();

/**
 * @test Prueba leer si se puede iluminar un objeto
 * @pre Al objeto se le ha asignado previamente la posibilidad de iluminar
 * @post La salida esperada es la movilidad asignada antes 
 */
void test1_object_Get_Light();

/**
 * @test Prueba leer la situacion de un objeto
 * @pre El objeto no ha sido inicializado previamente
 * @post La salida esperada es FALSE
 */
void test2_object_Get_Light();


#endif