#include <iomanip>

#include "L3_Gagea_Tiberiu_Problem1_complex.h"
#include <iostream>

int main() {
    std::cout << std::fixed << std::setprecision(2); //Fixam afisarea la 2 zecimale pt claritate
    Complex c1(3.0, 4.0);
    Complex c2(1.0, -2.0);
    std::cout << "c1 = " << c1 << "\n";
    std::cout << "c2 = " << c2 << "\n";

    std::cout << "Suma (c1 + c2): " << (c1 + c2) << "\n";
    std::cout << "Diferenta (c1 - c2): " << (c1 - c2) << "\n";
    std::cout << "Inmultirea (c1 * c2): " << (c1 * c2) << "\n";
    std::cout << "Impartirea (c1 / c2): " << (c1 / c2) << "\n\n";

    Complex c3(3.00000000001, 4.0);
    if (c1 == c3) {
        std::cout << "c1 este egal cu c3 (toleranta functioneaza!)\n\n";
    } else {
        std::cout << "c1 NU este egal cu c3\n\n";
    }

    std::cout << "Modulul lui c1: " << c1.absolute() << "\n";
    std::cout << "Conjugatul lui c1: " << c1.conjugate() << "\n";
    return 0;
}