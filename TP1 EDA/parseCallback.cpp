/***************************************************************************//**
  @file     +parseCallback.cpp+
  @brief    +valida las entradas del usuario por consola y guarda los datos en la estructura dada.+
  @author   +Grupo 3. TP1.+
 ******************************************************************************/

 /*******************************************************************************
  * INCLUDE HEADER FILES
  ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parseCallback.h"

  /*******************************************************************************
   * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
   ******************************************************************************/
#define NRO_CLAVES	17
#define INVALID		-1

#define CLAVES		0
#define TIPOS		1
#define LISTAS		2

#define LISTA_0		"0"
#define LISTA_1		"1"

/*******************************************************************************
* ENUMERATIONS AND STRUCTURES AND TYPEDEFS
******************************************************************************/
typedef const char* lista_t[];	//arreglo de punteros a string
typedef lista_t* pToLista_t[];	//arreglo de punteros a arreglos de punteros a string

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static int check(const char* palabra, const char* lista[], int items);
static int checkForZero(char* cadena);
static void saveNumber(userData_t* pointerData, int opNumber, double number);
static int adminKeys(int* ptKeyPlace, userData_t* pointerData);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
/*OPCIONES: en la primera fila están las claves, en la segunda, el tipo de dato (num o word) y en la tercera si el dato es libre o está en una lista.
			Si el dato está en una lista, figura el número de lista*/
static const char* opciones[][NRO_CLAVES] = {
	{"suma","resta","producto",	"cociente",	"fact",	"sen",	"cos","tan","raiz",	"ln",	"log",	"modulo","exp",	"base", "y",	"angulo","nota"},
	{"num",	"num",	"num",		"num",	   	"num",	"num",  "num","num","num",	"num",	"num",	"num",	"num",	"num",  "num",	"word",  "word"},
	{"any",	"any",	"any",		"any",		"any",	"any",  "any","any","any",	"any",	"any",	"any",	LISTA_1,	"any",  "any",	LISTA_0,	 "any" }
};

/* list0: valores de ángulo */
static lista_t list0 = { "grados", "radianes" , "gradianes" };
/* list1: valores de exp */
static lista_t list1 = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
/* ptLista es un arreglo de punteros a las listas */
static pToLista_t ptLista = { (lista_t *) &list0, (lista_t *) &list1 }; 

/* lista de parámetros aislados permitidos */
static const char* parametros[] = { "redondeo1","redondeo2", "redondeo3","redondeo4","ayuda"};

/*******************************************************************************
 *******************************************************************************
						GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/************************************  parseCallback  ***********************************
Recibe tres punteros. Los dos primeros apuntas a datos ingresados por el usuario.
key apunta a la clave si la hay, y sino es NULL
value es el valor de la clave si esta existe o un parámetro aislado si key es NULL
userData apunta a la estructura de datos
Devuelve un int: 0 si hay errores y 1 sino.
****************************************************************************************/
int parseCallback(char* key, char* value, void* userData) {

	/*testing*/
	//static int k = 1;
	//printf("Callback nro %d: con key %s, value %s y pointer %p\n", k++, key, value, userData);
	/********/

	userData_t* pointerData = (userData_t*)userData;	//puntero a la estructura datos

	int keyPlace = INVALID;			//lugar de la clave en el arreglo de opciones
	int valuePlace = INVALID;			//lugar del valor en una lista
	int parameterPlace = INVALID;		//lugar del parámetro en el arreglo de parámetros
	int numberList = INVALID;
	double valor = 0;			//valor numérico ingresado por el usuario

	//PARAMETROS
	if (key == NULL)
	{
		parameterPlace = check(value, parametros, sizeof(parametros) / sizeof(char*));	//lugar del parámetro en la lista de parámetros
		if (parameterPlace == INVALID)	//caso parámetro inválido
		{
			//printf("CASO 7 -R0\n");
			return 0;
		}
		else if ( ((parameterPlace == redondeo1) || (parameterPlace == redondeo2) || (parameterPlace == redondeo3) || (parameterPlace == redondeo4)) 
			&& ( pointerData->redondeo1 == true || pointerData->redondeo2 == true || pointerData->redondeo3 == true || pointerData->redondeo4 == true) )	//si se ingresan dos parametros de redondeo
		{
			//printf("CASO 8 -R0\n");
			return 0;				
		}
		else if (parameterPlace == ayuda && pointerData->ayuda == true)		//si se ingresa ayuda dos veces
		{
			//printf("CASO 9 -R0\n");
			return 0;
		}
		else
		{
			if (parameterPlace == redondeo1) { pointerData->redondeo1 = true; }
			if (parameterPlace == redondeo2) { pointerData->redondeo2 = true; }
			if (parameterPlace == redondeo3) { pointerData->redondeo3 = true; }
			if (parameterPlace == redondeo4) { pointerData->redondeo4 = true; }
			if (parameterPlace == ayuda) { pointerData->ayuda = true; }
			//printf("CASO 6 - R1\n");
			return 1;
		}
	}


	//CLAVE
	//printf("CLAVE\n");
	keyPlace = check(key, opciones[CLAVES], sizeof(opciones[CLAVES]) / sizeof(char*));	//lugar de la clave en el arreglo de claves 
	//printf("keyPlace = %d\n", keyPlace);

	if (key != NULL)
	{
		if (keyPlace == INVALID)
		{
			//printf("CASO 1 -R0\n");
			return 0;
		}
		else if (adminKeys(&keyPlace, pointerData) == 0) {	//si hay un error con la clave
			//printf("adminKeys\n");
			return 0;
		}
	}

	//printf("valor\n");
	//VALOR
	if (strcmp("any", opciones[LISTAS][keyPlace]) != 0)			//si la palabra o número no puede ser cualquiera
	{
		numberList = atoi(opciones[LISTAS][keyPlace]);			//número de lista
		int sizeLista;
		switch (numberList) {
		case 0:
			sizeLista = sizeof(list0);
			break;
		case 1:
			sizeLista = sizeof(list1);
			break;
		default:
			printf("default sizeLista\n");
			break;
		}

		valuePlace = check(value, *ptLista[numberList], sizeLista / sizeof(char*));	//lugar del valor en la lista correspondiente
		if (valuePlace == INVALID)
		{
			//printf("numberList = %d\n", numberList);
			//printf("CASO 5 -R0\n");
			return 0;				//valor de la palabra o número no está en la lista correspondiente.
		}
		else				//aca guardo el valor de la palabra en el enum correspondiente y en la variable correspondiente.	
		{
			if (keyPlace == angulo) { pointerData->angulo = valuePlace; }
			//printf("exponente %d\n", valuePlace);
			//printf("%d = %d\n", keyPlace, expo);
			if (keyPlace == expo) { pointerData->exponente = valuePlace; }
			//otros ifs
			//printf("CASO 3 - R1\n");
			return 1;
		}
	}
	else if ((strcmp("num", opciones[TIPOS][keyPlace]) == 0) && (strcmp("any", opciones[LISTAS][keyPlace])) == 0)  	//si el valor debe ser un número cualquiera
	{
		if ((valor = checkForZero(value)) == 0) {}	//si es cero se guarda
		else if ((valor = atof(value)) == 0) 	//si no, se guarda el numero ingresado con atof (devuelve 0 si no se pudo hacer la conversión--> caso valor inválido)
		{
			printf("CASO 6 -R0\n");
			return 0;
		}
		//printf("numero %f _ keyplace %d\n", valor, keyPlace);
		saveNumber(pointerData, keyPlace, valor);
		//printf("CASO 4 - R1\n");
		return 1;
	}
	else if ((strcmp("word", opciones[TIPOS][keyPlace]) == 0) && ((strcmp("any", opciones[LISTAS][keyPlace])) == 0)) //si el valor debe ser una palabra cualquiera siempre es válido
	{
		if (keyPlace == nota) {
			char* clipNote = pointerData->nota;
			strcpy_s(clipNote, 140, value);
		}
		//otros ifs
		//printf("CASO 5 - R1\n");
		return 1;
	}

}



/*******************************************************************************
 *******************************************************************************
						LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

//verifica si la palabra está o no en una lista de palabras. Devuelve el lugar del item correspondiente si está y -1 sino.
static int check(const char* palabra, const char* lista[], int items)
{
	for (int i = 0; i < items; i++) {
		if (strcmp(palabra, *(lista + i)) == 0)		//si la palabra está en la lista
			return i;								//devuelve el lugar en la lista
	}
	return INVALID;		//si la palabra no está en la lista.
}

//Verifica si el usuario ingresó como valor numérico el cero. En tal caso devuelve cero. Caso contrario devuelve 1.
static int checkForZero(char* cadena) {
	bool point = 0;
	bool cero = 0;
	while (*cadena != '\0') {
		if (*cadena != '0') {
			if ((*cadena == '.') && (point == 0))
			{
				point = 1;
			}
			else
			{
				return 1;		//no es cero
			}
		}
		else 
		{
			cero = 1;
		}
		cadena++;
	}
	if (cero == 1)
		return 0;	//es cero
	else
	{
		return 1;
	}
}

//guarda el valor numérico según la çlave. Recibe un puntero a la estructura de datos, el lugar de la clave en el arreglo y el número.
static void saveNumber(userData_t* pointerData, int opNumber, double number)
{
	//printf("keyPlace in saveNumber: %d\n", opNumber);
	static int counter = 0;
	if (opNumber != y)		
	{
		//printf("check number %f\n",number);
		pointerData->operando1 = number;		//si la clave no es y guarda el valor en operando1
		//printf("Operando1: %f\n", pointerData->operando1);
		//printf("counter = %d\n", counter);
		if (opNumber <= cociente)						//si la operacion es binaria aumenta counter
		{ 
			counter++;						
		}
		//printf("counter = %d\n", counter);
	}
	else if (opNumber == y)
	{
		//printf("saves second value\n");
		pointerData->operando2 = number;		//si la clave es y guarda el valor en operando 2
	}
	
	if (opNumber == base)
	{
		//printf("Save in base(%d) %f confirmed\n",base, number);
		pointerData->base = number;				//si la clave es base, guarda el valor en base.
	}
	return;
}

/*administra la validez de la clave ingresada y la registra en la estructura.
Recibe un puntero al lugar de la clave en el arreglo y un puntero a la estructura.
*/
static int adminKeys(int* ptKeyPlace, userData_t * pointerData)
{
	enum keyStates {INIT, EXPO, BASE, POTENCIA, BINARIO, AND, UNARIO, ANGULO, NOTA};
	static int keyState = INIT;		//estado de la FSM
	int keyPlace = *ptKeyPlace;		//lugar de la clave en el arreglo
	//printf("Entra con keyState %d\n", keyState);
	switch (keyState) {
	case INIT:
		if (keyPlace == expo) 
		{
			pointerData->operacion = keyPlace;
			keyState = EXPO; 
		}
		else if (keyPlace == base) 
		{
			pointerData->operacion = expo;
			keyState = BASE; 
		}
		else if (keyPlace <= cociente) 
		{ 
			pointerData->operacion = keyPlace;
			keyState = BINARIO; 
		}
		else if (keyPlace >= fact && keyPlace <= modulo) 
		{
			pointerData->operacion = keyPlace;
			keyState = UNARIO; 
		}
		else if (keyPlace == angulo) 
		{ 
			keyState = ANGULO; 
		}
		else if (keyPlace == nota) 
		{ 
			keyState = NOTA; 
		}
		else 
		{ 
			return 0; 
			//printf("con keyState %d\n", keyState); 
		}
		break;
	case EXPO:
		if (keyPlace == base && pointerData->base == -1) 
		{ 
			keyState = POTENCIA; 
		}
		else 
		{ 
			return 0; 
			//printf("con keyState %d\n", keyState); 
		}
		break;
	case BASE:
		if (keyPlace == expo && pointerData->exponente == INVALID) 
		{ 
			pointerData->operacion = keyPlace;
			keyState = POTENCIA; 
		}
		else 
		{ 
			return 0; 
			//printf("con keyState %d\n", keyState); 
		}
		break;
	case POTENCIA: case AND: case UNARIO:
		if (keyPlace == nota && pointerData->nota[0] == '\0') 
		{ 
			keyState = NOTA; 
		}
		else if (keyPlace == angulo && pointerData->angulo == -1) 
		{ 
			keyState = ANGULO; 
		}
		else 
		{ 
			return 0; 
			//printf("con keyState %d\n", keyState); 
		}
		break;
	case BINARIO:
		if (keyPlace == y) 
		{ 
			keyState = AND; 
		}
		else 
		{ 
			return 0; 
			//printf("con keyState %d\n", keyState); 
		}
		break;
	case ANGULO:
		if (keyPlace == expo && pointerData->exponente == INVALID) 
		{ 
			pointerData->operacion = keyPlace;
			keyState = EXPO; 
		}
		else if (keyPlace == base && pointerData->base == INVALID) 
		{ 
			pointerData->operacion = expo;
			keyState = BASE; 
		}
		else if (keyPlace <= cociente && pointerData->operacion == INVALID) 
		{
			pointerData->operacion = keyPlace;
			keyState = BINARIO; 
		}
		else if (keyPlace >= fact && keyPlace <= modulo && pointerData->operacion == INVALID) 
		{ 
			pointerData->operacion = keyPlace;
			keyState = UNARIO; 
		}
		else if (keyPlace == nota && pointerData->nota[0] == '\0') 
		{ 
			keyState = NOTA; 
		}
		else 
		{ 
			return 0; 
			//printf("con keyState %d\n", keyState); 
		}
		break;
	case NOTA:
		if (keyPlace == expo && pointerData->exponente == INVALID) 
		{
			pointerData->operacion = keyPlace;
			keyState = EXPO; 
		}
		else if (keyPlace == base && pointerData->base == INVALID)
		{ 
			pointerData->operacion = expo;
			keyState = BASE; 
		}
		else if (keyPlace <= cociente && pointerData->operacion == INVALID)
		{ 
			pointerData->operacion = keyPlace;
			keyState = BINARIO; 
		}
		else if (keyPlace >= fact && keyPlace <= modulo && pointerData->operacion == INVALID)
		{ 
			pointerData->operacion = keyPlace;
			keyState = UNARIO; 
		}
		else if (keyPlace == angulo && pointerData->angulo == INVALID)
		{ 
			keyState = ANGULO; 
		}
		else 
		{ 
			return 0; 
			//printf("con keyState %d\n", keyState); 
		}
		break;
	}
	//printf("adminKeys returns 1\n");
	return 1;
}