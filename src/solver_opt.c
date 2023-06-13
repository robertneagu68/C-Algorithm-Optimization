#include "utils.h"

static double *transposeMatrix(int N, double *matrix) {
	double *transpose = (double *) calloc(N * N, sizeof(double));

	register int i;
	register int j;

	if (transpose == NULL || matrix == NULL) {
		printf("Alocarea dinamica pentru transpusa a esuat sau matricea primita ca parametru este NULL.");
		exit(1);
	}

	for(i = 0; i < N; i++) 
		for (j = 0; j < N; j++) {
			transpose[N * j + i] = matrix[N * i + j];
		}
	
	return transpose;
}

static double *transposeTriangular(int N, double *matrix) {
	double *transpose = (double *) calloc(N * N, sizeof(double));

	register int i;
	register int j;

	if (transpose == NULL || matrix == NULL) {
		printf("Alocarea dinamica pentru transpusa a esuat sau matricea primita ca parametru este NULL.");
		exit(1);
	}

	for(i = 0; i < N; i++) 
		for (j = i; j < N; j++) {
			transpose[N * j + i] = matrix[N * i + j];
		}
	
	return transpose;
}

static double *multiplyBA(int N, double *A, double *B) {
	double *result = (double *) calloc(N * N, sizeof(double));

	if(result == NULL) {
		printf("Alocarea dinamica pentru matricea rezultat, la multiplicarea lui B cu A a esuat!");
		exit(1);
	}

	register int i;
	register int j;
	register int k;

	for(i = 0; i < N; i++) {
		double *orig_pa = &B[i * N];
		for(j = 0; j < N; j++) {
			register double *pa = orig_pa;
			register double *pb = &A[j];
			register double suma = 0.0;
			for(k = 0; k < j + 1; k++) {
					suma += *pa * *pb;
					pa++;
					pb += N;
			}
			result[i * N + j] = suma;
		}
	}
	
	return result;
}

static double *multiplyBAAtranspose(int N, double *BA, double *Atr) {
	double *result = (double *) calloc(N * N, sizeof(double));

	if(result == NULL) {
		printf("Alocarea dinamica pentru matricea rezultat, la multiplicarea lui BA cu A transpus a esuat!");
		exit(1);
	}
	
	register int i;
	register int j;
	register int k;
	
	for(i = 0; i < N; i++) {
		double *orig_pa = &BA[i * N];
		for(j = 0; j < N; j++) {
			register double *pa = orig_pa + j;
			register double *pb = &Atr[j * N + j];
			register double suma = 0.0;
			for(k = j; k < N; k++) {
					suma += *pa * *pb;
					pa++;
					pb += N;
			}
			result[i * N + j] = suma;
		}
	}
	
	return result;
}

static double *multiplyBBtranspose(int N, double *B, double *Btr) {
	double *result = (double *) calloc(N * N, sizeof(double));

	if(result == NULL) {
		printf("Alocarea dinamica pentru matricea rezultat, la multiplicarea lui B cu B transpus esuat!");
		exit(1);
	}

	register int i;
	register int j;
	register int k;
	
	for(i = 0; i < N; i++) {
		double *orig_pa = &Btr[i * N];
		for(j = 0; j < N; j++) {
			register double *pa = orig_pa;
			register double *pb = &B[j];
			register double suma = 0.0;
			for(k = 0; k < N; k++) {
				suma += *pa * *pb;
				pa++;
				pb += N;
			}
			result[i * N + j] = suma;
		}
	}
					
	return result;
}

static double *addMatrix(int N, double *A, double *B) {
	double *result = (double *) calloc(N * N, sizeof(double));

	if(result == NULL) {
		printf("Alocarea dinamica pentru matricea rezultat, la adunarea matricelor a esuat!");
		exit(1);
	}

	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			result[i * N + j] = A[i * N + j] + B[i * N + j];

	return result;
}

double* my_solver(int N, double *A, double* B) {
	double *matrixATranspose = transposeTriangular(N, A);
	double *matrixBTranspose = transposeMatrix(N, B);
	double *partialLeftProduct = multiplyBA(N, A, B);
	double *leftProduct = multiplyBAAtranspose(N, partialLeftProduct, matrixATranspose);
	double *rightProduct = multiplyBBtranspose(N, B, matrixBTranspose);
	double *sum = addMatrix(N, leftProduct, rightProduct);

	free(matrixATranspose);
	free(matrixBTranspose);
	free(leftProduct);
	free(partialLeftProduct);
	free(rightProduct);

	return sum;
}

