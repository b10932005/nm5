#include "mat.h"

int main() {
	complex_f64 a[] = {3 + 2 * I, 4, -I, 1},
				b[] = {2 + I, 3},
				c[] = {0.8, -0.4, 0,
					   -0.4, 0.8, -0.4,
					   0, -0.4, 0.8},
				d[] = {41, 25, 105};

	complex_mat *m1 = cmat_new(2, 2, a),
				*m2 = cmat_new(2, 1, b);

	complex_f64 *x1 = cmat_solve(m1, m2),
				*x2 = cmat_solve(cmat_new(3, 3, c), cmat_new(3, 1, d));

	cmat_printf("%6.2lf%+6.2lfi", 2, m1, m2);
	cf64_printf("%6.2lf%+6.2lfi\n", 2, x1[0], x1[1]);
	puts("");
	cf64_printf("%6.2lf\n", 3, x2[0], x2[1], x2[2]);
};