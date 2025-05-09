// <copyright file="distance.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * LHS_DETAIL_NAMESPACE::square_row_distances
 */
template<class TValue, LHS_NAMESPACE::matrix_layout Layout>
std::enable_if_t<std::is_arithmetic_v<TValue>,std::vector<TValue>&>
LHS_DETAIL_NAMESPACE::square_row_distances(
        _Out_ std::vector<TValue>& result,
        _In_ const matrix<TValue, Layout>& mat) {
    constexpr auto one = static_cast<std::size_t>(1);
    const auto rows = mat.rows();

    result.clear();
    result.reserve((rows * ((std::max)(one, rows) - one)) / 2);

    for (std::size_t i = 0; i + 1 < rows; ++i) {
        for (std::size_t j = i + 1; j < rows; ++j) {
            result.push_back(square_distance(
                mat.begin_row(i),
                mat.end_row(i),
                mat.begin_row(j)));
        }
    }

    return result;
}
