// <copyright file="submatrix.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * LHS_NAMESPACE::submatrix<TMatrix>::submatrix
 */
template<class TMatrix>
LHS_NAMESPACE::submatrix<TMatrix>::submatrix(
        _In_ TMatrix& matrix,
        _In_ const std::size_t row,
        _In_ const std::size_t column,
        _In_ const std::size_t rows,
        _In_ const std::size_t columns)
    : _column(column),
        _columns(columns),
        _matrix(matrix),
        _row(row),
        _rows(rows) {
    if (this->_row + this->_rows >= this->_matrix.rows()) {
        std::range_error("The row range exceeds the number of rows of the "
            "underlying matrix.");
    }
    if (this->_column + this->_columns >= this->_matrix.columns()) {
        std::range_error("The column range exceeds the number of columns of "
            "the underlying matrix.");
    }
}


/*
 * LHS_NAMESPACE::submatrix<TMatrix>::operator ==
 */
template<class TMatrix>
bool LHS_NAMESPACE::submatrix<TMatrix>::operator ==(
        _In_ const submatrix& rhs) const noexcept {
    return (this->_column == rhs._column)
        && (this->_columns == rhs._columns)
        && (this->_row == rhs._row)
        && (this->_rows == rhs._rows)
        && (std::addressof(this->_matrix) == std::addressof(rhs._matrix));
}


/*
 * LHS_NAMESPACE::submatrix<TMatrix>::location
 */
template<class TMatrix>
void LHS_NAMESPACE::submatrix<TMatrix>::location(
        _Out_ std::size_t& row,
        _Out_ std::size_t& column,
        _In_ const std::size_t index) const noexcept {
    if (detail::layout_v<TMatrix> == matrix_layout::row_major) {
        row = index / this->_columns;
        column = index % this->_columns;
    } else {
        column = index / this->_rows;
        row = index % this->_rows;
    }
}
