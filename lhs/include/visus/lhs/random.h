// <copyright file="random.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_RANDOM_H)
#define _LHS_RANDOM_H
#pragma once

#include <initializer_list>
#include <iterator>
#include <random>
#include <type_traits>

#include "visus/lhs/matrix.h"
#include "visus/lhs/order.h"
#include "visus/lhs/range.h"


LHS_NAMESPACE_BEGIN

/// <summary>
/// Fill <paramref name="result" /> with a Latin Hypercube sample.
/// </summary>
/// <typeparam name="Layout">The memory layout of the matrix. It is reasonable
/// to use row-major matrices here, because in this case, the parameter values
/// for a sample are laid out contiguously in memory.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate random
/// numbers.</typeparam>
/// <param name="result">The matrix to receive the Latin Hypercube sample. The
/// values are ignored on entry. However, the number of rows represents the
/// number of samples for each parameter whereas the number of columns represents
/// the number of parameters.</param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name"="distribution" />.</param>
/// <param name="distribution">The distribution used to sample the random
/// numbers from. This should be a uniform distribution. Note that the numbers
/// generated here are not directly part of the result, but only used for
/// ordering the indices randomly.</param>
/// <returns><paramref name="result" />.</returns>
template<matrix_layout Layout, class TRng, class TDist>
matrix<std::size_t, Layout>& random(
    _Inout_ matrix<std::size_t, Layout>& result,
    _In_ TRng& rng,
    _In_ TDist& distribution);

/// <summary>
/// Fill <paramref name="result" /> with a Latin Hypercube sample.
/// </summary>
/// <typeparam name="Layout">The memory layout of the matrix. It is reasonable
/// to use row-major matrices here, because in this case, the parameter values
/// for a sample are laid out contiguously in memory.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <param name="result">The matrix to receive the Latin Hypercube sample. The
/// values are ignored on entry. However, the number of rows represents the
/// number of samples for each parameter whereas the number of columns represents
/// the number of parameters.</param>
/// <param name="rng">The random number generator used to sample a uniform
/// real distribution within [0, 1].</param>
/// <returns><paramref name="result" />.</returns>
template<matrix_layout Layout, class TRng>
inline matrix<std::size_t, Layout>& random(
        _Inout_ matrix<std::size_t, Layout>& result,
        _In_ TRng&& rng) {
    return random(result,
        std::forward<TRng>(rng),
        std::uniform_real_distribution<float>());
}

/// <summary>
/// Create a Latin Hypercube sample.
/// </summary>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate random
/// numbers.</typeparam>
/// <param name="samples">The number of samples per parameter (rows) of the
/// Latin hypercube sample.</param>
/// <param name="parameters">The number of parameters (columns) in the
/// Latin hypercube sample.</param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name"="distribution" />.</param>
/// <param name="distribution">The distribution used to sample the random
/// numbers from. This should be a uniform distribution. Note that the numbers
/// generated here are not directly part of the result, but only used for
/// ordering the indices randomly.</param>
/// <returns></returns>
template<class TRng, class TDist>
inline matrix<std::size_t> random(
        _In_ const std::size_t samples,
        _In_ const std::size_t parameters,
        _In_ TRng&& rng,
        _In_ TDist&& distribution) {
    matrix<std::size_t> result(samples, parameters);
    return random(result,
        std::forward<TRng>(rng),
        std::forward<TDist>(distribution));
}

/// <summary>
/// Create a Latin Hypercube sample.
/// </summary>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <param name="samples">The number of samples per parameter (rows) of the
/// Latin hypercube sample.</param>
/// <param name="parameters">The number of parameters (columns) in the
/// Latin hypercube sample.</param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name"="distribution" />.</param>
/// <param name="rng">The random number generator used to sample a uniform
/// real distribution within [0, 1].</param>
/// <returns></returns>
template<class TRng>
inline matrix<std::size_t> random(
        _In_ const std::size_t samples,
        _In_ const std::size_t parameters,
        _In_ TRng&& rng) {
    matrix<std::size_t> result(samples, parameters);
    return random(result,
        std::forward<TRng>(rng),
        std::uniform_real_distribution<float>());
}

/// <summary>
/// Fill <paramref name="result" /> with a (uniformly distributed) stratified
/// sample from unit hypercube.
/// </summary>
/// <typeparam name="TValue">The type of values to be created, which must be a
/// floating point type.</typeparam>
/// <typeparam name="Layout">The memory layout of the matrix. It is reasonable
/// to use row-major matrices here, because in this case, the parameter values
/// for a sample are laid out contiguously in memory.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate random
/// numbers.</typeparam>
/// <param name="result"></param>
/// <param name="preserve_draw"></param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name"="distribution" />.</param>
/// <param name="distribution">The distribution to draw samples from, which
/// typically is a uniform real distribution creating numbers within [0, 1].
/// </param>
/// <returns><paramref name="result" />.</returns>
template<class TValue, matrix_layout Layout, class TRng, class TDist>
std::enable_if_t<std::is_floating_point_v<TValue>, matrix<TValue, Layout>&>
random(_Inout_ matrix<TValue, Layout>& result,
    _In_ const bool preserve_draw,
    _In_ TRng& rng,
    _In_ TDist& distribution);

/// <summary>
/// Create a (uniformly distributed) stratified sample from unit hypercube.
/// </summary>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate random
/// numbers.</typeparam>
/// <param name="samples"></param>
/// <param name="parameters"></param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name"="distribution" />.</param>
/// <param name="distribution">The distribution to draw samples from, which
/// typically is a uniform real distribution creating numbers within [0, 1].
/// </param>
/// <returns></returns>
template<class TRng, class TDist>
inline matrix<typename TDist::result_type> random(
        _In_ const std::size_t samples,
        _In_ const std::size_t parameters,
        _In_ const bool preserve_draw,
        _In_ TRng&& rng,
        _In_ TDist&& distribution) {
    matrix<typename TDist::result_type> result(samples, parameters);
    return random(result,
        preserve_draw,
        std::forward<TRng>(rng),
        std::forward<TDist>(distribution));
}

/// <summary>
/// Create a uniformly distributed stratified sample from unit hypercube.
/// </summary>
/// <typeparam name="TValue">The type of values to be created, which must be a
/// floating point type.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <param name="samples"></param>
/// <param name="parameters"></param>
/// <param name="preserve_draw"></param>
/// <param name="rng">The random number generator used to sample a uniform
/// real distribution within [0, 1].</param>
/// <returns></returns>
template<class TValue, class TRng>
inline std::enable_if_t<std::is_floating_point_v<TValue>, matrix<TValue>>
random(_In_ const std::size_t samples,
        _In_ const std::size_t parameters,
        _In_ const bool preserve_draw,
        _In_ TRng&& rng) {
    matrix<TValue> result(samples, parameters);
    return random(result,
        preserve_draw,
        std::forward<TRng>(rng),
        std::uniform_real_distribution<TValue>());
}

/// <summary>
/// Create a (uniformly distributed) stratified sample from a hypercube with
/// the given parameter <see cref="range{TValue}" />s.
/// </summary>
/// <typeparam name="TIterator">An iterator over the parameter
/// <paramref name="range{TValue}" />s. The elements iterated by this
/// type must be floating-point numbers.</typeparam>
/// <typeparam name="TRng"></typeparam>
/// <typeparam name="TDist"></typeparam>
/// <param name="samples"></param>
/// <param name="begin"></param>
/// <param name="end"></param>
/// <param name="preserve_draw"></param>
/// <param name="rng"></param>
/// <param name="distribution"></param>
/// <returns></returns>
template<class TIterator, class TRng, class TDist>
std::enable_if_t<
    std::is_floating_point_v<
        typename std::iterator_traits<TIterator>::value_type::value_type>,
    matrix<typename std::iterator_traits<TIterator>::value_type::value_type>>
random(_In_ const std::size_t samples,
    _In_ const TIterator begin,
    _In_ const TIterator end,
    _In_ const bool preserve_draw,
    _In_ TRng&& rng,
    _In_ TDist&& distribution);

/// <summary>
/// Create a uniformly distributed stratified sample from a hypercube with
/// the given parameter <see cref="range{TValue}" />s.
/// </summary>
/// <typeparam name="TIterator"></typeparam>
/// <typeparam name="TRng"></typeparam>
/// <param name="samples"></param>
/// <param name="begin"></param>
/// <param name="end"></param>
/// <param name="preserve_draw"></param>
/// <param name="rng"></param>
/// <param name="distribution"></param>
/// <returns></returns>
template<class TIterator, class TRng>
inline std::enable_if_t<
    std::is_floating_point_v<
        typename std::iterator_traits<TIterator>::value_type::value_type>,
    matrix<typename std::iterator_traits<TIterator>::value_type::value_type>>
random(_In_ const std::size_t samples,
        _In_ TIterator&& begin,
        _In_ TIterator&& end,
        _In_ const bool preserve_draw,
        _In_ TRng&& rng) {
    typedef typename std::iterator_traits<TIterator>::value_type range_type;
    typedef typename range_type::value_type value_type;
    return random(samples,
        std::forward<TIterator>(begin),
        std::forward<TIterator>(end),
        preserve_draw,
        std::forward<TRng>(rng),
        std::uniform_real_distribution<value_type>());
}

/// <summary>
/// Create a (uniformly distributed) stratified sample from a hypercube with
/// the given parameter <see cref="range{TValue}" />s.
/// </summary>
/// <typeparam name="TValue"></typeparam>
/// <typeparam name="TRng"></typeparam>
/// <typeparam name="TDist"></typeparam>
/// <param name="samples"></param>
/// <param name="parameters"></param>
/// <param name="preserve_draw"></param>
/// <param name="rng"></param>
/// <param name="distribution"></param>
/// <returns></returns>
template<class TValue, class TRng, class TDist>
inline std::enable_if_t<
    std::is_floating_point_v<TValue>,
    matrix<typename TValue>>
random(_In_ const std::size_t samples,
        _In_ const std::initializer_list<range<TValue>>& parameters,
        _In_ const bool preserve_draw,
        _In_ TRng&& rng,
        _In_ TDist&& distribution) {
    return random(samples,
        parameters.begin(),
        parameters.end(),
        preserve_draw,
        std::forward<TRng>(rng),
        std::forward<TDist>(distribution));
}

/// <summary>
/// Create a uniformly distributed stratified sample from a hypercube with
/// the given parameter <see cref="range{TValue}" />s.
/// </summary>
/// <typeparam name="TValue"></typeparam>
/// <typeparam name="TRng"></typeparam>
/// <param name="samples"></param>
/// <param name="parameters"></param>
/// <param name="preserve_draw"></param>
/// <param name="rng"></param>
/// <returns></returns>
template<class TValue, class TRng, class TDist>
inline std::enable_if_t<
    std::is_floating_point_v<TValue>,
    matrix<typename TValue>>
random(_In_ const std::size_t samples,
        _In_ const std::initializer_list<range<TValue>>& parameters,
        _In_ const bool preserve_draw,
        _In_ TRng&& rng) {
    return random(samples,
        parameters.begin(),
        parameters.end(),
        preserve_draw,
        std::forward<TRng>(rng),
        std::uniform_real_distribution<TValue>());
}

LHS_NAMESPACE_END

#include "visus/lhs/random.inl"

#endif /* !defined(_LHS_RANDOM_H) */
