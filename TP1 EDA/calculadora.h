#ifndef CALCULADORA_H
#define CALCULADORA_H

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct
{
	int operacion = -1;

	double operando1 = 0;
	double operando2 = 0; //opcional

	double base = -1;
	int exponente = -1;

	int angulo = -1;
	char nota[140] = { '\0' };	//como mucho un tweet

	//parametros
	bool redondeo1, redondeo2, redondeo3, redondeo4 = false;
}userData_t;

enum claves { suma, resta, producto, cociente, fact, seno, coseno, tg, raiz, ln, logd, modulo, expo, base, y, angulo, nota };
enum angulos { grados, radianes, gradianes };
enum potencias { n1, n2, n3, n4, n5, n6, n7, n8, n9, n10 };
enum parametros { redondeo1, redondeo2, redondeo3, redondeo4 };

//PROTOTIPOS
void calculadora(userData_t datos);

#endif