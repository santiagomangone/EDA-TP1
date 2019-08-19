#include <stdio.h>
#include <cmath>
#include "parseLib.h"
#include "parseCallback.h"
#include "calculadora.h"

int main(int argc, char* argv[]) {

	pCallback_t pToCallback = parseCallback;
	userData_t datos;
	
	int arguments = parseCmdLine(argc, argv, pToCallback, &datos);

	if (arguments == -1)
	{
		printf("Error\n");
		return 0;
	}
	
	calculadora(datos);
	return 0;
}