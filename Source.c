#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>
#define  max_line_length 1000

int count = 0;

void LeerMatrizA() {
	{
		char const* const filename = "matrixA2500.txt";
		FILE* fh;

		fopen_s(&fh, filename, "r");

		if (!fh) {
			printf("\n unable to open : %s ", filename);
			return -1;
		}

		char line[500];

		while (fgets(line, sizeof(line), fh)) {
			count++;
			//float valor_convertido = atof(line);
			//printf("float value : %.11f\n", valor_convertido);
		}
		fclose(fh);
		//printf("total num: %i", count);
		
	}
}


int main(int argc, char* argv[]) {

	FILE* fh;
	char const* const filename = "matrixA2500.txt";
	char line[500];
	//Estos valores los debe de ingresar el usuario y hay que hacer validacion
	int filasA = 50;  
	int columnasA = 50;
	int filasB = 50;
	int columnasB = 50;

	int total_esperado = filasA * columnasB;

	float* B, * C, * A;

	//Checar que se puedan multiplicar las matrices
	if (columnasA != filasB) {
		printf("\n matrices no se pueden multiplicar, intente denuevo");
	}

	//Leer la matriz A para contar cuantos valores tiene
	LeerMatrizA();
	printf("total num: %i", count);

	//Checar que los tamanos coincidan
	if (total_esperado != count) {
		printf("\n total de valores en el archivo no coincide con tamaño de la matriz");
	}
	
	A = (float*)malloc(sizeof(float) * count);

	//*************************************************************************************************

	fopen_s(&fh, filename, "r");

	if (!fh) {
		printf("\n unable to open : %s ", filename);
		return -1;
	}

	int i = 0;
	float valor_convertido2 = 0.0;
	while (fgets(line, sizeof(line), fh)) {
		valor_convertido2 = atof(line);
		A[i] = valor_convertido2;
		i++;
	}

	for (int j = 0; j < count; j++) {
		printf("\n %.11f ", A[j]);
	}

	fclose(fh);
	return 0;
}



//int valor_convertido2 = 0;
//int i = 0;
//for (int x = 0; x < filasA; x++) {
//	for (int y = 0; y < columnasA; y++) {
//		fgets(line, sizeof(line), fh);
//		valor_convertido2 = atoi(line); //4 bytes
//		//A[i] = valor_convertido2;
//		A[i] = 0;
//		i++;
//	}
//}