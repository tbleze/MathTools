#ifndef DATA_H
#define DATA_H

#include <complex>
#include <iostream>
#include <vector>
#include <stdexcept>

class Data {
public:
    enum Type { SHORT, INT, LONG, FLOAT, DOUBLE, COMPLEX, MATRIX, UNKNOWN } type;

    union {
        short int sVal;
        int iVal;
        long long int lVal;
        float fVal;
        double dVal;
    };

    std::complex<double> cVal;
    std::vector<std::vector<double>> matrixVal;  

    // **构造函数**
    Data() : type(UNKNOWN) {}

    // **标量类型设置函数**
    void setValue(short int val) { sVal = val; type = SHORT; }
    void setValue(int val) { iVal = val; type = INT; }
    void setValue(long long int val) { lVal = val; type = LONG; }
    void setValue(float val) { fVal = val; type = FLOAT; }
    void setValue(double val) { dVal = val; type = DOUBLE; }
    void setValue(std::complex<double> val) { cVal = val; type = COMPLEX; }

    // **矩阵设置函数（使用 const 引用减少拷贝）**
    void setValue(const std::vector<std::vector<double>>& val) {
        matrixVal = val;
        type = MATRIX;
    }

    // **获取值**
    template <typename T>
    T getValue() const {
        switch (type) {
            case SHORT: return static_cast<T>(sVal);
            case INT: return static_cast<T>(iVal);
            case LONG: return static_cast<T>(lVal);
            case FLOAT: return static_cast<T>(fVal);
            case DOUBLE: return static_cast<T>(dVal);
            case COMPLEX: return static_cast<T>(std::abs(cVal));
            case MATRIX: throw std::runtime_error("Cannot return matrix as a scalar!");
            default: throw std::runtime_error("Data type not set!");
        }
    }

    // **矩阵运算**
    Data operator+(const Data& other) const {
        if (type != MATRIX || other.type != MATRIX)
            throw std::runtime_error("Addition only supported for matrices!");

        if (matrixVal.size() != other.matrixVal.size() || matrixVal[0].size() != other.matrixVal[0].size())
            throw std::runtime_error("Matrix dimensions must match for addition!");

        Data result;
        result.type = MATRIX;
        result.matrixVal = matrixVal;  // 直接初始化，不调用 `setValue()`

        for (size_t i = 0; i < matrixVal.size(); i++) {
            for (size_t j = 0; j < matrixVal[0].size(); j++) {
                result.matrixVal[i][j] += other.matrixVal[i][j];
            }
        }
        return result;
    }

    Data operator-(const Data& other) const {
        if (type != MATRIX || other.type != MATRIX)
            throw std::runtime_error("Subtraction only supported for matrices!");

        if (matrixVal.size() != other.matrixVal.size() || matrixVal[0].size() != other.matrixVal[0].size())
            throw std::runtime_error("Matrix dimensions must match for subtraction!");

        Data result;
        result.type = MATRIX;
        result.matrixVal = matrixVal;

        for (size_t i = 0; i < matrixVal.size(); i++) {
            for (size_t j = 0; j < matrixVal[0].size(); j++) {
                result.matrixVal[i][j] -= other.matrixVal[i][j];
            }
        }
        return result;
    }

    Data operator*(const Data& other) const {
        if (type != MATRIX || other.type != MATRIX)
            throw std::runtime_error("Multiplication only supported for matrices!");

        size_t rowsA = matrixVal.size(), colsA = matrixVal[0].size();
        size_t rowsB = other.matrixVal.size(), colsB = other.matrixVal[0].size();

        if (colsA != rowsB)
            throw std::runtime_error("Matrix multiplication dimension mismatch!");

        Data result;
        result.type = MATRIX;
        result.matrixVal.resize(rowsA, std::vector<double>(colsB, 0.0));

        for (size_t i = 0; i < rowsA; i++) {
            for (size_t j = 0; j < colsB; j++) {
                for (size_t k = 0; k < colsA; k++) {
                    result.matrixVal[i][j] += matrixVal[i][k] * other.matrixVal[k][j];
                }
            }
        }
        return result;
    }

    // **矩阵赋值运算符**
    Data& operator=(const Data& other) {
        if (this == &other) return *this;  // 避免自赋值

        type = other.type;
        if (type == MATRIX) {
            matrixVal = other.matrixVal;
        } else {
            sVal = other.sVal;  // 复制联合体数据
        }
        return *this;
    }

    // **矩阵打印**
    void printMatrix() const {
        if (type != MATRIX)
            throw std::runtime_error("Data is not a matrix!");

        for (const auto& row : matrixVal) {
            for (double val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif
