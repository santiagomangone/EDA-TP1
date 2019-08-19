/***************************************************************************//**
  @file     +calculadora.h+
  @brief    +Realiza las operaciones a partir de la estructura de datos+
  @author   +Grupo 3. Alejo Figueroa, Pablo Gonzalez, Santiago Mangone+
 ******************************************************************************/

#ifndef CALCULADORA_H
#define CALCULADORA_H

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct
{
	int operacion = -1;

	double operando1 = 0;
	double operando2 = 0;	//para operaciones binarias 

	//potencia
	double base = -1;
	int exponente = -1;

	//otras opciones
	int angulo = -1;
	char nota[140] = { '\0' };	//como mucho un tweet

	//parametros
	bool redondeo1, redondeo2, redondeo3, redondeo4 = false;
	bool ayuda = false;
}userData_t;

enum claves { suma, resta, producto, cociente, fact, seno, coseno, tg, raiz, ln, logd, modulo, expo, base, y, angulo, nota };
enum parametros { redondeo1, redondeo2, redondeo3, redondeo4 ,ayuda};

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
 /**
  * @brief calculadora: recibe una estructura 'datos' y hace las operaciones indicadas en ella.
  * @param datos estructura que contiene operacion, operandos y algunas configuraciones adicionales.
  * @return void
 */
void calculadora(userData_t datos);

#endif