// <copyright file="range.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_RANGE_H)
#define _LHS_RANGE_H
#pragma once

#include <algorithm>

#include "visus/lhs/api.h"


LHS_NAMESPACE_BEGIN

/// <summary>
/// Represents an numeric range.
/// </summary>
/// <typeparam name="TValue">The type of the numbers.</typeparam>
template<class TValue> class range final {

public:

    /// <summary>
    /// The type of the numbers.
    /// </summary>
    typedef TValue value_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="begin">The begin of the range. If this is larger than the
    /// <paramref name="end" />, the values will be swapped.</param>
    /// <param name="end">The end of the range. if this is smaller than the
    /// <paramref name="begin" />, the values will be swapped.</param>
    inline range(_In_ const value_type begin = static_cast<value_type>(0),
            _In_ const value_type end = static_cast<value_type>(0)) noexcept
        : _begin((std::min)(begin, end)),
            _end((std::max)(begin, end)) { }

    /// <summary>
    /// Answer the begin of the range.
    /// </summary>
    /// <returns>The begin of the range, which is guaranteed to be at most the
    /// same as <see cref="end" />.</returns>
    inline constexpr value_type begin(void) const noexcept {
        return this->_begin;
    }

    /// <summary>
    /// Answer whether the range is empty, i.e. the begin and end are the same.
    /// </summary>
    /// <returns><c>true</c> if the begin and the end are the same,
    /// <c>false</c> otherwise.</returns>
    inline constexpr auto empty(void) const noexcept {
        return (this->_begin == this->_end);
    }

    /// <summary>
    /// Answer the distance between the begin and the end of the range.
    /// </summary>
    /// <returns>The distance between the begin and the end of the range.
    /// </returns>
    inline constexpr value_type distance(void) const noexcept {
        return (this->_end - this->_begin);
    }

    /// <summary>
    /// Answer the end of the range.
    /// </summary>
    /// <returns>The end of the range, which is guaranteed to be at least the
    /// same as <see cref="begin" />.</returns>
    inline constexpr value_type end(void) const noexcept {
        return this->_end;
    }

private:

    value_type _begin;
    value_type _end;
};


/// <summary>
/// Creates a new range from <paramref name="begin" /> to
/// <paramref name="end" />.
/// </summary>
/// <typeparam name="TValue">The type of the numbers.</typeparam>
/// <param name="begin">The begin of the range. If this is larger than the
/// <paramref name="end" />, the values will be swapped.</param>
/// <param name="end">The end of the range. if this is smaller than the
/// <paramref name="begin" />, the values will be swapped.</param>
/// <returns>The range between <paramref name="begin" /> and
/// <paramref name="end" />.</returns>
template<class TValue>
inline constexpr range<TValue> make_range(_In_ const TValue begin,
        _In_ const TValue end) noexcept {
    return range<TValue>(begin, end);
}

/// <summary>
/// Creates a new range from <paramref name="begin" /> to
/// <paramref name="begin" /> + <paramref name="end" />.
/// </summary>
/// <typeparam name="TValue">The type of the numbers.</typeparam>
/// <param name="begin">The begin of the range.</param>
/// <param name="distance">The length of the range.</param>
/// <returns>The range between <paramref name="begin" /> and
/// <paramref name="begin" /> + <paramref name="distance" />.</returns>
template<class TValue>
inline constexpr range<TValue> range_from_distance(_In_ const TValue begin,
    _In_ const TValue distance) noexcept {
    return range<TValue>(begin, begin + distance);
}

LHS_NAMESPACE_END

#endif /* !defined(_LHS_RANGE_H) */
