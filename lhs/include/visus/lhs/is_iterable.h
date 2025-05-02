// <copyright file="is_iterable.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_IS_ITERABLE_H)
#define _LHS_IS_ITERABLE_H
#pragma once

#include <type_traits>

#include "visus/lhs/api.h"


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Tests whether <paramref name="TType" /> has a <c>begin</c> and <c>end</c>
/// method that returns something that can be dereferenced.
/// </summary>
/// <typeparam name="TType">The type to be tested.</typeparam>
/// <returns><c>std::true_type</c>.</returns>
template<class TType>
inline constexpr auto has_begin_end(int) -> decltype(
        std::declval<TType>().begin(),
        std::declval<TType>().end(),
        void(*std::begin(std::declval<TType&>())),
        std::true_type()) {
    return std::true_type();
}

/// <summary>
/// Overload for non-iterable types.
/// </summary>
/// <typeparam name="TType">The type to be tested.</typeparam>
/// <returns><c>std::false_type</c>.</returns>
template<class TType>
inline constexpr auto has_begin_end(...) -> std::false_type {
    return std::false_type();
}

/// <summary>
/// Answer whether <paramref name="TType" /> can be iterated over.
/// </summary>
/// <typeparam name="TType">The type to be tested.</typeparam>
template<class TType>
using is_iterable = decltype(has_begin_end<TType>(0));

/// <summary>
/// Answer whether <paramref name="TType" /> can be iterated over.
/// </summary>
/// <typeparam name="TType">The type to be tested.</typeparam>
template<class TType>
constexpr bool is_iterable_v = typename is_iterable<TType>::value;

LHS_DETAIL_NAMESPACE_END

#endif /* !defined(_LHS_IS_ITERABLE_H) */
