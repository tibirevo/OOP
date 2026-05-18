#pragma once
#include <string>
#include "L10_Gagea_Tiberiu_ptr_ast.hpp"

namespace ast {
    class Node {
    public:
        virtual ~Node() = default;
        virtual double evaluate() const = 0;
        virtual std::string print() const = 0;
    };

    class ValueNode : public Node {
    private:
        double value;
    public:
        explicit ValueNode(double val);
        double evaluate() const override;
        std::string print() const override;
    };

    enum class Operator {
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE
    };

    class OperatorNode : public Node {
    private:
        Operator op;
        UniquePtr<Node> left;
        UniquePtr<Node> right;
    public:
        OperatorNode(Operator o, UniquePtr<Node> l, UniquePtr<Node> r);
        OperatorNode(OperatorNode&&) noexcept = default;
        OperatorNode& operator=(OperatorNode&&) noexcept = default;

        double evaluate() const override;
        std::string print() const override;
    };

    OperatorNode parse_expression(std::string expression);
    double evaluate_expression(std::string expression);
}