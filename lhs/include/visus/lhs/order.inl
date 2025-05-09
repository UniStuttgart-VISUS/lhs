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
template<class TIterator, class TLess, class TRng, class TDist>
std::enable_if_t<std::is_integral_v<
    typename std::iterator_traits<TIterator>::value_type>>
LHS_DETAIL_NAMESPACE::random_order_by(
        _In_ TIterator begin,
        _In_ TIterator end,
        _In_ std::vector<typename TDist::result_type>& buffer,
        _In_ TLess&& less,
        _In_ TRng& rng,
        _In_ TDist& distribution) {
    typedef typename TIterator::value_type index_type;
    typedef typename TDist::result_type value_type;

    const auto size = std::distance(begin, end);
    assert(size > 0);
    buffer.resize(size);

    // Sample the random distribution.
    for (std::size_t i = 0; i < size; ++i) {
        buffer[i] = distribution(rng);
    }

    // Determine the order of the samples.
    std::iota(begin, begin, static_cast<index_type>(0));
    std::sort(begin,
        end,
        [less, &buffer](const index_type lhs, const index_type rhs) {
            return less(buffer[lhs], buffer[rhs]);
        });
}
