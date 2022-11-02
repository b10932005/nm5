#include <complex.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef double complex complex_f64;
typedef struct {
	int row;
	int col;
	complex_f64 *val;
} complex_mat;

complex_mat *cmat_new(int row, int col, complex_f64 val[row * col]) {
	complex_mat *ret = (complex_mat *)malloc(sizeof(complex_mat));
	ret->row = row;
	ret->col = col;
	ret->val = val;
	return ret;
}

complex_mat *cmat_col_replace(complex_mat *mat, complex_mat *vec, int col) {
	if (mat->row != vec->row || vec->col != 1) {
		fprintf(stderr, "matrix size not matched!");
		return NULL;
	}

	complex_f64 *arr =
		(complex_f64 *)malloc(mat->row * mat->col * sizeof(complex_f64));
	for (size_t i = 0; i < mat->row * mat->col; i++) {
		arr[i] = mat->val[i];
	}
	for (size_t i = 0; i < mat->row; i++) {
		arr[i * mat->col + col] = vec->val[i];
	}

	return cmat_new(mat->row, mat->col, arr);
}

complex_mat *cmat_mul(complex_mat *m1, const complex_mat *m2) {
	if (m1->col != m2->row) {
		fprintf(stderr, "matrix size not matched!");
		return NULL;
	}

	complex_mat *ret = (complex_mat *)malloc(sizeof(complex_mat));
	ret->row = m1->row;
	ret->col = m2->col;
	ret->val = (complex_f64 *)calloc(m1->row * m2->col, sizeof(complex_f64));

	// i th row in m1
	for (size_t i = 0; i < m1->row; i++) {
		// j th col in m2
		for (size_t j = 0; j < m2->col; j++)
			// k th element in m1,m2
			for (size_t k = 0; k < m1->row; k++) {
				ret->val[i * ret->col + j] +=
					m1->val[i * m1->col + k] * m2->val[k * m2->col + j];
			}
	}

	return ret;
}

complex_f64 cmat_det(complex_mat *mat) {
	if (mat->row != mat->col) {
		fprintf(stderr, "invalid matrix size!");
		return;
	}

	complex_f64 det = 1;

	// loop for traversing the diagonal elements
	for (size_t i = 0; i < mat->row; i++) {
		size_t index = i;
		// find the index with non zero value
		for (; index < mat->row && mat->val[index * mat->col + i] == 0; index++) {
		}
		if (index == mat->row)
			return 0;
		if (index != i) {
			// swap the row
			for (size_t j = 0; j < mat->row; j++) {
				complex_f64 temp = mat->val[index * mat->col + j];
				mat->val[index * mat->col + j] = mat->val[i * mat->col + j];
				mat->val[i * mat->col + j] = temp;
			}
			if ((index - i) | 1)
				det = -det;
		}

		/*
		things to add
		 */
	}

	return det;
}

void cmat_printf(const char *format, int count, ...) {
	va_list list;
	va_start(list, count);

	for (size_t i = 0; i < count; i++) {
		complex_mat cur = va_arg(list, complex_mat);
		for (size_t j = 0; j < cur.row; j++) {
			char c = '\0';
			printf("|");
			for (size_t k = 0; k < cur.col; k++) {
				printf("%c", c);
				printf(format, creal(cur.val[j * cur.col + k]),
					   cimag(cur.val[j * cur.col + k]));
				c = '\t';
			}
			printf("|\n");
		}
		puts("");
	}
}