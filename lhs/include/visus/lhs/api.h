// <copyright file="api.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_API_H)
#define _LHS_API_H
#pragma once

#include "visus/lhs/macro_concat.h"


/******************************************************************************\
 * Update the ABI version (i.e. if something in the interface changes) here:  *
\******************************************************************************/
#define LHS_ABI_MAJOR 0
#define LHS_ABI_MINOR 1


/// <summary>
/// Creates the full ABI versison string.
/// </summary>
/// <param name="mj">The major version of the ABI.</param>
/// <param name="mn">The minor version of the ABI.</param>
#define LHS_ABI_VERSION(mj, mn) LHS_CONCAT(mj, LHS_CONCAT(_, mn))


/// <summary>
/// Creates the name of the namespace for the specified ABI version.
/// </summary>
/// <param name="mj">The major version of the ABI.</param>
/// <param name="mn">The minor version of the ABI.</param>
#define LHS_ABI_NAMESPACE(mj, mn) LHS_CONCAT(v, LHS_ABI_VERSION(mj, mn))


/// <summary>
/// Creates the name of the current ABI namespace.
/// </summary>
/// <remarks>
/// Use this macro when defining implementations in cpp or inline files.
/// </remarks>
#define LHS_NAMESPACE visus::lhs::\
LHS_ABI_NAMESPACE(LHS_ABI_MAJOR, LHS_ABI_MINOR)


/// <summary>
/// Creates the name of the namespace for the implementation details.
/// </summary>
/// <remarks>
/// Use this macro when defining implementations in cpp or inline files.
/// </remarks>
#define LHS_DETAIL_NAMESPACE LHS_NAMESPACE::detail


/// <summary>
/// Helper for opening the namespace <paramref name="n" />.
/// </summary>
#define _LHS_NAMESPACE_BEGIN(n) namespace n {


/// <summary>
/// Marks the begin of the current ABI namespace.
/// </summary>
#define LHS_NAMESPACE_BEGIN \
_LHS_NAMESPACE_BEGIN(visus)\
_LHS_NAMESPACE_BEGIN(lhs)\
inline _LHS_NAMESPACE_BEGIN(\
    LHS_ABI_NAMESPACE(LHS_ABI_MAJOR, LHS_ABI_MINOR))

/// <summary>
/// Marks the end of the current ABI namespace.
/// </summary>
#define LHS_NAMESPACE_END } } }

/// <summary>
/// Marks the begin of the namespace for implementation details.
/// </summary>
#define LHS_DETAIL_NAMESPACE_BEGIN \
LHS_NAMESPACE_BEGIN _LHS_NAMESPACE_BEGIN(detail)

/// <summary>
/// Marks the end of the namespace for implementation details.
/// </summary>
#define LHS_DETAIL_NAMESPACE_END } LHS_NAMESPACE_END


#if defined(_WIN32)
#include <sal.h>
#else /* defined(_WIN32) */
#include "visus/lhs/nosal.h"
#endif /* defined(_WIN32) */

#endif /* !defined(_LHS_API_H) */
