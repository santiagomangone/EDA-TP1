/***************************************************************************//**
  @file     +parseCallback.cpp+
  @brief    +valida las entradas del usuaria por consola y guarda los datos en la estructura dada.+
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

#define CLAVES		0
#define TIPOS		1
#define LISTAS		2

   /*******************************************************************************
	* ENUMERATIONS AND STRUCTURES AND TYPEDEFS
	******************************************************************************/
enum claves { suma, resta, producto, cociente, fact, sen, cos, tan, raiz, ln, log, modulo, base, exp, y, angulo, nota };
enum angulos { grados, radianes, gradianes };
enum potencias { n1, n2, n3, n4, n5, n6, n7, n8, n9, n10 };
enum parametros { redondeo, notcientifica };



typedef const char* lista_t[];
typedef lista_t* pToLista_t[];


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static int check(char* palabra, const char* lista[], int items);
static int checkForZero(char* cadena);
static void saveNumber(userData_t* pointerData, int opNumber, double number);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static const char* opciones[][NRO_CLAVES] = {
	{"suma","resta","producto",	"cociente",	"fact",	"sen",	"cos","tan","raiz",	"ln",	"log",	"modulo","exp",	"base", "y",	"angulo","nota"},
	{"num",	"num",	"num",		"num",	   	"num",	"num",  "num","num","num",	"num",	"num",	"num",	"num",	"num", "num","word",  "word"},
	{"any",	"any",	"any",		"any",		"any",	"any",  "any","any","any",	"any",	"any",	"any",	"1",	"any",   "any","0",	 "any" }
};


static lista_t list0 = { "grados", "radianes" , "gradianes" };
static lista_t list1 = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
static pToLista_t ptLista = { (lista_t *) &list0, (lista_t *) &list1 , NULL};

static const char* parametros[] = { "redondeo","notcientifica" };

/*******************************************************************************
 *******************************************************************************
						GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/************************************  parseCallback  ***********************************/
int parseCallback(char* key, char* value, void* userData) {
	userData_t* pointerData = (userData_t*)userData;
	static int opY = 0;		//inicialmente nose puede usar -y
	//bool aridad = 1;		//si la operacion es unaria o binaria
	bool newOp = 1;		//habilita otra operación
	//int counter = 0;		//cuenta cantidad de operandos
	int keyPlace;			//lugar de la clave en el arreglo de opciones
	int valuePlace;			//lugar del valor en una lista
	int parameterPlace;
	int numberList;
	double valor;			//valor numérico 

	printf("clave\n");
	//CLAVE
	keyPlace = check(key, opciones[CLAVES], sizeof(opciones[CLAVES]) / sizeof(char*));
	printf("keyPlace = %d\n", keyPlace);
	if ((key != NULL) && (keyPlace == -1))	//caso clave inválida
	{
		printf("CASO 1 -R0\n");
		return 0;
	}
	else if (keyPlace < y && pointerData->operacion != -1)	//caso dos operaciones
	{
		printf("CASO 2 -R0\n");
		return 0;
	}
	else if (keyPlace == y && opY == 0)	//caso donde no valía -y
	{
		printf("CASO 3 -R0\n");
		return 0;
	}
	else if ((keyPlace == angulo && pointerData->angulo != -1) || (keyPlace == nota && pointerData->nota[0] != '\0'))
	{
		printf("CASO 4 -R0\n");
		return 0;
	}
	else
	{
		if (keyPlace < base)
		{
			pointerData->operacion = keyPlace;		//guarda la operacion
		}
		if (keyPlace < 4)
		{
			opY = 1;
		}
		if (keyPlace == y)
		{
			opY = 0;
		}
	}
	printf("valor\n");
	//VALOR
	if (strcmp("any", opciones[LISTAS][keyPlace]) != 0)			//si la palabra o número no puede ser cualquiera
	{
		numberList = atoi(opciones[LISTAS][keyPlace]);
		int sizeLista;
		switch (numberList) {
		case 0:
			sizeLista = sizeof(list0);
			break;
		case 1:
			sizeLista = sizeof(list1);
			break;
		default:
			printf("default\n");
			break;
		}

		valuePlace = check(value, *ptLista[numberList], sizeLista / sizeof(char*));
		if (valuePlace == -1)
		{
			printf("numberList = %d\n", numberList);
			printf("CASO 5 -R0\n");
			return 0;				//valor de la palabra o número no está en la lista correspondiente.
		}
		else				//aca guardo el valor de la palabra en el enum correspondiente y en la variable correspondiente.	
		{
			if (keyPlace == angulo) { pointerData->angulo = valuePlace; }
			if (keyPlace == exp) { pointerData->exponente = valuePlace; }
			//otros ifs
			printf("CASO 3 - R1\n");
			return 1;
		}
	}
	else if ((strcmp("num", opciones[TIPOS][keyPlace]) == 0) && (strcmp("any", opciones[LISTAS][keyPlace])) == 0)  	//si el valor debe ser un número cualquiera
	{
		
		if ((valor = checkForZero(value)) == 0) {}	//si es cero se guarda
		else if ((valor = atof(value)) == 0) 	//si no se guarda el numero ingresado con atof (devuelve 0 si no se pudo hacer la conversión--> caso valor inválido)
		{
			printf("CASO 6 -R0\n");
			return 0;
		}
		printf("numero %f keyplace %d\n",valor, keyPlace);
		saveNumber(pointerData, keyPlace, valor);
		printf("CASO 4 - R1\n");
		return 1;

	}
	else if ((strcmp("word", opciones[TIPOS][keyPlace]) == 0) && ((strcmp("any", opciones[LISTAS][keyPlace])) == 0)) //si el valor debe ser una palabra cualquiera siempre es válido
	{
		if (keyPlace == nota) { 
			char* clipNote = pointerData->nota;
			strcpy_s(clipNote, 140, value); 
		};
		//otros ifs
		printf("CASO 5 - R1\n");
		return 1;
	}

	//PARAMETROS
	if (key == NULL)
	{
		parameterPlace = check(value, parametros, sizeof(parametros) / sizeof(char*));
		if (parameterPlace == -1)	//caso parámetro inválido
		{
			printf("CASO 7 -R0\n");
			return 0;
		}
		else if ((parameterPlace == redondeo && pointerData->redondeo == 1) || (parameterPlace == notcientifica && pointerData->notcientifica == 1))
		{
			printf("CASO 8 -R0\n");
			return 0;
		}
		else
		{
			if (parameterPlace == redondeo) { pointerData->redondeo = 1; }
			if (parameterPlace == notcientifica) { pointerData->notcientifica = 1; }
			printf("CASO 6 - R1\n");
			return 1;
		}
	}
}


/*******************************************************************************
 *******************************************************************************
						LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

//verifica si la palabra está o no en una lista de palabras. Devuelve el lugar del item correspondiente si está y -1 sino.
static int check(char* palabra, const char* lista[], int items)
{
	for (int i = 0; i < items; i++) {
		if (strcmp(palabra, *(lista + i)) == 0)		//si la palabra está en la lista
			return i;
	}
	return -1;		//si la palabra no está en la lista.
}

//verifica si el usuario ingresó como valor numérico el cero.
static int checkForZero(char* cadena) {
	bool point = 0;
	bool cero = 0;
	while (*cadena != '\0') {
		if (*cadena != '0') {
			if ((*cadena == '.') && (point == 0))
				point = 1;
			else
			{
				printf("CASO 1 - R1\n");
				return 1;		//no es cero
			}
		}
		else {
			cero = 1;
		}
		cadena++;
	}
	if (cero == 1)
		return 0;	//es cero
	else
	{
		printf("CASO 2 - R1\n");
		return 1;
	}
}

static void saveNumber(userData_t* pointerData, int opNumber, double number)
{
	printf("save number: %d\n", opNumber);
	static int counter = 0;
	if (opNumber != y)
	{
		printf("check number %f\n",number);
		pointerData->operando1 = number;
		printf("counter = %d\n", counter);
		if (opNumber < 4) { counter++; }
		printf("counter = %d\n", counter);
	}
	else if (opNumber == y)
	{
		printf("check here\n");
		pointerData->operando2 = number;
	}
	return;
}