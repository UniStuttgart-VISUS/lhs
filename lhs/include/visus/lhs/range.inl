// <copyright file="range.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * LHS_NAMESPACE::range<TValue>::range
 */
template<class TValue>
LHS_NAMESPACE::range<TValue>::range(
        _In_ const std::initializer_list<value_type>& initialiser) {
    if (initialiser.size() < 2) {
        throw std::invalid_argument("The initialiser list must contain at "
            "least two elements.");
    }

    auto b = *initialiser.begin();
    auto e = *(initialiser.begin() + 1);

    this->_begin = (std::min)(b, e);
    this->_end = (std::max)(b, e);
}
