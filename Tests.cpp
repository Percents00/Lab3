#include <iostream>
#include "Tests.h"
#include <cassert>
#include "SquareMatrix.h"
#include "Vector.h"

using namespace std;

#define RESET   "\033[0m"   
#define GREEN   "\033[32m"
#define RED     "\033[31m"

void testMatrixConstructors() {
    SquareMatrix<int> m1;
    assert(m1.GetDimension() == 0);

    SquareMatrix<int> m2(3);
    assert(m2.GetDimension() == 3);

    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    SquareMatrix<int> m3(data, 3);
    assert(m3.GetDimension() == 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(m3(i, j) == data[i * 3 + j]);
        }
    }

    cout << "testMatrixConstructors: " << GREEN << "OK" << RESET << endl;
}

void testMatrixOperations() {
    int data1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int data2[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    SquareMatrix<int> m1(data1, 3);
    SquareMatrix<int> m2(data2, 3);

    SquareMatrix<int> m3 = m1 + m2;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(m3(i, j) == data1[i * 3 + j] + data2[i * 3 + j]);
        }
    }

    SquareMatrix<int> m4 = m1 * 2;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(m4(i, j) == data1[i * 3 + j] * 2);
        }
    }

    cout << "testMatrixOperations: " << GREEN << "OK" << RESET << endl;
}

void testMatrixNorm() {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    SquareMatrix<int> m(data, 3);
    double norm = m.Norm();
    assert(abs(norm - 16.88194) < 0.001);

    cout << "testMatrixNorm: " << GREEN << "OK" << RESET << endl;
}

void testMatrixTransformations() {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    SquareMatrix<int> m(data, 3);

    m.SwapRows(0, 1);
    assert(m(0, 0) == 4 && m(0, 1) == 5 && m(0, 2) == 6 &&
           m(1, 0) == 1 && m(1, 1) == 2 && m(1, 2) == 3);

    m.MultiplyRow(0, 3);
    assert(m(0, 0) == 12 && m(0, 1) == 15 && m(0, 2) == 18);

    m.AddRowToRow(0, 2, 2);
    assert(m(2, 0) == 31 && m(2, 1) == 38 && m(2, 2) == 45);


    cout << "testMatrixTransformations: " << GREEN << "OK" << RESET << endl;
}

void testVectorConstructors() {
    Vector<int> v1;
    assert(v1.GetDimension() == 0);

    int data[] = {1, 2, 3, 4, 5};
    Vector<int> v2(data, 5);
    assert(v2.GetDimension() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(v2[i] == data[i]);
    }

    Vector<int> v3(v2);
    assert(v3.GetDimension() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(v3[i] == data[i]);
    }

    cout << "testVectorConstructors: " << GREEN << "OK" << RESET << endl;
}

void testVectorOperations() {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6};
    Vector<int> v1(data1, 3);
    Vector<int> v2(data2, 3);

    Vector<int> v3 = v1 + v2;
    assert(v3.GetDimension() == 3);
    assert(v3[0] == 5 && v3[1] == 7 && v3[2] == 9);

    Vector<int> v4 = v1 * 2;
    assert(v4.GetDimension() == 3);
    assert(v4[0] == 2 && v4[1] == 4 && v4[2] == 6);

    cout << "testVectorOperations: " << GREEN << "OK" << RESET << endl;
}

void testVectorNorm() {
    int data[] = {1, 2, 3};
    Vector<int> v(data, 3);
    double norm = v.Norm();
    assert(abs(norm - 3.74166) < 0.001); 

    cout << "testVectorNorm: " << GREEN << "OK" << RESET << endl;
}

void testVectorScalarProduct() {
    int data1[] = {1, 2, 3};
    int data2[] = {4, -5, 6};
    Vector<int> v1(data1, 3);
    Vector<int> v2(data2, 3);

    int scalarProduct = v1 * v2;
    assert(scalarProduct == 12); 

    cout << "testVectorScalarProduct: " << GREEN << "OK" << RESET << endl;
}

void runTests() {
    cout << "Running tests...\nMatrix:" << endl;
    testMatrixConstructors();
    testMatrixOperations();
    testMatrixNorm();
    testMatrixTransformations();

    cout << "\nVector:" << endl;
    testVectorConstructors();
    testVectorOperations();
    testVectorNorm();
    testVectorScalarProduct();

}