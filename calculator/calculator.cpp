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