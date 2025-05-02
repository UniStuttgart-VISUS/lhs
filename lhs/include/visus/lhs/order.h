// <copyright file="order.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_ORDER_H)
#define _LHS_ORDER_H
#pragma once

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iterator>
#include <numeric>
#include <type_traits>
#include <vector>

#include "visus/lhs/api.h"


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Determines the order of the elements in the specified range by the given
/// <typeparamref name="TLess" /> function without modifying the range itself.
/// </summary>
/// <typeparam name="TIterator">An iterator over the item to determine the order
/// of. The iterator must be a random access iterator.</typeparam>
/// <typeparam name="TLess">A function that determines whether which of the
/// iterated items is smaller.</typeparam>
/// <param name="indices">Receives the zero-based indices of the sorted range
/// [<paramref name="begin" />, <paramref name="end" />[. Callers should not
/// reserve the array as the function must do this anyways.</param>
/// <param name="begin">An iterator for the begin of the range of items to
/// determine the order of.</param>
/// <param name="end">An iterator past the range of items to determine the
/// order of.</param>
/// <param name="less">A predicate which determines which of two of the iterated
/// items is the smaller one.</param>
template<class TIterator, class TLess>
void order_by(_Inout_ std::vector<std::size_t>& indices,
    _In_ const TIterator begin,
    _In_ const TIterator end,
    _In_ const TLess& less);

/// <summary>
/// Determines the order of the elements in the specified range by the given
/// <typeparamref name="TLess" /> function without modifying the range itself.
/// </summary>
/// <typeparam name="TIterator">An iterator over the item to determine the order
/// of. The iterator must be a random access iterator.</typeparam>
/// <typeparam name="TLess">A function that determines whether which of the
/// iterated items is smaller.</typeparam>
/// <param name="begin">An iterator for the begin of the range of items to
/// determine the order of.</param>
/// <param name="end">An iterator past the range of items to determine the
/// order of.</param>
/// <param name="less">A predicate which determines which of two of the iterated
/// items is the smaller one.</param>
/// <returns>The zero-based indices of the sorted range range
/// [<paramref name="begin" />, <paramref name="end" />[.</returns>
template<class TIterator, class TLess>
inline std::vector<std::size_t> order_by(
        _In_ TIterator&& begin,
        _In_ TIterator&& end,
        _In_ TLess&& less) {
    std::vector<std::size_t> retval;
    order_by(retval,
        std::forward<TIterator>(begin),
        std::forward<TIterator>(end),
        std::forward<TLess>(less));
    return retval;
}

/// <summary>
/// Determines the order of the elements in the specified range without
/// modifying the range itself.
/// </summary>
/// <typeparam name="TIterator">An iterator over the item to determine the order
/// of. The iterator must be a random access iterator.</typeparam>
/// <param name="indices">Receives the zero-based indices of the sorted range
/// [<paramref name="begin" />, <paramref name="end" />[. Callers should not
/// reserve the array as the function must do this anyways.</param>
/// <param name="begin">An iterator for the begin of the range of items to
/// determine the order of.</param>
/// <param name="end">An iterator past the range of items to determine the
/// order of.</param>
template<class TIterator>
inline void order(_Inout_ std::vector<std::size_t>& indices,
        _In_ const TIterator begin,
        _In_ const TIterator end) {
    typedef typename std::iterator_traits<TIterator>::value_type value_type;
    order_by(indices, begin, end, std::less<value_type>());
}

/// <summary>
/// Determines the order of the elements in the specified range without
/// modifying the range itself.
/// </summary>
/// <typeparam name="TIterator">An iterator over the item to determine the order
/// of. The iterator must be a random access iterator.</typeparam>
/// <param name="begin">An iterator for the begin of the range of items to
/// determine the order of.</param>
/// <param name="end">An iterator past the range of items to determine the
/// order of.</param>
/// <returns>The zero-based indices of the sorted rangerange
/// [<paramref name="begin" />, <paramref name="end" />[.</returns>
template<class TIterator>
inline std::vector<std::size_t> order(
        _In_ TIterator&& begin,
        _In_ TIterator&& end) {
    typedef typename std::iterator_traits<TIterator>::value_type value_type;
    std::vector<std::size_t> retval;
    order_by(retval,
        std::forward<TIterator>(begin),
        std::forward<TIterator>(end),
        std::less<value_type>());
    return retval;
}

/// <summary>
/// Creates a order from zero to the size of <paramref name="indices" /> that is
/// based on sampling the given <paramref name="distribution" /> using the given
/// <paramref name="rng" />.
/// </summary>
/// <typeparam name="TLess">A function that determines whether which of the
/// generated random items is smaller.</typeparam>
/// <typeparam name="TDist">The type of the distribution to sample the random
/// items from.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <param name="indices">The buffer receiving the generated permutation. This
/// buffer also determines the size of the permutation.</param>
/// <param name="buffer">A working buffer to create the random numbers. This is
/// provided to the method in order to allow callers reduce the number of
/// reallocations required in loops using this function.</param>
/// <param name="less">A predicate which determines which of two of the iterated
/// items is the smaller one.</param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <param name="distribution">The distribution to be sampled.</param>
/// <returns><paramref name="indices" />.</returns>
template<class TLess, class TRng, class TDist>
std::vector<std::size_t>& random_order_by(
    _Inout_ std::vector<std::size_t>& indices,
    _In_ std::vector<typename TDist::result_type>& buffer,
    _In_ TLess&& less,
    _In_ TRng& rng,
    _In_ TDist& distribution);

/// <summary>
/// Creates a order from zero to the size of <paramref name="indices" /> that is
/// based on sampling the given <paramref name="distribution" /> using the given
/// <paramref name="rng" />.
/// </summary>
/// <typeparam name="TDist">The type of the distribution to sample the random
/// items from.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <param name="indices">The buffer receiving the generated permutation. This
/// buffer also determines the size of the permutation.</param>
/// <param name="buffer">A working buffer to create the random numbers. This is
/// provided to the method in order to allow callers reduce the number of
/// reallocations required in loops using this function.</param>
/// <param name="less">A predicate which determines which of two of the iterated
/// items is the smaller one.</param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <param name="distribution">The distribution to be sampled.</param>
/// <returns><paramref name="indices" />.</returns>
template<class TRng, class TDist>
inline std::vector<std::size_t>& random_order(
        _Inout_ std::vector<std::size_t>& indices,
        _In_ std::vector<typename TDist::result_type>& buffer,
        _In_ TRng& rng,
        _In_ TDist& distribution) {
    return random_order_by(indices,
        buffer,
        std::less<typename TDist::result_type>(),
        rng,
        distribution);
}

/// <summary>
/// Create a random index sequence of the specified size.
/// </summary>
/// <remarks>
/// The random order is determined by whatever <c>std::shuffle</c> does with
/// the given <paramref name="rng" />.
/// </remarks>
/// <typeparam name="TValue">The type of the indices, which must be an integral
/// number.</typeparam>
/// <typeparam name="TRng">The type of the random generator to be used.
/// </typeparam>
/// <param name="indices">The vector receving the random sequence.</param>
/// <param name="n">The length of the sequence.</param>
/// <param name="rng">The random number generator.</param>
/// <returns><paramref name="indices" />.</returns>
template<class TValue, class TRng>
inline std::enable_if_t<std::is_integral_v<TValue>, std::vector<TValue>&>
random_order(_Inout_ std::vector<TValue>& indices,
        _In_ const std::size_t n,
        _In_ TRng&& rng) {
    indices.resize(n);
    std::iota(indices.begin(), indices.end(), static_cast<TValue>(0));
    std::shuffle(indices.begin(), indices.end(), std::forward<TRng>(rng));
    return indices;
}

/// <summary>
/// Create a random index sequence of the specified size.
/// </summary>
/// <remarks>
/// The random order is determined by whatever <c>std::shuffle</c> does with
/// the given <paramref name="rng" />.
/// </remarks>
/// <typeparam name="TValue">The type of the indices, which must be an integral
/// number.</typeparam>
/// <typeparam name="TRng">The type of the random generator to be used.
/// </typeparam>
/// <param name="n">The length of the sequence.</param>
/// <param name="rng">The random number generator.</param>
/// <returns>A random permutation of [0, <paramref name="indices" />].</returns>
template<class TValue, class TRng>
inline std::enable_if_t<std::is_integral_v<TValue>, std::vector<TValue>>
random_order(_In_ const std::size_t n, TRng&& rng) {
    std::vector<TValue> retval;
    return random_order(retval, n, std::forward<TRng>(rng));
}

/// <summary>
/// Create a random index sequence of the specified size.
/// </summary>
/// <remarks>
/// The random order is determined by whatever <c>std::shuffle</c> does with
/// the given <c>std::mt19937</c> random number generator that has been
/// initialised using the <c>std::random_device</c>.
/// </remarks>
/// <typeparam name="TValue">The type of the indices, which must be an integral
/// number.</typeparam>
/// <param name="n">The length of the sequence.</param>
/// <returns>A random permutation of [0, <paramref name="indices" />].</returns>
template<class TValue>
inline std::enable_if_t<std::is_integral_v<TValue>, std::vector<TValue>>
random_order(_In_ const std::size_t n) {
    std::vector<TValue> retval;
    std::random_device rd;
    std::mt19937 rng(rd());
    return random_order(retval, n, rng);
}

LHS_DETAIL_NAMESPACE_END

#include "visus/lhs/order.inl"

#endif /* !defined(_LHS_ORDER_H) */
