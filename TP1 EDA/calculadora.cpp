#include <stdio.h>
#include <math.h>
#include "calculadora.h"

#define PI 3.141592654

static double fsuma(double a, double b);
static double fresta(double a, double b);
static double fproducto(double a, double b);
static double fcociente(double a, double b);
static double factorial( double n);
static double redondear(double number, int figures);
//static double potencia(double base, double exponente);

void calculadora(userData_t datos) {
	printf("Operacion %d, Op1 %f, Op2 %f, Base %f, Exp %d, Angulo %d, Nota %s\n", datos.operacion, datos.operando1, datos.operando2, datos.base, datos.exponente, datos.angulo, datos.nota);
	double angle = datos.operando1;
	double ans;
	int figures = 0;

	typedef double (*binaria) (double,double);
	typedef double (*unaria) (double);
	void* funciones[] = { fsuma,fresta,fproducto,fcociente,factorial,sin,cos,tan,sqrt,log,log10,fabs,pow };


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
		printf("Operacion sin angulos\n");

	printf("Operando1: %f ... Operando2: %f\n", datos.operando1, datos.operando2);


	//NOTAS DEL USUARIO
	if (datos.nota[0] != '\0')
		printf("%s\n", datos.nota);

	//CUENTAS
	if (datos.operacion <= cociente)
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

	//AL USUARIO
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
			printf("El denominador es cero, la división no está definida.\n");
		printf("%f / %f = %f\n", datos.operando1, datos.operando2, ans);
		break;
	case fact:
		if (datos.operando1 < 0 || (datos.operando1) != (int)datos.operando1)
			printf("Error. El factorial está definido sobre los naturales y el cero.");
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
			printf("La raíz cuadrada no está definida para números negativos.\n");
		else
			printf("sqrt(%f) = %f\n", datos.operando1, ans);
		break;
	case ln:
		if (datos.operando1 < 0)
			printf("El logaritmo natural no está definido para números negativos.\n");
		else
			printf("ln(%f) = %f\n", datos.operando1, ans);
		break;
	case logd:
		if (datos.operando1 < 0)
			printf("El logaritmo decimal no está definido para números negativos.\n");
		else
			printf("log(%.2f) = %.2f\n", datos.operando1, ans);
		break;
	case modulo:
		printf("|%f| = %f\n", datos.operando1, ans);
		break;
	case expo:
		if (datos.base < 0)
			printf("La potencia está definida para base positiva o cero.\n");
		else
			printf("%f^%d = %f", datos.base, datos.exponente, ans);
		break;
	}
}

//factorial
static double factorial(double n) 
{
	if ( (int)n != n)
	{
		printf("El factorial se define para enteros no negativos\n");
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
		printf("Denominador 0");
	}
	return a / b;
}
/*
static double potencia(double base, double exponente) {
	return exp(exponente * log(base));
}
*/

static double redondear(double number, int figures) {
	double a, b, c, result;
	bool up;
	a = number * pow(10, (double)(figures));
	b = a - (int)a;
	c = (int)(10 * b);
	((c >= 5) || (c <= -5)) ? (up = 1) : (up = 0);
	printf("a:%f b:%f c:%f\n", a, b, c);
	if (up == 1 && number >= 0)
		result = (int)(number * pow(10, (double)(figures)) + 1) / pow(10, figures);
	else if (up == 1 && number < 0)
		result = (int)(number * pow(10, (double)(figures)) - 1) / pow(10, figures);
	else
		result = (int)(number * pow(10, (double)figures)) / pow(10, figures);
	return result;
}