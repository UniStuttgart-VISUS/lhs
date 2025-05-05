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
/// <typeparam name="Consecutive">The axis the iterator should traverse. For an
/// iterator over the columns, you want to see the rows as a consecutive range,
/// i.e. this parameter should be <see cref="matrix_layout::row_major" />. For
/// an iterator over the columns, use <see cref="matrix_layout::column_major" />
/// to make the rows seem to be consecutive elements.</typeparam>
template<class TMatrix, matrix_layout Consecutive>
class matrix_iterator final
        : public std::iterator<std::forward_iterator_tag, TMatrix> {

public:

    /// <summary>
    /// The type of the matrix to be iterated over.
    /// </summary>
    typedef TMatrix matrix_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="matrix"></param>
    /// <param name="position"></param>
    inline explicit matrix_iterator(
            _In_ matrix_type& matrix,
            _In_ const std::size_t position = 0) noexcept
        : _matrix(matrix), _position(position) { }

    reference operator *(void) const {
        throw "TODO";
    }

    pointer operator->() {
        throw "TODO";
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
    inline bool operator ==(_In_ const matrix_iterator &rhs) const noexcept {
        return (std::addressof(this->_matrix) == std::addressof(rhs._matrix))
            && (this->_position == rhs._position);
    }

    /// <summary>
    /// Test for inequality.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>true</c> if this iterator and <paramref name="rhs" /> do not
    /// designate the same matrix element, <c>false</c> otherwise.</returns>
    inline bool operator !=(_In_ const matrix_iterator &rhs) const noexcept {
        return !(*this == rhs);
    }

private:

    inline constexpr std::size_t step(void) const noexcept {
        return (Consecutive == layout_v<matrix_type>)
            ? this->_matrix._stride
            : static_cast<std::size_t>(1);
    }

    matrix_type& _matrix;
    std::size_t _position;
};

LHS_DETAIL_NAMESPACE_END

#endif /* !defined(_LHS_MATRIX_ITERATOR_H) */
