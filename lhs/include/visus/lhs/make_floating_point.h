// <copyright file="make_floating_point.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_MAKE_FLOATING_POINT_H)
#define _LHS_MAKE_FLOATING_POINT_H
#pragma once

#include <type_traits>

#include "visus/lhs/api.h"


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Determines the floating-point type that has the same size as the given
/// numeric type.
/// </summary>
/// <typeparam name="TType">The type to get the matching floating-point type
/// for.</typeparam>
/// <typeparam name="IsFloat">Indicates that the type is already a
/// floating-point type.</typeparam>
/// <typeparam name="IsInt">Indicates that the type is an integral type.
/// </typeparam>
template<class TType,
    bool IsFloat = std::is_floating_point_v<TType>,
    bool IsInt = std::is_integral_v<TType>>
struct make_floating_point { };

/// <summary>
/// Specialisation for floating-point types.
/// </summary>
/// <typeparam name="TType">The type to get the matching floating-point type
/// for.</typeparam>
template<class TType> struct make_floating_point<TType, true, false> final {
    typedef TType type;
};


/// <summary>
/// Specialisation for integral types.
/// </summary>
/// <typeparam name="TType">The type to get the matching floating-point type
/// for.</typeparam>
template<class TType> struct make_floating_point<TType, false, true> final {
    typedef std::conditional_t<(sizeof(TType) <= sizeof(float)),
        float,
        double> type;
};

/// <summary>
/// Determines the floating-point type that has the same size as the given
/// numeric type.
/// </summary>
/// <typeparam name="TType">The type to get the matching floating-point type
/// for.</typeparam>
template<class TType>
using make_floating_point_t = typename make_floating_point<TType>::type;


LHS_DETAIL_NAMESPACE_END

#endif /* !defined(_LHS_MAKE_FLOATING_POINT_H) */
