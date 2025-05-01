// <copyright file="order.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_ORDER_H)
#define _LHS_ORDER_H
#pragma once

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <numeric>
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
/// <param name="indices">Receives the <paramref name="offset" />-based indices
/// of the sorted range [<paramref name="begin" />, <paramref name="end" />[.
/// Callers should not reserve the array as the function must do this anyways.
/// </param>
/// <param name="begin">An iterator for the begin of the range of items to
/// determine the order of.</param>
/// <param name="end">An iterator past the range of items to determine the
/// order of.</param>
/// <param name="less">A predicate which determines which of two of the iterated
/// items is the smaller one.</param>
/// <param name="offset">An offset added to all indices generated. This
/// parameter defaults to zero.</param>
template<class TIterator, class TLess>
void order_by(_Inout_ std::vector<std::size_t>& indices,
    _In_ const TIterator begin,
    _In_ const TIterator end,
    _In_ const TLess& less,
    _In_ const std::size_t offset = 0);

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
/// <param name="offset">An offset added to all indices generated. This
/// parameter defaults to zero.</param>
/// <returns>The <paramref name="offset" />-based indices of the sorted range
/// range [<paramref name="begin" />, <paramref name="end" />[.</returns>
template<class TIterator, class TLess>
inline std::vector<std::size_t> order_by(
        _In_ TIterator&& begin,
        _In_ TIterator&& end,
        _In_ TLess&& less,
        _In_ const std::size_t offset = 0) {
    std::vector<std::size_t> retval;
    order_by(retval,
        std::forward<TIterator>(begin),
        std::forward<TIterator>(end),
        std::forward<TLess>(less),
        offset);
    return retval;
}

/// <summary>
/// Determines the order of the elements in the specified range without
/// modifying the range itself.
/// </summary>
/// <typeparam name="TIterator">An iterator over the item to determine the order
/// of. The iterator must be a random access iterator.</typeparam>
/// <param name="indices">Receives the <paramref name="offset" />-based indices
/// of the sorted range [<paramref name="begin" />, <paramref name="end" />[.
/// Callers should not reserve the array as the function must do this anyways.
/// </param>
/// <param name="begin">An iterator for the begin of the range of items to
/// determine the order of.</param>
/// <param name="end">An iterator past the range of items to determine the
/// order of.</param>
/// <param name="offset">An offset added to all indices generated. This
/// parameter defaults to zero.</param>
template<class TIterator>
inline void order(_Inout_ std::vector<std::size_t>& indices,
        _In_ const TIterator begin,
        _In_ const TIterator end,
        _In_ const std::size_t offset = 0) {
    typedef typename std::iterator_traits<TIterator>::value_type value_type;
    order_by(indices, begin, end, std::less<value_type>(), offset);
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
/// <param name="offset">An offset added to all indices generated. This
/// parameter defaults to zero.</param>
/// <returns>The <paramref name="offset" />-based indices of the sorted range
/// range [<paramref name="begin" />, <paramref name="end" />[.</returns>
template<class TIterator>
inline std::vector<std::size_t> order(
        _In_ TIterator&& begin,
        _In_ TIterator&& end,
        _In_ const std::size_t offset = 0) {
    typedef typename std::iterator_traits<TIterator>::value_type value_type;
    std::vector<std::size_t> retval;
    order_by(retval,
        std::forward<TIterator>(begin),
        std::forward<TIterator>(end),
        std::less<value_type>(),
        offset);
    return retval;
}

LHS_DETAIL_NAMESPACE_END

#include "visus/lhs/order.inl"

#endif /* !defined(_LHS_ORDER_H) */
