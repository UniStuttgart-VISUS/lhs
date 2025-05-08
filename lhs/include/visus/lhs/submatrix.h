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
    /// <param name="matrix">The matrix to create a sub-view of.</param>
    /// <param name="row">The zero-based index of the first row.</param>
    /// <param name="column">The zero-based index of the first column.</param>
    /// <param name="rows">The number of rows in the submatrix.</param>
    /// <param name="columns">The number of columns in the submatrix.</param>
    /// <exception cref="std::range_error">The specified subrange exceeds the
    /// bounds of the given <paramref name="matrix" />.</exception>
    submatrix(_In_ TMatrix& matrix,
        _In_ const std::size_t row,
        _In_ const std::size_t column,
        _In_ const std::size_t rows,
        _In_ const std::size_t columns);

    /// <summary>
    /// Answer the underlying matrix.
    /// </summary>
    /// <returns>A reference to the underlying matix.</returns>
    inline TMatrix& base(void) noexcept {
        return this->_matrix;
    }

    /// <summary>
    /// Answer the underlying matrix.
    /// </summary>
    /// <returns>A reference to the underlying matix.</returns>
    inline const TMatrix& base(void) const noexcept {
        return this->_matrix;
    }

    /// <summary>
    /// Answer the number of columns in the submatrix.
    /// </summary>
    /// <returns>The number of columns in the submatrix.</returns>
    inline std::size_t columns(void) const noexcept {
        return this->_columns;
    }

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
        return detail::layout_v<submatrix>;
    }

    /// <summary>
    /// Answer the number of rows in the submatrix.
    /// </summary>
    /// <returns>The number of rows in the submatrix.</returns>
    inline std::size_t rows(void) const noexcept {
        return this->_rows;
    }

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
        return this->_matrix[this->index(row, column)];
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
        return this->_matrix[this->index(row, column)];
    }

    /// <summary>
    /// Answer the element at the specified position.
    /// </summary>
    /// <param name="index">The flattened index of the submatrix element.</param>
    /// <returns>The element at the specified position.</returns>
    inline const return_value_type operator[](
            _In_ const std::size_t index) const noexcept {
        assert(index < this->size());
        return this->_matrix[this->index(index)];
    }

    /// <summary>
    /// Answer the element at the specified position.
    /// </summary>
    /// <param name="index">The flattened index of the submatrix element.</param>
    /// <returns>The element at the specified position.</returns>
    inline value_type& operator[](_In_ const std::size_t index) noexcept {
        assert(index < this->size());
        return this->_matrix[this->index(index)];
    }

    /// <summary>
    /// Realise the submatrix as an actual <see cref="matrix{TValue, Layout}" />.
    /// </summary>
    /// <returns>The submatrix as a new matrix.</returns>
    operator TMatrix(void) const;

private:

    /// <summary>
    /// Answer the submatrix row and column in the base matrix.
    /// </summary>
    std::size_t index(_In_ const std::size_t row,
        _In_ const std::size_t column) const noexcept;

    /// <summary>
    /// Translate an index relative to the submatrix to an index in the
    /// base matrix.
    /// </summary>
    std::size_t index(_In_ const std::size_t index) const noexcept;

    std::size_t _columns;
    TMatrix& _matrix;
    std::size_t _offset;
    std::size_t _rows;

};

LHS_NAMESPACE_END

#include "visus/lhs/submatrix.inl"

#endif /* !defined(_LHS_SUBMATRIX_H) */
