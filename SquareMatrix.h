#pragma once

#include "Sequences/MutableArraySequence.h"
#include <cmath>
#include <complex>

template <typename T>
class SquareMatrix {
    private:
        MutableArraySequence<T> *data;
        int size;

    public:
        SquareMatrix() : size(0), data(nullptr) {}

        SquareMatrix(int size) : size(size) {
            if (size <= 0) {
                throw std::invalid_argument("Size must be positive");
            }
            this->data = new MutableArraySequence<T>(new DynamicArray<T>(size * size));
        }

        SquareMatrix(T* items, int size) : size(size) {
            if (size <= 0) {
                throw std::invalid_argument("Matrix size must be positive.");
            }
            if (items == nullptr) {
                throw std::invalid_argument("Input array cannot be nullptr.");
            }
            this->data = new MutableArraySequence<T>(items, size * size);
        }

        SquareMatrix(const SquareMatrix<T>& other) : size(other.size) {
            data = new MutableArraySequence<T>(*other.data);
        }

        ~SquareMatrix() {
            delete data;
        }

        T& operator()(int row, int col) {
            if (row < 0 || row >= size || col < 0 || col >= size) {
                throw std::out_of_range("Matrix indices out of bounds.");
            }
            return data->Get(row * size + col);
        }

        const T& operator()(int row, int col) const {
            if (row < 0 || row >= size || col < 0 || col >= size) {
                throw std::out_of_range("Matrix indices out of bounds.");
            }
            return data->Get(row * size + col);
        }

        SquareMatrix<T> operator+(const SquareMatrix<T>& other) const {
            if (size != other.size) {
                throw std::invalid_argument("Matrices must have the same dimensions for addition.");
            }
            SquareMatrix<T> result(size);
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    result(i, j) = (*this)(i, j) + other(i, j);
                }
            }
            return result;
        }

        SquareMatrix<T> operator*(const T& scalar) const {
            SquareMatrix<T> result(size);
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    result(i, j) = (*this)(i, j) * scalar;
                }
            }
            return result;
        }

        double Norm() const {
            double sum = 0;
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    sum += std::norm((*this)(i, j)); 
                }
            }
            return std::sqrt(sum);
        }

        void SwapRows(int row1, int row2) {
            if (row1 < 0 || row1 >= size || row2 < 0 || row2 >= size) {
                throw std::out_of_range("Row indices out of bounds.");
            }
            for (int j = 0; j < size; ++j) {
                std::swap((*this)(row1, j), (*this)(row2, j));
            }
        }

        void MultiplyRow(int row, const T& scalar) {
            if (row < 0 || row >= size) {
                throw std::out_of_range("Row index out of bounds.");
            }
            for (int j = 0; j < size; ++j) {
                (*this)(row, j) *= scalar;
            }
        }

        void AddRowToRow(int srcRow, int destRow, const T& scalar) {
            if (srcRow < 0 || srcRow >= size || destRow < 0 || destRow >= size) {
                throw std::out_of_range("Row indices out of bounds.");
            }
            for (int j = 0; j < size; ++j) {
                (*this)(destRow, j) += (*this)(srcRow, j) * scalar;
            }
        }


        friend std::ostream& operator<<(std::ostream& os, const SquareMatrix<T>& matrix) {
            for (int i = 0; i < matrix.size; ++i) {
                for (int j = 0; j < matrix.size; ++j) {
                    os << matrix(i, j) << " ";
                }
                os << std::endl;
            }
            return os;
        } 

        int GetDimension() const {
            return size;
        }

};