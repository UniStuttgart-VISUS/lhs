// <copyright file="iteration_order.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_ITERATION_ORDER_H)
#define _LHS_ITERATION_ORDER_H
#pragma once

#include <type_traits>

#include "visus/lhs/layout.h"


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Determines the order for the <see cref="matrix_iterator{TMatrix}" /> when the
/// desired order should be <typeparamref name="Order" />.
/// </summary>
/// <typeparam name="TMatrix">The matrix to determine the iteration order for.
/// </typeparam>
/// <typeparam name="Order"><see cref="matrix_layout::row_major" /> to enumerate
/// the rows column by column, <see cref="matrix_layout::column_mahor" /> to
/// enumerate the columns row by row.</typeparam>
template<class TMatrix, matrix_layout Order>
struct iteration_order final : std::integral_constant<matrix_layout,
    (Order == layout_v<TMatrix>)
    ? layout_v<TMatrix>
    : invert_layout_v<layout_v<TMatrix>>> { };

/// <summary>
/// Determines the order for the <see cref="matrix_iterator{TMatrix}" /> when the
/// desired order should be <typeparamref name="Order" />.
/// </summary>
/// <typeparam name="TMatrix">The matrix to determine the iteration order for.
/// </typeparam>
/// <typeparam name="Order"><see cref="matrix_layout::row_major" /> to enumerate
/// the rows column by column, <see cref="matrix_layout::column_mahor" /> to
/// enumerate the columns row by row.</typeparam>
template<class TMatrix, matrix_layout Order>
constexpr auto iteration_order_v = iteration_order<TMatrix, Order>::value;

LHS_DETAIL_NAMESPACE_END

#endif /* !defined(_LHS_ITERATION_ORDER_H) */
