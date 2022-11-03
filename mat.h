#include <complex.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef double complex complex_f64;
typedef struct {
	int row;
	int col;
	complex_f64 *val;
} complex_mat;

complex_mat *cmat_new(int row, int col, complex_f64 *val) {
	complex_mat *ret = (complex_mat *)malloc(sizeof(complex_mat));
	ret->row = row;
	ret->col = col;
	ret->val = val;
	return ret;
}

complex_mat *cmat_col_replace(const complex_mat *mat, const complex_mat *vec, int col) {
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

complex_mat *cmat_mul(const complex_mat *m1, const complex_mat *m2) {
	if (m1->col != m2->row) {
		fprintf(stderr, "matrix size not matched!");
		return NULL;
	}

	complex_mat *ret = cmat_new(m1->row, m2->col, NULL);
	ret->val = (complex_f64 *)calloc(m1->row * m2->col, sizeof(complex_f64));

	// i th row in m1
	for (size_t i = 0; i < m1->row; i++) {
		// j th col in m2
		for (size_t j = 0; j < m2->col; j++) {
			// k th element in m1,m2
			for (size_t k = 0; k < m1->row; k++) {
				ret->val[i * ret->col + j] +=
					m1->val[i * m1->col + k] * m2->val[k * m2->col + j];
			}
		}
	}

	return ret;
}

complex_f64 cmat_det(const complex_mat *mat) {
	if (mat->row != mat->col) {
		fprintf(stderr, "invalid matrix size!");
		return 0;
	}

	complex_f64 det = 1, mul = 1;
	// copy input
	complex_mat *temp = cmat_new(mat->row, mat->col, NULL);
	temp->val = (complex_f64 *)malloc(temp->row * temp->col * sizeof(complex_f64));
	for (size_t i = 0; i < temp->row * temp->col; i++) {
		temp->val[i] = mat->val[i];
	}

	// loop for traversing the diagonal elements
	for (size_t i = 0; i < temp->row; i++) {
		size_t index = i;
		// find the index with non zero value
		for (; index < temp->row && temp->val[index * temp->col + i] == 0; index++) {
		}
		if (index == temp->row)
			return 0;
		if (index != i) {
			// swap the row
			for (size_t j = 0; j < temp->row; j++) {
				complex_f64 swap = temp->val[index * temp->col + j];
				temp->val[index * temp->col + j] = temp->val[i * temp->col + j];
				temp->val[i * temp->col + j] = swap;
			}
			if ((index - i) | 1)
				det = -det;
		}

		for (size_t j = i + 1; j < temp->row; j++) {
			// mat[j,:] = mat[j,:]*mat[i,i] - mat[i,:]*mat[j,i]
			complex_f64 factor[2] = {temp->val[i * temp->col + i],
									 temp->val[j * temp->col + i]};
			for (size_t k = 0; k < temp->row; k++) {
				temp->val[j * temp->col + k] =
					(temp->val[j * temp->col + k] * factor[0]) -
					(temp->val[i * temp->col + k] * factor[1]);
			}
			mul *= factor[0];
		}
	}
	for (size_t i = 0; i < temp->col; i++) {
		det *= temp->val[i * temp->col + i];
	}

	return det / mul;
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

void cf64_printf(const char *format, int count, ...) {
	va_list list;
	va_start(list, count);

	for (size_t i = 0; i < count; i++) {
		complex_f64 cur = va_arg(list, complex_f64);
		printf(format, creal(cur), cimag(cur));
	}
}