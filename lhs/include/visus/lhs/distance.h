﻿// <copyright file="distance.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_SQUARE_DISTANCE_H)
#define _LHS_SQUARE_DISTANCE_H
#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>
#include <tuple>
#include <type_traits>
#include <vector>

#include "visus/lhs/matrix.h"


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Computes the square of <paramref name="value" />.
/// </summary>
/// <typeparam name="TValue">A numeric type that supports multiplication.
/// </typeparam>
/// <param name="value">The value to be squared.</param>
/// <returns>The square of <paramref name="value" />.</returns>
template<class TValue>
inline constexpr TValue square(_In_ const TValue value) noexcept {
    return (value * value);
}

/// <summary>
/// Computes the square of the difference between two values.
/// </summary>
/// <typeparam name="TValue">A numeric type that supports multiplication.
/// </typeparam>
/// <param name="lhs">The left-hand-side operand.</param>
/// <param name="rhs">The right-hand-side operand.</param>
/// <returns>The square of the difference between the two operands.</returns>
template<class TValue>
inline constexpr TValue square_difference(
        _In_ const TValue lhs,
        _In_ const TValue rhs) noexcept {
    return square(lhs - rhs);
}

/// <summary>
/// Computes the squared distance between two vectors.
/// </summary>
/// <typeparam name="TValue">A numeric type that supports multiplication and
/// addition.</typeparam>
/// <param name="lhs">The left-hand-side operand.</param>
/// <param name="rhs">The right-hand-side operand.</param>
/// <returns>The squared distance between the two operands.</returns>
template<class TValue> inline TValue square_distance(
        _In_ const std::vector<TValue>& lhs,
        _In_ const std::vector<TValue>& rhs) noexcept {
    assert(lhs.size() == rhs.size());
    return std::inner_product(
        lhs.begin(),
        lhs.end(),
        rhs.begin(),
        static_cast<TValue>(0),
        std::plus<TValue>(),
        square_difference<TValue>);
}

/// <summary>
/// Computes the squared distance between two vectors.
/// </summary>
/// <typeparam name="TIterator">An iterator over the components of a vector.
/// </typeparam>
/// <param name="lbegin">The begin of the left-hand-side operand.</param>
/// <param name="lend">The end of the left-hand-sude operand.</param>
/// <param name="rbegin">The begin of the right-hand-side operand.</param>
/// <returns>The squared distance between the two operands.</returns>
template<class TIterator>
inline std::enable_if_t<
    std::is_arithmetic_v<typename std::iterator_traits<TIterator>::value_type>,
    typename std::iterator_traits<TIterator>::value_type>
square_distance(
        _In_ TIterator&& lbegin,
        _In_ TIterator&& lend,
        _In_ TIterator&& rbegin) noexcept {
    typedef typename std::iterator_traits<TIterator>::value_type value_type;
    return std::inner_product(
        std::forward<TIterator>(lbegin),
        std::forward<TIterator>(lend),
        std::forward<TIterator>(rbegin),
        static_cast<value_type>(0),
        std::plus<value_type>(),
        square_difference<value_type>);
}

/// <summary>
/// Computes the squared distances between all pairs of rows in a matrix.
/// </summary>
/// <typeparam name="TValue">The type of the elements in the matrix.</typeparam>
/// <typeparam name="Layout">The memory layout of the matrix.</typeparam>
/// <param name="result">Receives the distances, first from the first row to
/// all subsequent ones, then from the second one to all subsequent ones, etc.
/// This is effectively a triangular matrix omitting all duplicates.</param>
/// <param name="mat">The matrix to compute the distances for.</param>
/// <returns><paramref name="result" />.</returns>
template<class TValue, matrix_layout Layout>
std::enable_if_t<std::is_arithmetic_v<TValue>, std::vector<TValue>&>
square_row_distances(_Out_ std::vector<TValue>& result,
    _In_ const matrix<TValue, Layout>& mat);

LHS_DETAIL_NAMESPACE_END

#include "visus/lhs/distance.inl"

#endif /* !defined(_LHS_SQUARE_DISTANCE_H) */
