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
        _In_ const TLess& less,
        _In_ const std::size_t offset) {
    indices.resize(std::distance(begin, end));
    std::iota(indices.begin(), indices.end(), offset);

    std::sort(indices.begin(),
        indices.end(),
        [&less, &begin](const std::size_t lhs, const std::size_t rhs) {
            return less(*(begin + lhs), *(begin + rhs));
        });
}
