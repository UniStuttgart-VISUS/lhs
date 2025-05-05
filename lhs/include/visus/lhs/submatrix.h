// <copyright file="submatrix.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_SUBMATRIX_H)
#define _LHS_SUBMATRIX_H
#pragma once

#include <cassert>
#include <cstdlib>
#include <memory>
#include <stdexcept>

#include "visus/lhs/layout.h"


LHS_NAMESPACE_BEGIN

/// <summary>
/// A view on a part of a <see cref="matrix{TValue, Layout}" />.
/// </summary>
/// <typeparam name="TMatrix">The type of the matrix.</typeparam>
template<class TMatrix> class submatrix final {

public:

    /// <summary>
    /// The return type of an accessor to a matrix element.
    /// </summary>
    typedef std::conditional_t<std::is_const_v<TMatrix>,
        const typename TMatrix::return_value_type,
        typename TMatrix::return_value_type> return_value_type;

    /// <summary>
    /// The type used to store a scalar.
    /// </summary>
    typedef typename TMatrix::value_type value_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="matrix"></param>
    /// <param name="row"></param>
    /// <param name="column"></param>
    /// <param name="rows"></param>
    /// <param name="columns"></param>
    /// <exception cref="std::range_error">The specified subrange exceeds the
    /// bounds of the given <paramref name="matrix" />.</exception>
    submatrix(_In_ TMatrix& matrix,
        _In_ const std::size_t row,
        _In_ const std::size_t column,
        _In_ const std::size_t rows,
        _In_ const std::size_t columns);

    ///// <summary>
    ///// Extracts a column from the submatrix.
    ///// </summary>
    ///// <typeparam name="L">The layout of <paramref name="dst" />.</typeparam>
    ///// <param name="dst">The submatrix to receive the single column.</param>
    ///// <param name="column">The zero-based index of the column to be extracted.
    ///// </param>
    ///// <returns><paramref name="dst" />.</returns>
    //template<submatrix_layout L> submatrix<TValue, L>& column(
    //    _Inout_ submatrix<TValue, L>& dst,
    //    _In_ const std::size_t column) const;

    ///// <summary>
    ///// Extracts a column from the submatrix.
    ///// </summary>
    ///// <param name="column">The zero-based index of the column to be extracted.
    ///// </param>
    ///// <returns>A new submatrix holding only the specified column.</returns>
    //inline submatrix column(_In_ const std::size_t column) const {
    //    submatrix retval(this->rows(), 1);
    //    return this->column(retval, column);
    //}

    /// <summary>
    /// Answer the number of columns in the submatrix.
    /// </summary>
    /// <returns>The number of columns in the submatrix.</returns>
    inline std::size_t columns(void) const noexcept {
        return this->_columns;
    }

    ///// <summary>
    ///// Gets an iterator over the columns of the submatrix.
    ///// </summary>
    ///// <returns>An iterator for the first column in the submatrix.</returns>
    //inline column_iterator column_begin(void) noexcept {
    //    return column_iterator(*this, 0);
    //}

    ///// <summary>
    ///// Gets an iterator over the columns of the submatrix.
    ///// </summary>
    ///// <returns>An iterator for the first column in the submatrix.</returns>
    //inline const_column_iterator column_begin(void) const noexcept {
    //    return const_column_iterator(*this, 0);
    //}

    ///// <summary>
    ///// Gets the end of columns of the submatrix.
    ///// </summary>
    ///// <returns>An iterator past the last column in the submatrix.</returns>
    //inline column_iterator column_end(void) noexcept {
    //    return column_iterator(
    //        *this,
    //        (Layout == submatrix_layout::row_major)
    //        ? this->size()
    //        : this->_consecutive);
    //}

    ///// <summary>
    ///// Gets the end of columns of the submatrix.
    ///// </summary>
    ///// <returns>An iterator past the last column in the submatrix.</returns>
    //inline const_column_iterator column_end(void) const noexcept {
    //    return const_column_iterator(
    //        *this,
    //        (Layout == submatrix_layout::row_major)
    //        ? this->size()
    //        : this->_consecutive);
    //}

    /// <summary>
    /// Answer whether the submatrix has no elements.
    /// </summary>
    /// <returns><c>true</c> if the submatrix has no elements,
    /// <c>false</c> otherwise.</returns>
    inline bool empty(void) const noexcept {
        return (this->size() == 0);
    }

    ///// <summary>
    ///// Fills all positions in the submatrix with the specified value.
    ///// </summary>
    ///// <param name="value">The value to set.</param>
    //inline void fill(_In_ const value_type value) noexcept {
    //    std::fill(this->_elements.begin(), this->_elements.end(), value);
    //}

    /// <summary>
    /// Answer the memory layout of the submatrix, which inherited from the
    /// underlying matrix.
    /// </summary>
    /// <returns>The memory layout of the submatrix.</returns>
    inline constexpr matrix_layout layout(void) const noexcept {
        return detail::layout_v<TMatrix>;
    }

    ///// <summary>
    ///// Extracts a row from the submatrix.
    ///// </summary>
    ///// <typeparam name="L">The layout of <paramref name="dst" />.</typeparam>
    ///// <param name="dst">The submatrix to receive the single row.</param>
    ///// <param name="row">The zero-based index of the row to be extracted.
    ///// </param>
    ///// <returns><paramref name="dst" />.</returns>
    //template<submatrix_layout L> submatrix<TValue, L>& row(
    //    _Inout_ submatrix<TValue, L>& dst,
    //    _In_ const std::size_t row) const;

    ///// <summary>
    ///// Extracts a row from the submatrix.
    ///// </summary>
    ///// <param name="row">The zero-based index of the row to be extracted.
    ///// </param>
    ///// <returns>A new submatrix holding only the specified row.</returns>
    //inline submatrix row(_In_ const std::size_t row) const {
    //    submatrix retval(1, this->columns());
    //    return this->row(retval, row);
    //}

    /// <summary>
    /// Answer the number of rows in the submatrix.
    /// </summary>
    /// <returns>The number of rows in the submatrix.</returns>
    inline std::size_t rows(void) const noexcept {
        return this->_rows;
    }

    ///// <summary>
    ///// Gets an iterator over the rows of the submatrix.
    ///// </summary>
    ///// <returns>An iterator for the first row in the submatrix.</returns>
    //inline row_iterator row_begin(void) noexcept {
    //    return row_iterator(*this, 0);
    //}

    ///// <summary>
    ///// Gets an iterator over the row of the submatrix.
    ///// </summary>
    ///// <returns>An iterator for the first row in the submatrix.</returns>
    //inline const_row_iterator row_begin(void) const noexcept {
    //    return const_row_iterator(*this, 0);
    //}

    ///// <summary>
    ///// Gets the end of rows of the submatrix.
    ///// </summary>
    ///// <returns>An iterator past the last row in the submatrix.</returns>
    //inline row_iterator row_end(void) noexcept {
    //    return row_iterator(
    //        *this,
    //        (Layout == submatrix_layout::row_major)
    //        ? this->_consecutive
    //        : this->size());
    //}

    ///// <summary>
    ///// Gets the end of rows of the submatrix.
    ///// </summary>
    ///// <returns>An iterator past the last row in the submatrix.</returns>
    //inline const const_row_iterator row_end(void) const noexcept {
    //    return const_row_iterator(
    //        *this,
    //        (Layout == submatrix_layout::row_major)
    //        ? this->_consecutive
    //        : this->size());
    //}

    /// <summary>
    /// Answer the number of elements in the submatrix.
    /// </summary>
    /// <returns>The number of elements in the submatrix.</returns>
    inline std::size_t size(void) const noexcept {
        return (this->_rows * this->_columns);
    }

    /// <summary>
    /// Test for equality.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>true</c> if all elements of this submatrix and of
    /// <paramref name="rhs" /> are equal, <c>false</c> otherwise.</returns>
    bool operator ==(_In_ const submatrix& rhs) const noexcept;

    /// <summary>
    /// Test for inequality.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>true</c> if not all elements of this submatrix and of
    /// <paramref name="rhs" /> are equal, <c>false</c> otherwise.</returns>
    inline bool operator !=(_In_ const submatrix& rhs) const noexcept {
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
        assert(row < this->_rows);
        assert(column < this->_columns);
        return this->_matrix(row + this->_row, column + this->_column);
    }

    /// <summary>
    /// Answer the element at the specified position.
    /// </summary>
    /// <param name="row">The zero-based row index.</param>
    /// <param name="column">The zero-based column index.</param>
    /// <returns>The element at the specified position.</returns>
    inline return_value_type& operator()(
            _In_ const std::size_t row,
            _In_ const std::size_t column) noexcept {
        assert(row < this->_rows);
        assert(column < this->_columns);
        return this->_matrix(row + this->_row, column + this->_column);
    }

    /// <summary>
    /// Answer the element at the specified position.
    /// </summary>
    /// <param name="index">The flattened index of the submatrix element.</param>
    /// <returns>The element at the specified position.</returns>
    inline const return_value_type operator[](
            _In_ const std::size_t index) const noexcept {
        assert(index < this->size());
        std::size_t r, c;
        this->location(r, c, index);
        return (*this)(r, c);
    }

    /// <summary>
    /// Answer the element at the specified position.
    /// </summary>
    /// <param name="index">The flattened index of the submatrix element.</param>
    /// <returns>The element at the specified position.</returns>
    inline value_type& operator[](_In_ const std::size_t index) noexcept {
        assert(index < this->size());
        std::size_t r, c;
        this->location(r, c, index);
        return (*this)(r, c);
    }

private:

    /// <summary>
    /// Answer the row and column of the given index local to the submatrix.
    /// </summary>
    /// <param name="row"></param>
    /// <param name="column"></param>
    /// <param name="index"></param>
    void location(_Out_ std::size_t& row, _Out_ std::size_t& column,
        _In_ const std::size_t index) const noexcept;

    /// <summary>
    /// Answer the offset of the submatrix in the underlying matrix.
    /// </summary>
    /// <returns></returns>
    inline std::size_t offset(void) const noexcept {
        return this->_matrix.index(this->_row, this->_column);
    }

    /// <summary>
    /// Answer the offset of the given index in the underlying matrix.
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    inline std::size_t offset(_In_ const std::size_t index) const noexcept {
        assert(index < this->size());
        auto retval = this->offset();
        //return (detail::layout_v<TMatrix> == matrix_layout::row_major)
        //    ? (row * this->_stride + column)
        //    : (column * this->_stride + row);
    }

    std::size_t _column;
    std::size_t _columns;
    TMatrix& _matrix;
    std::size_t _row;
    std::size_t _rows;

};

LHS_NAMESPACE_END

#include "visus/lhs/submatrix.inl"

#endif /* !defined(_LHS_SUBMATRIX_H) */
