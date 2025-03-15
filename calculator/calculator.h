#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <stdexcept>
#include "../Data/Data.h"

class Calculator {
public:
    // **标量运算（保留原有功能）**
    template <typename T, typename U>
    auto add(T a, U b) -> typename std::common_type<T, U>::type {
        return a + b;
    }

    template <typename T, typename U>
    auto sub(T a, U b) -> typename std::common_type<T, U>::type {
        return a - b;
    }

    template <typename T, typename U>
    auto mul(T a, U b) -> typename std::common_type<T, U>::type {
        return a * b;
    }

    template <typename T, typename U>
    auto div(T a, U b) -> typename std::common_type<T, U>::type {
        if (b == 0) {
            throw std::runtime_error("Error: Division by zero!");
        }
        return a / b;
    }

    // **矩阵运算**
    Data add(const Data &A, const Data &B);
    Data sub(const Data &A, const Data &B);
    Data mul(const Data &A, const Data &B);

    void readUserInput(Data &data);
};

#endif
