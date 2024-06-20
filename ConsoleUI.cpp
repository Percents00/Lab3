#include "ConsoleUI.h"
#include <iostream>
#include <limits>

using namespace std;

template<typename T>
void ConsoleUI<T>::run() {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Matrix addition\n";
        cout << "2. Multiply matrix by a scalar\n";
        cout << "3. Calculate matrix norm\n";
        cout << "4. Vector addition\n";
        cout << "5. Multiply vector by a scalar\n";
        cout << "6. Calculate vector norm\n";
        cout << "7. Calculate scalar product\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        choice = getChoice(0, 7); 

        switch (choice) {
            case 1: {
                SquareMatrix<T> m1 = inputMatrix();
                SquareMatrix<T> m2 = inputMatrix();
                displayMatrix(m1 + m2);
                break;
            }
            case 2: {
                SquareMatrix<T> m = inputMatrix();
                T scalar = getValue("Enter scalar value: ");
                displayMatrix(m * scalar);
                break;
            }
            case 3: {
                SquareMatrix<T> m = inputMatrix();
                cout << "Matrix norm: " << m.Norm() << endl;
                break;
            }
            case 4: {
                Vector<T> v1 = inputVector();
                Vector<T> v2 = inputVector();
                displayVector(v1 + v2);
                break;
            }
            case 5: {
                Vector<T> v = inputVector();
                T scalar = getValue("Enter scalar value: ");
                displayVector(v * scalar);
                break;
            }
            case 6: {
                Vector<T> v = inputVector();
                cout << "Vector norm: " << v.Norm() << endl;
                break;
            }
            case 7: {
                Vector<T> v1 = inputVector();
                Vector<T> v2 = inputVector();
                cout << "Scalar product: " << (v1 * v2) << endl;
                break;
            }
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}


template <typename T>
SquareMatrix<T> ConsoleUI<T>::inputMatrix(const std::string& prompt) const {
    int size = getPositiveInt("Enter matrix size: ");
    SquareMatrix<T> matrix(size);
    cout << prompt << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix(i, j) = getValue("Enter element [" + to_string(i) + "][" + to_string(j) + "]: ");
        }
    }
    return matrix;
}

template <typename T>
Vector<T> ConsoleUI<T>::inputVector(const std::string& prompt) const {
    int size = getPositiveInt("Enter vector size: ");
    Vector<T> vector(size);
    cout << prompt << endl;
    for (int i = 0; i < size; ++i) {
        vector[i] = getValue("Enter element [" + to_string(i) + "]: ");
    }
    return vector;
}

template <typename T>
void ConsoleUI<T>::displayMatrix(const SquareMatrix<T>& matrix, 
                                 const std::string& message) const {
    cout << message << endl << matrix << endl;
}

template <typename T>
void ConsoleUI<T>::displayVector(const Vector<T>& vector, 
                                const std::string& message) const {
    cout << message << " (";
    for (int i = 0; i < vector.GetDimension(); ++i) {
        cout << vector[i];
        if (i < vector.GetDimension() - 1) {
            cout << ", ";
        }
    }
    cout << ")" << endl;
}

template <typename T>
int ConsoleUI<T>::getChoice(int minChoice, int maxChoice) const {
    int choice;
    while (!(cin >> choice) || choice < minChoice || choice > maxChoice) {
        cout << "Invalid choice. Please enter a number between "
             << minChoice << " and " << maxChoice << ": ";
        clearCin();
    }
    return choice;
}

template <typename T>
int ConsoleUI<T>::getPositiveInt(const std::string& message) const {
    int value;
    cout << message;
    while (!(cin >> value) || value <= 0) {
        cout << "Invalid input. Please enter a positive integer: ";
        clearCin();
    }
    return value;
}

template <typename T>
T ConsoleUI<T>::getValue(const std::string& message) const {
    T value;
    cout << message;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number: ";
        clearCin();
    }
    return value;
}

template <typename T>
void ConsoleUI<T>::clearCin() const {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}