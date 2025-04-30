// <copyright file="matrix_layout.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_MATRIX_LAYOUT_H)
#define _LHS_MATRIX_LAYOUT_H
#pragma once

#include "visus/lhs/api.h"


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Specifies possible ways to store a matrix in memory.
/// </summary>
enum class matrix_layout {

    /// <summary>
    /// The matrix is stored in column-major order (colexicographical order).
    /// </summary>
    /// <remarks>
    /// In this layout, consecutive elements in a column are stored next to each
    /// other in memory.
    /// </remarks>
    column_major,

    /// <summary>
    /// The matrix is stored in row-major order (lexicographical order).
    /// </summary>
    /// <remarks>
    /// This is the native layout for C/C++ arrays where consecutive elements in
    /// a row are stored next to each other in memory.
    /// </remarks>
    row_major
};

LHS_DETAIL_NAMESPACE_END

#endif /* !defined(_LHS_MATRIX_LAYOUT_H) */
