﻿// <copyright file="macro_concat.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_MACRO_CONCAT_H)
#define _LHS_MACRO_CONCAT_H
#pragma once


/// <summary>
/// A helper for implementing <see cref="LHS_CONCAT" />.
/// </summary>
#define _LHS_CONCAT(l, r) l ##r


/// <summary>
/// Concatenates two preprocessor symbols.
/// </summary>
/// <param name="l">The left-hand side operand.</param>
/// <param name="r">The right-hand side operand.</param>
#define LHS_CONCAT(l, r) _LHS_CONCAT(l, r)

#endif /* !defined(_LHS_MACRO_CONCAT_H) */
