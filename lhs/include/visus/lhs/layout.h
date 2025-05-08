// <copyright file="layout.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_LAYOUT_H)
#define _LHS_LAYOUT_H
#pragma once

#include "visus/lhs/matrix_layout.h"


/* Forward declarations. */
LHS_NAMESPACE_BEGIN
template<class, matrix_layout> class matrix;
LHS_NAMESPACE_END;

LHS_DETAIL_NAMESPACE_BEGIN
template<class, matrix_layout> class matrix_iterator;
LHS_DETAIL_NAMESPACE_END


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Derives the memory layout of the given <typeparamref name="TMatrix" />
/// type.
/// </summary>
/// <typeparam name="TMatrix">The matrix to determine the layout of.</typeparam>
template<class TMatrix> struct layout final { };

/// <summary>
/// Specialisation for actual matrices.
/// </summary>
/// <typeparam name="TValue">The type of the elements in the matrix.</typeparam>
/// <typeparamref name="Layout">The layout of the matrix.</typeparam>
template<class TValue, matrix_layout Layout>
struct layout<matrix<TValue, Layout>> final {
    static constexpr const matrix_layout value = Layout;
};

/// <summary>
/// Specialisation for actual matrices.
/// </summary>
/// <typeparam name="TValue">The type of the elements in the matrix.</typeparam>
/// <typeparamref name="Layout">The layout of the matrix.</typeparam>
template<class TValue, matrix_layout Layout>
struct layout<const matrix<TValue, Layout>> final {
    static constexpr const matrix_layout value = Layout;
};

/// <summary>
/// Specialisation for matrix iterators.
/// </summary>
/// <typeparam name="TValue">The type of the elements in the matrix.</typeparam>
/// <typeparamref name="Layout">The layout of the matrix.</typeparam>
template<class TMatrix, matrix_layout Layout>
struct layout<matrix_iterator<TMatrix, Layout>> final {
    static constexpr const matrix_layout value = Layout;
};

/// <summary>
/// Derives the memory layout of the given <typeparamref name="TMatrix" />
/// type.
/// </summary>
/// <typeparam name="TMatrix">The matrix to determine the layout of.</typeparam>
template<class TMatrix>
constexpr matrix_layout layout_v = layout<TMatrix>::value;

/// <summary>
/// Derives the inverse matrix layout of the given
/// <typeparamref name="Layout" />.
/// </summary>
/// <typeparam name="Layout">The matrix layout to invert.</typeparam>
template<matrix_layout Layout>
struct invert_layout final {
    static constexpr const matrix_layout value
        = (Layout == matrix_layout::row_major)
        ? matrix_layout::column_major
        : matrix_layout::row_major;
};

/// <summary>
/// Derives the inverse matrix layout of the given
/// <typeparamref name="Layout" />.
/// </summary>
/// <typeparam name="Layout">The matrix layout to invert.</typeparam>
template<matrix_layout Layout>
constexpr matrix_layout invert_layout_v = invert_layout<Layout>::value;

LHS_DETAIL_NAMESPACE_END

#endif /* !defined(_LHS_LAYOUT_H) */
