// <copyright file="random.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * LHS_NAMESPACE::random
 */
template<LHS_NAMESPACE::matrix_layout Layout, class TRng, class TDist>
LHS_NAMESPACE::matrix<std::size_t, Layout>& LHS_NAMESPACE::random(
        _Inout_ matrix<std::size_t, Layout>& result,
        _In_ TRng& rng,
        _In_ TDist& distribution) {
    // Derived from https://github.com/bertcarnell/lhs/blob/4be72495c0eba3ce0b1ae602122871ec83421db6/src/randomLHS.cpp#L26C1-L43C5
    const auto n = result.rows();
    std::vector<std::size_t> indices(n);
    std::vector<typename TDist::result_type> values(n);

    for (std::size_t c = 0, k = result.columns(); c < k; ++c) {
        for (std::size_t r = 0; r < n; ++r) {
            values[r] = distribution(rng);
        }

        detail::order(indices, values.begin(), values.end());

        for (std::size_t r = 0; r < n; ++r) {
            result(r, c) = indices[r];
        }
    }

    return result;
}


/*
 * LHS_NAMESPACE::random
 */
template<class TValue,
    LHS_NAMESPACE::matrix_layout Layout,
    class TRng,
    class TDist>
std::enable_if_t<std::is_floating_point_v<TValue>,
    LHS_NAMESPACE::matrix<TValue, Layout>&>
LHS_NAMESPACE::random(_Inout_ matrix<TValue, Layout>& result,
        _In_ const bool preserve_draw,
        _In_ TRng& rng,
        _In_ TDist& distribution) {
    // Derived from https://github.com/bertcarnell/lhs/blob/4be72495c0eba3ce0b1ae602122871ec83421db6/src/randomLHS.cpp#L46C2-L113C10
    const auto n = result.rows();
    std::vector<std::size_t> indices(n);
    std::vector<TValue> values(n);

    if (preserve_draw) {
        std::vector<TValue> values2(values.size());

        for (std::size_t c = 0, k = result.columns(); c < k; ++c) {
            for (std::size_t r = 0; r < n; ++r) {
                values[r] = static_cast<TValue>(distribution(rng));
            }
            // Note: do not merge into one loop as this would change how
            // the 'distribution' is sampled.
            for (std::size_t r = 0; r < n; ++r) {
                values2[r] = static_cast<TValue>(distribution(rng));
            }

            detail::order(indices, values.begin(), values.end());

            for (std::size_t r = 0; r < n; ++r) {
                result(r, c) = static_cast<TValue>(indices[r]) + values2[r];
                result(r, c) /= static_cast<TValue>(n);
            }
        } /* for (std::size_t c = 0, k = result.columns(); c < k; ++c) */

    } else {
        const auto k = result.columns();

        for (std::size_t c = 0; c < k; ++c) {
            for (std::size_t r = 0; r < n; ++r) {
                values[r] = static_cast<TValue>(distribution(rng));
            }

            detail::order(indices, values.begin(), values.end());

            for (std::size_t r = 0; r < n; ++r) {
                result(r, c) = static_cast<TValue>(indices[r]);
            }
        }

        std::decay_t<decltype(result)> values2(result.rows(), result.columns());
        for (std::size_t i = 0; i < values2.size(); ++i) {
            values2[i] = static_cast<TValue>(distribution(rng));
        }

        for (std::size_t c = 0; c < k; ++c) {
            for (std::size_t r = 0; r < n; ++r) {
                result(r, c) += values2(r, c);
                result(r, c) /= static_cast<TValue>(n);
            }
        }
    } /* if (preserve_draw) */

    return result;
}


/*
 * LHS_NAMESPACE::random
 */
template<class TIterator, class TRng, class TDist>
std::enable_if_t<
    std::is_floating_point_v<
        typename std::iterator_traits<TIterator>::value_type::value_type>,
    LHS_NAMESPACE::matrix<
        typename std::iterator_traits<TIterator>::value_type::value_type>>
LHS_NAMESPACE::random(_In_ const std::size_t samples,
        _In_ const TIterator begin,
        _In_ const TIterator end,
        _In_ const bool preserve_draw,
        _In_ TRng&& rng,
        _In_ TDist&& distribution) {
    typedef typename std::iterator_traits<TIterator>::value_type range_type;
    typedef typename range_type::value_type value_type;
    matrix<value_type> retval(samples, std::distance(begin, end));

    // Create random samples within [0, 1].
    random(retval,
        preserve_draw,
        std::forward<TRng>(rng),
        std::forward<TDist>(distribution));

    // Scale the samples to the ranges defined by the parameters like suggested
    // in https://stat.ethz.ch/pipermail/r-help/2007-January/124143.html.
    for (std::size_t r = 0; r < samples; ++r) {
        std::size_t c = 0;

        for (auto it = begin; it != end; ++it, ++c) {
            retval(r, c) = it->begin() + it->distance() * retval(r, c);
        }
    }

    return retval;
}
