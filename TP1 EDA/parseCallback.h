/***************************************************************************//**
  @file     +parseCallback.h+
  @brief    +valida las entradas del usuaria por consola y guarda los datos en la estructura dada.+
  @author   +Grupo 3. TP1.+
 ******************************************************************************/
#ifndef _parseCallback_H_
#define _parseCallback_H_

#include <stdio.h>
#include <stdio.h>

 /*******************************************************************************
  * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
  ******************************************************************************/
typedef struct
{
	int operacion = -1;

	double operando1;
	double operando2; //opcional

	double base;
	int exponente = -1;

	int angulo = -1;
	char nota[140] = {'\0'};	//como mucho un tweet

	//parametros
	bool redondeo = false;
	bool notcientifica = false;
}userData_t;

 /*******************************************************************************
  * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
  ******************************************************************************/
int parseCallback(char* key, char* value, void* userData);

#endif