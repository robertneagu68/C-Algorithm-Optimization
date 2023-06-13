#include "utils.h"
#include <cblas.h>

double* my_solver(int N, double *A, double *B) {
	double *leftProduct = (double *) malloc(N * N * sizeof(double));
	double *partialLeftProduct = (double *) malloc(N * N * sizeof(double));
	double *rightProduct = (double *) malloc(N * N * sizeof(double));

	// Copiaza matricea B in partialLeftProduct
	cblas_dcopy(N * N, B, 1, partialLeftProduct, 1);

	// Inmulteste matricea partialLeftProduct (in care este B) cu matricea A, tinand cont ca A este superior triunghiulara
	// iar rezultatul este scris in partialLeftProduct
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1.0, A, N, partialLeftProduct, N);

	// Inmulteste matricea partialLeftProduct (in care este B * A) cu transpusa matricei A, tinand cont ca A este superior
	// triunghiulara iar rezultatul este scris in partialLeftProduct
    cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1.0, A, N, partialLeftProduct, N);

	// Copiaza matricea partialLeftProduct in matricea leftProduct
	cblas_dcopy(N * N, partialLeftProduct, 1, leftProduct, 1);

	// Inmulteste matricea B transpus cu matricea B iar rezultatul este scris in rightProduct
    cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N, N, 1.0, B, N, B, N, 0.0, rightProduct, N);
	
	// Aduna matricele leftProduct (B * A * A transpus) si rightProduct(B transpus * B)
	cblas_daxpy(N * N, 1, leftProduct, 1, rightProduct, 1);

	// Eliberam memoria pentru variabilele care nu se vor returna
	free(leftProduct);
	free(partialLeftProduct);

	return rightProduct;
}

