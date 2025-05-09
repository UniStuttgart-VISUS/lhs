// <copyright file="maximin.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * LHS_NAMESPACE::maximin
 */
template<class TValue, LHS_NAMESPACE::matrix_layout Layout>
std::enable_if_t<std::is_arithmetic_v<TValue>,
    LHS_NAMESPACE::matrix<TValue, Layout>&>
LHS_NAMESPACE::maximin(_Inout_ matrix<TValue, Layout>& lhs,
        _In_ const TValue epsilon,
        _In_ const std::size_t iterations) {
    // Based on https://github.com/bertcarnell/lhs/blob/4be72495c0eba3ce0b1ae602122871ec83421db6/R/maximinLHS.R#L109-L176
    static constexpr auto one = static_cast<TValue>(1);
    const auto n = lhs.rows();
    const auto k = lhs.columns();
    std::vector<TValue> distances;

    // Find the reference minimum distance between two samples in the current
    // 'lhs', which we want to maximise in the subsequent iterations.
    detail::square_row_distances(distances, lhs);
    auto reference = *std::min_element(distances.begin(), distances.end());

    for (std::size_t i = 0; i < iterations; ++i) {
        auto minimum = reference;
        std::array<std::size_t, 3> swap;

        for (std::size_t c = 0; c < k; ++c) {
            // Try all pairwise row swaps in the current column whether they
            // result in an improved distance.
            for (std::size_t r = 0; r + 1 < n; ++r) {
                for (std::size_t s = r + 1; s < n; ++s) {
                    std::swap(lhs(r, c), lhs(s, c));

                    detail::square_row_distances(distances, lhs);
                    auto m = *std::min_element(
                        distances.begin(),
                        distances.end());

                    if (m > minimum) {
                        // The new minimum is larger than the previous one, so
                        // we remember this as our best swap in the iteration.
                        minimum = m;
                        swap[0] = r;
                        swap[1] = s;
                        swap[2] = c;
                    }

                    std::swap(lhs(r, c), lhs(s, c));
                } /* for (std::size_t s = r + 1; s < n; ++s) */
            } /* for (std::size_t r = 0; r + 1 < n; ++r) */
        } /* for (std::size_t c = 0; c < k; ++c) */

        if (minimum > reference) {
            // We found a better minimum distance, so we apply swap.
            std::swap(lhs(swap[0], swap[2]), lhs(swap[1], swap[2]));
            reference = minimum;

            if (minimum < (one + epsilon) * reference) {
                // The improvement is not significant enough, so we stop.
                break;
            }

        } else {
            // We found no possible improvement in this iteration, so we stop.
            break;
        }
    }

    return lhs;
}


/*
 * LHS_NAMESPACE::maximin
 */
template<LHS_NAMESPACE::matrix_layout Layout, class TRng, class TDist>
LHS_NAMESPACE::matrix<std::size_t, Layout> LHS_NAMESPACE::maximin(
        _Inout_ matrix<std::size_t, Layout>& result,
        _In_ const std::size_t duplication,
        _In_ TRng& rng,
        _In_ TDist& distribution) {
    // Derived from https://github.com/bertcarnell/lhs/blob/4be72495c0eba3ce0b1ae602122871ec83421db6/src/maximinLHS.cpp#L40-L198
    typedef typename TDist::result_type float_type;
    static constexpr auto one = static_cast<std::size_t>(1);
    static constexpr auto zero = static_cast<std::size_t>(0);

    // Create a random index in [0, n] from 'rng' and 'distribution'.
    const auto random_index = [&rng, &distribution](const std::size_t n) {
        assert(n > 0);
        auto v = distribution(rng) * static_cast<float_type>(n);
        return static_cast<std::size_t>(std::floor(v));
    };

    // Cache the number of samples 'n' and parameters 'k'.
    const auto n = result.rows();
    const auto k = result.columns();

    // Length of candidate points.
    assert(n > 0);
    const auto len = duplication * ((std::max)(n, one) - one);

    matrix<std::size_t, Layout> avail(n, k);
    matrix<std::size_t, Layout> point1(len, k);
    std::vector<std::size_t> list1(len);

    // Initialise the availability matrix.
    detail::initialise_availability(avail);

    for (std::size_t c = 0; c < k; ++c) {
        // Come up with a random sample in the last row of the 'result'.
        const auto r = random_index(n);
        result(n - 1, c) = r;

        // Use the random order we just created to place an the index of the
        // last sample value randomly through the 'avail' matrix.
        avail(r, c) = n - 1;
    }

    // Move backwards through the samples in 'result' and fill them.
    for (std::size_t s = n - 1; s > 0; --s) {
        for (std::size_t c = 0; c < k; ++c) {
            for (std::size_t r = 0; r < duplication; ++r) {
                for (std::size_t i = 0; i < s; ++i) {
                    list1[i + r * s] = avail(i, c);
                }
            }

            for (std::size_t r = s * duplication; r > 0; --r) {
                auto v = random_index(r);
                point1(r - 1, c) = list1[v];
                list1[v] = list1[r - 1];
            }
        }

        auto min_idx = zero;
        auto min_val = zero;

        for (std::size_t r = 0; r + 1 < duplication * s; ++r) {
            // Search the candidate point with the minimum distance.
            auto dist = (std::numeric_limits<std::size_t>::max)();

            // Compute the squared distance between the candidate points and the
            // points already in the sample and remember the smallest one.
            for (std::size_t i = s; i < n; ++i) {
                auto d = zero;

                for (std::size_t j = 0; j < k; ++j) {
                    d += square(point1(r, j) - result(i, j));
                }

                if (d < dist) {
                    dist = d;
                }
            }

            // Remember the point if the minimum distance is the largest so far.
            if (dist > min_val) {
                min_val = dist;
                min_idx = r;
            }
        }

        // Commit the best candidate to the sample.
        for (std::size_t c = 0; c < k; ++c) {
            result(s - 1, c) = point1(min_idx, c);
        }

        // Update the availability of the remaining points.
        for (std::size_t c = 0; c < k; ++c) {
            for (std::size_t r = 0; r < n; ++r) {
                if (avail(r, c) == result(s - 1, c)) {
                    avail(r, c) = avail(s - 1, c);
                }
            }
        }
    }

    // There is only one choice left for the last sample.
    for (std::size_t c = 0; c < k; ++c) {
        result(0, c) = avail(0, c);
    }

    ASSERT_VALID_LHS(result);
    return result;
}


/*
 * LHS_DETAIL_NAMESPACE::initialise_availability
 */
template<LHS_NAMESPACE::matrix_layout Layout>
LHS_NAMESPACE::matrix<std::size_t, Layout>&
LHS_DETAIL_NAMESPACE::initialise_availability(
        _Inout_ matrix<std::size_t, Layout>& mat) {
    static constexpr auto zero = static_cast<std::size_t>(0);

    for (std::size_t c = 0, e = mat.columns(); c < e; ++c) {
        std::iota(mat.begin_column(c), mat.end_column(c), zero);
    }

    return mat;
}
