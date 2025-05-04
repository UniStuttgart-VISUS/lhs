// <copyright file="is_range.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_IS_RANGE_H)
#define _LHS_IS_RANGE_H
#pragma once

#include <type_traits>

#include "visus/lhs/range.h"


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Answer whether <paramref name="TType" /> is an instance of
/// <see cref="range{TType}" />.
/// </summary>
/// <typeparam name="TType">The type to be tested.</typeparam>
template<class TType> struct is_range final : std::false_type { };

/// <summary>
/// Specialisation for actual ranges.
/// </summary>
/// <typeparam name="TType">The numeric type of the range.</typeparam>
template<class TType> struct is_range<range<TType>> final : std::true_type { };

/// <summary>
/// Answer whether <paramref name="TType" /> is an instance of
/// <see cref="range{TType}" />.
/// </summary>
/// <typeparam name="TType">The type to be tested.</typeparam>
template<class TType>
constexpr bool is_range_v = typename is_range<TType>::value;

LHS_DETAIL_NAMESPACE_END

#endif /* !defined(_LHS_IS_RANGE_H) */
