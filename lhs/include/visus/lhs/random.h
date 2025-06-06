﻿// <copyright file="random.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_RANDOM_H)
#define _LHS_RANDOM_H
#pragma once

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <random>
#include <stdexcept>
#include <type_traits>

#include "visus/lhs/make_floating_point.h"
#include "visus/lhs/matrix.h"
#include "visus/lhs/is_iterable.h"
#include "visus/lhs/is_range.h"
#include "visus/lhs/order.h"
#include "visus/lhs/range.h"
#include "visus/lhs/scale.h"
#include "visus/lhs/valid.h"


LHS_NAMESPACE_BEGIN

/// <summary>
/// Fill <paramref name="result" /> with a Latin Hypercube sample.
/// </summary>
/// <remarks>
/// This function creates what the R implmenetation also calls a
/// &quot;grid&quot; of samples.
/// </remarks>
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
/// <param name="rng">The random number generator used to sample the given
/// <paramref name="distribution" />.</param>
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
/// <remarks>
/// This function creates what the R implmenetation also calls a
/// &quot;grid&quot; of samples.
/// </remarks>
/// <typeparam name="Layout">The memory layout of the matrix. It is reasonable
/// to use row-major matrices here, because in this case, the parameter values
/// for a sample are laid out contiguously in memory.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <param name="result">The matrix to receive the Latin Hypercube sample. The
/// values are ignored on entry. However, the number of rows represents the
/// number of samples for each parameter whereas the number of columns
/// represents the number of parameters.</param>
/// <param name="rng">The random number generator used to sample a uniform
/// real distribution within [0, 1].</param>
/// <returns><paramref name="result" />.</returns>
template<matrix_layout Layout, class TRng>
inline matrix<std::size_t, Layout>& random(
        _Inout_ matrix<std::size_t, Layout>& result,
        _In_ TRng& rng) {
    return random(result, rng, std::uniform_real_distribution<float>());
}

/// <summary>
/// Fill <paramref name="result" /> with a Latin Hypercube sample.
/// </summary>
/// <remarks>
/// This function creates what the R implmenetation also calls a
/// &quot;grid&quot; of samples.
/// </remarks>
/// <typeparam name="Layout">The memory layout of the matrix. It is reasonable
/// to use row-major matrices here, because in this case, the parameter values
/// for a sample are laid out contiguously in memory.</typeparam>
/// <param name="result">The matrix to receive the Latin Hypercube sample. The
/// values are ignored on entry. However, the number of rows represents the
/// number of samples for each parameter whereas the number of columns
/// represents the number of parameters.</param>
/// <returns><paramref name="result" />.</returns>
template<matrix_layout Layout, class TRng>
inline matrix<std::size_t, Layout>& random(
        _Inout_ matrix<std::size_t, Layout>& result) {
    std::random_device rd;
    std::mt19937 rng(rd());
    return random(result, rng, std::uniform_real_distribution<float>());
}

/// <summary>
/// Create a Latin Hypercube sample.
/// </summary>
/// <remarks>
/// This function creates what the R implmenetation also calls a
/// &quot;grid&quot; of samples.
/// </remarks>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate random
/// numbers.</typeparam>
/// <param name="samples">The number of samples per parameter (rows) of the
/// Latin hypercube sample.</param>
/// <param name="parameters">The number of parameters (columns) in the
/// Latin hypercube sample.</param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <param name="distribution">The distribution used to sample the random
/// numbers from. This should be a uniform distribution. Note that the numbers
/// generated here are not directly part of the result, but only used for
/// ordering the indices randomly.</param>
/// <returns></returns>
template<class TRng, class TDist>
inline matrix<std::size_t> random(
        _In_ const std::size_t samples,
        _In_ const std::size_t parameters,
        _In_ TRng& rng,
        _In_ TDist& distribution) {
    matrix<std::size_t> result(samples, parameters);
    return random(result, rng, distribution);
}

/// <summary>
/// Create a Latin Hypercube sample.
/// </summary>
/// <remarks>
/// This function creates what the R implmenetation also calls a
/// &quot;grid&quot; of samples.
/// </remarks>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <param name="samples">The number of samples per parameter (rows) of the
/// Latin hypercube sample.</param>
/// <param name="parameters">The number of parameters (columns) in the
/// Latin hypercube sample.</param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <param name="rng">The random number generator used to sample a uniform
/// real distribution within [0, 1].</param>
/// <returns></returns>
template<class TRng>
inline matrix<std::size_t> random(
        _In_ const std::size_t samples,
        _In_ const std::size_t parameters,
        _In_ TRng& rng) {
    matrix<std::size_t> result(samples, parameters);
    return random(result, rng, std::uniform_real_distribution<float>());
}

/// <summary>
/// Create a Latin Hypercube sample.
/// </summary>
/// <remarks>
/// This function creates what the R implmenetation also calls a
/// &quot;grid&quot; of samples.
/// </remarks>
/// <param name="samples">The number of samples per parameter (rows) of the
/// Latin hypercube sample.</param>
/// <param name="parameters">The number of parameters (columns) in the
/// Latin hypercube sample.</param>
/// <param name="rng">The random number generator used to sample a uniform
/// real distribution within [0, 1].</param>
/// <returns></returns>
inline matrix<std::size_t> random(
        _In_ const std::size_t samples,
        _In_ const std::size_t parameters) {
    matrix<std::size_t> result(samples, parameters);
    std::random_device rd;
    std::mt19937 rng(rd());
    return random(result, rng, std::uniform_real_distribution<float>());
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
/// <param name="result">The matrix to receive the Latin Hypercube sample. The
/// values are ignored on entry. However, the number of rows represents the
/// number of samples for each parameter whereas the number of columns
/// represents the number of parameters.</param>
/// <param name="preserve_draw">Indicates whether the order of the draw should
/// be preserved if less columns are selected.</param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name="distribution" />.</param>
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
/// <param name="samples">The number of samples to draw (the number of rows in
/// the resulting matrix).</param>
/// <param name="parameters">The number of parameters (columns in the resulting
/// matrix), which will all be within [0, 1].</param>
/// <param name="preserve_draw">Indicates whether the order of the draw should
/// be preserved if less columns are selected.</param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <param name="distribution">The distribution to draw samples from, which
/// typically is a uniform real distribution creating numbers within [0, 1].
/// </param>
/// <returns></returns>
template<class TRng, class TDist>
inline matrix<typename TDist::result_type> random(
        _In_ const std::size_t samples,
        _In_ const std::size_t parameters,
        _In_ const bool preserve_draw,
        _In_ TRng& rng,
        _In_ TDist& distribution) {
    matrix<typename TDist::result_type> result(samples, parameters);
    return random(result, preserve_draw, rng, distribution);
}

/// <summary>
/// Create a uniformly distributed stratified sample from unit hypercube.
/// </summary>
/// <typeparam name="TValue">The type of values to be created, which must be a
/// floating point type.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <param name="samples">The number of samples to draw (the number of rows in
/// the resulting matrix).</param>
/// <param name="parameters">The number of parameters (columns in the resulting
/// matrix), which will all be within [0, 1].</param>
/// <param name="preserve_draw">Indicates whether the order of the draw should
/// be preserved if less columns are selected.</param>
/// <param name="rng">The random number generator used to sample a uniform
/// real distribution within [0, 1].</param>
/// <returns></returns>
template<class TValue, class TRng>
inline std::enable_if_t<std::is_floating_point_v<TValue>, matrix<TValue>>
random(_In_ const std::size_t samples,
        _In_ const std::size_t parameters,
        _In_ const bool preserve_draw,
        _In_ TRng& rng) {
    matrix<TValue> result(samples, parameters);
    return random(result, preserve_draw, rng,
        std::uniform_real_distribution<TValue>());
}


/// <summary>
/// Create a uniformly distributed stratified sample from unit hypercube.
/// </summary>
/// <typeparam name="TValue">The type of values to be created, which must be a
/// floating point type.</typeparam>
/// <param name="samples">The number of samples to draw (the number of rows in
/// the resulting matrix).</param>
/// <param name="parameters">The number of parameters (columns in the resulting
/// matrix), which will all be within [0, 1].</param>
/// <param name="preserve_draw">Indicates whether the order of the draw should
/// be preserved if less columns are selected. This parameter defaults to
/// <c>false</c>.</param>
/// <returns></returns>
template<class TValue>
inline std::enable_if_t<std::is_floating_point_v<TValue>, matrix<TValue>>
random(_In_ const std::size_t samples,
        _In_ const std::size_t parameters,
        _In_ const bool preserve_draw = false) {
    std::random_device rd;
    std::mt19937 rng(rd());
    matrix<TValue> result(samples, parameters);
    return random(result, preserve_draw, rng,
        std::uniform_real_distribution<TValue>());
}

/// <summary>
/// Create a (uniformly distributed) stratified sample from a hypercube with
/// the given parameter <see cref="range{TValue}" />s.
/// </summary>
/// <remarks>
/// <para>This function will first create a uniformly distributed sample from
/// a unit hypercube. Afterwards, the resulting values will be scaled to the
/// specified parameter ranges. If the parameters are integral numbers, the
/// results will be rounded to the nearest integer value.</para>
/// </remarks>
/// <typeparam name="TIterator">An iterator over the parameter
/// <paramref name="range{TValue}" />s. The elements, which can be
/// floating-point or integral numbers, iterated here determine the type of the
/// returned sample as well.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate random
/// numbers.</typeparam>
/// <param name="samples">The number of samples to draw (the number of rows in
/// the resulting matrix).</param>
/// <param name="begin">The begin of the range of parameter ranges which are
/// used to scale the distribution.</param>
/// <param name="end">The end of the range of parameter ranges. The distance
/// between <paramref name="begin" /> and <paramref name="end" /> is the number
/// of parameters (or number of columns in the matrix).</param>
/// <param name="preserve_draw">Indicates whether the order of the draw should
/// be preserved if less columns are selected.</param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <param name="distribution">The distribution used to sample the random
/// numbers from. This should be a uniform distribution. Note that the numbers
/// generated here are not directly part of the result, but only used for
/// ordering the indices randomly.</param>
/// <returns></returns>
template<class TIterator, class TRng, class TDist>
inline std::enable_if_t<detail::is_range_v<
        typename std::iterator_traits<TIterator>::value_type>,
    matrix<typename std::iterator_traits<TIterator>::value_type::value_type>>
random(_In_ const std::size_t samples,
    _In_ TIterator&& begin,
    _In_ TIterator&& end,
    _In_ const bool preserve_draw,
    _In_ TRng& rng,
    _In_ TDist& distribution);

/// <summary>
/// Create a uniformly distributed stratified sample from a hypercube with
/// the given parameter <see cref="range{TValue}" />s.
/// </summary>
/// <remarks>
/// <para>This function will first create a uniformly distributed sample from
/// a unit hypercube. Afterwards, the resulting values will be scaled to the
/// specified parameter ranges. If the parameters are integral numbers, the
/// results will be rounded to the nearest integer value.</para>
/// </remarks>
/// <typeparam name="TIterator">An iterator over the parameter
/// <paramref name="range{TValue}" />s. The elements, which can be
/// floating-point or integral numbers, iterated here determine the type of the
/// returned sample as well.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <param name="samples">The number of samples to draw (the number of rows in
/// the resulting matrix).</param>
/// <param name="begin">The begin of the range of parameter ranges which are
/// used to scale the distribution.</param>
/// <param name="end">The end of the range of parameter ranges. The distance
/// between <paramref name="begin" /> and <paramref name="end" /> is the number
/// of parameters (or number of columns in the matrix).</param>
/// <param name="preserve_draw">Indicates whether the order of the draw should
/// be preserved if less columns are selected.</param>
/// <param name="rng">The random number generator used to sample the given
/// random distribution.</param>
/// <returns></returns>
template<class TIterator, class TRng>
inline std::enable_if_t<detail::is_range_v<
        typename std::iterator_traits<TIterator>::value_type>,
    matrix<typename std::iterator_traits<TIterator>::value_type::value_type>>
random(_In_ const std::size_t samples,
        _In_ TIterator&& begin,
        _In_ TIterator&& end,
        _In_ const bool preserve_draw,
        _In_ TRng& rng) {
    typedef typename std::iterator_traits<TIterator>::value_type range_type;
    typedef typename range_type::value_type value_type;
    typedef make_floating_point_t<value_type> float_type;
    return random(samples,
        std::forward<TIterator>(begin),
        std::forward<TIterator>(end),
        preserve_draw,
        rng,
        std::uniform_real_distribution<float_type>());
}

/// <summary>
/// Create a (uniformly distributed) stratified sample from a hypercube with
/// the given parameter <see cref="range{TValue}" />s.
/// </summary>
/// <remarks>
/// <para>This function will first create a uniformly distributed sample from
/// a unit hypercube. Afterwards, the resulting values will be scaled to the
/// specified parameter ranges. If the parameters are integral numbers, the
/// results will be rounded to the nearest integer value.</para>
/// </remarks>
/// <typeparam name="TValue">The type of samples to be generated.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate random
/// numbers.</typeparam>
/// <param name="samples">The number of samples to draw (the number of rows in
/// the resulting matrix).</param>
/// <param name="parameters">The ranges for all parameters to which the output
/// values are scaled. The number of initialises is equal to the number of
/// parameters or number of columns of the resulting matrix.</param>
/// <param name="preserve_draw">Indicates whether the order of the draw should
/// be preserved if less columns are selected.</param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <param name="distribution">The distribution used to sample the random
/// numbers from. This should be a uniform distribution. Note that the numbers
/// generated here are not directly part of the result, but only used for
/// ordering the indices randomly.</param>
/// <returns></returns>
template<class TValue, class TRng, class TDist>
inline matrix<TValue> random(_In_ const std::size_t samples,
        _In_ const std::initializer_list<range<TValue>>& parameters,
        _In_ const bool preserve_draw,
        _In_ TRng& rng,
        _In_ TDist& distribution) {
    return random(samples, parameters.begin(), parameters.end(), preserve_draw,
        rng, distribution);
}

/// <summary>
/// Create a uniformly distributed stratified sample from a hypercube with
/// the given parameter <see cref="range{TValue}" />s.
/// </summary>
/// <remarks>
/// <para>This function will first create a uniformly distributed sample from
/// a unit hypercube. Afterwards, the resulting values will be scaled to the
/// specified parameter ranges. If the parameters are integral numbers, the
/// results will be rounded to the nearest integer value.</para>
/// </remarks>
/// <typeparam name="TValue">The type of samples to be generated.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <param name="samples">The number of samples to draw (the number of rows in
/// the resulting matrix).</param>
/// <param name="parameters">The ranges for all parameters to which the output
/// values are scaled. The number of initialises is equal to the number of
/// parameters or number of columns of the resulting matrix.</param>
/// <param name="preserve_draw">Indicates whether the order of the draw should
/// be preserved if less columns are selected.</param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <returns></returns>
template<class TValue, class TRng, class TDist>
inline matrix<TValue> random(_In_ const std::size_t samples,
        _In_ const std::initializer_list<range<TValue>>& parameters,
        _In_ const bool preserve_draw,
        _In_ TRng& rng) {
    return random(samples, parameters.begin(), parameters.end(), preserve_draw,
        rng, std::uniform_real_distribution<TValue>());
}

/// <summary>
/// Creates a sample from a hypercube of zero-based indices for the specified
/// number of expressions per parameter.
/// </summary>
/// <remarks>
/// This function is intended for application cases where the parameters are
/// categorical and have different numbers of expressions. The resulting matrix
/// will hold the zero-based index of the category. Note that the distribution
/// of the samples might suffer from rounding errors.
/// </remarks>
/// <typeparam name="TIterator">An iterator over a range of integral numbers.
/// </typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate random
/// numbers.</typeparam>
/// <param name="samples">The number of samples to draw, which is the number
/// of rows in the resulting matrix.</param>
/// <param name="begin">The begin of the range of parameters. This range
/// describes the number of expressions for each parameter.</param>
/// <param name="end">The end of the range of parameters.</param>
/// <param name="preserve_draw">Indicates whether the order of the draw should
/// be preserved if less columns are selected.</param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <param name="distribution">The distribution used to sample the random
/// numbers from. This should be a uniform distribution. Note that the numbers
/// generated here are not directly part of the result, but only used for
/// ordering the indices randomly.</param>
/// <returns></returns>
template<class TIterator, class TRng, class TDist>
std::enable_if_t<std::is_integral_v<
    typename std::iterator_traits<TIterator>::value_type>,
    matrix<typename std::iterator_traits<TIterator>::value_type>>
random(_In_ const std::size_t samples,
    _In_ TIterator&& begin,
    _In_ TIterator&& end,
    _In_ const bool preserve_draw,
    _In_ TRng& rng,
    _In_ TDist& distribution);

/// <summary>
/// Creates a sample from a hypercube of zero-based indices for the specified
/// number of expressions per parameter.
/// </summary>
/// <remarks>
/// This function is intended for application cases where the parameters are
/// categorical and have different numbers of expressions. The resulting matrix
/// will hold the zero-based index of the category. Note that the distribution
/// of the samples might suffer from rounding errors.
/// </remarks>
/// <typeparam name="TIterator">An iterator over a range of integral numbers.
/// </typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <param name="samples">The number of samples to draw, which is the number
/// of rows in the resulting matrix.</param>
/// <param name="begin">The begin of the range of parameters. This range
/// describes the number of expressions for each parameter.</param>
/// <param name="end">The end of the range of parameters.</param>
/// <param name="preserve_draw">Indicates whether the order of the draw should
/// be preserved if less columns are selected.</param>
/// <param name="rng">The random number generator used to sample a uniform
/// distribution within [0, 1].</param>
/// <returns></returns>
template<class TIterator, class TRng>
inline std::enable_if_t<std::is_integral_v<
    typename std::iterator_traits<TIterator>::value_type>,
    matrix<typename std::iterator_traits<TIterator>::value_type>>
random(_In_ const std::size_t samples,
        _In_ const TIterator begin,
        _In_ const TIterator end,
        _In_ const bool preserve_draw,
        _In_ TRng&& rng) {
    return random(samples,
        parameters.begin(),
        parameters.end(),
        preserve_draw,
        std::forward<TRng>(rng),
        std::uniform_real_distribution<TValue>());
}

/// <summary>
/// Creates a sample from a hypercube of zero-based indices for the specified
/// number of expressions per parameter.
/// </summary>
/// <remarks>
/// This function is intended for application cases where the parameters are
/// categorical and have different numbers of expressions. The resulting matrix
/// will hold the zero-based index of the category. Note that the distribution
/// of the samples might suffer from rounding errors.
/// </remarks>
/// <typeparam name="TSize">An integral type used to specify the number of
/// expressions per parameter.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate random
/// numbers.</typeparam>
/// <param name="samples">The number of samples to draw, which is the number
/// of rows in the resulting matrix.</param>
/// <param name="sizes">A list of numbers describing how many expressions each
/// parameter has. The size of this list determines the number of columns of
/// the resulting matrix.</param>
/// <param name="preserve_draw">Indicates whether the order of the draw should
/// be preserved if less columns are selected.</param>
/// <param name="rng">The random number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <param name="distribution">The distribution used to sample the random
/// numbers from. This should be a uniform distribution. Note that the numbers
/// generated here are not directly part of the result, but only used for
/// ordering the indices randomly.</param>
/// <returns></returns>
template<class TSize, class TRng, class TDist>
inline std::enable_if_t<std::is_integral_v<TSize>, matrix<TSize>>
random(_In_ const std::size_t samples,
        _In_ const std::initializer_list<TSize>& sizes,
        _In_ const bool preserve_draw,
        _In_ TRng& rng,
        _In_ TDist& distribution) {
    return random(samples,
        sizes.begin(),
        sizes.end(),
        preserve_draw,
        rng,
        distribution);
}

/// <summary>
/// Creates a sample from a hypercube of zero-based indices for the specified
/// number of expressions per parameter.
/// </summary>
/// <remarks>
/// This function is intended for application cases where the parameters are
/// categorical and have different numbers of expressions. The resulting matrix
/// will hold the zero-based index of the category. Note that the distribution
/// of the samples might suffer from rounding errors.
/// </remarks>
/// <typeparam name="TSize">An integral type used to specify the number of
/// expressions per parameter.</typeparam>
/// <typeparam name="TRng">The type of the random number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate random
/// numbers.</typeparam>
/// <param name="samples">The number of samples to draw, which is the number
/// of rows in the resulting matrix.</param>
/// <param name="sizes">A list of numbers describing how many expressions each
/// parameter has. The size of this list determines the number of columns of
/// the resulting matrix.</param>
/// <param name="preserve_draw">Indicates whether the order of the draw should
/// be preserved if less columns are selected.</param>
/// <param name="rng">The random number generator used to sample a uniform
/// distribution within [0, 1].</param>
/// <returns></returns>
template<class TSize, class TRng>
inline std::enable_if_t<std::is_integral_v<TSize>, matrix<TSize>>
random(_In_ const std::size_t samples,
        _In_ const std::initializer_list<TSize>& sizes,
        _In_ const bool preserve_draw,
        _In_ TRng& rng) {
    typedef make_floating_point_t<TSize> float_type;
    return random(samples,
        sizes.begin(),
        sizes.end(),
        preserve_draw,
        rng,
        std::uniform_real_distribution<float_type>());
}

LHS_NAMESPACE_END

#include "visus/lhs/random.inl"

#endif /* !defined(_LHS_RANDOM_H) */
