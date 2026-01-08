#include <iostream>
#include "Sparse1DArreay.h"
#include "Sparse2DArray.h"

int main() {
    SparseMatrix mat(10, 10);
    mat.set_value(5, 3, 5);
    mat.set_value(7, 3, 7);
    mat.set_value(2, 3, 2);
    mat.set_value(0, 3, 2);
    mat.set_value(6, 5, 6);
    mat.set_value(4, 5, 4);
    mat.set_value(3, 7, 3);
    mat.set_value(1, 7, 1);
    mat.print_matrix();
    std::cout << "\n";
    mat.print_matrix_nonzero();

    SparseMatrix mat2(10, 10);
    mat2.set_value(5, 1, 9);
    mat2.set_value(6, 3, 8);
    mat2.set_value(9, 9, 9);

    mat.add(mat2);

    std::cout << "\n";
    mat.print_matrix_nonzero();
    return 0;
}
