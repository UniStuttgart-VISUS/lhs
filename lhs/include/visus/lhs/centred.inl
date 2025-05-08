// <copyright file="centred.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * LHS_NAMESPACE::centred
 */
template<class TValue,
    LHS_NAMESPACE::matrix_layout Layout,
    class TRng,
    class TDist>
std::enable_if_t<std::is_floating_point_v<TValue>,
    LHS_NAMESPACE::matrix<TValue, Layout>&>
LHS_NAMESPACE::centred(_Inout_ matrix<TValue, Layout>& result,
        _In_ TRng& rng,
        _In_ TDist& distribution) {
    constexpr auto half = static_cast<TValue>(0.5);
    // Derived from https://github.com/relf/egobox/blob/15a1225454f4d1c06df2301b9b5b69a9c900c788/crates/doe/src/lhs.rs#L253-L267
    const auto n = result.rows();
    const auto k = result.columns();
    std::vector<std::size_t> indices(n);
    std::vector<TValue> samples(n);
    std::vector<TValue> values(n);

    // Create the interval centres to select from.
    const auto step = static_cast<TValue>(1) / static_cast<TValue>(n);
    for (std::size_t i = 0; i < n; ++i) {
        samples[i] = (i + half) * step;
    }

    // Create the samples from 'values'.
    for (std::size_t c = 0; c < k; ++c) {
        for (std::size_t r = 0; r < n; ++r) {
            values[r] = static_cast<TValue>(distribution(rng));
        }

        detail::order(indices, values.begin(), values.end());

        for (std::size_t r = 0; r < n; ++r) {
            result(r, c) = samples[indices[r]];
        }
    }

    ASSERT_VALID_LHS(result);
    return result;
}

#if false
/*
 * LHS_NAMESPACE::centred
 */
template<class TIterator, class TRng, class TDist>
inline std::enable_if_t<LHS_DETAIL_NAMESPACE::is_range_v<
        typename std::iterator_traits<TIterator>::value_type>,
    LHS_NAMESPACE::matrix<
        typename std::iterator_traits<TIterator>::value_type::value_type>>
LHS_NAMESPACE::centred(_In_ const std::size_t samples,
        _In_ TIterator&& begin,
        _In_ TIterator&& end,
        _In_ const bool preserve_draw,
        _In_ TRng&& rng,
        _In_ TDist&& distribution) {
    typedef typename std::iterator_traits<TIterator>::value_type range_type;
    typedef typename range_type::value_type int_type;
    typedef make_floating_point_t<int_type> float_type;

    matrix<float_type> retval(samples, std::distance(begin, end));

    // Create centred samples within [0, 1].
    centred(retval,
        preserve_draw,
        std::forward<TRng>(rng),
        std::forward<TDist>(distribution));

    // Scale to the requested range.
    return detail::scale(retval,
        std::forward<TIterator>(begin),
        std::forward<TIterator>(end));
}


/*
 * LHS_NAMESPACE::centred
 */
template<class TIterator, class TRng, class TDist>
std::enable_if_t<std::is_integral_v<
    typename std::iterator_traits<TIterator>::value_type>,
    LHS_NAMESPACE::matrix<typename std::iterator_traits<TIterator>::value_type>>
LHS_NAMESPACE::centred(_In_ const std::size_t samples,
        _In_ TIterator&& begin,
        _In_ TIterator&& end,
        _In_ const bool preserve_draw,
        _In_ TRng& rng,
        _In_ TDist& distribution) {
    typedef typename std::iterator_traits<TIterator>::value_type int_type;
    typedef make_floating_point_t<int_type> float_type;

    // Create a sample from the unit hypercube.
    matrix<float_type> unit(samples, std::distance(begin, end));
    centred(unit, preserve_draw, rng, distribution);

    // Scale the cube to the the specified ranges.
    return scale(unit,
        std::forward<TIterator>(begin),
        std::forward<TIterator>(end));
}
#endif
