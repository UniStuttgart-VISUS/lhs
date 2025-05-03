// <copyright file="valid.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_VALID_H)
#define _LHS_VALID_H
#pragma once

#include <cassert>
#include <cstdlib>
#include <stdexcept>

#include "visus/lhs/matrix.h"


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Answer whether <paramref name="lhs" /> is (likely) a valid Latin Hypercube
/// sample based on the heuristic from
/// https://github.com/bertcarnell/lhslib/blob/557bec455c5bf2d20438bbace2096c2a7e3823ff/src/lhslib/utilityLHS.cpp#L25-L53
/// </summary>
/// <typeparam name="Layout">The memory layout of the matrix.</typeparam>
/// <param name="lhs">A Latin Hypercube sample.</param>
/// <returns><c>true</c> if the sample is valid, <c>false</c> otherwise.
/// </returns>
template<matrix_layout Layout>
bool valid(_In_ const matrix<std::size_t, Layout>& lhs) noexcept {
    const auto n = lhs.rows();
    const auto k = lhs.columns();
    const auto expected = n * (n + 1) / 2;

    for (std::size_t c = 0; c < k; ++c) {
        std::size_t sum = 0;

        for (std::size_t r = 0; r < n; ++r) {
            // Note: we use zero-based indexing, so we need to add one to each
            // of the elements.
            sum += (lhs(r, c) + 1);
        }

        if (sum != expected) {
            return false;
        }
    }

    return true;
}

/// <summary>
/// Answer whether the given matrix is a valid Latin hypercube sample from
/// a unit hypercube according to the method at
/// https://github.com/bertcarnell/lhslib/blob/557bec455c5bf2d20438bbace2096c2a7e3823ff/src/lhslib/utilityLHS.cpp#L55-L68
/// </summary>
/// <typeparam name="TValue">The type of the matrix elements, which must be a
/// floating-point number.</typeparam>
/// <typeparam name="Layout">The memory layout of the matrix.</typeparam>
/// <param name="lhs">A Latin Hypercube sample.</param>
/// <returns><c>true</c> if the sample is valid, <c>false</c> otherwise.
/// </returns>
/// <exception cref="std::invalid_argument">If the sample is not from a unit
/// hypercube. This method cannot work on scaled samples.</exception>
template<class TValue, matrix_layout Layout>
std::enable_if_t<std::is_floating_point_v<TValue>, bool> valid(
        _In_ const matrix<TValue, Layout>& lhs) {
    const auto n = static_cast<TValue>(lhs.rows());
    matrix<std::size_t, Layout> indices(lhs.rows(), lhs.columns());

    auto oit = indices.begin();
    for (auto it = lhs.begin(), e = lhs.end(); it != e; ++it) {
        if ((*it < 0.0) || (*it > 1.0)) {
            throw std::invalid_argument("The sample must be from a unit "
                "hypercube.");
        }

        // Note: we assume zero-based indexing, so the integer variant will
        // add one for us.
        *oit++ = static_cast<std::size_t>(floor(n * *it));
    }

    return valid(indices);
}

LHS_DETAIL_NAMESPACE_END


#if (defined(DEBUG) || defined(_DEBUG))
#define ASSERT_VALID_LHS(lhs) assert(LHS_DETAIL_NAMESPACE::valid(lhs))
#else /* (defined(DEBUG) || defined(_DEBUG)) */
#define ASSERT_VALID_LHS(lhs) (static_cast<void>(0))
#endif /* (defined(DEBUG) || defined(_DEBUG)) */

#endif /* !defined(_LHS_VALID_H) */
