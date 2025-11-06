#pragma once
#include <initializer_list>

template <std::size_t Rows, std::size_t Cols, typename T = float>
struct Matrix
{
	T m[Cols][Rows];

    Matrix() {
        for (std::size_t c = 0; c < Cols; ++c)
            for (std::size_t r = 0; r < Rows; ++r)
                m[c][r] = (Rows == Cols && r == c) ? T(1) : T(0);

    }

    Matrix(std::initializer_list<T> values) {
        assert(values.size() == Rows * Cols);
        auto it = values.begin();
        for (std::size_t c = 0; c < Cols; ++c)
            for (std::size_t r = 0; r < Rows; ++r)
                m[c][r] = *it++;
    }

    T& operator()(std::size_t row, std::size_t col) {
        return m[col][row]; // column-major layout
    }

    const T& operator()(std::size_t row, std::size_t col) const {
        return m[col][row];
    }
};