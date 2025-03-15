// calculator.cpp

#include "calculator.h"

void Calculator::readUserInput(Data &data) {
    std::string input;
    std::cout << "Enter a number (int, float, double, or complex as 'a+bi'): ";
    std::cin >> input;

    try {
        if (input.find('+') != std::string::npos || input.find('i') != std::string::npos) {
            double real, imag;
            sscanf(input.c_str(), "%lf+%lfi", &real, &imag);
            data.setValue(std::complex<double>(real, imag));
        } else if (input.find('.') != std::string::npos) {
            double val = std::stod(input);
            data.setValue(val);
        } else {
            int val = std::stoi(input);
            data.setValue(val);
        }
    } catch (...) {
        throw std::invalid_argument("Invalid number format!");
    }
}

#include "calculator.h"

// **矩阵加法**
Data Calculator::add(const Data &A, const Data &B) {
    if (A.type != Data::MATRIX || B.type != Data::MATRIX) {
        throw std::invalid_argument("Error: Both operands must be matrices for addition.");
    }

    size_t rows = A.matrixVal.size();
    size_t cols = A.matrixVal[0].size();
    
    if (B.matrixVal.size() != rows || B.matrixVal[0].size() != cols) {
        throw std::invalid_argument("Error: Matrices must have the same dimensions for addition.");
    }

    Data result;
    result.type = Data::MATRIX;
    result.matrixVal.resize(rows, std::vector<double>(cols, 0));

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result.matrixVal[i][j] = A.matrixVal[i][j] + B.matrixVal[i][j];
        }
    }
    return result;
}

// **矩阵减法**
Data Calculator::sub(const Data &A, const Data &B) {
    if (A.type != Data::MATRIX || B.type != Data::MATRIX) {
        throw std::invalid_argument("Error: Both operands must be matrices for subtraction.");
    }

    size_t rows = A.matrixVal.size();
    size_t cols = A.matrixVal[0].size();
    
    if (B.matrixVal.size() != rows || B.matrixVal[0].size() != cols) {
        throw std::invalid_argument("Error: Matrices must have the same dimensions for subtraction.");
    }

    Data result;
    result.type = Data::MATRIX;
    result.matrixVal.resize(rows, std::vector<double>(cols, 0));

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result.matrixVal[i][j] = A.matrixVal[i][j] - B.matrixVal[i][j];
        }
    }
    return result;
}

// **矩阵乘法**
Data Calculator::mul(const Data &A, const Data &B) {
    if (A.type != Data::MATRIX || B.type != Data::MATRIX) {
        throw std::invalid_argument("Error: Both operands must be matrices for multiplication.");
    }

    size_t rowsA = A.matrixVal.size();
    size_t colsA = A.matrixVal[0].size();
    size_t rowsB = B.matrixVal.size();
    size_t colsB = B.matrixVal[0].size();

    if (colsA != rowsB) {
        throw std::invalid_argument("Error: Matrix multiplication requires A.cols == B.rows.");
    }

    Data result;
    result.type = Data::MATRIX;
    result.matrixVal.resize(rowsA, std::vector<double>(colsB, 0));

    for (size_t i = 0; i < rowsA; i++) {
        for (size_t j = 0; j < colsB; j++) {
            for (size_t k = 0; k < colsA; k++) {
                result.matrixVal[i][j] += A.matrixVal[i][k] * B.matrixVal[k][j];
            }
        }
    }
    return result;
}
