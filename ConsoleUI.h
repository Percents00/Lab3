#pragma once

#include <iostream>
#include "SquareMatrix.h"
#include "Vector.h"

template <typename T>
class ConsoleUI {
public:
    void run();

private:
    SquareMatrix<T> inputMatrix(const std::string& prompt = "Enter matrix: ") const;
    
    Vector<T> inputVector(const std::string& prompt = "Enter vector: ") const;
    
    void displayMatrix(const SquareMatrix<T>& matrix, 
                       const std::string& message = "Matrix:") const;

    void displayVector(const Vector<T>& vector, 
                        const std::string& message = "Vector:") const;

    int getChoice(int minChoice, int maxChoice) const;

    int getPositiveInt(const std::string& message) const;

    T getValue(const std::string& message) const;

    void clearCin() const;

};

template class ConsoleUI<int>;
template class ConsoleUI<double>;