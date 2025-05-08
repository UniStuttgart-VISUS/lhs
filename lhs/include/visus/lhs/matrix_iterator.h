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

#include "visus/lhs/layout.h"


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// An iterator for the elements of a matrix.
/// </summary>
/// <typeparam name="TMatrix">The type of the matrix to be iterated over.
/// </typeparam>
/// <typeparam name="Order">Determines the order in which the elements should
/// be enumerated. If this is <see cref="matrix_layout::row_major" />, the
/// elements are enumerated row by row.</typeparam>
template<class TMatrix, matrix_layout Order>
class matrix_iterator final : public std::iterator<std::forward_iterator_tag,
        typename TMatrix::value_type> {

public:

    /// <summary>
    /// The type of the matrix to be iterated over.
    /// </summary>
    typedef TMatrix matrix_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="matrix">The matrix to be iterated.</param>
    /// <param name="position">The zero-based initial position of the iterator.
    /// </param>
    inline explicit matrix_iterator(
            _In_ matrix_type& matrix,
            _In_ const std::size_t position = 0) noexcept
        : _matrix(matrix), _position(position) { }

    /// <summary>
    /// Gets a pointer to the current element.
    /// </summary>
    /// <returns>A pointer to the current element.</returns>
    inline pointer operator ->(void) {
        return std::addressof(*this);
    }

    /// <summary>
    /// Prefix increment.
    /// </summary>
    /// <returns>The iterator after it has been advanced.</returns>
    matrix_iterator& operator ++(void);

    /// <summary>
    /// Postfix increment.
    /// </summary>
    /// <returns>The iterator before it has been advanced.</returns>
    inline matrix_iterator operator ++(int) {
        auto retval = *this;
        ++(*this);
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

    /// <summary>
    /// Answer how many elements to skip to get to the next row or column.
    /// </summary>
    inline constexpr std::size_t step(void) const noexcept {
        return (Order == layout_v<matrix_type>)
            ? static_cast<std::size_t>(1)
            : this->_matrix.stride();
    }

    matrix_type& _matrix;
    std::size_t _position;

public:

    /// <summary>
    /// Gets the current element.
    /// </summary>
    /// <returns>The current element.</returns>
    inline auto operator *(void) -> decltype(this->_matrix[0]) {
        const auto q = this->_position / this->_matrix.size();
        const auto r = this->_position % this->_matrix.size();
        return this->_matrix[q + r];
    }
};

LHS_DETAIL_NAMESPACE_END

#include "visus/lhs/matrix_iterator.inl"

#endif /* !defined(_LHS_MATRIX_ITERATOR_H) */
