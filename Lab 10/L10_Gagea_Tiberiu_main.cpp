#include <iostream>
#include "L10_Gagea_Tiberiu_ast.hpp"

int main() {
    try {
        std::string expr = "(2*(5+3))";
        std::cout << "Se parseaza: " << expr << "\n";

        ast::OperatorNode tree = ast::parse_expression(expr);

        std::cout << "Arbore construit: " << tree.print() << "\n";
        std::cout << "Rezultat calculat: " << tree.evaluate() << "\n\n";

        std::string expr2 = "((10/2)+4)";
        std::cout << "Evaluare directa pentru " << expr2 << ": ";
        std::cout << ast::evaluate_expression(expr2) << "\n\n";

        std::cout << "Test impartire la zero (1/0):\n";
        ast::evaluate_expression("(1/0)");

    }catch (const std::exception& e) {
        std::cout << "Eroare prinsa: " << e.what() << "\n";
    }
    return 0;
}
