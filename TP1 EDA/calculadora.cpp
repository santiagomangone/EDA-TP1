/***************************************************************************//**
 @file     +calculadora.cpp+
 @brief    +Realiza las operaciones a partir de la estructura de datos+
 @author   +Grupo 3. Alejo Figueroa, Pablo Gonzalez, Santiago Mangone+
******************************************************************************/

/*******************************************************************************
* INCLUDE HEADER FILES
******************************************************************************/
#include <stdio.h>
#include <math.h>
#include "calculadora.h"

/*******************************************************************************
* CONSTANT AND MACRO DEFINITIONS USING #DEFINE
******************************************************************************/
#define PI 3.141592654

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef double (*binaria) (double, double);
typedef double (*unaria) (double);

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static double fsuma(double a, double b);
static double fresta(double a, double b);
static double fproducto(double a, double b);
static double fcociente(double a, double b);
static double factorial( double n);
static double redondear(double number, int figures);
static void manual(void);

/*******************************************************************************
 *******************************************************************************
						GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void calculadora(userData_t datos) {
	/* TESTING */
	//printf("Operacion %d, Op1 %f, Op2 %f, Base %f, Exp %d, Angulo %d, Nota %s\n", datos.operacion, datos.operando1, datos.operando2, datos.base, datos.exponente, datos.angulo, datos.nota);
	/************/

	double angle = datos.operando1;
	double ans;
	int figures = 0;

	void* funciones[] = { fsuma,fresta,fproducto,fcociente,factorial,sin,cos,tan,sqrt,log,log10,fabs,pow };

	//AYUDA
	if (datos.ayuda == true)
		manual();

	//ANGULOS
	if (datos.operacion >= seno && datos.operacion <= tg) {
		if (datos.angulo == 0) {
			datos.operando1 *= PI / 180;
			printf("D\n");
		}
		else if (datos.angulo == 1)
			printf("R\n");
		else if (datos.angulo == 2) {
			datos.operando1 *= PI / 200;
			printf("G\n");
		}
	}
	else if (datos.angulo != -1)
		printf("Nota: Operacion sin angulos\n");

	//NOTAS DEL USUARIO
	if (datos.nota[0] != '\0')
		printf("%s\n", datos.nota);

	//CUENTAS
	if (datos.operacion <= cociente && datos.operacion>=suma)
	{
		ans = ((binaria)funciones[datos.operacion])(datos.operando1, datos.operando2);
	}
	else if (datos.operacion >= fact && datos.operacion < expo)
	{
		ans = ((unaria)funciones[datos.operacion])(datos.operando1);
	}
	else if (datos.operacion == expo)
	{
		ans = ((binaria)funciones[datos.operacion])(datos.base, (double)datos.exponente);
	}
	
	//REDONDEO
	if (datos.redondeo1 == true)
		figures = 1;
	else if (datos.redondeo2 == true)
		figures = 2;
	else if (datos.redondeo3 == true)
		figures = 3;
	else if (datos.redondeo4 == true)
		figures = 4;
	if (figures != 0) {
		datos.operando1 = redondear(datos.operando1, figures);
		datos.operando2 = redondear(datos.operando2, figures);
		ans = redondear(ans, figures);
	}

	//INTERFACE
	switch (datos.operacion)
	{
	case suma:
		printf("%f + %f = %f\n", datos.operando1, datos.operando2, ans);
		break;
	case resta:
		printf("%f - %f = %f\n", datos.operando1, datos.operando2, ans);
		break;
	case producto:
		printf("%f * %f = %f\n", datos.operando1, datos.operando2, ans);
		break;
	case cociente:
		if (datos.operando2 == 0)
			printf("El denominador es cero, la division no esta definida.\n");
		else
			printf("%f / %f = %f\n", datos.operando1, datos.operando2, ans);
		break;
	case fact:
		if (datos.operando1 < 0 || (datos.operando1) != (int)datos.operando1)
			printf("Error. El factorial esta definido sobre los naturales y el cero.");
		else
			printf("%.0f! = %f\n", datos.operando1, ans);
		break;
	case seno:
		printf("sen(%f) = %f\n", angle, ans);
		break;
	case coseno:
		printf("cos(%f) = %f\n", angle, ans);
		break;
	case tg:
		printf("tan(%f) = %f\n", angle, ans);
		break;
	case raiz:
		if (datos.operando1 < 0)
			printf("La raiz cuadrada no esta definida para numeros negativos.\n");
		else
			printf("sqrt(%f) = %f\n", datos.operando1, ans);
		break;
	case ln:
		if (datos.operando1 <= 0)
			printf("El logaritmo natural no esta definido para numeros no positivos.\n");
		else
			printf("ln(%f) = %f\n", datos.operando1, ans);
		break;
	case logd:
		if (datos.operando1 <= 0)
			printf("El logaritmo decimal no esta definido para numeros no positivos.\n");
		else
			printf("log(%.2f) = %.2f\n", datos.operando1, ans);
		break;
	case modulo:
		printf("|%f| = %f\n", datos.operando1, ans);
		break;
	case expo:
		if (datos.base < 0)
			printf("Defina una base válida. La potencia esta definida para base positiva o cero.\n");
		else if (datos.exponente == -1)
			printf("Defina un exponente valido: entero 0-10.");
		else
			printf("%f^%d = %f", datos.base, datos.exponente, ans);
		break;
	}
}

static void manual(void)
{
	printf(
		"___________________________________________________________________________________________________________________\n"
		"\nTrabajo Practico Nro 1 - EDA\n"
		"Grupo 3\n"
		"  Alejo Figueroa\n"
		"  Pablo Gonzalez\n"
		"  Santiago Mangone\n"
		"\nOperaciones binarias\n"
		"  -suma, -resta, -producto, -cociente\n"
		"  Nota 1: las operaciones binarias usan la opcion -y para el segundo valor.\n"
		"  Ejemplo: -suma 18.67 -y -12\n"
		"\nPotenciacion\n"
		"  Se usa -base para la base y -exp para el exponente (entero 0-10). Deben colocarse de forma contigua.\n"
		"  Ejemplo: -base 12.5 -exp 4\n"
		"\nOperaciones unarias\n"
		"  -fact, -sen, -cos, -tan, -raiz, -ln, -log, -modulo\n"
		"  Nota 2: salvo aclaracion, los valores son double. Luego se validan los dominios de las funciones.\n"
		"\nOtras opciones\n"
		"  -angulo. Permite elegir entre grados, radianes y gradianes para operaciones con angulos.\n"
		"\nParametros\n"
		"  nota. Permite agregar una nota del usuario a la cuenta final.\n"
		"  ayuda. Despliega este manual.\n"
		"___________________________________________________________________________________________________________________\n"
	);
	return;
}

/*******************************************************************************
 *******************************************************************************
						LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static double factorial(double n) 
{
	if ( (int)n != n)
	{
		return -1;
	}
	if (n < 1)
		return 1;
	else
		return n * factorial(n - 1);
}

static double fsuma(double a, double b)
{
	return a + b;
}

static double fresta(double a, double b)
{
	return a - b;
}

static double fproducto(double a, double b)
{
	return a * b;
}

static double fcociente(double a, double b)
{
	if (b == 0)
	{
		printf("Denominador 0\n");
	}
	return a / b;
}

static double redondear(double number, int figures) {
	double a, b, c, result;
	bool up;
	a = number * pow(10, (double)(figures));	
	b = a - (int)a;
	c = (int)(10 * b);	//guarda como int el decimal siguiente al que se quiere redondear

	((c >= 5) || (c <= -5)) ? (up = 1) : (up = 0);	//evalua si debe redondear hacia arriba o hacia abajo

	if (up == 1 && number >= 0)
		result = (int)(number * pow(10, (double)(figures)) + 1) / pow(10, figures);		//redondea hacia arriba un positivo
	else if (up == 1 && number < 0)
		result = (int)(number * pow(10, (double)(figures)) - 1) / pow(10, figures);		//redondea hacia arriba un negativo
	else
		result = (int)(number * pow(10, (double)figures)) / pow(10, figures);			//redondea hacia abajo

	return result;
}