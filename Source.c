#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>
#define  max_line_length 1000


void ContarMatrizA(int *count) {
	{
		char const* const filename = "matrizA.txt";
		FILE* fh;

		fopen_s(&fh, filename, "r");

		if (!fh) {
			printf("\n unable to open : %s ", filename);
			return -1;
		}

		char line[500];

		while (fgets(line, sizeof(line), fh)) {
			(*count)++;
			//float valor_convertido = atof(line);
			//printf("float value : %.11f\n", valor_convertido);
		}
		fclose(fh);
		//printf("total num: %i", count);

	}
}

void ContarMatrizB(int* count2) {
	{
		char const* const filename2 = "matrizB.txt";
		FILE* fh2;

		fopen_s(&fh2, filename2, "r");

		if (!fh2) {
			printf("\n unable to open : %s ", filename2);
			return -1;
		}

		char line[500];

		while (fgets(line, sizeof(line), fh2)) {
			(*count2)++;
			//float valor_convertido = atof(line);
			//printf("float value : %.11f\n", valor_convertido);
		}
		fclose(fh2);
		//printf("total num: %i", count);

	}
}
int main(int argc, char* argv[]) {

	FILE* fh;
	FILE* fh2;
	FILE* fh3;

	char const* const filename = "matrizA.txt";
	char const* const filename2 = "matrizB.txt";
	char const* const filename3 = "matrizC.txt";

	char line[500];
	//Estos valores los debe de ingresar el usuario y hay que hacer validacion
	//int filasA = 50;
	//int columnasA = 50;
	//int filasB = 50;
	//int columnasB = 50;
	int filasA, columnasA, filasB, columnasB;
	
	//Pedir valores a usuario
	printf("Ingrese filas A: ");
	scanf_s("%d", &filasA);
	printf("Ingrese columnas A: ");
	scanf_s("%d", &columnasA);
	printf("Ingrese filas B: ");
	scanf_s("%d", &filasB);
	printf("Ingrese columnas B: ");
	scanf_s("%d", &columnasB);

	int count = 0;
	int count2 = 0;

	int tam_matA = filasA * columnasA;
	int tam_matB = filasB * columnasB;
	int tam_matC = filasA * columnasB;

	float* arrayB, * traspB, * arrayC, * arrayA;


	//Checar que se puedan multiplicar las matrices
	if (columnasA != filasB) {
		printf("\n matrices no se pueden multiplicar, intente denuevo");
		exit(1);
	}

	//Leer la matriz A para contar cuantos valores tiene
	ContarMatrizA(&count);
	printf("\ntotal num matriz A: %i", count);

	//Leer la matriz B para contar cuantos valores tiene
	ContarMatrizB(&count2);
	printf("\ntotal num matriz B: %i", count2);

	//Checar que los tamanos coincidan de matriz A
	if (tam_matA != count) {
		printf("\n total de valores en el archivo no coincide con tamaño de la matriz A");
		exit(1);
	}

	//Checar que los tamanos coincidan de matriz B
	if (tam_matB != count2) {
		printf("\n total de valores en el archivo no coincide con tamaño de la matriz B");
		exit(1);
	}

	//Asignar memoria dinamica a arrays
	arrayA = (float*)malloc(sizeof(float) * count);
	arrayB = (float*)malloc(sizeof(float) * count2);
	traspB = (float*)malloc(sizeof(float) * count2);
	arrayC = (float*)malloc(sizeof(float) * tam_matC);

	//*************************************************************************************************
	//********************* Guardar valores de .txt en array matA *************************************
	fopen_s(&fh, filename, "r");

	if (!fh) {
		printf("\n unable to open : %s ", filename);
		return -1;
	}

	int i = 0;
	float valor_convertido2 = 0.0;
	while (fgets(line, sizeof(line), fh)) {
		valor_convertido2 = atof(line);
		arrayA[i] = valor_convertido2;
		i++;
	}

	fclose(fh);
	//*************************************************************************************************

	//********************* Guardar valores de .txt en array matB *************************************
	fopen_s(&fh2, filename2, "r");

	if (!fh2) {
		printf("\n unable to open : %s ", filename2);
		return -1;
	}

	i = 0;
	valor_convertido2 = 0.0;
	while (fgets(line, sizeof(line), fh2)) {
		valor_convertido2 = atof(line);
		arrayB[i] = valor_convertido2;
		i++;
	}

	fclose(fh2);
	//*************************************************************************************************

	//Trasponer el arreglo B (matriz B)
	//Para trasponer solo hay que reacomodar los valores
	i = 0;
	for (int x = 0; x < columnasB; x++) {
		for (int y = 0; y < filasB; y++) {
			traspB[i] = arrayB[x + (columnasB * y)];
			i++;
		}
	}

	//imprimir valores de arrayB traspuesta para comprobar que se guardaron bien.
	//for (int j = 0; j < count; j++) {
	//	printf("\n %.11f ", traspB[j]);
	//}

	//Multiplicacion MatA x MatB filas x filas
	i = 0;
	for (int x = 0; x < filasA; x++) {
		for (int y = 0; y < columnasB; y++) {
			arrayC[i] = 0;
			for (int z = 0; z < filasB; z++) {
				arrayC[i] += arrayA[z + (x*filasB)] * traspB[z + (y*filasB)]; 
			}
			i++;
		}
	}

	//imprimir valores de arrayC
	for (int j = 0; j < tam_matC; j++) {
		printf("\n %.11f ", arrayC[j]);
	}	

	//**************************** imprimir en archivo matrixC *************************************** 
	fopen_s(&fh3, filename3, "w");

	if (!fh3) {
		printf("\n unable to open : %s ", filename3);
		return -1;
	}

	for (int i = 0; i < tam_matC; i++) {
		fprintf(fh3, "\n%11f", arrayC[i]);
	}
	//fwrite(arrayC, sizeof(float), sizeof(arrayC), fh3);

	fclose(fh3);
	//*************************************************************************************************

	

	//liberar espacio de memoria del malloc()
	free(arrayA);
	free(arrayB);
	free(arrayC);
	free(traspB);
	return 0;
}
