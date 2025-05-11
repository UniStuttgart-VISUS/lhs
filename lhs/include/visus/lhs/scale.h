// <copyright file="scale.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_SCALE_H)
#define _LHS_SCALE_H
#pragma once

#include <cassert>
#include <iterator>
#include <stdexcept>

#include "visus/lhs/is_range.h"
#include "visus/lhs/matrix.h"
#include "visus/lhs/valid.h"


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Converts a floating-point number in the range [0, 1] to a zero-based index.
/// </summary>
/// <typeparam name="TValue">A floating-point type.</typeparam>
/// <param name="value">A value within [0, 1].</param>
/// <param name="cnt">The total number of elements, which must be at least one.
/// </param>
/// <returns>A zero-based index into <paramref name="cnt" /> elements.</returns>
/// <exception cref="std::invalid_argument">If <paramref name="cnt" /> is less than
/// one or <paramref name="value" /> is not within [0, 1].</exception>
template<class TValue>
std::enable_if_t<std::is_floating_point_v<TValue>, std::size_t> scale(
    _In_ const TValue value, _In_ const std::size_t cnt);

/// <summary>
/// Scales the parameters of the given unit hypercube sample to the ranges
/// defined by the range <paramref name="begin" /> to </paramref name="end" />
/// in place.
/// </summary>
/// <typeparam name="TIterator">An iterator over floating-point
/// <see cref="range{TValue}" />s. The iterated type must be the type of the
/// matrix elements of <paramref name="lhs" /> at the same time.</typeparam>
/// <typeparam name="Layout">The matrix layout of <paramref name="lhs" />.
/// </typeparam>
/// <param name="lhs">The unit hypercube sample to be scaled. The number of
/// rows is the number of parameters, which must match the length of the
/// range <paramref name="begin" /> to <paramref name="end" />.</param>
/// <param name="begin">The begin of the range of parameter ranges which are
/// used to scale the distribution.</param>
/// <param name="end">The end of the range of parameter ranges. The distance
/// between <paramref name="begin" /> and <paramref name="end" /> must be equal
/// to the number of parameters (or number of columns in the matrix).</param>
/// <returns><paramref name="lhs" /> after scaling.</returns>
template<class TIterator, matrix_layout Layout>
std::enable_if_t<is_range_v<
        typename std::iterator_traits<TIterator>::value_type>
    && std::is_floating_point_v<
        typename std::iterator_traits<TIterator>::value_type::value_type>,
    matrix<
        typename std::iterator_traits<TIterator>::value_type::value_type,
        Layout>&>
scale(_Inout_ matrix<typename
    std::iterator_traits<TIterator>::value_type::value_type, Layout>& lhs,
    _In_ const TIterator begin,
    _In_ const TIterator end);

/// <summary>
/// Scales the parameters of the given unit hypercube sample to the integer
/// ranges by the range <paramref name="begin" /> to </paramref name="end" />.
/// The function will round to the nearest integer value.
/// </summary>
/// <typeparam name="TIterator">An iterator over the ranges of of the
/// parameters. The value iterated here is the type of the matrix elements
/// returned at the same time.</typeparam>
/// <typeparam name="Layout">The matrix layout of <paramref name="lhs" />. The
/// same layout will be used for the return value.</typeparam>
/// <typeparam name="TElement">A floating-point type used for the elements of
/// the unit hypercube sample <paramref name="lhs" />.</typeparam>
/// <param name="lhs">The unit hypercube sample to be scaled. The number of
/// rows is the number of parameters, which must match the length of the
/// range <paramref name="begin" /> to <paramref name="end" />.</param>
/// <param name="begin">The begin of the range of parameter ranges which are
/// used to scale the distribution.</param>
/// <param name="end">The end of the range of parameter ranges. The distance
/// between <paramref name="begin" /> and <paramref name="end" /> must be equal
/// to the number of parameters (or number of columns in the matrix).</param>
/// <returns>A scaled, integer variant of <paramref name="lhs" />.</returns>
template<class TIterator, matrix_layout Layout, class TElement>
std::enable_if_t<is_range_v<
        typename std::iterator_traits<TIterator>::value_type>
    && std::is_integral_v<
        typename std::iterator_traits<TIterator>::value_type::value_type>
    && std::is_floating_point_v<TElement>,
    matrix<typename std::iterator_traits<TIterator>::value_type::value_type,
        Layout>>
scale(_In_ const matrix<TElement, Layout>& lhs,
    _In_ const TIterator begin,
    _In_ const TIterator end);

/// <summary>
/// Scales the parameters of the given unit hypercube sample to the given 
/// exclusive integer index ranges specified by <paramref name="begin" /> to
/// <paramref name="end" />.
/// </summary>
/// <typeparam name="TIterator">An iterator over the size of the ranges to scale
/// the parameters to. The value iterated here is the type of the matrix
/// elements returned at the same time.
/// </typeparam>
/// <typeparam name="Layout">The matrix layout of <paramref name="lhs" />. The
/// same layout will be used for the return value.</typeparam>
/// <typeparam name="TElement">A floating-point type used for the elements of
/// the unit hypercube sample <paramref name="lhs" />.</typeparam>
/// <param name="lhs">The unit hypercube sample to be scaled. The number of
/// rows is the number of parameters, which must match the length of the
/// range <paramref name="begin" /> to <paramref name="end" />.</param>
/// <param name="begin">The begin of the range of parameter sizes. The range
/// from zero up to one before the specified size will be used to scale the
/// parameter values.</param>
/// <param name="end">The end of the range of parameter ranges. The distance
/// between <paramref name="begin" /> and <paramref name="end" /> must be equal
/// to the number of parameters (or number of columns in the matrix).</param>
/// <returns>A scaled, integer variant of <paramref name="lhs" />.</returns>
template<class TIterator, matrix_layout Layout, class TElement>
std::enable_if_t<std::is_integral_v<
        typename std::iterator_traits<TIterator>::value_type>
    && std::is_floating_point_v<TElement>,
    matrix<typename std::iterator_traits<TIterator>::value_type, Layout>>
scale(_In_ const matrix<TElement, Layout>& lhs,
    _In_ const TIterator begin,
    _In_ const TIterator end);

LHS_DETAIL_NAMESPACE_END

#include "visus/lhs/scale.inl"

#endif /* !defined(_LHS_SCALE_H) */
