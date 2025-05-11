// <copyright file="sample_type.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_SAMPLE_TYPE_H)
#define _LHS_SAMPLE_TYPE_H
#pragma once

#include <array>
#include <initializer_list>
#include <list>
#include <set>
#include <tuple>
#include <type_traits>
#include <vector>

#include "visus/lhs/range.h"
#include "visus/lhs/scale.h"


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Derives the type used in a sample from the description given
/// <typeparamref name="TParameter">TParameter</typeparamref>.
/// </summary>
/// <typeparam name="TParameter">The type describing the parameter, which can be
/// an enumeration of parameter expressions or numerical ranges.</typeparam>
template<class TParameter> struct sample_value_type final {

    /// <summary>
    /// The user-specified type specifying the parameter range.
    /// </summary>
    typedef TParameter input_type;

    /// <summary>
    /// The type of the parameter in the sample.
    /// </summary>
    typedef TParameter type;

    /// <summary>
    /// Realises the parameter based on the given sample value.
    /// </summary>
    /// <typeparam name="TValue">The sample value, which must be a
    /// floating-point number.</typeparam>
    /// <param name="value">The sample value within [0, 1].</param>
    /// <param name="parameter">The user-specified parameter value.</param>
    /// <returns><paramref name="parameter" />.</returns>
    template<class TValue> inline static constexpr std::enable_if_t<
        std::is_floating_point_v<TValue>, type&>
    realise(_In_ const TValue value, _In_ const input_type& parameter) {
        return parameter;
    }
};

/// <summary>
/// Specialisation for a categorical parameter in an
/// <see cref="std::array{TParameter, Count}"/>.
/// </summary>
template<class TParameter, std::size_t Count>
struct sample_value_type<std::array<TParameter, Count>> final {
    static_assert(Count > 0, "The list of parameter expressions must be "
        "greater than zero.");

    typedef std::array<TParameter, Count> input_type;
    typedef TParameter type;

    template<class TValue> inline static constexpr std::enable_if_t<
        std::is_floating_point_v<TValue>, type>
    realise(_In_ const TValue value, _In_ const input_type& parameter) {
        return parameter[scale(value, Count)];
    }
};

/// <summary>
/// Specialisation for a categorical parameter in an
/// <see cref="std::initializer_list{TParameter, Count}"/>.
/// </summary>
template<class TParameter>
struct sample_value_type<std::initializer_list<TParameter>> final {
    typedef std::initializer_list<TParameter> input_type;
    typedef TParameter type;

    template<class TValue> inline static constexpr std::enable_if_t<
        std::is_floating_point_v<TValue>, type>
    realise(_In_ const TValue value, _In_ const input_type& parameter) {
        auto it = parameter.begin();
        std::advance(it, scale(value, parameter.size()));
        return *it;
    }
};

/// <summary>
/// Specialisation for a categorical parameter in an
/// <see cref="std::list{TParameter, Count}"/>.
/// </summary>
template<class TParameter>
struct sample_value_type<std::list<TParameter>> final {
    typedef std::list<TParameter> input_type;
    typedef TParameter type;

    template<class TValue> inline static constexpr std::enable_if_t<
        std::is_floating_point_v<TValue>, type>
    realise(_In_ const TValue value, _In_ const input_type& parameter) {
        return parameter[scale(value, parameter.size())];
    }
};

/// <summary>
/// Specialisation for a numerical range.
/// </summary>
template<class TParameter> struct sample_value_type<range<TParameter>> final {
    typedef range<TParameter> input_type;
    typedef TParameter type;

    template<class TValue> inline static std::enable_if_t<
        std::is_floating_point_v<TValue>, type>
    realise(_In_ const TValue value, _In_ const input_type& parameter) {
        assert(value >= static_cast<TValue>(0));
        assert(value <= static_cast<TValue>(1));
        const auto offset = static_cast<type>(value * parameter.distance());
        return parameter.begin() + offset;
    }
};

/// <summary>
/// Specialisation for a categorical parameter in an
/// <see cref="std::set{TParameter, Count}"/>.
/// </summary>
template<class TParameter> struct sample_value_type<std::set<TParameter>> final {
    typedef std::set<TParameter> input_type;
    typedef TParameter type;

    template<class TValue> inline static constexpr std::enable_if_t<
        std::is_floating_point_v<TValue>, type>
    realise(_In_ const TValue value, _In_ const input_type& parameter) {
        return parameter.begin() + scale(value, parameter.size());
    }
};

/// <summary>
/// Specialisation for a categorical parameter in an
/// <see cref="std::vector{TParameter, Count}"/>.
/// </summary>
template<class TParameter> struct sample_value_type<std::vector<TParameter>> final {
    typedef std::vector<TParameter> input_type;
    typedef TParameter type;

    template<class TValue> inline static constexpr std::enable_if_t<
        std::is_floating_point_v<TValue>, type>
    realise(_In_ const TValue value, _In_ const input_type& parameter) {
        return parameter[scale(value, parameter.size())];
    }
};


/// <summary>
/// Derives the type used in a sample from the description given
/// <typeparamref name="TParameter">TParameter</typeparamref>.
/// </summary>
/// <typeparam name="TParameter">The type describing the parameter, which can be
/// an enumeration of parameter expressions or numerical ranges.</typeparam>
template<class TParameter> 
using sample_value_type_t = typename sample_value_type<TParameter>::type;


/// <summary>
/// Derives the type of a sample from the list of parameters.
/// </summary>
/// <typeparam name="TParameters">The list of parameters, which must be
/// resolvable individually using <see cref="sample_type_type_t{TParameter}" />.
/// </typeparam>
template<class... TParameters> struct sample_type final {

    /// <summary>
    /// The type of the parameter in the sample.
    /// </summary>
    typedef std::tuple<sample_value_type_t<TParameters>...> type;
};


/// <summary>
/// Derives the type of a sample from the list of parameters.
/// </summary>
/// <typeparam name="TParameters">The list of parameters, which must be
/// resolvable individually using <see cref="sample_type_type_t{TParameter}" />.
/// </typeparam>
template<class... TParameters>
using sample_type_t = typename sample_type<TParameters...>::type;

LHS_DETAIL_NAMESPACE_END

#endif /* !defined(_LHS_SAMPLE_TYPE_H) */
