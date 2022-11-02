#include "mat.h"

int main() {
	complex_f64 a[] = {3 + 2 * I, 4, -I, 1};
	complex_f64 b[] = {2 + I, 3};

	complex_mat *m1 = cmat_new(2, 2, a);
	complex_mat *m2 = cmat_new(2, 1, b);
	complex_mat *m3 = cmat_mul(m1, m2);
	cmat_printf("%6.2lf%+6.2lfi", 4, m1, m2, m3, cmat_col_replace(m1, m2, 0));
	complex_f64 det1 = cmat_det(m1);
	printf("%6.2lf%+6.2lfi", creal(det1), cimag(det1));
};