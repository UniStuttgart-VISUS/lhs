// <copyright file="matrix_iterator.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_MATRIX_ITERATOR_H)
#define _LHS_MATRIX_ITERATOR_H
#pragma once

#include <cassert>
#include <cstdlib>
#include <iterator>
#include <memory>
#include <type_traits>

#include "visus/lhs/submatrix.h"


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// An iterator for rows or columns of a matrix.
/// </summary>
/// <typeparam name="TMatrix">The type of the matrix to be iterated over.
/// </typeparam>
/// <typeparam name="Consecutive">Determines the axis the iterator should
/// traverse by specifying which elements consecutive in the iterated
/// submatrices. For an iterator over the columns, you want to see the rows as
/// a consecutive range, i.e. this parameter should be
/// <see cref="matrix_layout::row_major" />. For an iterator over the rows, use
/// <see cref="matrix_layout::column_major" /> to make the rows seem to be
/// consecutive elements.</typeparam>
template<class TMatrix, matrix_layout Consecutive>
class matrix_iterator final : public std::iterator<std::forward_iterator_tag,
        submatrix<TMatrix>> {

public:

    /// <summary>
    /// The type of the matrix to be iterated over.
    /// </summary>
    typedef TMatrix matrix_type;

    /// <summary>
    /// Indicates whether the iterator traverses the matrix column by column.
    /// </summary>
    static constexpr const bool column_iterator
        = (Consecutive == matrix_layout::row_major);

    /// <summary>
    /// Indicates whether the iterator traverses the matrix row by row.
    /// </summary>
    static constexpr const bool row_iterator
        = (Consecutive == matrix_layout::column_major);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="matrix"></param>
    /// <param name="position"></param>
    inline explicit matrix_iterator(
            _In_ matrix_type& matrix,
            _In_ const std::size_t position = 0) noexcept
        : _matrix(matrix), _position(position) { }

    /// <summary>
    /// Gets a view of the row or column.
    /// </summary>
    /// <returns>The current row or column.</returns>
    inline value_type operator *(void) const {
        const auto coords = this->_matrix.index(this->_position);
        const auto rows = row_iterator ? 1 : this->_matrix.rows();
        const auto cols = column_iterator ? 1 : this->_matrix.columns();
        return submatrix<TMatrix>(this->_matrix,
            coords.first, coords.second,
            rows, cols);
    }

    /// <summary>
    /// Gets a view of the row or column.
    /// </summary>
    /// <returns>The current row or column.</returns>
    inline value_type operator ->(void) const {
        return *this;
    }

    /// <summary>
    /// Prefix increment.
    /// </summary>
    /// <returns>The iterator after it has been advanced.</returns>
    matrix_iterator& operator ++(void) {
        this->_position += this->step();
        return *this;
    }

    /// <summary>
    /// Postfix increment.
    /// </summary>
    /// <returns>The iterator before it has been advanced.</returns>
    matrix_iterator operator ++(int) {
        auto retval = *this;
        this->_position += this->step();
        return retval;
    }

    /// <summary>
    /// Test for equality.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>true</c> if this iterator and <paramref name="rhs" />
    /// designate the same matrix element, <c>false</c> otherwise.</returns>
    inline bool operator ==(_In_ const matrix_iterator& rhs) const noexcept {
        assert(std::addressof(this->_matrix) == std::addressof(rhs._matrix));
        return (this->_position == rhs._position);
    }

    /// <summary>
    /// Test for inequality.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>true</c> if this iterator and <paramref name="rhs" /> do not
    /// designate the same matrix element, <c>false</c> otherwise.</returns>
    inline bool operator !=(_In_ const matrix_iterator& rhs) const noexcept {
        return !(*this == rhs);
    }

private:

    inline constexpr std::size_t step(void) const noexcept {
        return (Consecutive != layout_v<matrix_type>)
            ? this->_matrix.stride()
            : static_cast<std::size_t>(1);
    }

    matrix_type& _matrix;
    std::size_t _position;
};

LHS_DETAIL_NAMESPACE_END

#endif /* !defined(_LHS_MATRIX_ITERATOR_H) */
