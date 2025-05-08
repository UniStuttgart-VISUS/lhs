// <copyright file="matrix_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <CppUnitTest.h>

#include "visus/lhs/layout.h"
#include "visus/lhs/matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace visus::lhs;


namespace test {

    TEST_CLASS(matrix_test) {

        TEST_METHOD(test_dimensions) {
            {
                matrix<float, matrix_layout::row_major> m(3, 4);
                Assert::AreEqual(static_cast<std::size_t>(3), m.rows(), L"rows", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(4), m.columns(), L"columns", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(12), m.size(), L"size", LINE_INFO());
                Assert::IsFalse(m.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(m.columns(), m.stride(), L"stride", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::row_major> m(4, 3);
                Assert::AreEqual(static_cast<std::size_t>(4), m.rows(), L"rows", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(3), m.columns(), L"columns", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(12), m.size(), L"size", LINE_INFO());
                Assert::IsFalse(m.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(m.columns(), m.stride(), L"stride", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> m(3, 4);
                Assert::AreEqual(static_cast<std::size_t>(3), m.rows(), L"rows", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(4), m.columns(), L"columns", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(12), m.size(), L"size", LINE_INFO());
                Assert::IsFalse(m.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(m.rows(), m.stride(), L"stride", LINE_INFO());
            }
        }

        TEST_METHOD(test_index) {
            {
                matrix<float, matrix_layout::row_major> m(3, 3);
                Assert::AreEqual(std::size_t(0), m.index(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(1), m.index(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(2), m.index(0, 2), L"0, 1", LINE_INFO());

                Assert::AreEqual(std::size_t(3), m.index(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(4), m.index(1, 1), L"1, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(5), m.index(1, 2), L"1, 1", LINE_INFO());

                Assert::AreEqual(std::size_t(6), m.index(2, 0), L"2, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(7), m.index(2, 1), L"2, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(8), m.index(2, 2), L"2, 1", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> m(3, 3);
                Assert::AreEqual(std::size_t(0), m.index(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(1), m.index(1, 0), L"1, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(2), m.index(2, 0), L"2, 1", LINE_INFO());

                Assert::AreEqual(std::size_t(3), m.index(0, 1), L"1, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(4), m.index(1, 1), L"1, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(5), m.index(2, 1), L"2, 1", LINE_INFO());

                Assert::AreEqual(std::size_t(6), m.index(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(std::size_t(7), m.index(1, 2), L"1, 2", LINE_INFO());
                Assert::AreEqual(std::size_t(8), m.index(2, 2), L"2, 2", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::row_major> m(3, 4);
                Assert::AreEqual(std::size_t(0), m.index(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(1), m.index(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(4), m.index(1, 0), L"1, 0", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::row_major> m(4, 3);
                Assert::AreEqual(std::size_t(0), m.index(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(1), m.index(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(3), m.index(1, 0), L"1, 0", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> m(3, 4);
                Assert::AreEqual(std::size_t(0), m.index(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(3), m.index(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(1), m.index(1, 0), L"1, 0", LINE_INFO());
            }
        }

        TEST_METHOD(test_reverse_index) {
            {
                matrix<float, matrix_layout::row_major> m(3, 4);

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 0);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 1);
                    Assert::AreEqual(std::size_t(0), row, L"row 1", LINE_INFO());
                    Assert::AreEqual(std::size_t(1), col, L"column 1", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 4);
                    Assert::AreEqual(std::size_t(1), row, L"row 4", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 4", LINE_INFO());
                }
            }

            {
                matrix<float, matrix_layout::row_major> m(4, 3);

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 0);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 1);
                    Assert::AreEqual(std::size_t(0), row, L"row 1", LINE_INFO());
                    Assert::AreEqual(std::size_t(1), col, L"column 1", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 3);
                    Assert::AreEqual(std::size_t(1), row, L"row 3", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 3", LINE_INFO());
                }
            }

            {
                matrix<float, matrix_layout::column_major> m(3, 4);

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 0);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 1);
                    Assert::AreEqual(std::size_t(1), row, L"row 1", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 1", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 3);
                    Assert::AreEqual(std::size_t(0), row, L"row 3", LINE_INFO());
                    Assert::AreEqual(std::size_t(1), col, L"column 3", LINE_INFO());
                }
            }

            {
                matrix<float, matrix_layout::row_major> m(1, 3);

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 0);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 1);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(1), col, L"column 1", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 2);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(2), col, L"column 2", LINE_INFO());
                }
            }

            {
                matrix<float, matrix_layout::column_major> m(1, 3);

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 0);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 1);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(1), col, L"column 1", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 2);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(2), col, L"column 2", LINE_INFO());
                }
            }

            {
                matrix<float, matrix_layout::row_major> m(3, 1);

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 0);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 1);
                    Assert::AreEqual(std::size_t(1), row, L"row 1", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 2);
                    Assert::AreEqual(std::size_t(2), row, L"row 2", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }
            }

            {
                matrix<float, matrix_layout::column_major> m(3, 1);

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 0);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 1);
                    Assert::AreEqual(std::size_t(1), row, L"row 1", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 2);
                    Assert::AreEqual(std::size_t(2), row, L"row 2", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }
            }
        }

        TEST_METHOD(test_indexers_row_major) {
            matrix<float, matrix_layout::row_major> m(3, 4);

            m(0, 0) = 0.0f;
            m(0, 1) = 0.1f;
            m(0, 2) = 0.2f;
            m(0, 3) = 0.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            m(1, 0) = 1.0f;
            m(1, 1) = 1.1f;
            m(1, 2) = 1.2f;
            m(1, 3) = 1.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            m(2, 0) = 2.0f;
            m(2, 1) = 2.1f;
            m(2, 2) = 2.2f;
            m(2, 3) = 2.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(2.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(2.1f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(2.2f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(2.3f, m(2, 3), L"2, 3", LINE_INFO());

            Assert::AreEqual(int(matrix_layout::row_major), int(m.layout()), L"Matrix layout", LINE_INFO());

            Assert::AreEqual(0.0f, m[0], L"0", LINE_INFO());
            Assert::AreEqual(0.1f, m[1], L"1", LINE_INFO());
            Assert::AreEqual(0.2f, m[2], L"2", LINE_INFO());
            Assert::AreEqual(0.3f, m[3], L"3", LINE_INFO());

            Assert::AreEqual(1.0f, m[4], L"4", LINE_INFO());
            Assert::AreEqual(1.1f, m[5], L"5", LINE_INFO());
            Assert::AreEqual(1.2f, m[6], L"6", LINE_INFO());
            Assert::AreEqual(1.3f, m[7], L"7", LINE_INFO());

            Assert::AreEqual(2.0f, m[8], L"8", LINE_INFO());
            Assert::AreEqual(2.1f, m[9], L"9", LINE_INFO());
            Assert::AreEqual(2.2f, m[10], L"10", LINE_INFO());
            Assert::AreEqual(2.3f, m[11], L"11", LINE_INFO());
        }

        TEST_METHOD(test_indexers_colum_major) {
            matrix<float, matrix_layout::column_major> m(3, 4);

            m(0, 0) = 0.0f;
            m(0, 1) = 0.1f;
            m(0, 2) = 0.2f;
            m(0, 3) = 0.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            m(1, 0) = 1.0f;
            m(1, 1) = 1.1f;
            m(1, 2) = 1.2f;
            m(1, 3) = 1.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            m(2, 0) = 2.0f;
            m(2, 1) = 2.1f;
            m(2, 2) = 2.2f;
            m(2, 3) = 2.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(2.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(2.1f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(2.2f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(2.3f, m(2, 3), L"2, 3", LINE_INFO());

            Assert::AreEqual(int(matrix_layout::column_major), int(m.layout()), L"Matrix layout", LINE_INFO());

            Assert::AreEqual(0.0f, m[0], L"0", LINE_INFO());
            Assert::AreEqual(1.0f, m[1], L"1", LINE_INFO());
            Assert::AreEqual(2.0f, m[2], L"2", LINE_INFO());

            Assert::AreEqual(0.1f, m[3], L"3", LINE_INFO());
            Assert::AreEqual(1.1f, m[4], L"4", LINE_INFO());
            Assert::AreEqual(2.1f, m[5], L"5", LINE_INFO());

            Assert::AreEqual(0.2f, m[6], L"6", LINE_INFO());
            Assert::AreEqual(1.2f, m[7], L"7", LINE_INFO());
            Assert::AreEqual(2.2f, m[8], L"8", LINE_INFO());

            Assert::AreEqual(0.3f, m[9], L"9", LINE_INFO());
            Assert::AreEqual(1.3f, m[10], L"10", LINE_INFO());
            Assert::AreEqual(2.3f, m[11], L"11", LINE_INFO());
        }

        TEST_METHOD(test_fill) {
            matrix<float> m(3, 4);
            m.fill(42.0f);

            Assert::AreEqual(42.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(42.0f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(42.0f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(42.0f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(42.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(42.0f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(42.0f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(42.0f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(42.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(42.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(42.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(42.0f, m(2, 3), L"2, 3", LINE_INFO());

            m.fill([&m](const std::size_t r, const std::size_t c) {
                return static_cast<float>(m.index(r, c));
            });

            Assert::AreEqual(0.0f, m[0], L"0", LINE_INFO());
            Assert::AreEqual(1.0f, m[1], L"1", LINE_INFO());
            Assert::AreEqual(2.0f, m[2], L"2", LINE_INFO());
            Assert::AreEqual(3.0f, m[3], L"3", LINE_INFO());

            Assert::AreEqual(4.0f, m[4], L"4", LINE_INFO());
            Assert::AreEqual(5.0f, m[5], L"5", LINE_INFO());
            Assert::AreEqual(6.0f, m[6], L"6", LINE_INFO());
            Assert::AreEqual(7.0f, m[7], L"7", LINE_INFO());

            Assert::AreEqual(8.0f, m[8], L"8", LINE_INFO());
            Assert::AreEqual(9.0f, m[9], L"9", LINE_INFO());
            Assert::AreEqual(10.0f, m[10], L"10", LINE_INFO());
            Assert::AreEqual(11.0f, m[11], L"11", LINE_INFO());
        }

        TEST_METHOD(test_equality) {
            matrix<float> m1(3, 4);
            m1.fill(42.0f);

            matrix<float> m2(3, 4);
            Assert::IsFalse(m1 == m2, L"m1 == m2", LINE_INFO());

            m2 = m1;
            Assert::IsTrue(m1 == m2, L"m1 == m2", LINE_INFO());

            matrix<float> m3(4, 3);
            m3.fill(42.0f);
            Assert::IsFalse(m1 == m3, L"m1 == m3", LINE_INFO());
        }

        TEST_METHOD(test_row) {
            matrix<float> m(3, 4);

            m(0, 0) = 0.0f;
            m(0, 1) = 0.1f;
            m(0, 2) = 0.2f;
            m(0, 3) = 0.3f;

            m(1, 0) = 1.0f;
            m(1, 1) = 1.1f;
            m(1, 2) = 1.2f;
            m(1, 3) = 1.3f;

            m(2, 0) = 2.0f;
            m(2, 1) = 2.1f;
            m(2, 2) = 2.2f;
            m(2, 3) = 2.3f;

            {
                matrix<float> r(1, 4);
                m.row(r, 0);
                Assert::AreEqual(0.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(0.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(0.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(0.3f, r(0, 3), L"0, 3", LINE_INFO());
            }

            {
                matrix<float> r(1, 4);
                m.row(r, 1);
                Assert::AreEqual(1.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(1.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(1.3f, r(0, 3), L"0, 3", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> r(1, 4);
                m.row(r, 0);
                Assert::AreEqual(0.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(0.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(0.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(0.3f, r(0, 3), L"0, 3", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> r(1, 4);
                m.row(r, 1);
                Assert::AreEqual(1.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(1.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(1.3f, r(0, 3), L"0, 3", LINE_INFO());
            }

            {
                auto r = m.row(0);
                Assert::AreEqual(0.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(0.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(0.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(0.3f, r(0, 3), L"0, 3", LINE_INFO());
            }

            {
                auto r = m.row(1);
                Assert::AreEqual(1.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(1.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(1.3f, r(0, 3), L"0, 3", LINE_INFO());
            }
        }

        TEST_METHOD(test_column) {
            matrix<float> m(3, 4);

            m(0, 0) = 0.0f;
            m(0, 1) = 0.1f;
            m(0, 2) = 0.2f;
            m(0, 3) = 0.3f;

            m(1, 0) = 1.0f;
            m(1, 1) = 1.1f;
            m(1, 2) = 1.2f;
            m(1, 3) = 1.3f;

            m(2, 0) = 2.0f;
            m(2, 1) = 2.1f;
            m(2, 2) = 2.2f;
            m(2, 3) = 2.3f;

            {
                matrix<float> c(3, 1);
                m.column(c, 0);
                Assert::AreEqual(0.0f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.0f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.0f, c(2, 0), L"2, 2", LINE_INFO());
            }

            {
                matrix<float> c(3, 1);
                m.column(c, 1);
                Assert::AreEqual(0.1f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.1f, c(2, 0), L"2, 2", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> c(3, 1);
                m.column(c, 0);
                Assert::AreEqual(0.0f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.0f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.0f, c(2, 0), L"2, 2", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> c(3, 1);
                m.column(c, 1);
                Assert::AreEqual(0.1f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.1f, c(2, 0), L"2, 2", LINE_INFO());
            }

            {
                auto c = m.column(0);
                Assert::AreEqual(0.0f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.0f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.0f, c(2, 0), L"2, 2", LINE_INFO());
            }

            {
                auto c = m.column(1);
                Assert::AreEqual(0.1f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.1f, c(2, 0), L"2, 2", LINE_INFO());
            }
        }

        TEST_METHOD(test_diagonal) {
            auto m = matrix<float>::diagonal(4, 42.0f);
            Assert::AreEqual(42.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(42.0f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(42.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(3, 0), L"3, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(3, 1), L"3, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(3, 2), L"3, 2", LINE_INFO());
            Assert::AreEqual(42.0f, m(3, 3), L"3, 3", LINE_INFO());
        }

        TEST_METHOD(test_identity) {
            auto m = matrix<float>::identity(4);
            Assert::AreEqual(1.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1.0f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(1.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(3, 0), L"3, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(3, 1), L"3, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(3, 2), L"3, 2", LINE_INFO());
            Assert::AreEqual(1.0f, m(3, 3), L"3, 3", LINE_INFO());
        }

        TEST_METHOD(test_layout) {
            {
                typedef matrix<float, matrix_layout::row_major> type;
                type m;
                Assert::AreEqual(int(matrix_layout::row_major), int(m.layout()), L"get", LINE_INFO());
                Assert::AreEqual(int(matrix_layout::row_major), int(detail::layout_v<type>), L"traits", LINE_INFO());
            }

            {
                typedef matrix<float, matrix_layout::column_major> type;
                type m;
                Assert::AreEqual(int(matrix_layout::column_major), int(m.layout()), L"get", LINE_INFO());
                Assert::AreEqual(int(matrix_layout::column_major), int(detail::layout_v<type>), L"traits", LINE_INFO());
            }
        }

        TEST_METHOD(test_cm_col_iterator) {
            matrix<float, matrix_layout::column_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_columns();

            Assert::AreEqual(0.0f, *it++, L"0, 0", LINE_INFO());
            Assert::AreEqual(1.0f, *it++, L"1, 0", LINE_INFO());
            Assert::AreEqual(2.0f, *it++, L"2, 0", LINE_INFO());

            Assert::AreEqual(0.1f, *it++, L"0, 1", LINE_INFO());
            Assert::AreEqual(1.1f, *it++, L"1, 1", LINE_INFO());
            Assert::AreEqual(2.1f, *it++, L"2, 1", LINE_INFO());

            Assert::AreEqual(0.2f, *it++, L"0, 2", LINE_INFO());
            Assert::AreEqual(1.2f, *it++, L"1, 2", LINE_INFO());
            Assert::AreEqual(2.2f, *it++, L"2, 2", LINE_INFO());

            Assert::AreEqual(0.3f, *it++, L"0, 3", LINE_INFO());
            Assert::AreEqual(1.3f, *it++, L"1, 3", LINE_INFO());
            Assert::AreEqual(2.3f, *it++, L"2, 3", LINE_INFO());

            Assert::IsTrue(it == m.end_columns(), L"end reached", LINE_INFO());
        }

        TEST_METHOD(test_cm_const_col_iterator) {
            const matrix<float, matrix_layout::column_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_columns();

            Assert::AreEqual(0.0f, *it++, L"0, 0", LINE_INFO());
            Assert::AreEqual(1.0f, *it++, L"1, 0", LINE_INFO());
            Assert::AreEqual(2.0f, *it++, L"2, 0", LINE_INFO());

            Assert::AreEqual(0.1f, *it++, L"0, 1", LINE_INFO());
            Assert::AreEqual(1.1f, *it++, L"1, 1", LINE_INFO());
            Assert::AreEqual(2.1f, *it++, L"2, 1", LINE_INFO());

            Assert::AreEqual(0.2f, *it++, L"0, 2", LINE_INFO());
            Assert::AreEqual(1.2f, *it++, L"1, 2", LINE_INFO());
            Assert::AreEqual(2.2f, *it++, L"2, 2", LINE_INFO());

            Assert::AreEqual(0.3f, *it++, L"0, 3", LINE_INFO());
            Assert::AreEqual(1.3f, *it++, L"1, 3", LINE_INFO());
            Assert::AreEqual(2.3f, *it++, L"2, 3", LINE_INFO());

            Assert::IsTrue(it == m.end_columns(), L"end reached", LINE_INFO());
        }

        TEST_METHOD(test_rm_col_iterator) {
            matrix<float, matrix_layout::row_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_columns();

            Assert::AreEqual(0.0f, *it++, L"0, 0", LINE_INFO());
            Assert::AreEqual(1.0f, *it++, L"1, 0", LINE_INFO());
            Assert::AreEqual(2.0f, *it++, L"2, 0", LINE_INFO());

            Assert::AreEqual(0.1f, *it++, L"0, 1", LINE_INFO());
            Assert::AreEqual(1.1f, *it++, L"1, 1", LINE_INFO());
            Assert::AreEqual(2.1f, *it++, L"2, 1", LINE_INFO());

            Assert::AreEqual(0.2f, *it++, L"0, 2", LINE_INFO());
            Assert::AreEqual(1.2f, *it++, L"1, 2", LINE_INFO());
            Assert::AreEqual(2.2f, *it++, L"2, 2", LINE_INFO());

            Assert::AreEqual(0.3f, *it++, L"0, 3", LINE_INFO());
            Assert::AreEqual(1.3f, *it++, L"1, 3", LINE_INFO());
            Assert::AreEqual(2.3f, *it++, L"2, 3", LINE_INFO());

            Assert::IsTrue(it == m.end_columns(), L"end reached", LINE_INFO());
        }

        TEST_METHOD(test_rm_const_col_iterator) {
            const matrix<float, matrix_layout::row_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_columns();

            Assert::AreEqual(0.0f, *it++, L"0, 0", LINE_INFO());
            Assert::AreEqual(1.0f, *it++, L"1, 0", LINE_INFO());
            Assert::AreEqual(2.0f, *it++, L"2, 0", LINE_INFO());

            Assert::AreEqual(0.1f, *it++, L"0, 1", LINE_INFO());
            Assert::AreEqual(1.1f, *it++, L"1, 1", LINE_INFO());
            Assert::AreEqual(2.1f, *it++, L"2, 1", LINE_INFO());

            Assert::AreEqual(0.2f, *it++, L"0, 2", LINE_INFO());
            Assert::AreEqual(1.2f, *it++, L"1, 2", LINE_INFO());
            Assert::AreEqual(2.2f, *it++, L"2, 2", LINE_INFO());

            Assert::AreEqual(0.3f, *it++, L"0, 3", LINE_INFO());
            Assert::AreEqual(1.3f, *it++, L"1, 3", LINE_INFO());
            Assert::AreEqual(2.3f, *it++, L"2, 3", LINE_INFO());

            Assert::IsTrue(it == m.end_columns(), L"end reached", LINE_INFO());
        }

        TEST_METHOD(test_cm_row_iterator) {
            matrix<float, matrix_layout::column_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_rows();

            Assert::AreEqual(0.0f, *it++, L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, *it++, L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, *it++, L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, *it++, L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, *it++, L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, *it++, L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, *it++, L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, *it++, L"1, 3", LINE_INFO());

            Assert::AreEqual(2.0f, *it++, L"2, 0", LINE_INFO());
            Assert::AreEqual(2.1f, *it++, L"2, 1", LINE_INFO());
            Assert::AreEqual(2.2f, *it++, L"2, 2", LINE_INFO());
            Assert::AreEqual(2.3f, *it++, L"2, 3", LINE_INFO());

            Assert::IsTrue(it == m.end_rows(), L"end reached", LINE_INFO());
        }

        TEST_METHOD(test_cm_const_row_iterator) {
            const matrix<float, matrix_layout::column_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_rows();

            Assert::AreEqual(0.0f, *it++, L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, *it++, L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, *it++, L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, *it++, L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, *it++, L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, *it++, L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, *it++, L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, *it++, L"1, 3", LINE_INFO());

            Assert::AreEqual(2.0f, *it++, L"2, 0", LINE_INFO());
            Assert::AreEqual(2.1f, *it++, L"2, 1", LINE_INFO());
            Assert::AreEqual(2.2f, *it++, L"2, 2", LINE_INFO());
            Assert::AreEqual(2.3f, *it++, L"2, 3", LINE_INFO());

            Assert::IsTrue(it == m.end_rows(), L"end reached", LINE_INFO());
        }

        TEST_METHOD(test_rm_row_iterator) {
            matrix<float, matrix_layout::row_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_rows();

            Assert::AreEqual(0.0f, *it++, L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, *it++, L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, *it++, L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, *it++, L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, *it++, L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, *it++, L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, *it++, L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, *it++, L"1, 3", LINE_INFO());

            Assert::AreEqual(2.0f, *it++, L"2, 0", LINE_INFO());
            Assert::AreEqual(2.1f, *it++, L"2, 1", LINE_INFO());
            Assert::AreEqual(2.2f, *it++, L"2, 2", LINE_INFO());
            Assert::AreEqual(2.3f, *it++, L"2, 3", LINE_INFO());

            Assert::IsTrue(it == m.end_rows(), L"end reached", LINE_INFO());
        }

        TEST_METHOD(test_rm_const_row_iterator) {
            const matrix<float, matrix_layout::row_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_rows();

            Assert::AreEqual(0.0f, *it++, L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, *it++, L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, *it++, L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, *it++, L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, *it++, L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, *it++, L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, *it++, L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, *it++, L"1, 3", LINE_INFO());

            Assert::AreEqual(2.0f, *it++, L"2, 0", LINE_INFO());
            Assert::AreEqual(2.1f, *it++, L"2, 1", LINE_INFO());
            Assert::AreEqual(2.2f, *it++, L"2, 2", LINE_INFO());
            Assert::AreEqual(2.3f, *it++, L"2, 3", LINE_INFO());

            Assert::IsTrue(it == m.end_rows(), L"end reached", LINE_INFO());
        }

        TEST_METHOD(test_cm_single_col_iterator) {
            matrix<float, matrix_layout::column_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_column(1);

            Assert::AreEqual(0.1f, *it++, L"0, 1", LINE_INFO());
            Assert::AreEqual(1.1f, *it++, L"1, 1", LINE_INFO());
            Assert::AreEqual(2.1f, *it++, L"2, 1", LINE_INFO());

            Assert::IsTrue(it == m.end_column(1), L"end reached", LINE_INFO());
        }

        TEST_METHOD(test_cm_single_const_col_iterator) {
            const matrix<float, matrix_layout::column_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_column(1);

            Assert::AreEqual(0.1f, *it++, L"0, 1", LINE_INFO());
            Assert::AreEqual(1.1f, *it++, L"1, 1", LINE_INFO());
            Assert::AreEqual(2.1f, *it++, L"2, 1", LINE_INFO());

            Assert::IsTrue(it == m.end_column(1), L"end reached", LINE_INFO());
        }

        TEST_METHOD(test_rm_single_col_iterator) {
            matrix<float, matrix_layout::row_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_column(1);

            Assert::AreEqual(0.1f, *it++, L"0, 1", LINE_INFO());
            Assert::AreEqual(1.1f, *it++, L"1, 1", LINE_INFO());
            Assert::AreEqual(2.1f, *it++, L"2, 1", LINE_INFO());

            Assert::IsTrue(it == m.end_column(1), L"end reached", LINE_INFO());
        }

        TEST_METHOD(test_rm_single_const_col_iterator) {
            matrix<float, matrix_layout::row_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_column(2);

            Assert::AreEqual(0.2f, *it++, L"0, 2", LINE_INFO());
            Assert::AreEqual(1.2f, *it++, L"1, 2", LINE_INFO());
            Assert::AreEqual(2.2f, *it++, L"2, 2", LINE_INFO());

            Assert::IsTrue(it == m.end_column(2), L"end reached", LINE_INFO());
        }

        TEST_METHOD(test_cm_single_row_iterator) {
            matrix<float, matrix_layout::column_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_row(2);

            Assert::AreEqual(2.0f, *it++, L"2, 0", LINE_INFO());
            Assert::AreEqual(2.1f, *it++, L"2, 1", LINE_INFO());
            Assert::AreEqual(2.2f, *it++, L"2, 2", LINE_INFO());
            Assert::AreEqual(2.3f, *it++, L"2, 3", LINE_INFO());

            Assert::IsTrue(it == m.end_row(2), L"end reached", LINE_INFO());
        }

        TEST_METHOD(test_cm_single_const_row_iterator) {
            const matrix<float, matrix_layout::column_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_row(0);

            Assert::AreEqual(0.0f, *it++, L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, *it++, L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, *it++, L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, *it++, L"0, 3", LINE_INFO());

            Assert::IsTrue(it == m.end_row(0), L"end reached", LINE_INFO());
        }

        TEST_METHOD(test_single_rm_row_iterator) {
            matrix<float, matrix_layout::row_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_row(1);

            Assert::AreEqual(1.0f, *it++, L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, *it++, L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, *it++, L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, *it++, L"1, 3", LINE_INFO());

            Assert::IsTrue(it == m.end_row(1), L"end reached", LINE_INFO());
        }

        TEST_METHOD(test_rm_single_const_row_iterator) {
            const matrix<float, matrix_layout::row_major> m(3, 4, [](std::size_t r, std::size_t c) { return float(r) + 0.1f * c; });

            auto it = m.begin_row(1);

            Assert::AreEqual(1.0f, *it++, L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, *it++, L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, *it++, L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, *it++, L"1, 3", LINE_INFO());

            Assert::IsTrue(it == m.end_row(1), L"end reached", LINE_INFO());
        }

    };

}
