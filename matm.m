format long

A = [8 5 1; 3 7 4; 2 3 9];
[L, U] = lu(A)
det(L) * det(U) == det(A)

m = [
    16 4 1;
    4 2 1;
    49 7 1;
    ];
cond(m, 2)
cond(m, "fro")
