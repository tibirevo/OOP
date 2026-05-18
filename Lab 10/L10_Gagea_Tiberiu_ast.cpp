#include "L10_Gagea_Tiberiu_ast.hpp"
#include <stdexcept>
#include <cctype>
#include <sstream>

namespace ast {
    ValueNode::ValueNode(double val) : value(val) {}

    double ValueNode::evaluate() const {
        return value;
    }

    std::string ValueNode::print() const {

        std::ostringstream oss;
        oss << value;
        return oss.str();
    }


    OperatorNode::OperatorNode(Operator o, UniquePtr<Node> l, UniquePtr<Node> r)
        : op(o), left(std::move(l)), right(std::move(r)) {}

    double OperatorNode::evaluate() const {
        double l_val = left->evaluate();
        double r_val = right->evaluate();

        switch (op) {
            case Operator::ADD: return l_val + r_val;
            case Operator::SUBTRACT: return l_val - r_val;
            case Operator::MULTIPLY: return l_val * r_val;
            case Operator::DIVIDE:
                if (r_val == 0.0) {
                    throw std::runtime_error("Division by zero");
                }
                return l_val / r_val;
            default:
                throw std::runtime_error("Unknown operator");
        }
    }

    std::string OperatorNode::print() const {
        std::string op_str;
        switch (op) {
            case Operator::ADD: op_str = "+"; break;
            case Operator::SUBTRACT: op_str = "-"; break;
            case Operator::MULTIPLY: op_str = "*"; break;
            case Operator::DIVIDE: op_str = "/"; break;
        }
        return "(" + left->print() + op_str + right->print() + ")";
    }


    static UniquePtr<Node> parse_helper(const std::string& expr) {
        std::string s;

        for (char c : expr) {
            if (c != ' ') s += c;
        }

        if (s.empty()) throw std::invalid_argument("Empty expression");


        while (s.length() >= 2 && s.front() == '(' && s.back() == ')') {
            int p = 0;
            bool valid_strip = true;
            for (size_t i = 0; i < s.length() - 1; ++i) {
                if (s[i] == '(') p++;
                else if (s[i] == ')') p--;


                if (p == 0) {
                    valid_strip = false;
                    break;
                }
            }
            if (valid_strip) {
                s = s.substr(1, s.length() - 2);
            } else {
                break;
            }
        }


        bool is_number = true;
        size_t start_idx = 0;


        if (s.length() > 0 && (s[0] == '-' || s[0] == '+')) {
            start_idx = 1;
        }
        if (start_idx == 1 && s.length() == 1) is_number = false;

        for (size_t i = start_idx; i < s.length(); ++i) {
            if (!std::isdigit(s[i]) && s[i] != '.') {
                is_number = false;
                break;
            }
        }

        if (is_number) {
            try {
                return UniquePtr<Node>(new ValueNode(std::stod(s)));
            } catch (...) {
                throw std::invalid_argument("Invalid number format");
            }
        }


        int parens = 0;
        size_t main_op_idx = std::string::npos;
        int min_precedence = 100;


        for (size_t i = s.length() - 1; i < s.length(); --i) {
            if (s[i] == ')') parens++;
            else if (s[i] == '(') parens--;
            else if (parens == 0) {
                if (s[i] == '+' || s[i] == '-') {

                    if (i > 0 && s[i-1] != '(' && s[i-1] != '+' && s[i-1] != '-' && s[i-1] != '*' && s[i-1] != '/') {
                        if (1 < min_precedence) {
                            min_precedence = 1;
                            main_op_idx = i;
                        }
                    }
                } else if (s[i] == '*' || s[i] == '/') {
                    if (2 < min_precedence) {
                        min_precedence = 2;
                        main_op_idx = i;
                    }
                }
            }
        }

        if (main_op_idx != std::string::npos) {
            std::string left_str = s.substr(0, main_op_idx);
            std::string right_str = s.substr(main_op_idx + 1);

            Operator o;
            if (s[main_op_idx] == '+') o = Operator::ADD;
            else if (s[main_op_idx] == '-') o = Operator::SUBTRACT;
            else if (s[main_op_idx] == '*') o = Operator::MULTIPLY;
            else o = Operator::DIVIDE;

            return UniquePtr<Node>(new OperatorNode(o, parse_helper(left_str), parse_helper(right_str)));
        }

        throw std::invalid_argument("Invalid expression format");
    }

    OperatorNode parse_expression(std::string expression) {
        UniquePtr<Node> root = parse_helper(expression);
        OperatorNode* op_node = dynamic_cast<OperatorNode*>(root.get());

        if (!op_node) {
            throw std::invalid_argument("Root expression must be an operation");
        }

        OperatorNode result = std::move(*op_node);
        return result;
    }

    double evaluate_expression(std::string expression) {
        OperatorNode root = parse_expression(expression);
        return root.evaluate();
    }
}