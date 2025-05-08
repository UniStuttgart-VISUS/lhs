// <copyright file="matrix_iterator.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * LHS_DETAIL_NAMESPACE::matrix_iterator<TMatrix, Order>::operator ++
 */
template<class TMatrix, LHS_NAMESPACE::matrix_layout Order>
LHS_DETAIL_NAMESPACE::matrix_iterator<TMatrix, Order>&
LHS_DETAIL_NAMESPACE::matrix_iterator<TMatrix, Order>::operator ++(void) {
    this->_position += this->step();
    return *this;
}
