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
#include <random>
#include <stdexcept>
#include <type_traits>

#include "visus/lhs/distance.h"
#include "visus/lhs/matrix.h"
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


#if false
/// <summary>
/// Fill <paramref name="result" /> with a (uniformly distributed) stratified
/// sample from unit hypercube, placing the values in the centre of the
/// <paramref name="samples" /> intervals.
/// </summary>
/// <typeparam name="TValue">The type of values to be created, which must be a
/// floating point type.</typeparam>
/// <typeparam name="Layout">The memory layout of the matrix. It is reasonable
/// to use row-major matrices here, because in this case, the parameter values
/// for a sample are laid out contiguously in memory.</typeparam>
/// <typeparam name="TRng">The type of the maximin number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate maximin
/// numbers.</typeparam>
/// <param name="result">The matrix to receive the Latin Hypercube sample. The
/// values are ignored on entry. However, the number of rows represents the
/// number of samples for each parameter whereas the number of columns
/// represents the number of parameters.</param>
/// <param name="rng">The maximin number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <param name="distribution">The distribution to draw samples from, which
/// typically is a uniform real distribution creating numbers within [0, 1].
/// </param>
/// <returns><paramref name="result" />.</returns>
template<class TValue, matrix_layout Layout, class TRng, class TDist>
std::enable_if_t<std::is_floating_point_v<TValue>, matrix<TValue, Layout>&>
maximin(_Inout_ matrix<TValue, Layout>& result,
    _In_ TRng& rng,
    _In_ TDist& distribution);

/// <summary>
/// Create a (uniformly distributed) stratified sample from unit hypercube,
/// placing the values in the centre of the <paramref name="samples" />
/// intervals.
/// </summary>
/// <typeparam name="TRng">The type of the maximin number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate maximin
/// numbers.</typeparam>
/// <param name="samples">The number of samples to draw (the number of rows in
/// the resulting matrix).</param>
/// <param name="parameters">The number of parameters (columns in the resulting
/// matrix), which will all be within [0, 1].</param>
/// <param name="rng">The maximin number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <param name="distribution">The distribution to draw samples from, which
/// typically is a uniform real distribution creating numbers within [0, 1].
/// </param>
/// <returns></returns>
template<class TRng, class TDist>
inline matrix<typename TDist::result_type> maximin(
        _In_ const std::size_t samples,
        _In_ const std::size_t parameters,
        _In_ TRng&& rng,
        _In_ TDist&& distribution) {
    matrix<typename TDist::result_type> result(samples, parameters);
    return maximin(result,
        std::forward<TRng>(rng),
        std::forward<TDist>(distribution));
}

/// <summary>
/// Create a uniformly distributed stratified sample from unit hypercube
/// placing the values in the centre of the <paramref name="samples" />
/// intervals.
/// </summary>
/// <typeparam name="TValue">The type of values to be created, which must be a
/// floating point type.</typeparam>
/// <typeparam name="TRng">The type of the maximin number generator.</typeparam>
/// <param name="samples">The number of samples to draw (the number of rows in
/// the resulting matrix).</param>
/// <param name="parameters">The number of parameters (columns in the resulting
/// matrix), which will all be within [0, 1].</param>
/// <param name="preserve_draw">Indicates whether the order of the draw should
/// be preserved if less columns are selected.</param>
/// <param name="rng">The maximin number generator used to sample a uniform
/// real distribution within [0, 1].</param>
/// <returns></returns>
template<class TValue, class TRng>
inline std::enable_if_t<std::is_floating_point_v<TValue>, matrix<TValue>>
maximin(_In_ const std::size_t samples,
        _In_ const std::size_t parameters,
        _In_ TRng&& rng) {
    matrix<TValue> result(samples, parameters);
    return maximin(result,
        std::forward<TRng>(rng),
        std::uniform_real_distribution<TValue>());
}


/// <summary>
/// Create a (uniformly distributed and maximin) stratified sample from a
/// hypercube with the given parameter <see cref="range{TValue}" />s.
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
/// <typeparam name="TRng">The type of the maximin number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate maximin
/// numbers.</typeparam>
/// <param name="samples">The number of samples to draw (the number of rows in
/// the resulting matrix).</param>
/// <param name="begin">The begin of the range of parameter ranges which are
/// used to scale the distribution.</param>
/// <param name="end">The end of the range of parameter ranges. The distance
/// between <paramref name="begin" /> and <paramref name="end" /> is the number
/// of parameters (or number of columns in the matrix).</param>
/// <param name="rng">The maximin number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <param name="distribution">The distribution used to sample the maximin
/// numbers from. This should be a uniform distribution. Note that the numbers
/// generated here are not directly part of the result, but only used for
/// ordering the indices maximinly.</param>
/// <returns></returns>
template<class TIterator, class TRng, class TDist>
inline std::enable_if_t<detail::is_range_v<
            typename std::iterator_traits<TIterator>::value_type>
        && std::is_floating_point_v<
            typename std::iterator_traits<TIterator>::value_type::value_type>,
    matrix<typename std::iterator_traits<TIterator>::value_type::value_type>>
maximin(_In_ const std::size_t samples,
    _In_ const TIterator& begin,
    _In_ const TIterator& end,
    _In_ TRng& rng,
    _In_ TDist& distribution);

/// <summary>
/// Create a (uniformly distributed and maximin) stratified sample from a
/// hypercube with the given parameter <see cref="range{TValue}" />s.
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
/// <typeparam name="TRng">The type of the maximin number generator.</typeparam>
/// <param name="samples">The number of samples to draw (the number of rows in
/// the resulting matrix).</param>
/// <param name="begin">The begin of the range of parameter ranges which are
/// used to scale the distribution.</param>
/// <param name="end">The end of the range of parameter ranges. The distance
/// between <paramref name="begin" /> and <paramref name="end" /> is the number
/// of parameters (or number of columns in the matrix).</param>
/// <param name="rng">The maximin number generator used to sample the given
/// maximin distribution.</param>
/// <returns></returns>
template<class TIterator, class TRng>
inline std::enable_if_t<detail::is_range_v<
        typename std::iterator_traits<TIterator>::value_type>,
    matrix<typename std::iterator_traits<TIterator>::value_type::value_type>>
maximin(_In_ const std::size_t samples,
        _In_ TIterator&& begin,
        _In_ TIterator&& end,
        _In_ TRng&& rng) {
    typedef typename std::iterator_traits<TIterator>::value_type range_type;
    typedef typename range_type::value_type value_type;
    typedef make_floating_point_t<value_type> float_type;
    return maximin(samples,
        std::forward<TIterator>(begin),
        std::forward<TIterator>(end),
        std::forward<TRng>(rng),
        std::uniform_real_distribution<float_type>());
}

/// <summary>
/// Create a (uniformly distributed and maximin) stratified sample from a
/// hypercube with the given parameter <see cref="range{TValue}" />s.
/// </summary>
/// <remarks>
/// <para>This function will first create a uniformly distributed sample from
/// a unit hypercube. Afterwards, the resulting values will be scaled to the
/// specified parameter ranges. If the parameters are integral numbers, the
/// results will be rounded to the nearest integer value.</para>
/// </remarks>
/// <typeparam name="TValue">The type of samples to be generated.</typeparam>
/// <typeparam name="TRng">The type of the maximin number generator.</typeparam>
/// <typeparam name="TDist">The type of the distribution used to generate maximin
/// numbers.</typeparam>
/// <param name="samples">The number of samples to draw (the number of rows in
/// the resulting matrix).</param>
/// <param name="parameters">The ranges for all parameters to which the output
/// values are scaled. The number of initialises is equal to the number of
/// parameters or number of columns of the resulting matrix.</param>
/// <param name="rng">The maximin number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <param name="distribution">The distribution used to sample the maximin
/// numbers from. This should be a uniform distribution. Note that the numbers
/// generated here are not directly part of the result, but only used for
/// ordering the indices maximinly.</param>
/// <returns></returns>
template<class TValue, class TRng, class TDist>
inline matrix<TValue> maximin(_In_ const std::size_t samples,
        _In_ const std::initializer_list<range<TValue>>& parameters,
        _In_ TRng&& rng,
        _In_ TDist&& distribution) {
    return maximin(samples,
        parameters.begin(),
        parameters.end(),
        std::forward<TRng>(rng),
        std::forward<TDist>(distribution));
}

/// <summary>
/// Create a (uniformly distributed and maximin) stratified sample from a
/// hypercube with the given parameter <see cref="range{TValue}" />s.
/// </summary>
/// <remarks>
/// <para>This function will first create a uniformly distributed sample from
/// a unit hypercube. Afterwards, the resulting values will be scaled to the
/// specified parameter ranges. If the parameters are integral numbers, the
/// results will be rounded to the nearest integer value.</para>
/// </remarks>
/// <typeparam name="TValue">The type of samples to be generated.</typeparam>
/// <typeparam name="TRng">The type of the maximin number generator.</typeparam>
/// <param name="samples">The number of samples to draw (the number of rows in
/// the resulting matrix).</param>
/// <param name="parameters">The ranges for all parameters to which the output
/// values are scaled. The number of initialises is equal to the number of
/// parameters or number of columns of the resulting matrix.</param>
/// <param name="rng">The maximin number generator used to sample the given
/// <paramref name="distribution" />.</param>
/// <returns></returns>
template<class TValue, class TRng, class TDist>
inline matrix<TValue> maximin(_In_ const std::size_t samples,
        _In_ const std::initializer_list<range<TValue>>& parameters,
        _In_ TRng&& rng) {
    return maximin(samples,
        parameters.begin(),
        parameters.end(),
        std::forward<TRng>(rng),
        std::uniform_real_distribution<TValue>());
}
#endif

LHS_NAMESPACE_END

#include "visus/lhs/maximin.inl"

#endif /* !defined(_LHS_MAXIMIN_H) */
