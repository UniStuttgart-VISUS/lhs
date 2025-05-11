// <copyright file="maximin.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_MAXIMIN_H)
#define _LHS_MAXIMIN_H
#pragma once

#include <algorithm>
#include <array>
#include <iterator>
#include <numeric>
#include <random>
#include <stdexcept>
#include <type_traits>

#include "visus/lhs/distance.h"
#include "visus/lhs/matrix.h"
#include "visus/lhs/order.h"
#include "visus/lhs/valid.h"


LHS_NAMESPACE_BEGIN

/// <summary>
/// Optimises an exisiting Latin Hypercube sample by maximising the minimum
/// distance between the rows (samples).
/// </summary>
/// <typeparam name="TValue">The type of the matrix elements.</typeparam>
/// <typeparam name="Layout">The memory layout of the matrix. It is reasonable
/// to use row-major matrices here, because in this case, the parameter values
/// for a sample are laid out contiguously in memory.</typeparam>
/// <param name="lhs">The sample to be optimised in place.</param>
/// <param name="epsilon">The minimum improvement that needs to be achieved in
/// each iteration in order to continue.</param>
/// <param name="iterations">The maximum number of iterations.</param>
/// <returns><paramref name="lhs" />.</returns>
template<class TValue, matrix_layout Layout>
std::enable_if_t<std::is_arithmetic_v<TValue>, matrix<TValue, Layout>&>
maximin(_Inout_ matrix<TValue, Layout>& lhs,
    _In_ const TValue epsilon = static_cast<TValue>(0.05),
    _In_ const std::size_t iterations = 128);

/// <summary>
/// Creates a maximin-optimised Latin Hypercube sample of zero-based indices.
/// </summary>
/// <typeparam name="Layout">The memory layout of the matrix. It is reasonable
/// to use row-major matrices here, because in this case, the parameter values
/// for a sample are laid out contiguously in memory.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate random
/// numbers.</typeparam>
/// <param name="result">The matrix to receive the Latin Hypercube sample. The
/// values are ignored on entry. However, the number of rows represents the
/// number of samples for each parameter whereas the number of columns
/// represents the number of parameters.</param>
/// <param name="duplication">The duplication factor which affects the number of
/// points that the optimisation algorithm has to choose from.</param>
/// <param name="rng">The maximin number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <param name="distribution">The distribution to draw samples from, which
/// typically is a uniform real distribution creating numbers within [0, 1].
/// </param>
/// <returns><paramref name="result" />.</returns>
template<matrix_layout Layout, class TRng, class TDist>
matrix<std::size_t, Layout> maximin(
    _Inout_ matrix<std::size_t, Layout>& result,
    _In_ const std::size_t duplication,
    _In_ TRng& rng,
    _In_ TDist& distribution);

/// <summary>
/// Creates a maximin-optimised Latin Hypercube sample of zero-based indices.
/// </summary>
/// <typeparam name="Layout">The memory layout of the matrix. It is reasonable
/// to use row-major matrices here, because in this case, the parameter values
/// for a sample are laid out contiguously in memory.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <param name="result">The matrix to receive the Latin Hypercube sample. The
/// values are ignored on entry. However, the number of rows represents the
/// number of samples for each parameter whereas the number of columns
/// represents the number of parameters.</param>
/// <param name="duplication">The duplication factor which affects the number of
/// points that the optimisation algorithm has to choose from.</param>
/// <param name="rng">The maximin number generator used to sample a uniform
/// real distribution within [0, 1].</param>
/// <returns><paramref name="result" />.</returns>
template<matrix_layout Layout, class TRng>
inline matrix<std::size_t, Layout> maximin(
        _Inout_ matrix<std::size_t, Layout>& result,
        _In_ const std::size_t duplication,
        _In_ TRng& rng) {
    return maximin(result, duplication, rng,
        std::uniform_real_distribution<float>());
}

/// <summary>
/// Creates a maximin-optimised Latin Hypercube sample of zero-based indices.
/// </summary>
/// <typeparam name="Layout">The memory layout of the matrix. It is reasonable
/// to use row-major matrices here, because in this case, the parameter values
/// for a sample are laid out contiguously in memory.</typeparam>
/// <param name="result">The matrix to receive the Latin Hypercube sample. The
/// values are ignored on entry. However, the number of rows represents the
/// number of samples for each parameter whereas the number of columns
/// represents the number of parameters.</param>
/// <param name="duplication">The duplication factor which affects the number of
/// points that the optimisation algorithm has to choose from.</param>
/// <returns><paramref name="result" />.</returns>
template<matrix_layout Layout, class TRng>
inline matrix<std::size_t, Layout> maximin(
        _Inout_ matrix<std::size_t, Layout>& result,
        _In_ const std::size_t duplication) {
    std::random_device rd;
    std::mt19937 rng(rd());
    return maximin(result, duplication, rng);
}

/// <summary>
/// Creates a maximin-optimised Latin Hypercube sample of zero-based indices.
/// </summary>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate random
/// numbers.</typeparam>
/// <param name="samples">The number of samples per parameter (rows) of the
/// Latin hypercube sample.</param>
/// <param name="parameters">The number of parameters (columns) in the
/// Latin hypercube sample.</param>
/// <param name="duplication">The duplication factor which affects the number of
/// points that the optimisation algorithm has to choose from.</param>
/// <param name="rng">The maximin number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <param name="distribution">The distribution to draw samples from, which
/// typically is a uniform real distribution creating numbers within [0, 1].
/// </param>
/// <returns>The hypercube sample.</returns>
template<class TRng, class TDist>
inline matrix<std::size_t> maximin(_In_ const std::size_t samples,
        _In_ const std::size_t parameters,
        _In_ const std::size_t duplication,
        _In_ TRng& rng,
        _In_ TDist& distribution) {
    matrix<std::size_t> result(samples, parameters);
    return maximin(result, duplication, rng, distribution);
}

/// <summary>
/// Creates a maximin-optimised Latin Hypercube sample of zero-based indices.
/// </summary>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <param name="samples">The number of samples per parameter (rows) of the
/// Latin hypercube sample.</param>
/// <param name="parameters">The number of parameters (columns) in the
/// Latin hypercube sample.</param>
/// <param name="duplication">The duplication factor which affects the number of
/// points that the optimisation algorithm has to choose from.</param>
/// <param name="rng">The maximin number generator used to sample a uniform
/// real distribution within [0, 1].</param>
/// <returns>The hypercube sample.</returns>
template<class TRng>
inline matrix<std::size_t> maximin(_In_ const std::size_t samples,
        _In_ const std::size_t parameters,
        _In_ const std::size_t duplication,
        _In_ TRng& rng) {
    matrix<std::size_t> result(samples, parameters);
    return maximin(result, duplication, rng,
        std::uniform_real_distribution<float>());
}

/// <summary>
/// Creates a maximin-optimised Latin Hypercube sample of zero-based indices.
/// </summary>
/// <param name="samples">The number of samples per parameter (rows) of the
/// Latin hypercube sample.</param>
/// <param name="parameters">The number of parameters (columns) in the
/// Latin hypercube sample.</param>
/// <param name="duplication">The duplication factor which affects the number of
/// points that the optimisation algorithm has to choose from.</param>
/// <returns>The hypercube sample.</returns>
inline matrix<std::size_t> maximin(_In_ const std::size_t samples,
        _In_ const std::size_t parameters,
        _In_ const std::size_t duplication) {
    std::random_device rd;
    std::mt19937 rng(rd());
    return maximin(samples, parameters, duplication, rng);
}

LHS_NAMESPACE_END

LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Initialises the availability matrix for constructing a maximin LHS sample.
/// </summary>
/// <typeparam name="Layout"></typeparam>
/// <param name="mat"></param>
/// <returns></returns>
template<matrix_layout Layout>
matrix<std::size_t, Layout>& initialise_availability(
    _Inout_ matrix<std::size_t, Layout>& mat);

LHS_DETAIL_NAMESPACE_END

#include "visus/lhs/maximin.inl"

#endif /* !defined(_LHS_MAXIMIN_H) */
