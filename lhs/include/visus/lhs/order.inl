// <copyright file="order.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * LHS_DETAIL_NAMESPACE::order_by
 */
template<class TIterator, class TLess>
void LHS_DETAIL_NAMESPACE::order_by(
        _Inout_ std::vector<std::size_t>& indices,
        _In_ const TIterator begin,
        _In_ const TIterator end,
        _In_ const TLess& less) {
    indices.resize(std::distance(begin, end));
    std::iota(indices.begin(), indices.end(), static_cast<std::size_t>(0));

    std::sort(indices.begin(),
        indices.end(),
        [less, begin](const std::size_t lhs, const std::size_t rhs) {
            return less(*(begin + lhs), *(begin + rhs));
        });
}


/*
 * LHS_DETAIL_NAMESPACE::random_order_by
 */
template<class TLess, class TRng, class TDist>
std::vector<std::size_t>& LHS_DETAIL_NAMESPACE::random_order_by(
        _Inout_ std::vector<std::size_t>& order,
        _In_ std::vector<typename TDist::result_type>& buffer,
        _In_ TLess&& less,
        _In_ TRng& rng,
        _In_ TDist& distribution) {
    assert(!order.empty());
    buffer.resize(order.size());

    // Sample the random distribution.
    for (std::size_t i = 0; i < order.size(); ++i) {
        buffer[i] = distribution(rng);
    }

    // Determine the order of the samples.
    std::iota(order.begin(), order.end(), static_cast<std::size_t>(0));
    std::sort(order.begin(),
        order.end(),
        [less, &buffer](const std::size_t lhs, const std::size_t rhs) {
            return less(buffer[lhs], buffer[rhs]);
        });

    return order;
}
