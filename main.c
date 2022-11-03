#include "mat.h"

int main() {
	complex_f64 a[] = {3 + 2 * I, 4, -I, 1};
	complex_f64 b[] = {2 + I, 3};

	complex_mat *m1 = cmat_new(2, 2, a);
	complex_mat *m2 = cmat_new(2, 1, b);
	complex_mat *m3 = cmat_mul(m1, m2);
	cmat_printf("%6.2lf%+6.2lfi", 3, m1, m2, m3);
	complex_f64 x[2] = {cmat_det(cmat_col_replace(m1, m2, 0)) / cmat_det(m1),
						cmat_det(cmat_col_replace(m1, m2, 1)) / cmat_det(m1)};
	cf64_printf("%6.2lf%+6.2lfi\n", 2, x[0], x[1]);
};