// <copyright file="sample.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * LHS_NAMESPACE::sample
 */
template<class TLhsGenerator, class... TParameters>
std::vector<LHS_DETAIL_NAMESPACE::sample_type_t<TParameters...>>
LHS_NAMESPACE::sample(_In_ TLhsGenerator lhs_generator,
        _In_ const TParameters&... parameters) {
    auto lhs = lhs_generator(sizeof...(parameters));
    ASSERT_VALID_LHS(lhs);

    if (lhs.columns() != sizeof...(parameters)) {
        throw std::invalid_argument("The number of columns in the Latin "
            "hypercube sample produced by the generator callback does not "
            "match the number of parameters.");
    }

    std::vector<detail::sample_type_t<TParameters...>> retval;
    retval.reserve(lhs.rows());

    for (std::size_t i = 0; i < lhs.rows(); ++i) {
        auto b = lhs.begin_row(i);
        auto e = lhs.end_row(i);
        retval.push_back(detail::realise_parameters(b, e, parameters...));
    }

    return retval;
}
