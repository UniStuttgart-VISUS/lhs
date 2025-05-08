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
#include <utility>
#include <vector>

#include "visus/lhs/matrix_iterator.h"
#include "visus/lhs/iteration_order.h"


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
    typedef detail::matrix_iterator<matrix, 
        detail::iteration_order_v<matrix, matrix_layout::column_major>>
        column_iterator;

    /// <summary>
    /// An iterator over the columns of a matrix.
    /// </summary>
    typedef detail::matrix_iterator<const matrix,
        detail::iteration_order_v<matrix, matrix_layout::column_major>>
        const_column_iterator;

    /// <summary>
    /// The return type of an accessor to a matrix element.
    /// </summary>
    typedef typename std::conditional<
        (sizeof(TValue) > sizeof(std::intptr_t)),
        const TValue&,
        TValue>::type const_return_value_type;

    /// <summary>
    /// The return type of an accessor to a matrix element.
    /// </summary>
    typedef typename TValue& return_value_type;

    /// <summary>
    /// An iterator over the rows of a matrix.
    /// </summary>
    typedef detail::matrix_iterator<matrix,
        detail::iteration_order_v<matrix, matrix_layout::row_major>>
        row_iterator;

    /// <summary>
    /// An iterator over the rows of a matrix.
    /// </summary>
    typedef detail::matrix_iterator<const matrix,
        detail::iteration_order_v<matrix, matrix_layout::row_major>>
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
    /// Initialises a new instance
    /// </summary>
    /// <typeparam name="TGenerator">The type of the generator, which must
    /// accept the zero-based row and column and yield a value for this matrix
    /// element.</typeparam>
    /// <param name="rows">The number of rows in the matrix.</param>
    /// <param name="columns">The number of columns in the matrix.</param>
    /// <param name="generator">The generator function that maps a row and
    /// column to a value to be applied.</param>
    template<class TGenerator>
    inline matrix(_In_ const std::size_t rows,
            _In_ const std::enable_if_t<!std::is_same_v<TGenerator, TValue>,
                std::size_t> columns,
            _In_ TGenerator&& generator)
        : _stride((Layout == matrix_layout::row_major) ? columns : rows),
            _elements(rows * columns) {
        this->fill(std::forward<TGenerator>(generator));
    }

    /// <summary>
    /// Gets a column-order iterator for the begin of the specified column.
    /// </summary>
    /// <param name="column">The zero-based index of the column to get the
    /// iterator for.</param>
    /// <returns>An iterator for the first element of the specified column,
    /// which will enumerate the elements in column-major order.</returns>
    inline column_iterator begin_column(
            _In_ const std::size_t column) noexcept {
        assert(column < this->columns());
        return column_iterator(*this, this->index(0, column));
    }

    /// <summary>
    /// Gets a column-order iterator for the begin of the specified column.
    /// </summary>
    /// <param name="column">The zero-based index of the column to get the
    /// iterator for.</param>
    /// <returns>An iterator for the first element of the specified column,
    /// which will enumerate the elements in column-major order.</returns>
    inline const_column_iterator begin_column(
            _In_ const std::size_t column) const noexcept {
        assert(column < this->columns());
        return const_column_iterator(*this, this->index(0, column));
    }

    /// <summary>
    /// Gets an iterator over the columns of the matrix.
    /// </summary>
    /// <returns>An iterator for the first element in the matrix, which will
    /// enumerate the elements in column-major order.</returns>
    inline column_iterator begin_columns(void) noexcept {
        return column_iterator(*this, 0);
    }

    /// <summary>
    /// Gets an iterator over the columns of the matrix.
    /// </summary>
    /// <returns>An iterator for the first element in the matrix, which will
    /// enumerate the elements in column-major order.</returns>
    inline const_column_iterator begin_columns(void) const noexcept {
        return const_column_iterator(*this, 0);
    }

    /// <summary>
    /// Gets a row-order iterator for the begin of the specified row.
    /// </summary>
    /// <param name="row">The zero-based index of the row to get the
    /// iterator for.</param>
    /// <returns>An iterator for the first element of the specified row,
    /// which will enumerate the elements in row-major order.</returns>
    inline row_iterator begin_row(_In_ const std::size_t row) noexcept {
        assert(row < this->rows());
        return row_iterator(*this, this->index(row, 0));
    }

    /// <summary>
    /// Gets a row-order iterator for the begin of the specified row.
    /// </summary>
    /// <param name="row">The zero-based index of the row to get the
    /// iterator for.</param>
    /// <returns>An iterator for the first element of the specified row,
    /// which will enumerate the elements in row-major order.</returns>
    inline const_row_iterator begin_row(
            _In_ const std::size_t row) const noexcept {
        assert(row < this->rows());
        return const_row_iterator(*this, this->index(row, 0));
    }

    /// <summary>
    /// Gets an iterator over the rows of the matrix.
    /// </summary>
    /// <returns>An iterator for the first element in the matrix, which will
    /// enumerate the elements in row-major order.</returns>
    inline row_iterator begin_rows(void) noexcept {
        return row_iterator(*this, 0);
    }

    /// <summary>
    /// Gets an iterator over the row of the matrix.
    /// </summary>
    /// <returns>An iterator for the first element in the matrix, which will
    /// enumerate the elements in row-major order.</returns>
    inline const_row_iterator begin_rows(void) const noexcept {
        return const_row_iterator(*this, 0);
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
        assert((this->_elements.size() % this->_stride) == 0);
        return this->row_major()
            ? this->_stride
            : this->_elements.size() / this->_stride;
    }

    /// <summary>
    /// Answer whether the matrix is stored in column-major order.
    /// </summary>
    /// <returns><c>true</c> if the matrix is a column-major matrix,
    /// <c>false</c> if it is a row-major matrix.</returns>
    inline constexpr bool column_major(void) const noexcept {
        return (Layout == matrix_layout::column_major);
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
    /// Gets a column-order iterator for the end of the specified column.
    /// </summary>
    /// <param name="column">The zero-based index of the column to get the
    /// iterator for.</param>
    /// <returns>An iterator past the last element of the specified column.
    /// </returns>
    inline column_iterator end_column(_In_ const std::size_t column) noexcept {
        assert(column < this->columns());
        const auto row = this->rows() - 1;
        column_iterator retval(*this, this->index(row, column));
        return ++retval;
    }

    /// <summary>
    /// Gets a column-order iterator for the end of the specified column.
    /// </summary>
    /// <param name="column">The zero-based index of the column to get the
    /// iterator for.</param>
    /// <returns>An iterator past the last element of the specified column.
    /// </returns>
    inline const const_column_iterator end_column(
            _In_ const std::size_t column) const noexcept {
        assert(column < this->columns());
        const auto row = this->rows() - 1;
        const_column_iterator retval(*this, this->index(row, column));
        return ++retval;
    }

    /// <summary>
    /// Gets a row-order iterator for the end of the specified row.
    /// </summary>
    /// <param name="row">The zero-based index of the row to get the
    /// iterator for.</param>
    /// <returns>An iterator past the last element of the specified row.
    /// </returns>
    inline row_iterator end_row(_In_ const std::size_t row) noexcept {
        assert(row < this->rows());
        const auto column = this->columns() - 1;
        row_iterator retval(*this, this->index(row, column));
        return ++retval;
    }

    /// <summary>
    /// Gets a row-order iterator for the end of the specified row.
    /// </summary>
    /// <param name="row">The zero-based index of the row to get the
    /// iterator for.</param>
    /// <returns>An iterator past the last element of the specified row.
    /// </returns>
    inline const_row_iterator end_row(
            _In_ const std::size_t row) const noexcept {
        assert(row < this->rows());
        const auto column = this->columns() - 1;
        const_row_iterator  retval(*this, this->index(row, column));
        return ++retval;
    }

    /// <summary>
    /// Gets the end of the columns of the matrix.
    /// </summary>
    /// <returns>An iterator past the last element in the matrix.</returns>
    inline column_iterator end_columns(void) noexcept {
        const auto step = this->step<column_iterator>();
        return column_iterator(*this, this->size() * step);
    }

    /// <summary>
    /// Gets the end of the columns  of the matrix.
    /// </summary>
    /// <returns>An iterator past the last element in the matrix.</returns>
    inline const const_column_iterator end_columns(void) const noexcept {
        const auto step = this->step<const_column_iterator>();
        return const_column_iterator(*this, this->size() * step);
    }

    /// <summary>
    /// Gets the end of the rows of the matrix.
    /// </summary>
    /// <returns>An iterator past the last element in the matrix.</returns>
    inline row_iterator end_rows(void) noexcept {
        const auto step = this->step<row_iterator>();
        return row_iterator(*this, this->size() * step);
    }

    /// <summary>
    /// Gets the end of the  rows of the matrix.
    /// </summary>
    /// <returns>An iterator past the last element in the matrix.</returns>
    inline const const_row_iterator end_rows(void) const noexcept {
        const auto step = this->step<const_row_iterator>();
        return const_row_iterator(*this, this->size() * step);
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
    /// Answer the row and column of the given index.
    /// </summary>
    /// <param name="row">Receives the zero-based row.</param>
    /// <param name="column">Receives the zero-based column.</param>
    /// <param name="index">The index to be converted into row and column.
    /// </param>
    /// <returns><c>true</c> if the index is valid, <c>false</c> otherwise.
    /// </returns>
    bool index(_Out_ std::size_t& row,
        _Out_ std::size_t& column,
        _In_ const std::size_t index) const noexcept;

    /// <summary>
    /// Answer the row and column of the given index.
    /// </summary>
    /// <param name="index">The index to be converted into row and column.
    /// </param>
    /// <returns>The row and column represented by teh given index, regardless
    /// of whether this index is valid or not.</returns>
    inline std::pair<std::size_t, std::size_t> index(
            _In_ const std::size_t index) const noexcept {
        std::pair<std::size_t, std::size_t> retval;
        this->index(retval.first, retval.second, index);
        return retval;
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
    /// Extracts a row from the matrix.
    /// </summary>
    /// <param name="row">The zero-based index of the row to be extracted.
    /// </param>
    /// <returns>The specified row of the matrix.</returns>
    /// </returns>
    inline matrix row(_In_ const std::size_t row) const {
        matrix retval(1, this->columns());
        return this->row(retval, row);
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
    /// Answer whether the matrix is stored in row-major order.
    /// </summary>
    /// <returns><c>true</c> if the matrix is a row-major matrix,
    /// <c>false</c> if it is a column-major matrix.</returns>
    inline constexpr bool row_major(void) const noexcept {
        return (Layout == matrix_layout::row_major);
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
    inline const_return_value_type operator ()(
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
    inline return_value_type operator ()(
            _In_ const std::size_t row,
            _In_ const std::size_t column) noexcept {
        return this->_elements[this->index(row, column)];
    }

    /// <summary>
    /// Answer the element at the specified position.
    /// </summary>
    /// <param name="index">The flattened index of the matrix element.</param>
    /// <returns>The element at the specified position.</returns>
    inline const_return_value_type operator [](
            _In_ const std::size_t index) const noexcept {
        assert(index < this->size());
        return this->_elements[index];
    }

    /// <summary>
    /// Answer the element at the specified position.
    /// </summary>
    /// <param name="index">The flattened index of the matrix element.</param>
    /// <returns>The element at the specified position.</returns>
    inline return_value_type operator [](
            _In_ const std::size_t index) noexcept {
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

    template<class TIterator>
    inline constexpr std::size_t step(void) const noexcept {
        return (detail::layout_v<TIterator> == Layout)
            ? static_cast<std::size_t>(1)
            : this->stride();
    }

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

    template<class, matrix_layout> friend class matrix;
};

LHS_NAMESPACE_END

#include "visus/lhs/matrix.inl"

#endif /* !defined(_LHS_MATRIX_H) */
