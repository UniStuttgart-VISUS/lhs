// <copyright file="matrix.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_MATRIX_H)
#define _LHS_MATRIX_H
#pragma once

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <vector>

#include "visus/lhs/matrix_layout.h"


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A minimal representation of a 2D matrix.
/// </summary>
/// <typeparam name="TValue">The type used to store a scalar.</typeparam>
/// <typeparam name="Layout">The memory layout used by the matrix</typeparam>
template<class TValue, matrix_layout Layout = matrix_layout::row_major>
class matrix final {

public:

    /// <summary>
    /// The type used to store a scalar.
    /// </summary>
    typedef TValue value_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="rows"></param>
    /// <param name="columns"></param>
    /// <param name="value"></param>
    inline matrix(_In_ const std::size_t rows = 0,
            _In_ const std::size_t columns = 0,
            _In_ value_type value = static_cast<value_type>(0))
        : _consecutive((Layout == matrix_layout::row_major) ? columns : rows),
            _elements(rows * columns, value) {
    }

    /// <summary>
    /// Extracts a column from the matrix.
    /// </summary>
    /// <typeparam name="L">The layout of <paramref name="dst" />.</typeparam>
    /// <param name="dst">The matrix to receive the single column.</param>
    /// <param name="column">The zero-based index of the column to be extracted.
    /// </param>
    /// <returns><paramref name="dst" />.</returns>
    template<matrix_layout L> matrix<TValue, L>& column(
        _Inout_ matrix<TValue, L>& dst,
        _In_ const std::size_t column) const;

    /// <summary>
    /// Extracts a column from the matrix.
    /// </summary>
    /// <param name="column">The zero-based index of the column to be extracted.
    /// </param>
    /// <returns>A new matrix holding only the specified column.</returns>
    inline matrix column(_In_ const std::size_t column) const {
        matrix retval(this->rows(), 1);
        return this->column(retval, column);
    }

    /// <summary>
    /// Answer the number of columns in the matrix.
    /// </summary>
    /// <returns>The number of columns in the matrix.</returns>
    inline std::size_t columns(void) const noexcept {
        assert((this->_elements.size() % this->_consecutive) == 0);
        return (Layout == matrix_layout::row_major)
            ? this->_consecutive
            : this->_elements.size() / this->_consecutive;
    }

    /// <summary>
    /// Answer whether the matrix has no elements.
    /// </summary>
    /// <returns><c>true</c> if the matrix has no elements,
    /// <c>false</c> otherwise.</returns>
    inline bool empty(void) const noexcept {
        return this->_elements.empty();
    }

    /// <summary>
    /// Fills all positions in the matrix with the specified value.
    /// </summary>
    /// <param name="value">The value to set.</param>
    inline void fill(_In_ const value_type value) noexcept {
        std::fill(this->_elements.begin(), this->_elements.end(), value);
    }

    /// <summary>
    /// Extracts a row from the matrix.
    /// </summary>
    /// <typeparam name="L">The layout of <paramref name="dst" />.</typeparam>
    /// <param name="dst">The matrix to receive the single row.</param>
    /// <param name="row">The zero-based index of the row to be extracted.
    /// </param>
    /// <returns><paramref name="dst" />.</returns>
    template<matrix_layout L> matrix<TValue, L>& row(
        _Inout_ matrix<TValue, L>& dst,
        _In_ const std::size_t row) const;


    /// <summary>
    /// Extracts a row from the matrix.
    /// </summary>
    /// <param name="row">The zero-based index of the row to be extracted.
    /// </param>
    /// <returns>A new matrix holding only the specified row.</returns>
    inline matrix row(_In_ const std::size_t row) const {
        matrix retval(1, this->columns());
        return this->row(retval, row);
    }

    /// <summary>
    /// Answer the number of rows in the matrix.
    /// </summary>
    /// <returns>The number of rows in the matrix.</returns>
    inline std::size_t rows(void) const noexcept {
        assert((this->_elements.size() % this->_consecutive) == 0);
        return (Layout == matrix_layout::row_major)
            ? this->_elements.size() / this->_consecutive
            : this->_consecutive;
    }

    /// <summary>
    /// Answer the number of elements in the matrix.
    /// </summary>
    /// <returns>The number of elements in the matrix.</returns>
    inline std::size_t size(void) const noexcept {
        return this->_elements.size();
    }

    /// <summary>
    /// Test for equality.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>true</c> if all elements of this matrix and of
    /// <paramref name="rhs" /> are equal, <c>false</c> otherwise.</returns>
    bool operator ==(_In_ const matrix& rhs) const noexcept;

    /// <summary>
    /// Test for inequality.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>true</c> if not all elements of this matrix and of
    /// <paramref name="rhs" /> are equal, <c>false</c> otherwise.</returns>
    inline bool operator !=(_In_ const matrix& rhs) const noexcept {
        return !(*this == rhs);
    }

    /// <summary>
    /// Answer the element at the specified position.
    /// </summary>
    /// <param name="row">The zero-based row index.</param>
    /// <param name="column">The zero-based column index.</param>
    /// <returns>The element at the specified position.</returns>
    inline value_type operator()(
            _In_ const std::size_t row,
            _In_ const std::size_t column) const noexcept {
        return this->_elements[this->index(row, column)];
    }

    /// <summary>
    /// Answer the element at the specified position.
    /// </summary>
    /// <param name="row">The zero-based row index.</param>
    /// <param name="column">The zero-based column index.</param>
    /// <returns>The element at the specified position.</returns>
    inline value_type& operator()(
            _In_ const std::size_t row,
            _In_ const std::size_t column) noexcept {
        return this->_elements[this->index(row, column)];
    }

private:

    inline std::size_t index(_In_ const std::size_t row,
            _In_ const std::size_t column) const noexcept {
        assert(row < this->rows());
        assert(column < this->columns());
        return (Layout == matrix_layout::row_major)
            ? (row * this->_consecutive + column)
            : (column * this->_consecutive + row);
    }

    std::size_t _consecutive;
    std::vector<value_type> _elements;

    // We are all a big family ...
    template<class, matrix_layout> friend class matrix;
};

LHS_DETAIL_NAMESPACE_END

#include "visus/lhs/matrix.inl"

#endif /* !defined(_LHS_MATRIX_H) */
