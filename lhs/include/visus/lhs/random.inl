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
    std::vector<std::size_t> indices(result.rows());
    std::vector<typename TDist::result_type> values(indices.size());

    for (std::size_t c = 0, ce = result.columns(); c < ce; ++c) {
        for (std::size_t r = 0, re = result.rows(); r < re; ++r) {
            values[r] = distribution(rng);
        }

        detail::order(indices, values.begin(), values.end());

        for (std::size_t r = 0, re = result.rows(); r < re; ++r) {
            result(r, c) = indices[r];
        }
    }

    return result;
}
