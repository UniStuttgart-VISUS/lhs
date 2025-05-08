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

/*
 * LHS_NAMESPACE::centred
 */
template<class TIterator, class TRng, class TDist>
inline std::enable_if_t<LHS_DETAIL_NAMESPACE::is_range_v<
        typename std::iterator_traits<TIterator>::value_type>
    && std::is_floating_point_v<
        typename std::iterator_traits<TIterator>::value_type::value_type>,
    LHS_NAMESPACE::matrix<
        typename std::iterator_traits<TIterator>::value_type::value_type>>
LHS_NAMESPACE::centred(_In_ const std::size_t samples,
        _In_ const TIterator& begin,
        _In_ const TIterator& end,
        _In_ TRng& rng,
        _In_ TDist& distribution) {
    typedef typename std::iterator_traits<TIterator>::value_type range_type;
    typedef typename range_type::value_type value_type;

    constexpr auto half = static_cast<value_type>(0.5);
    const auto k = std::distance(begin, end);
    std::vector<std::size_t> indices(samples);
    matrix<value_type> retval(samples, k);
    std::vector<value_type> values(samples);

    std::size_t c = 0;
    for (auto it = begin; it != end; ++it, ++c) {
        for (std::size_t r = 0; r < samples; ++r) {
            values[r] = static_cast<value_type>(distribution(rng));
        }

        detail::order(indices, values.begin(), values.end());

        auto step = it->distance() / static_cast<value_type>(samples);
        for (std::size_t i = 0; i < samples; ++i) {
            values[i] = (i + half) * step + it->begin();
        }

        for (std::size_t r = 0; r < samples; ++r) {
            retval(r, c) = values[indices[r]];
        }
    }

    return retval;
}
