// <copyright file="sample.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_SAMPLE_H)
#define _LHS_SAMPLE_H
#pragma once

#include <stdexcept>

#include "visus/lhs/sample_type.h"
#include "visus/lhs/valid.h"


LHS_NAMESPACE_BEGIN

/// <summary>
/// Create a list of Latin Hypercube samples for the given parameter ranges.
/// </summary>
/// <typeparam name="TLhsGenerator">The type of the generator function that
/// creates a stratified Latin unit hypercube sample.</typeparam>
/// <typeparam name="TParameters">The type of the parameters, which can either
/// be enumerated categorical parameters or numeric ranges.</typeparam>
/// <param name="lhs_generator">The generator producing the Latin hypercube
/// sample on a unit hypercube, which will subsequently be transformed into
/// specific parameter expressions. The number of rows returned by the function
/// determines the number of samples selected. The function receives the number
/// of parameters as input, which must be the number of columns in the matrix
/// returned.</param>
/// <param name="parameters">The parameters of the sample.</param>
/// <returns>The actual parameter expressions for the sample.</returns>
template<class TLhsGenerator, class... TParameters>
std::vector<detail::sample_type_t<TParameters...>> sample(
    _In_ TLhsGenerator lhs_generator, _In_ const TParameters&... parameters);

LHS_NAMESPACE_END


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Realise the <paramref name="parameter" /> expression based on the given
/// sample value.
/// </summary>
/// <typeparam name="TValue">A floating-point type.</typeparam>
/// <typeparam name="TParameters">The type of the parameters, which can either
/// be enumerated categorical parameters or numeric ranges.</typeparam>
/// <param name="value">The sample value within [0, 1].</param>
/// <param name="parameters">The parameters of the sample.</param>
/// <returns>The parameter expression for the given sample
/// <paramref name="value" />.</returns>
template<class TIterator, class TParameter, class... TParameters>
inline sample_type_t<TParameter, TParameters...> realise_parameters(
        _In_ TIterator begin,
        _In_ TIterator end,
        _In_ const TParameter& parameter,
        _In_ const TParameters&... parameters) {
    typedef sample_value_type<TParameter> current_parameter;
    static_assert(std::is_floating_point_v<typename TIterator::value_type>,
        "The sample value must be a floating-point number witin [0, 1].");
    assert(begin != end);
    auto next = begin;
    std::advance(next, 1);
    return std::tuple_cat(
        std::make_tuple(current_parameter::realise(*begin, parameter)),
        realise_parameters(next, end, parameters...));
}

/// <summary>
/// Recursion stop fo <see cref="realise_parameters"/>.
/// </summary>
template<class TIterator> inline constexpr std::tuple<> realise_parameters(
        _In_ TIterator begin, _In_ TIterator end) {
    assert(begin == end);
    static const std::tuple<> retval;
    return retval;
}

LHS_DETAIL_NAMESPACE_END

#include "visus/lhs/sample.inl"

#endif /* !defined(_LHS_SAMPLE_H) */
