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
#include <type_traits>
#include <vector>

#include "visus/lhs/matrix_iterator.h"
#include "visus/lhs/matrix_layout.h"


LHS_NAMESPACE_BEGIN

/// <summary>
/// A minimal representation of a 2D matrix.
/// </summary>
/// <remarks>
/// This type is relatively dumb and supports barely any methods. Its main
/// purpose is providing row/column-based indexing into a flat storage structure
/// for a 2D grid. Matrices of this type are used as input and, more
/// importantly, output of the sampling functions.
/// </remarks>
/// <typeparam name="TValue">The type used to store a scalar.</typeparam>
/// <typeparam name="Layout">The memory layout used by the matrix</typeparam>
template<class TValue, matrix_layout Layout = matrix_layout::row_major>
class matrix final {

public:

    /// <summary>
    /// An iterator over the columns of a matrix.
    /// </summary>
    typedef detail::matrix_iterator<matrix, matrix_layout::row_major>
        column_iterator;

    /// <summary>
    /// An iterator over the columns of a matrix.
    /// </summary>
    typedef detail::matrix_iterator<const matrix, matrix_layout::row_major>
        const_column_iterator;

    /// <summary>
    /// The return type of an accessor to a matrix element.
    /// </summary>
    typedef typename std::conditional<
        (sizeof(TValue) > sizeof(std::intptr_t)),
        TValue&,
        TValue>::type return_value_type;

    /// <summary>
    /// An iterator over the rows of a matrix.
    /// </summary>
    typedef detail::matrix_iterator<matrix, matrix_layout::column_major>
        row_iterator;

    /// <summary>
    /// An iterator over the rows of a matrix.
    /// </summary>
    typedef detail::matrix_iterator<const matrix, matrix_layout::column_major>
        const_row_iterator;

    /// <summary>
    /// The type used to store a scalar.
    /// </summary>
    typedef TValue value_type;

    /// <summary>
    /// Create a diagonal matrix with the given size.
    /// </summary>
    /// <param name="size">The number of rows and columns of the matrix.</param>
    /// <param name="value">The value on the diagonal.</param>
    /// <returns>A diagonal matrix.</returns>
    static constexpr matrix diagonal(_In_ const std::size_t size,
        _In_ const value_type value);

    /// <summary>
    /// Create an identity matrix with the given size.
    /// </summary>
    /// <param name="size">The number of rows and columns of the matrix.</param>
    /// <returns>An identity matrix.</returns>
    static inline constexpr matrix identity(_In_ const std::size_t size) {
        return diagonal(size, static_cast<value_type>(1));
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="rows">The number of rows in the matrix.</param>
    /// <param name="columns">The number of columns in the matrix.</param>
    /// <param name="value">The initial value of all matrix elements. This
    /// parameter defaults to zero.</param>
    inline matrix(_In_ const std::size_t rows = 0,
            _In_ const std::size_t columns = 0,
            _In_ value_type value = static_cast<value_type>(0))
        : _stride((Layout == matrix_layout::row_major) ? columns : rows),
            _elements(rows * columns, value) { }

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
        assert((this->_elements.size() % this->_stride) == 0);
        return (Layout == matrix_layout::row_major)
            ? this->_stride
            : this->_elements.size() / this->_stride;
    }

    /// <summary>
    /// Gets an iterator over the columns of the matrix.
    /// </summary>
    /// <returns>An iterator for the first column in the matrix.</returns>
    inline column_iterator column_begin(void) noexcept {
        return column_iterator(*this, 0);
    }

    /// <summary>
    /// Gets an iterator over the columns of the matrix.
    /// </summary>
    /// <returns>An iterator for the first column in the matrix.</returns>
    inline const_column_iterator column_begin(void) const noexcept {
        return const_column_iterator(*this, 0);
    }

    /// <summary>
    /// Gets the end of columns of the matrix.
    /// </summary>
    /// <returns>An iterator past the last column in the matrix.</returns>
    inline column_iterator column_end(void) noexcept {
        return column_iterator(
            *this,
            (Layout == matrix_layout::row_major)
            ? this->size()
            : this->_stride);
    }

    /// <summary>
    /// Gets the end of columns of the matrix.
    /// </summary>
    /// <returns>An iterator past the last column in the matrix.</returns>
    inline const_column_iterator column_end(void) const noexcept {
        return const_column_iterator(
            *this,
            (Layout == matrix_layout::row_major)
            ? this->size()
            : this->_stride);
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
    /// Fills all positions in the matrix using a generator callback that maps a
    /// pair of row and column to the respective value.
    /// </summary>
    /// <typeparam name="TGenerator">The type of the generator, which must
    /// accept the zero-based row and column and yield a value for this matrix
    /// element.</typeparam>
    /// <param name="generator">The generator function that maps a row and
    /// column to a value to be applied.</param>
    template<class TGenerator>
    void fill(_In_ const TGenerator& generator);

    /// <summary>
    /// Answer the index of the given <paramref name="row" /> and
    /// <paramref name="column" /> in the in-memory representation of the
    /// matrix.
    /// </summary>
    /// <param name="row">The zero-based row to get the index of. The parameter
    /// is not checked for validity.</param>
    /// <param name="column">The zero-based column to get the index of. The
    /// parameter is not checked for validity.</param>
    /// <returns>The index of the matrix element in the in-memory representation
    /// of the matrix.</returns>
    inline std::size_t index(
            _In_ const std::size_t row,
            _In_ const std::size_t column) const noexcept {
        assert(row < this->rows());
        assert(column < this->columns());
        return (Layout == matrix_layout::row_major)
            ? (row * this->_stride + column)
            : (column * this->_stride + row);
    }

    /// <summary>
    /// Answer the memory layout of the matrix.
    /// </summary>
    /// <returns>The memory layout of the matrix.</returns>
    inline constexpr matrix_layout layout(void) const noexcept {
        return Layout;
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
    /// Extracts the view of a row from the matrix.
    /// </summary>
    /// <param name="row">The zero-based index of the row to be extracted.
    /// </param>
    /// <returns>A submatrix providing access to only the specified row.
    /// </returns>
    inline submatrix<const matrix> row(_In_ const std::size_t row) const {
        return submatrix<const matrix>(*this, row, 0, 1, this->columns());
    }

    /// <summary>
    /// Extracts the view of a row from the matrix.
    /// </summary>
    /// <param name="row">The zero-based index of the row to be extracted.
    /// </param>
    /// <returns>A submatrix providing access to only the specified row.
    /// </returns>
    inline submatrix<matrix> row(_In_ const std::size_t row) {
        return submatrix<matrix>(*this, row, 0, 1, this->columns());
    }

    /// <summary>
    /// Answer the number of rows in the matrix.
    /// </summary>
    /// <returns>The number of rows in the matrix.</returns>
    inline std::size_t rows(void) const noexcept {
        assert((this->_elements.size() % this->_stride) == 0);
        return (Layout == matrix_layout::row_major)
            ? this->_elements.size() / this->_stride
            : this->_stride;
    }

    /// <summary>
    /// Gets an iterator over the rows of the matrix.
    /// </summary>
    /// <returns>An iterator for the first row in the matrix.</returns>
    inline row_iterator row_begin(void) noexcept {
        return row_iterator(*this, 0);
    }

    /// <summary>
    /// Gets an iterator over the row of the matrix.
    /// </summary>
    /// <returns>An iterator for the first row in the matrix.</returns>
    inline const_row_iterator row_begin(void) const noexcept {
        return const_row_iterator(*this, 0);
    }

    /// <summary>
    /// Gets the end of rows of the matrix.
    /// </summary>
    /// <returns>An iterator past the last row in the matrix.</returns>
    inline row_iterator row_end(void) noexcept {
        return row_iterator(
            *this,
            (Layout == matrix_layout::row_major)
            ? this->_stride
            : this->size());
    }

    /// <summary>
    /// Gets the end of rows of the matrix.
    /// </summary>
    /// <returns>An iterator past the last row in the matrix.</returns>
    inline const const_row_iterator row_end(void) const noexcept {
        return const_row_iterator(
            *this,
            (Layout == matrix_layout::row_major)
            ? this->_stride
            : this->size());
    }

    /// <summary>
    /// Answer the number of elements in the matrix.
    /// </summary>
    /// <returns>The number of elements in the matrix.</returns>
    inline std::size_t size(void) const noexcept {
        return this->_elements.size();
    }

    /// <summary>
    /// Answer the number of consecutively stored elements. The layout of the
    /// matrix determines whether this is the number of rows or the number of
    /// columns.
    /// </summary>
    /// <returns>The number of consecutively stored elements.</returns>
    inline std::size_t stride(void) const noexcept {
        return this->_stride;
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
    inline const return_value_type operator()(
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

    /// <summary>
    /// Answer the element at the specified position.
    /// </summary>
    /// <param name="index">The flattened index of the matrix element.</param>
    /// <returns>The element at the specified position.</returns>
    inline const return_value_type operator[](
            _In_ const std::size_t index) const noexcept {
        assert(index < this->size());
        return this->_elements[index];
    }

    /// <summary>
    /// Answer the element at the specified position.
    /// </summary>
    /// <param name="index">The flattened index of the matrix element.</param>
    /// <returns>The element at the specified position.</returns>
    inline value_type& operator[](_In_ const std::size_t index) noexcept {
        assert(index < this->size());
        return this->_elements[index];
    }

    /// <summary>
    /// Answer the flat in-memory representation of the matrix.
    /// </summary>
    /// <returns>The elements in the matrix. The order of the return value
    /// depends on the layout of the matrix.</returns>
    inline operator const std::vector<value_type>&(void) const noexcept {
        return this->_elements;
    }

private:

    std::vector<value_type> _elements;
    std::size_t _stride;

public:

    /// <summary>
    /// Gets an iterator for the begin of elements. The order of the elements
    /// depends of the layout of the matrix.
    /// </summary>
    /// <returns>An iterator for the begin of the elements.</returns>
    inline auto begin(void) noexcept -> decltype(this->_elements.begin()) {
        return this->_elements.begin();
    }

    /// <summary>
    /// Gets an iterator for the begin of elements. The order of the elements
    /// depends of the layout of the matrix.
    /// </summary>
    /// <returns>An iterator for the begin of the elements.</returns>
    inline auto begin(void) const noexcept
            -> decltype(this->_elements.begin()) {
        return this->_elements.begin();
    }

    /// <summary>
    /// Gets an iterator for the end of elements. The order of the elements
    /// depends of the layout of the matrix.
    /// </summary>
    /// <returns>An iterator for the end of the elements.</returns>
    inline auto end(void) noexcept -> decltype(this->_elements.end()) {
        return this->_elements.end();
    }

    /// <summary>
    /// Gets an iterator for the end of elements. The order of the elements
    /// depends of the layout of the matrix.
    /// </summary>
    /// <returns>An iterator for the end of the elements.</returns>
    inline auto end(void) const noexcept -> decltype(this->_elements.end()) {
        return this->_elements.end();
    }

    friend column_iterator;
    friend const_column_iterator;
    template<class, matrix_layout> friend class matrix;
    friend row_iterator;
    friend const_row_iterator;
};

LHS_NAMESPACE_END

#include "visus/lhs/matrix.inl"

#endif /* !defined(_LHS_MATRIX_H) */
